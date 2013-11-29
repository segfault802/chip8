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

//Determines what opcode the given instruction represents
//Returns an integer corresponding to the opcode which can be used
//by various other functions to do things
byte lookupOp(Instruction* instr)
{   
    switch(instr->unpack.q1){
        case 0x0:
            switch(instr->unpack.q4){
                case 0x0: return 0;
                case 0xE: return 1;
                default: return 2;
            }
        case 0x1: return 3;
        case 0x2: return 4;
        case 0x3: return 5;
        case 0x4: return 6;
        case 0x5: return 7;
        case 0x6: return 8;
        case 0x7: return 9;
        case 0x8:
            switch(instr->unpack.q4){
                case 0x0: return 10;
                case 0x1: return 11;
                case 0x2: return 12;
                case 0x3: return 13;
                case 0x4: return 14;
                case 0x5: return 15;
                case 0x6: return 16;
                case 0x7: return 17;
                case 0xE: return 18;
            }
        case 0x9: return 19;
        case 0xA: return 20;
        case 0xB: return 21;
        case 0xC: return 22;
        case 0xD: return 23;
        case 0xE:
            switch(instr->unpack.q3){
                case 0x9: return 24;
                case 0xA: return 25;
            }
        case 0xF:
            switch(instr->unpack.q3){
                case 0x0:
                    switch(instr->unpack.q4){
                        case 0x7: return 26;
                        case 0xA: return 27;
                    }
                case 0x1:
                    switch(instr->unpack.q4){
                        case 0x5: return 28;
                        case 0x8: return 29;
                        case 0xE: return 30;
                    }
                case 0x2: return 31;
                case 0x3: return 32;
                case 0x5: return 33;
                case 0x6: return 34;
            }
    } 
}
