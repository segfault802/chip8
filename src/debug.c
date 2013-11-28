//Some functions to aid in debugging of the emulator

#include <stdio.h>
#include "debug.h"

//print the contents of all registers to fp
void printregs(FILE *fp,byte* reg)
{
	int i;
	for(i=0;i<16;i++){
	    fprintf(fp,"V%X:%X ",i,reg[i]);
	}
	fprintf(fp,"\n");
}

//print contents of memory from start to end
//addresses are chip8 normalized
void printmem(FILE* fp,byte* mem,word start, word end)
{
	byte* mstart = mem + start;
	byte* mend = mem + end;
	int linecount = 0;
	byte* i = mstart;
	fprintf(fp,"%X: ",(i-mem));
	while(i<=mend){
		//fprintf(fp,"Address: %p\n",i);
		if(linecount > 16){
			fprintf(fp,"\n%X: ",(i-mem));
			linecount = 0;
		}
		else{
			linecount++;
		}
		fprintf(fp,"%.2X ",*i);
		i++;
	}
	fprintf(fp,"\n");
}
