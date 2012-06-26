//Some functions to aid in debugging of the emulator

#include <stdio.h>
#include "debug.h"

//print the contents of all registers
void prntregs(byte* reg)
{
	int i, linecount = 0;
	for(i=0;i<16;i++){
		if(linecount > 8){
			printf("\n");
			linecount = 0;
		}
		else{
			linecount++;
		}
		printf("V%X:%X ",i,reg[i]);
	}
	printf("\n");
}
void clearregs(byte* reg)
{	
	int i;
	for(i=0;i<16;i++){
		reg[i] = 0;
	}
}

//print contents of memory from start to end
//addresses are chip8 normalized
void printmem(byte* mem,word start, word end)
{
	byte* mstart = mem + start;
	byte* mend = mem + end;
	int linecount = 0;
	byte* i = mstart;
	while(i<=mend){
		//printf("Address: %p\n",i);
		if(linecount > 8){
			printf("\n");
			linecount = 0;
		}
		else{
			linecount++;
		}
		printf("%.2X ",*i);
		i++;
	}
	printf("\n");
}
