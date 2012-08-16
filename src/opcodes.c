//implementation of all opcodes in no particular order
#include "opcodes.h"
#include <stdio.h>
#include <stdlib.h> 

//6XNN: set-immediate
void seti(byte* reg, byte val)
{
	*reg = val;
}


//8XY0: set
void set(byte* regx, byte* regy)
{
	*regx = *regy;
}

//7XNN: add-immediate
void addi(byte* reg, byte val)
{
	*reg += val;
}

//8XY4: add, VF acts as a carry flag, 1 if carry, 0 if not
void add(byte* regx, byte* regy, byte* vf)
{
	*regx += *regy;
	if((*regx + *regy) > CARRY_HI){
		*vf = 0x01;
	}
	else{
		*vf = 0x00;
	}
}


//8XY5: subtract y from x, VF is a *NOT* carry flag
void subyx(byte* regx, byte* regy, byte* vf)
{
	*regx = *regx - *regy;
	if((*regx - *regy) > CARRY_LO){
		*vf = 0x01;
	}
	else{
		*vf = 0x00;
	}
}

//8XY7: subtract x from y
void subxy(byte* regx, byte* regy, byte* vf)
{
	*regx = *regy - *regx;
	if((*regy - *regx) > CARRY_LO){
		*vf = 0x01;
	}
	else{
		*vf = 0x00;
	}
}

//FX65: load
//loads registers V0 though VX with bytes starting at I
void load(byte* reg, byte x,byte* mem, word* I)
{	
	byte* cpystart =  *I + mem;
	byte* i = cpystart;
	byte* cpyend = cpystart + x;
	while(i<=cpyend){
		*reg = *i;
		reg++;
		i++;
	}
}

//FX55: store
//stores bytes in V0 through VX in memory at I
void stor(byte* reg, byte x, byte* mem, word* I)
{
	byte* cpystart =  *I + mem;
	byte* i = cpystart;
	byte* cpyend = cpystart + x;
	while(i<=cpyend){
		*i = *reg;
		reg++;
		i++;
	}
}

//8XY1: bitwise OR
void or(byte* regx, byte* regy)
{
	*regx = *regx | *regy;
}

//8XY2: bitwise AND
void and(byte* regx, byte* regy)
{
	*regx = *regx & *regy;
}

//8XY3: bitwise XOR
void xor(byte* regx, byte* regy)
{
	*regx = *regx ^ *regy;
}

//8XY6: shifts right by 1, VF is set to the least significant bit in VX
void shr(byte* reg, byte* vf)
{
	*vf = *reg & 0x01;
	*reg = *reg >> 1;	
}

//8XYE: //shifts left by 1, VF is set to the most significant bit in VX
void shl(byte* reg, byte* vf)
{
	*vf = (*reg & 0x80) >> 7;
	*reg = *reg << 1;
}

//ANNN: sets I to NNN
void iset(word* I, word N)
{
	*I  = N;
}

//CXNN: set VX to a random number anded with NN
void setrand(byte* reg, byte val)
{
	byte rnum = rand() % 256;
	printf("rand: %X, val: %d, result: %d\n",rnum,val,rnum & val);
	//printf("before: %d, ",*reg);
	*reg = (rnum & val);
	//printf("after: %d\n",*reg);
}

//1NNN: jump to address NNN
void jmp(word n,byte* mem,byte** pc)
{
	*pc = n+mem;
}

//3XNN: skip next instruction if VX = NN
void seq(byte* reg,byte val,byte** pc)
{
	printf("reg: %d, val: %d\n",*reg,val);
	if(*reg == val){
		*pc+=2;
	}
}

//4XNN: skip next instruction if VX != NN
void sne(byte* reg,byte val,byte** pc)
{
	if(*reg != val){
		*pc+=2;
	}
}

//5XY0: skip next instruction if VX = VY
void sey(byte* regx,byte* regy,byte** pc)
{
	if(*regx == *regy){
		*pc+=2;
	}
}

//9XY0: skip next instruction if VX != VY
void sney(byte* regx, byte* regy, byte** pc)
{	
	if(*regx != *regy){
		*pc+=2;
	}
}

//BNNN: jump to NNN + V0
void jmp0(byte* reg, word n,byte** pc)
{
	*pc = (byte*)(n + *reg);
}

//FX1E: add VX to I
void addaddr(byte* reg, word* I)
{
	*I += *reg;
}
