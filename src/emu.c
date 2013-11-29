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
            ret(&state->sp,&state->pc);
            break;       
        case 3:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            if(state->pc == state->mem+longOp){
                //done = 1; //detect if we've entered an infinite loop
            }
            else{
                jmp(longOp,state->mem,&state->pc);
            }
            break;  
        case 4:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            call(longOp,state->mem,&state->sp,&state->pc);
            break;
        case 5:
            seq(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 6:
            sne(state->reg+q2,(q3<<4)+q4,&state->pc);
            break;
        case 7:
            sey(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 8:
            seti(state->reg+q2,(q3<<4)+q4);
            break;
        case 9:
            addi(state->reg+q2,(q3<<4)+q4);
            break;
        case 10:
            set(state->reg+q2,state->reg+q3);
            break;  
        case 11:
            or(state->reg+q2,state->reg+q3);
            break;
        case 12:
            and(state->reg+q2,state->reg+q3);
            break;
        case 13:
            xor(state->reg+q2,state->reg+q3);
            break;
        case 14:
            add(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 15:
            subyx(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 16:
            shr(state->reg+q2,state->vf);
            break;
        case 17:
            subxy(state->reg+q2,state->reg+q3,state->vf);
            break;
        case 18:
            shl(state->reg+q2,state->vf);
            break;
        case 19:
            sney(state->reg+q2,state->reg+q3,&state->pc);
            break;
        case 20:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            iset(&state->I,longOp);
            break;  
        case 21:
            longOp = (word)((q2<<8)+(q3<<4)+q4);
            jmp0(state->reg,longOp,&state->pc);
            break;
        case 22:
            setrand(state->reg+q2,(q3<<4)+q4);
            break;
        case 23:
            drawSprite(*(state->reg+q2),*(state->reg+q3),q4,state->mem+state->I,state->vf);
            break;
        case 24:
            skip(state->reg+q2,&state->pc);
            break;
        case 25:
            skipnp(state->reg+q2,&state->pc);
            break;
        case 26:
            readdt(state->reg+q2,&state->dt);
            break;
        case 27:
            getkey(state->reg+q2);
            break;
        case 28:
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
