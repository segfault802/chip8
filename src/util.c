#include <stdio.h>
#include <string.h>
#include "decs.h"
#include "debug.h"


//preload all the sprites into interpreter reserved memory at 0x1B0 (432)
void preload(byte* mem)
{
    byte zero[5] = {0xf0,0x90,0x90,0x90,0xf0};
    byte one[5] = {0x20,0x60,0x20,0x20,0x70}; 
    byte two[5] = {0xf0,0x10,0xf0,0x80,0xf0}; 
    byte three[5] = {0xf0,0x10,0xf0,0x10,0xf0};
    byte four[5] = {0x90,0x90,0xf0,0x10,0x10};
    byte five[5] = {0xf0,0x80,0xf0,0x10,0xf0};
    byte six[5] = {0xf0,0x80,0xf0,0x90,0xf0};
    byte seven[5] = {0xf0,0x10,0x20,0x40,0x40};
    byte eight[5] = {0xf0,0x90,0xf0,0x90,0xf0};
    byte nine[5] = {0xf0,0x90,0xf0,0x10,0xf0};
    byte A[5] = {0xf0,0x90,0xf0,0x90,0x90};
    byte B[5] = {0xe0,0x90,0xe0,0x90,0xe0};
    byte C[5] = {0xf0,0x80,0x80,0x80,0xf0};
    byte D[5] = {0xe0,0x90,0x90,0x90,0xe0};
    byte E[5] = {0xf0,0x80,0xf0,0x80,0xf0};
    byte F[5] = {0xf0,0x80,0xf0,0x80,0x80};
    memcpy(mem,zero,5);
    memcpy(mem+5,one,5);
    memcpy(mem+10,two,5);
    memcpy(mem+15,three,5);
    memcpy(mem+20,four,5);
    memcpy(mem+25,five,5);
    memcpy(mem+30,six,5);
    memcpy(mem+35,seven,5);
    memcpy(mem+40,eight,5);
    memcpy(mem+45,nine,5);
    memcpy(mem+50,A,5);
    memcpy(mem+55,B,5);
    memcpy(mem+60,C,5);
    memcpy(mem+65,D,5);
    memcpy(mem+70,E,5);
    memcpy(mem+75,F,5);
}

//set up the initial state of the registers and memory
void initialize(SystemState* state)
{
    memset(state->reg,0,REG_COUNT);
    state->vf = &state->reg[REG_COUNT-1];
    state->pc = state->mem+PROGRAM_START;
    state->sp = state->stack;
}

//Copies the specified file into CHIP-8 memory
void loadFile(char* file, SystemState* state)
{
    size_t size;
    byte* ptr = state->mem + 0x200;
    FILE* fp = fopen(file,"rb");
    while(!feof(fp)){
        size = fread(ptr,1,2,fp);   
        ptr += 0x02;
    }
    fclose(fp);
}
