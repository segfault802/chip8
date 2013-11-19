#include <stdio.h>
#include <limits.h>
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
	printf("Initialize registers\n");
	seti(reg+0x0,0);
	seti(reg+0x1,2);
	seti(reg+0x2,3);
	seti(reg+0x3,255);
	printregs(stdout,reg);
	shl(reg+0x3,reg+0xF);
	printf("Shift V3 left,V3 = 254,VF = 1\n");
	printregs(stdout,reg);
	shl(reg+0x1,reg+0xF);
	printf("Shift V1 left,V1 = 4,VF = 0\n");
	printregs(stdout,reg);
	shr(reg+0x1,reg+0xF);
	printf("Shift V1 right,V1 = 2,VF = 0\n");
	printregs(stdout,reg);
	seti(reg+0x4,255);
	seti(reg+0x5,7);
	and(reg+0x4,reg+0x5);
	printf("V4 = 255,V5 = 7, V4 = V4 & V5 -> 7\n");
	printregs(stdout,reg);
	seti(reg+0x6,15);
	seti(reg+0x7,240);
	or(reg+0x6,reg+0x7);
	printf("V6 = 15, V7 = 240,V6 = V6 | V7 -> 255\n");
	printregs(stdout,reg);
	seti(reg+0x8,0xF0);
	seti(reg+0x9,0x0F);
	xor(reg+0x8,reg+0x9);
	printf("V8 = 0xF0,V9 = 0x0F, V8 = V8 ^ V9 -> FF\n");
	printregs(stdout,reg);
	return 0;
}
