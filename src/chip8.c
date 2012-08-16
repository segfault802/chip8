#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "decs.h"
#include "opcodes.h"
#include "debug.h"
#include "util.h"



int main(int argc, char* argv[])
{	
	//set the RNG
	srand(time(0));

	//allocate registers and program memory
	byte  reg[16];
	clearregs(reg);
	byte* vf = &reg[15];
	byte mem[4096];
	byte* pc = mem+0x200;
	word instr,longOp;
	word I;
	byte q1, q2, q3, q4;
	byte keepAlive = 1;
	//printf("Memory start: %p\n",mem);
	byte *ptr = mem + 0x200;
	size_t size;
	FILE *fp;
	
	//load the file into memory
	if(argc > 1){
		fp = fopen(argv[1],"rb");
		printf("opening %s\n",argv[1]);
	}
	else{
		printf("no file specified!\n");
		return 1;
	}
	while(!feof(fp)){
		//printf("Pointer Address: %p\n",ptr);
		size = fread(ptr,1,2,fp);	
		printf("Read %d bytes, %.2X%.2X\n",size,*ptr,*(ptr+0x1));
		ptr += 0x02;
	}
	fclose(fp);
	printmem(mem,0x200,0x223);
	
	//main emulation loop
	
	while(keepAlive){
		instr = (*pc << 8) + *(pc + 0x1);
		q1 = getQuartet(instr,1);
		q2 = getQuartet(instr,2);
		q3 = getQuartet(instr,3);
		q4 = getQuartet(instr,4);
		if(q1 == 0 && q2 == 0 && q3 == 0 && q4 == 0){
			keepAlive = 0;
		}
		else{
			switch(q1){
				case 0x0:		
					break;
				case 0x1:
					//1NNN: jump to address NNN
					longOp = (word)((q2<<8)+(q3<<4)+q4);
					printf("jump to %.3X\n",longOp);
					jmp(longOp,mem,&pc);
					break;	
				case 0x2:
					break;
				case 0x3:
					//3XNN: skip next instruction if VX = NN
					printf("skip if V%X = %.2X\n",q2,(q3<<4)+q4);
					seq(reg+q2,(q3<<4)+q4,&pc);
					break;
				case 0x4:
					//4XNN: skip next instruction if VX != NN
					printf("skip if V%X != %.2X\n",q2,(q3<<4)+q4);
					sne(reg+q2,(q3<<4)+q4,&pc);
					break;
				case 0x5:
					//5XY0: skip next instruction if VX = VY
					printf("skip if V%X = V%X\n",q2,q3);
					sey(reg+q2,reg+q3,&pc);
					break;
				case 0x6:
					//6XNN: set-immediate
					printf("set V%X to %.2X\n",q2,(q3<<4)+q4);
					seti(reg+q2,(q3<<4)+q4);
					break;
				case 0x7:
					//7XNN: add-immediate
					printf("add %.2X to V%X\n",(q3<<4)+q4,q2);	
					addi(reg+q2,(q3<<4)+q4);
					break;
				case 0x8:
					switch(q4){
						case 0x0:
							//8XY0: set
							printf("set V%X to V%X\n",q2,q3);
							set(reg+q2,reg+q3);
							break;	
						case 0x1:
							//8XY1: bitwise OR
							printf("V%X OR V%X\n",q2,q3);
							or(reg+q2,reg+q3);
							break;
						case 0x2:
							//8XY2: bitwise AND
							printf("V%X AND V%X\n",q2,q3);
							and(reg+q2,reg+q3);
							break;
						case 0x3:
							//8XY3: bitwise XOR
							printf("V%X XOR V%X\n",q2,q3);
							xor(reg+q2,reg+q3);
							break;
						case 0x4:
							//8XY4: add, VF acts as a carry flag,
							printf("V%X + V%X\n",q2,q3);
							add(reg+q2,reg+q3,vf);
							break;
						case 0x5:
							//8XY5: subtract y from x, VF is a *NOT* carry flag
							printf("V%X - V%X\n",q2,q3);
							subyx(reg+q2,reg+q3,vf);
							break;
						case 0x6:
							//8XY6: shifts right by 1
							printf("V%X >> 1\n",q2);
							shr(reg+q2,vf);
							break;
						case 0x7:
							//8XY7: subtract x from y
							printf("V%X - V%X\n",q3,q2);
							subxy(reg+q2,reg+q3,vf);
							break;
						case 0xE:
							//8XYE: //shifts left by 1
							printf("V%X << 1\n",q2);
							shl(reg+q2,vf);
							break;
					}
					break;
				case 0x9:
					//9XY0: skip next instruction if VX != VY
					printf("skip if V%X != V%X\n",q2,q3);
					sney(reg+q2,reg+q3,&pc);
					break;
				case 0xA:
					//ANNN: sets I to NNN
					longOp = (word)((q2<<8)+(q3<<4)+q4);
					printf("set I to %.3X\n",longOp);
					iset(&I,longOp);
					break;	
				case 0xB:
					//BNNN: jump to NNN + V0
					longOp = (word)((q2<<8)+(q3<<4)+q4);
					printf("jump to %.3X + V0\n",longOp);
					jmp0(reg,longOp,&pc);
					break;
				case 0xC:
					//CXNN: set VX to a random number anded with NN
					printf("set V%X to (rand & %.2X)\n",q2,(q3<<4)+q4);
					setrand(reg+q2,(q3<<4)+q4);
					break;
				case 0xD:
					//DXYN: draw sprite at VX,VY of height N loaded from I
					printf("draw sprite of height %X at V%X,V%X*\n",q4,q2,q3);
					break;
				case 0xE:
					switch(q3){
						case 0x9:
							//EX9E: skip if key in VX is pressed
							printf("skip if key in V%X is pressed*\n",q2);
							break;
						case 0xA:
							//EXA1: skip if key in VX isn't pressed
							printf("skip if key in V%X isn't pressed*\n",q2);
							break;
					}
					break;
				case 0xF:
					switch(q3){
						case 0x0:
							switch(q4){
								case 0x7:
									//FX07: set VX to the delay timer
									printf("set V%X to the delay timer*\n",q2);
									break;
								case 0xA:
									//FX0A: store next keypress in VX
									printf("store next keypress in V%X*\n",q2);
									break;
							}
							break;
						case 0x1:
							switch(q4){
								case 0x5:
									//FX15: set delay timer to VX
									printf("set delay timer to V%X*",q2);
									break;
								case 0x8:
									//FX18: set sound timer to VX
									printf("set sound timer to V%X*",q2);
									break;
								case 0xE:
									//FX1E: add VX to I
									printf("I += V%X\n",q2);
									addaddr(reg+q2,&I);
									break;
							}
							break;
						case 0x2:
							//FX29
							break;
						case 0x3:
							//FX33: 
							break;
						case 0x5:
							//FX55: store
							printf("store V0 - V%X in memory starting at I\n",q2);
							stor(reg,q2,mem,&I);
							break;
						case 0x6:
							//FX65: load
							printf("load V0 - V%X with bytes starting at I\n",q2);
							load(reg,q2,mem,&I);
							break;
					break;
				}
			}
			prntregs(reg);
			//printf("I: %.3X PC: %.3X\n",I,pc-mem);
			//printmem(mem,0x200,0x223);
			//printf("%X %X %X %X\n",q1,q2,q3,q4);
		pc += 0x2;
		}
	}
	return 0;
}
