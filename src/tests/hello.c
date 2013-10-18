#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "../decs.h"
#include "../opcodes.h"
#include "../debug.h"



int main()
{	
	//allocate memory for registers and program data
	byte  reg[16];
	byte mem[4096];
	//unsigned int offset = (unsigned int)mem - 0x200;
	word I = 0x200;
	int i;
	//printf("Hello World!\n");
	//printf("Char size: %u\n",CHAR_BIT);
	//printf("Char min: %u\n",CHAR_MIN);
	//printf("Char max: %u\n",UCHAR_MAX);
	//printf("mem start: %p\n",mem);
	//printf("mem + 1: %p\n",mem+1);

	//fill registers to make the string "Hello World",
	//print it with printf, save it to memory, then
	//load it again 
	seti(reg+0x0,0x48);
	seti(reg+0x1,0x65);
	seti(reg+0x2,0x6C);
	seti(reg+0x3,0x6C);
	seti(reg+0x4,0x6F);
	seti(reg+0x5,0x20);
	seti(reg+0x6,0x57);
	seti(reg+0x7,0x6F);
	seti(reg+0x8,0x72);
	seti(reg+0x9,0x6C);
	seti(reg+0xA,0x64);
	seti(reg+0xB,0x0);
	//print string
	printf("%s\n",reg);
	printf("Register contents after setting\n");
	printregs(stdout,reg);
	printf("Memory contents before doing anythong\n");
	printmem(stdout,mem,0x200,0x20F);
	//printf("Store register contents in memory");
	stor(reg,0xB,mem,&I);
	//printmem(stdout,mem,0x200,0x20F);
	//zero all the registers
	memset(reg,0,REG_COUNT);
	printf("Memory after saving\n");
	printmem(stdout,mem,0x200,0x20F);
	printf("Read memory as a string, line below should read \"Hello World\"\n");
	printf("%s\n",mem+0x200);
	printf("Registers should all be 0\n");
	printregs(stdout,reg);
	printf("Registers should now hold just the 2nd word\n");
	I = 0x206;
	load(reg,0x5,mem,&I); //should load "World"
	printregs(stdout,reg);
	printf("%s\n",reg);
	
	//test the other opcodes
	printf("Clear registers\n");
	memset(reg,0,REG_COUNT);
	printregs(stdout,reg);
	seti(reg+0x0,0x1);
	printf("set V0 to 1\n");
	printregs(stdout,reg);
	set(reg+0x1,reg+0x0);
	printf("Set V1 to V0 (1)\n");
	printregs(stdout,reg);
	addi(reg+0x0,0x2);
	printf("Added 2 to V0,should now be 3\n");
	printregs(stdout,reg);
	add(reg+0x0,reg+0x1,reg+0xF);
	printf("Add V0 and V1, store answer in V0\n");
	printregs(stdout,reg);
	addi(reg+0x2,0xFF);
	add(reg+0x0,reg+0x2,reg+0xF);
	printf("Testing carry flag, add 255 to V2 and add V2 to V0 (sets CF)\n");
	printregs(stdout,reg);
	subyx(reg+0x0,reg+0x2,reg+0xF);
	printf("V0 - V2, V0 should be 0xFC, VF = 0\n");
	printregs(stdout,reg);
	subxy(reg+0x1,reg+0x2,reg+0xF);
	printf("V2 (0xFF) - V1 (0x1) -> V1 (0xFE),VF = 1\n");
	printregs(stdout,reg);
}
