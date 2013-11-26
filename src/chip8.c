#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "decs.h"
#include "emu.h"
#include "io.h"
#include "opcodes.h"
#include "debug.h"
#include "util.h"



int main(int argc, char* argv[])
{    
    //set the RNG
    srand(time(0));

    //initialize ncurses
    initscr();
    cbreak();//don't wait for carriage return when reading input
    noecho();//don't print chars to screen
    nodelay(stdscr,true); //don't wait for input when getch is called
    
    FILE *log = fopen("./bin/log","w");

    //set up the initial system state
    SystemState state;
    initialize(&state);
    
    //some other stuff
    word instr,longOp;
    preload(state.mem);
    byte q1, q2, q3, q4;
    byte done = 0;
    
    //load the file into memory
    if(argc > 1){
        loadFile(argv[1],&state);
    }
    else{
        printf("no input file!\n");
        return 1;
    }
   
    //main emulation loop
    //split apart each instruction and determine the opcode
    while(!done){
        fprintf(log,"BEFORE\n");
        printregs(log,state.reg);
        fprintf(log,"I: %.3X PC: %.3X\n",state.I,state.pc-state.mem);
        printmem(log,state.mem,0x2F0,0x2F3);  
        instr = (*(state.pc) << 8) + *(state.pc + 0x1);
        q1 = getQuartet(instr,1);
        q2 = getQuartet(instr,2);
        q3 = getQuartet(instr,3);
        q4 = getQuartet(instr,4);
        if(q1 == 0 && q2 == 0 && q3 == 0 && q4 == 0){
            done = 1;
        }
        else{
            clockStep(&state.dt);
            fprintf(log,"DT: %.3X\n",state.dt);
            fprintf(log,"$%X: ",instr);
            executeOp(&state,q1,q2,q3,q4);
            fprintf(log,"AFTER\n");
            printregs(log,state.reg);
            fprintf(log,"I: %.3X PC: %.3X\n",state.I,state.pc-state.mem);
            //printmem(log,mem,0x200,0x270);
            fprintf(log,"##########\n");
            //fprintf(log,"%X %X %X %X\n",q1,q2,q3,q4);
        state.pc += 0x2;
        }
    }
    getch();
    endwin();
    return 0;
}
