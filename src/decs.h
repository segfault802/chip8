//some declarations
#include <stdio.h>
#ifndef H_GUARD
    //some helpful constants
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
    
    //defines for each assigned opcode
    #define CLS 0
    #define RET 1
    #define SYS 2
    #define JP_A 3  
    #define CALL 4
    #define SE_B 5
    #define SNE_B 6
    #define SE_R 7
    #define LD_B 8
    #define ADD_B 9
    #define LD_R 10
    #define OR 11
    #define AND 12
    #define XOR 13
    #define ADD_R 14
    #define SUB 15
    #define SHR 16
    #define SUBN 17
    #define SHL 18
    #define SNE_R 19
    #define LD_I 20
    #define JP_R 21
    #define RND 22
    #define DRW 23
    #define SKP 24
    #define SKNP 25
    #define LD_D_R 26
    #define LD_K 27
    #define LD_R_D 28
    #define LD_A 29
    #define ADD_I 30
    #define LD_F 31
    #define LD_B 32
    #define LD_S 33
    #define LD_L 34
    
     
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
