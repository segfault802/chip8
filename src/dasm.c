#include <stdio.h>
#include "decs.h"
#include "util.h"

void printInstr(Instruction* instr);

int main(int argc, char* argv[])
{
    FILE* fp;
    size_t size;
    byte a,b;
    Instruction instr;
    if(argc <= 1) {
        printf("no input file!\n");
        return 1;
    }
    fp = fopen(argv[1],"rb");
    while(!feof(fp)) {
        size = fread(&a,1,1,fp);
        size = fread(&b,1,1,fp);
        instr.pack = (a << 8) + b;
        printInstr(&instr);
    }
}

void printInstr(Instruction* instr)
{
    byte q1,q2,q3,q4;
    byte opcode = lookupOp(instr);
    q1 = instr->unpack.q1;
    q2 = instr->unpack.q2;
    q3 = instr->unpack.q3;
    q4 = instr->unpack.q4;
    printf("--%.4X--\n",instr->pack);
    switch(opcode) {
        case 0:
            printf("cls"); 
            break;
        case 1:
            printf("ret");
            break;
        case 2:
            printf("sys $%x%x%x",q2,q3,q4);
            break;
        case 3:
            printf("jp $%x%x%x",q2,q3,q4);
            break;
        case 4:
            printf("call $%x%x%x",q2,q3,q4);
            break;
        case 5:
            printf("se v%x, %x%x",q2,q3,q4);
            break;
        case 6:
            printf("sne v%x, %x%x",q2,q3,q4);
        case 7:
            printf("se v%x, v%x",q2,q3);
            break;
        case 8:
            printf("ld v%x, %x%x",q2,q3,q4);
            break;
        case 9:
            printf("add v%x, %x%x",q2,q3,q4);
            break;
        case 10:
            printf("ld v%x, v%x",q2,q3);
            break;
        case 11:
            printf("or v%x, v%x",q2,q3);
            break;
        case 12:
            printf("and v%x, v%x",q2,q3);
            break;
        case 13:
            printf("xor v%x, v%x",q2,q3);
            break;
        case 14:
            printf("add v%x, v%x",q2,q3);
            break;
        case 15:
            printf("sub v%x, v%x",q2,q3);
            break;
        case 16:
            printf("shr v%x, v%x",q2,q3);
            break;
        case 17:
            printf("subn v%x, v%x",q2,q3);
            break;
        case 18:
            printf("shl v%x, v%x",q2,q3);
            break;
        case 19:
            printf("sne v%x, v%x",q2,q3);
            break;
        case 20:
            printf("ld i, $%x%x%x",q2,q3,q4);
            break;
        case 21:
            printf("jp v0, $%x%x%x",q2,q3,q4);
            break;
        case 22:
            printf("rnd v%x, %x%x",q2,q3,q4);
            break;
        case 23:
            printf("drw v%x, v%x, %x",q2,q3,q4);
            break;
        case 24:
            printf("skp v%x",q2);
            break;
        case 25:
            printf("sknp v%x",q2);
            break;
        //case 26:
        //    break;
        default:
            printf("%X",instr->pack);
            break;
    }
    printf("\n");
}



