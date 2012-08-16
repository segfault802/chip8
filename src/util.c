#include <stdio.h>
#include "decs.h"



byte getQuartet(word w, byte i)
{
	byte quartet;
	switch(i){
		case 1:
			quartet = w >> 12;
			break;
		case 2:
			quartet = (w & 0x0F00) >> 8;
			break;
		case 3:
			quartet = (w & 0x00F0) >> 4;
			break;
		case 4:
			quartet = w & 0x000F;
			break;
	}
	return quartet;
}
/*
int main()
{
	word instr = 0xA21E;
	printf("%X\n",instr);
	printf("The first part is %X\n",getQuartet(instr,1));	
	printf("The second part is %X\n",getQuartet(instr,2));
	printf("The third part is %X\n",getQuartet(instr,3));	
	printf("The fourth part is %X\n",getQuartet(instr,4));
	return 0;
}*/
