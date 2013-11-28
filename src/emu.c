#include <ncurses.h>
#include "decs.h"
#include "emu.h"
#include "io.h"
#include "opcodes.h"
#include "util.h"

//Executes the opcode based on the split instruction passed in (q1-q4) 
void executeOp(SystemState* state, Instruction* instr)
{
    byte q1,q2,q3,q4;
    word longOp;
    byte opcode = lookupOp(instr);
    q1 = instr->unpack.q1;
    q2 = instr->unpack.q2;
    q3 = instr->unpack.q3;
    q4 = instr->unpack.q4;
    switch(opcode){
        case 0: 
            clearScreen();
            break;
        case 1:
            //fprintf(log,"return from sub\n");
            ret(&state->sp,&state->pc);
            break;       
        case 3:
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
        case 4:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"call sub at %.3X\n",longOp);
            call(longOp,state->mem,&state->sp,&state->pc);
            break;
        case 5:
            //fprintf(log,"skip if V%X = %.2X\n",q2,(q3<<4)+q4);
            seq(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 6:
            //fprintf(log,"skip if V%X != %.2X\n",q2,(q3<<4)+q4);
            sne(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 7:
            //fprintf(log,"skip if V%X = V%X\n",q2,q3);
            sey(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 8:
            //fprintf(log,"set V%X to %.2X\n",q2,(q3<<4)+q4);
            seti(state->reg+q2,(q3<<4)+q4);
            break;
        case 9:
            //fprintf(log,"add %.2X to V%X\n",(q3<<4)+q4,q2); 
            addi(state->reg+q2,(q3<<4)+q4);
            break;
        case 10:
            //fprintf(log,"set V%X to V%X\n",q2,q3);
            set(state->reg+q2,state->reg+q3);
            break;  
        case 11:
            //8XY1: bitwise OR
            //fprintf(log,"V%X OR V%X\n",q2,q3);
            or(state->reg+q2,state->reg+q3);
            break;
        case 12:
            //8XY2: bitwise AND
            //fprintf(log,"V%X AND V%X\n",q2,q3);
            and(state->reg+q2,state->reg+q3);
            break;
        case 13:
            //fprintf(log,"V%X XOR V%X\n",q2,q3);
            xor(state->reg+q2,state->reg+q3);
            break;
        case 14:
            //fprintf(log,"V%X + V%X\n",q2,q3);
            add(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 15:
            //fprintf(log,"V%X - V%X\n",q2,q3);
            subyx(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 16:
            //fprintf(log,"V%X >> 1\n",q2);
            shr(state->reg+q2,state->vf);
            break;
        case 17:
            //8XY7: subtract x from y
            //fprintf(log,"V%X - V%X\n",q3,q2);
            subxy(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 18:
            //fprintf(log,"V%X << 1\n",q2);
            shl(state->reg+q2,state->vf);
            break;
        case 19:
            //fprintf(log,"skip if V%X != V%X\n",q2,q3);
            sney(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 20:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"set I to %.3X\n",longOp);
            iset(&state->I,longOp);
            break;  
        case 21:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            //fprintf(log,"jump to %.3X + V0\n",longOp);
            jmp0(state->reg,longOp,&state->pc);
            break;
        case 22:
            //fprintf(log,"set V%X to (rand & %.2X)\n",q2,(q3<<4)+q4);
            setrand(state->reg+q2,(q3<<4)+q4);
            break;
        case 23:
            //fprintf(log,"draw sprite at V%X,V%X,H%X\n",q2,q3,q4);
            drawSprite(*(state->reg+q2),*(state->reg+q3),q4,state->mem+state->I,state->vf);
            break;
        case 24:
            //fprintf(log,"skip if key in V%X is pressed*\n",q2);
            skip(state->reg+q2,&state->pc);
            break;
        case 25:
            //fprintf(log,"skip if key in V%X isn't pressed*\n",q2);
            skipnp(state->reg+q2,&state->pc);
            break;
        case 26:
            //fprintf(log,"set V%X to the delay timer\n",q2);
            readdt(state->reg+q2,&state->dt);
            break;
        case 27:
            //fprintf(log,"store next keypress in V%X*\n",q2);
            getkey(state->reg+q2);
            break;
        case 28:
            //fprintf(log,"set delay timer to V%X",q2);
            setdt(state->reg+q2,&state->dt);
            break;
        case 29:
            //FX18: set sound timer to VX
            //fprintf(log,"set sound timer to V%X*",q2);
            break;
        case 30:
            //FX1E: add VX to I
            //fprintf(log,"I += V%X\n",q2);
            addaddr(state->reg+q2,&state->I);
            break;
        case 31:
            //FX29
            //fprintf(log,"set I to the address of sprite in V%X\n",q2);
            state->I = *(state->reg+q2) * 5;
            break;
        case 32:
            //FX33:
            //fprintf(log,"set I to the BCD of V%X\n",q2);
            bcd(state->reg+q2,state->mem,state->I); //possible bug 
            break;
        case 33:
            //FX55: store
            //fprintf(log,"store V0 - V%X in memory starting at I\n",q2);
            stor(state->reg,q2,state->mem,&state->I);
            break;
        case 34:
            //FX65: load
            //fprintf(log,"load V0 - V%X with bytes starting at I\n",q2);
            load(state->reg,q2,state->mem,&state->I);
            break;
    }
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
