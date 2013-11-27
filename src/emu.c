#include <ncurses.h>
#include "decs.h"
#include "opcodes.h"
#include "util.h"

//Executes the opcode based on the split instruction passed in (q1-q4) 
void executeOp(SystemState* state, byte q1, byte q2, byte q3, byte q4)
{
    word longOp;
    switch(q1){
        case 0x0:
            switch(q4){
                case 0x0:
                    clearScreen();
                    break;
                case 0xE:
                    //fprintf(log,"return from sub\n");
                    ret(&state->sp,&state->pc);
                    break;
            }       
            break;
        case 0x1:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"jump to %.3X\n",longOp);
            if(state->pc == state->mem+longOp){
                //fprintf(log,"Entered an infinite loop through a recursive jump! breaking...\n");
                //done = 1;
            }
            else{
                jmp(longOp,state->mem,&state->pc);
            }
            break;  
        case 0x2:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"call sub at %.3X\n",longOp);
            call(longOp,state->mem,&state->sp,&state->pc);
            break;
        case 0x3:
            //fprintf(log,"skip if V%X = %.2X\n",q2,(q3<<4)+q4);
            seq(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 0x4:
            //fprintf(log,"skip if V%X != %.2X\n",q2,(q3<<4)+q4);
            sne(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 0x5:
            //fprintf(log,"skip if V%X = V%X\n",q2,q3);
            sey(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 0x6:
            //fprintf(log,"set V%X to %.2X\n",q2,(q3<<4)+q4);
            seti(state->reg+q2,(q3<<4)+q4);
            break;
        case 0x7:
            //fprintf(log,"add %.2X to V%X\n",(q3<<4)+q4,q2); 
            addi(state->reg+q2,(q3<<4)+q4);
            break;
        case 0x8:
            switch(q4){
                case 0x0:
                    //fprintf(log,"set V%X to V%X\n",q2,q3);
                    set(state->reg+q2,state->reg+q3);
                    break;  
                case 0x1:
                    //8XY1: bitwise OR
                    //fprintf(log,"V%X OR V%X\n",q2,q3);
                    or(state->reg+q2,state->reg+q3);
                    break;
                case 0x2:
                    //8XY2: bitwise AND
                    //fprintf(log,"V%X AND V%X\n",q2,q3);
                    and(state->reg+q2,state->reg+q3);
                    break;
                case 0x3:
                    //fprintf(log,"V%X XOR V%X\n",q2,q3);
                    xor(state->reg+q2,state->reg+q3);
                    break;
                case 0x4:
                    //fprintf(log,"V%X + V%X\n",q2,q3);
                    add(state->reg+q2,state->reg+q3,state->vf);
                    break;
                case 0x5:
                    //fprintf(log,"V%X - V%X\n",q2,q3);
                    subyx(state->reg+q2,state->reg+q3,state->vf);
                    break;
                case 0x6:
                    //fprintf(log,"V%X >> 1\n",q2);
                    shr(state->reg+q2,state->vf);
                    break;
                case 0x7:
                    //8XY7: subtract x from y
                    //fprintf(log,"V%X - V%X\n",q3,q2);
                    subxy(state->reg+q2,state->reg+q3,state->vf);
                    break;
                case 0xE:
                    //fprintf(log,"V%X << 1\n",q2);
                    shl(state->reg+q2,state->vf);
                    break;
            }
            break;
        case 0x9:
            //fprintf(log,"skip if V%X != V%X\n",q2,q3);
            sney(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 0xA:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"set I to %.3X\n",longOp);
            iset(&state->I,longOp);
            break;  
        case 0xB:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"jump to %.3X + V0\n",longOp);
            jmp0(state->reg,longOp,&state->pc);
            break;
        case 0xC:
            //fprintf(log,"set V%X to (rand & %.2X)\n",q2,(q3<<4)+q4);
            setrand(state->reg+q2,(q3<<4)+q4);
            break;
        case 0xD:
            //fprintf(log,"draw sprite at V%X,V%X,H%X\n",q2,q3,q4);
            drawSprite(*(state->reg+q2),*(state->reg+q3),q4,state->mem+state->I,state->vf);
            break;
        case 0xE:
            switch(q3){
                case 0x9:
                    //fprintf(log,"skip if key in V%X is pressed*\n",q2);
                    skip(state->reg+q2,&state->pc);
                    break;
                case 0xA:
                    //fprintf(log,"skip if key in V%X isn't pressed*\n",q2);
                    skipnp(state->reg+q2,&state->pc);
                    break;
            }
            break;
        case 0xF:
            switch(q3){
                case 0x0:
                    switch(q4){
                        case 0x7:
                            //fprintf(log,"set V%X to the delay timer\n",q2);
                            readdt(state->reg+q2,&state->dt);
                            break;
                        case 0xA:
                            //fprintf(log,"store next keypress in V%X*\n",q2);
                            getkey(state->reg+q2);
                            break;
                    }
                    break;
                case 0x1:
                    switch(q4){
                        case 0x5:
                            //fprintf(log,"set delay timer to V%X",q2);
                            setdt(state->reg+q2,&state->dt);
                            break;
                        case 0x8:
                            //FX18: set sound timer to VX
                            //fprintf(log,"set sound timer to V%X*",q2);
                            break;
                        case 0xE:
                            //FX1E: add VX to I
                            //fprintf(log,"I += V%X\n",q2);
                            addaddr(state->reg+q2,&state->I);
                            break;
                    }
                    break;
                case 0x2:
                    //FX29
                    //fprintf(log,"set I to the address of sprite in V%X\n",q2);
                    state->I = *(state->reg+q2) * 5;
                    break;
                case 0x3:
                    //FX33:
                    //fprintf(log,"set I to the BCD of V%X\n",q2);
                    bcd(state->reg+q2,state->mem,state->I); //possible bug 
                    break;
                case 0x5:
                    //FX55: store
                    //fprintf(log,"store V0 - V%X in memory starting at I\n",q2);
                    stor(state->reg,q2,state->mem,&state->I);
                    break;
                case 0x6:
                    //FX65: load
                    //fprintf(log,"load V0 - V%X with bytes starting at I\n",q2);
                    load(state->reg,q2,state->mem,&state->I);
                    break;
            break;
        }
    } 
}

//Determines what opcode the given instruction represents
//Returns an integer corresponding to the opcode which can be used
//by various other functions to do things
byte lookupOp(word instr)
{
    byte q1,q2,q3,q4;
    q1 = getQuartet(instr,1);
    q2 = getQuartet(instr,2);
    q3 = getQuartet(instr,3);
    q4 = getQuartet(instr,4); 
    switch(q1){
        case 0x0:
            switch(q4){
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
            switch(q4){
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
            switch(q3){
                case 0x9: return 24;
                case 0xA: return 25;
            }
        case 0xF:
            switch(q3){
                case 0x0:
                    switch(q4){
                        case 0x7: return 26;
                        case 0xA: return 27;
                    }
                case 0x1:
                    switch(q4){
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
