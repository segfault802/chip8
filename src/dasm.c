#include <stdio.h>
#include <stdlib.h>
#include "decs.h"
#include "util.h"

typedef struct {
    Instruction instr;
    byte jmp;        //is this a jump instruction?
    byte data;       //is this a data byte?
    byte jmpTarget;  //is this the target of a jump?
    byte opcode;     //the numerical opcode as returned by lookupOp
    char str[20];    //human readable string
} DecodedInstr;


void setStr(DecodedInstr* instr);

int main(int argc, char* argv[])
{
    FILE* fp;
    size_t size;
    long fileSize;
    int i;
    byte a,b;
    DecodedInstr* program;
    DecodedInstr dinstr;
    Instruction instr;
    if(argc <= 1) {
        printf("no input file!\n");
        return 1;
    }
    fp = fopen(argv[1],"rb");
    //get the size of the file and allocate a buffer
    fseek(fp,0,SEEK_END);
    fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);
    program = (DecodedInstr*)malloc(sizeof(DecodedInstr)*fileSize);
    i = 0;
    while(!feof(fp)) {
        size = fread(&a,1,1,fp);
        size = fread(&b,1,1,fp);
        instr.pack = (a << 8) + b;
        program[i].instr = instr;
        program[i].opcode = lookupOp(&program[i].instr);
        setStr(&program[i]);
        printf("%s\n",program[i].str);
        i++;
    }
    return 0;
}

void setStr(DecodedInstr* instr)
{
    byte q1,q2,q3,q4;
    q1 = instr->instr.unpack.q1;
    q2 = instr->instr.unpack.q2;
    q3 = instr->instr.unpack.q3;
    q4 = instr->instr.unpack.q4;
    switch(instr->opcode) {
        case 0:
            sprintf(instr->str,"%-5s","cls");
            break;
        case 1:
            sprintf(instr->str,"%-5s","ret");
            break;
        case 2:
            sprintf(instr->str,"%-5s $%x%x%x","sys",q2,q3,q4);
            break;
        case 3:
            sprintf(instr->str,"%-5s $%x%x%x","jp",q2,q3,q4);
            break;
        case 4:
            sprintf(instr->str,"%-5s $%x%x%x","call",q2,q3,q4);
            break;
        case 5:
            sprintf(instr->str,"%-5s v%x, %x%x","se",q2,q3,q4);
            break;
        case 6:
            sprintf(instr->str,"%-5s v%x, %x%x","sne",q2,q3,q4);
            break;
        case 7:
            sprintf(instr->str,"%-5s v%x, v%x","se",q2,q3);
            break;
        case 8:
            sprintf(instr->str,"%-5s v%x, %x%x","ld",q2,q3,q4);
            break;
        case 9:
            sprintf(instr->str,"%-5s v%x, %x%x","add",q2,q3,q4);
            break;
        case 10:
            sprintf(instr->str,"%-5s v%x, v%x","ld",q2,q3);
            break;
        case 11:
            sprintf(instr->str,"%-5s v%x, v%x","or",q2,q3);
            break;
        case 12:
            sprintf(instr->str,"%-5s v%x, v%x","and",q2,q3);
            break;
        case 13:
            sprintf(instr->str,"%-5s v%x, v%x","xor",q2,q3);
            break;
        case 14:
            sprintf(instr->str,"%-5s v%x, v%x","add",q2,q3);
            break;
        case 15:
            sprintf(instr->str,"%-5s v%x, v%x","sub",q2,q3);
            break;
        case 16:
            sprintf(instr->str,"%-5s v%x, v%x","shr",q2,q3);
            break;
        case 17:
            sprintf(instr->str,"%-5s v%x, v%x","subn",q2,q3);
            break;
        case 18:
            sprintf(instr->str,"%-5s v%x, v%x","shl",q2,q3);
            break;
        case 19:
            sprintf(instr->str,"%-5s v%x, v%x","sne",q2,q3);
            break;
        case 20:
            sprintf(instr->str,"%-5s i, $%x%x%x","ld",q2,q3,q4);
            break;
        case 21:
            sprintf(instr->str,"%-5s v0, $%x%x%x","jp",q2,q3,q4);
            break;
        case 22:
            sprintf(instr->str,"%-5s v%x, %x%x","rnd",q2,q3,q4);
            break;
        case 23:
            sprintf(instr->str,"%-5s v%x, v%x, %x","drw",q2,q3,q4);
            break;
        case 24:
            sprintf(instr->str,"%-5s v%x","skp",q2);
            break;
        case 25:
            sprintf(instr->str,"%-5s v%x","sknp",q2);
            break;
        case 26:
            sprintf(instr->str,"%-5s v%x, dt","ld",q2);
            break;
        case 27:
            sprintf(instr->str,"%-5s v%x, k","ld",q2);
            break;
        case 28:
            sprintf(instr->str,"%-5s dt, v%x","ld",q2);
            break;
        case 29:
            sprintf(instr->str,"%-5s st, v%x","ld",q2);
            break;
        case 30:
            sprintf(instr->str,"%-5s i, v%x","add",q2);
            break;
        case 31:
            sprintf(instr->str,"%-5s f, v%x","ld",q2);
            break;
        case 32:
            sprintf(instr->str,"%-5s b, v%x","ld",q2);
            break;
        case 33:
            sprintf(instr->str,"%-5s [i], v%x","ld",q2);
            break;
        case 34:
            sprintf(instr->str,"%-5s v%x, [i]","ld",q2);
            break;
        default:
            sprintf(instr->str,"%X",instr->instr.pack);
            break;
    }
}



