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
	byte* cpystart = *I + mem;
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
	byte* cpystart = *I + mem;
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
	//printf("rand: %X, val: %d, result: %d\n",rnum,val,rnum & val);
	//printf("before: %d, ",*reg);
	*reg = (rnum & val);
	//printf("after: %d\n",*reg);
}

//1NNN: jump to address NNN
void jmp(word n,byte* mem,byte** pc)
{
	*pc = (n+mem)-0x2;
}

//3XNN: skip next instruction if VX = NN
void seq(byte* reg,byte val,byte** pc)
{
	//printf("reg: %d, val: %d\n",*reg,val);
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

//00EE	Returns from a subroutine.
void ret(byte*** sp, byte** pc)
{
	*pc = **sp;
	*sp--;
}

//2NNN: Call subroutine at NNN
void call(word n,byte* mem,byte*** sp,byte** pc)
{
    **sp = *pc;
	*sp++;
	*pc = (n+mem)-0x2;
}

//FX29 set I to the location of the sprite in VX (might need to hack this)
//void setSprite(byte* reg, word* I)
//{
//}

//FX33 set memory at I to the bcd of the value in reg
void bcd(byte* reg, byte* mem, word I)
{
    byte hund,tens,ones,val;
    val = *reg;
    ones = val % 10;
    val /= 10;
    tens = val % 10;
    val /= 10;
    hund = val;
    *(mem+I) = (word)hund;
    *(mem+I+1) = (word)tens;
    *(mem+I+2) = (word)ones;
}

//FX07 set VX to the delay timer
void readdt(byte* reg, byte* dt)
{
    *reg = *dt;
}


//FX15 set the delay timer
void setdt(byte* reg, byte* dt)
{
    *dt = *reg;
}

