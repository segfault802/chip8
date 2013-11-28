//some declarations
#include <stdio.h>
#ifndef H_GUARD
    #define H_GUARD
    #define REG_COUNT 16
    #define MEM_SIZE 4096
    #define STACK_SIZE 16
    #define CARRY_HI 255
    #define CARRY_LO 0
    #define PROGRAM_START 0x200
    #define MASK_1 0xF000
    #define MASK_2 0x0F00
    #define MASK_3 0x00F0
    #define MASK_4 0x000F
    #define CLOCK_TICK 16666
    #define SCREEN_H 31
    #define SCREEN_W 63

    typedef unsigned char byte;
    typedef unsigned short word;

    typedef struct  {
        byte reg[REG_COUNT];       //16 8 bit registers
        byte* vf;                  //carry flag
        byte mem[MEM_SIZE];        //4KB of main memory (first 512 bytes reserved)
        byte* pc;                  //program counter
        byte* stack[STACK_SIZE];   //call stack stores up to 16 addresses
        byte** sp;                 //stack pointer
        word I;                    //address register
        byte dt;                   //delay timer
    } SystemState;

    //A container for a single 16 bit instruction
    //the identifiers in the 'unpack' struct need to be 
    //reversed due to endianness
    typedef union {
        struct {
            byte q4:4;
            byte q3:4;
            byte q2:4;
            byte q1:4;
        } unpack;
        word pack;
    } Instruction;
        
#endif
