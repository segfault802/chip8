#include <stdio.h>
#include <limits.h>
#include "opcodes.h"




int main()
{	
	//allocate memory for registers and program memory
	byte  reg[16];
	byte mem[4096];
	int offset = mem - 0x200;
	
	
	printf("Hello World!\n");
	//printf("Char size: %u\n",CHAR_BIT);
	//printf("Char min: %u\n",CHAR_MIN);
	//printf("Char max: %u\n",UCHAR_MAX);
	printf("mem start: %p\n",mem);
	printf("mem + 1: %p\n",mem+1);
}
