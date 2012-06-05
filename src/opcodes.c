//implementation of all opcodes in no particular order
#include "opcodes.h"

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
	
	byte* offset = mem - 0x200;
	byte* cpystart =  *I + offset;
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
	byte* offset = mem - 0x200;
	byte* cpystart =  *I + offset;
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
