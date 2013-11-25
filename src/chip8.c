#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "decs.h"
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
    word sprites[16]; //addresses to each sprite in reserved memory
    preload(state.mem,sprites);
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
            switch(q1){
                case 0x0:
                    switch(q4){
                        case 0x0:
                            clearScreen();
                            break;
                        case 0xE:
                            fprintf(log,"return from sub\n");
                            ret(&state.sp,&state.pc);
                            break;
                    }       
                    break;
                case 0x1:
                    longOp = (word)((q2<<8)+(q3<<4)+q4);
                    fprintf(log,"jump to %.3X\n",longOp);
                    if(state.pc == state.mem+longOp){
                        fprintf(log,"Entered an infinite loop through a recursive jump! breaking...\n");
                        done = 1;
                    }
                    else{
                        jmp(longOp,state.mem,&state.pc);
                    }
                    break;  
                case 0x2:
                    longOp = (word)((q2<<8)+(q3<<4)+q4);
                    fprintf(log,"call sub at %.3X\n",longOp);
                    call(longOp,state.mem,&state.sp,&state.pc);
                    break;
                case 0x3:
                    fprintf(log,"skip if V%X = %.2X\n",q2,(q3<<4)+q4);
                    seq(state.reg+q2,(q3<<4)+q4,&state.pc);
                    break;
                case 0x4:
                    fprintf(log,"skip if V%X != %.2X\n",q2,(q3<<4)+q4);
                    sne(state.reg+q2,(q3<<4)+q4,&state.pc);
                    break;
                case 0x5:
                    fprintf(log,"skip if V%X = V%X\n",q2,q3);
                    sey(state.reg+q2,state.reg+q3,&state.pc);
                    break;
                case 0x6:
                    fprintf(log,"set V%X to %.2X\n",q2,(q3<<4)+q4);
                    seti(state.reg+q2,(q3<<4)+q4);
                    break;
                case 0x7:
                    fprintf(log,"add %.2X to V%X\n",(q3<<4)+q4,q2); 
                    addi(state.reg+q2,(q3<<4)+q4);
                    break;
                case 0x8:
                    switch(q4){
                        case 0x0:
                            fprintf(log,"set V%X to V%X\n",q2,q3);
                            set(state.reg+q2,state.reg+q3);
                            break;  
                        case 0x1:
                            //8XY1: bitwise OR
                            fprintf(log,"V%X OR V%X\n",q2,q3);
                            or(state.reg+q2,state.reg+q3);
                            break;
                        case 0x2:
                            //8XY2: bitwise AND
                            fprintf(log,"V%X AND V%X\n",q2,q3);
                            and(state.reg+q2,state.reg+q3);
                            break;
                        case 0x3:
                            fprintf(log,"V%X XOR V%X\n",q2,q3);
                            xor(state.reg+q2,state.reg+q3);
                            break;
                        case 0x4:
                            fprintf(log,"V%X + V%X\n",q2,q3);
                            add(state.reg+q2,state.reg+q3,state.vf);
                            break;
                        case 0x5:
                            fprintf(log,"V%X - V%X\n",q2,q3);
                            subyx(state.reg+q2,state.reg+q3,state.vf);
                            break;
                        case 0x6:
                            fprintf(log,"V%X >> 1\n",q2);
                            shr(state.reg+q2,state.vf);
                            break;
                        case 0x7:
                            //8XY7: subtract x from y
                            fprintf(log,"V%X - V%X\n",q3,q2);
                            subxy(state.reg+q2,state.reg+q3,state.vf);
                            break;
                        case 0xE:
                            fprintf(log,"V%X << 1\n",q2);
                            shl(state.reg+q2,state.vf);
                            break;
                    }
                    break;
                case 0x9:
                    fprintf(log,"skip if V%X != V%X\n",q2,q3);
                    sney(state.reg+q2,state.reg+q3,&state.pc);
                    break;
                case 0xA:
                    longOp = (word)((q2<<8)+(q3<<4)+q4);
                    fprintf(log,"set I to %.3X\n",longOp);
                    iset(&state.I,longOp);
                    break;  
                case 0xB:
                    longOp = (word)((q2<<8)+(q3<<4)+q4);
                    fprintf(log,"jump to %.3X + V0\n",longOp);
                    jmp0(state.reg,longOp,&state.pc);
                    break;
                case 0xC:
                    fprintf(log,"set V%X to (rand & %.2X)\n",q2,(q3<<4)+q4);
                    setrand(state.reg+q2,(q3<<4)+q4);
                    break;
                case 0xD:
                    fprintf(log,"draw sprite at V%X,V%X,H%X\n",q2,q3,q4);
                    drawSprite(*(state.reg+q2),*(state.reg+q3),q4,state.mem+state.I,state.vf);
                    break;
                case 0xE:
                    switch(q3){
                        case 0x9:
                            fprintf(log,"skip if key in V%X is pressed*\n",q2);
                            skip(state.reg+q2,&state.pc);
                            break;
                        case 0xA:
                            fprintf(log,"skip if key in V%X isn't pressed*\n",q2);
                            skipnp(state.reg+q2,&state.pc);
                            break;
                    }
                    break;
                case 0xF:
                    switch(q3){
                        case 0x0:
                            switch(q4){
                                case 0x7:
                                    fprintf(log,"set V%X to the delay timer\n",q2);
                                    readdt(state.reg+q2,&state.dt);
                                    break;
                                case 0xA:
                                    fprintf(log,"store next keypress in V%X*\n",q2);
                                    getkey(state.reg+q2);
                                    break;
                            }
                            break;
                        case 0x1:
                            switch(q4){
                                case 0x5:
                                    fprintf(log,"set delay timer to V%X",q2);
                                    setdt(state.reg+q2,&state.dt);
                                    break;
                                case 0x8:
                                    //FX18: set sound timer to VX
                                    fprintf(log,"set sound timer to V%X*",q2);
                                    break;
                                case 0xE:
                                    //FX1E: add VX to I
                                    fprintf(log,"I += V%X\n",q2);
                                    addaddr(state.reg+q2,&state.I);
                                    break;
                            }
                            break;
                        case 0x2:
                            //FX29
                            fprintf(log,"set I to the address of sprite in V%X\n",q2);
                            state.I = sprites[*(state.reg+q2)];
                            break;
                        case 0x3:
                            //FX33:
                            fprintf(log,"set I to the BCD of V%X\n",q2);
                            bcd(state.reg+q2,state.mem,state.I); //possible bug 
                            break;
                        case 0x5:
                            //FX55: store
                            fprintf(log,"store V0 - V%X in memory starting at I\n",q2);
                            stor(state.reg,q2,state.mem,&state.I);
                            break;
                        case 0x6:
                            //FX65: load
                            fprintf(log,"load V0 - V%X with bytes starting at I\n",q2);
                            load(state.reg,q2,state.mem,&state.I);
                            break;
                    break;
                }
            }
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
