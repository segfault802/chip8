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
    switch(opcode) {
        case 0:
            printf("%-5s","cls");
            break;
        case 1:
            printf("%-5s","ret");
            break;
        case 2:
            printf("%-5s $%x%x%x","sys",q2,q3,q4);
            break;
        case 3:
            printf("%-5s $%x%x%x","jp",q2,q3,q4);
            break;
        case 4:
            printf("%-5s $%x%x%x","call",q2,q3,q4);
            break;
        case 5:
            printf("%-5s v%x, %x%x","se",q2,q3,q4);
            break;
        case 6:
            printf("%-5s v%x, %x%x","sne",q2,q3,q4);
            break;
        case 7:
            printf("%-5s v%x, v%x","se",q2,q3);
            break;
        case 8:
            printf("%-5s v%x, %x%x","ld",q2,q3,q4);
            break;
        case 9:
            printf("%-5s v%x, %x%x","add",q2,q3,q4);
            break;
        case 10:
            printf("%-5s v%x, v%x","ld",q2,q3);
            break;
        case 11:
            printf("%-5s v%x, v%x","or",q2,q3);
            break;
        case 12:
            printf("%-5s v%x, v%x","and",q2,q3);
            break;
        case 13:
            printf("%-5s v%x, v%x","xor",q2,q3);
            break;
        case 14:
            printf("%-5s v%x, v%x","add",q2,q3);
            break;
        case 15:
            printf("%-5s v%x, v%x","sub",q2,q3);
            break;
        case 16:
            printf("%-5s v%x, v%x","shr",q2,q3);
            break;
        case 17:
            printf("%-5s v%x, v%x","subn",q2,q3);
            break;
        case 18:
            printf("%-5s v%x, v%x","shl",q2,q3);
            break;
        case 19:
            printf("%-5s v%x, v%x","sne",q2,q3);
            break;
        case 20:
            printf("%-5s i, $%x%x%x","ld",q2,q3,q4);
            break;
        case 21:
            printf("%-5s v0, $%x%x%x","jp",q2,q3,q4);
            break;
        case 22:
            printf("%-5s v%x, %x%x","rnd",q2,q3,q4);
            break;
        case 23:
            printf("%-5s v%x, v%x, %x","drw",q2,q3,q4);
            break;
        case 24:
            printf("%-5s v%x","skp",q2);
            break;
        case 25:
            printf("%-5s v%x","sknp",q2);
            break;
        case 26:
            printf("%-5s v%x, dt","ld",q2);
            break;
        case 27:
            printf("%-5s v%x, k","ld",q2);
            break;
        case 28:
            printf("%-5s dt, v%x","ld",q2);
            break;
        case 29:
            printf("%-5s st, v%x","ld",q2);
            break;
        case 30:
            printf("%-5s i, v%x","add",q2);
            break;
        case 31:
            printf("%-5s f, v%x","ld",q2);
            break;
        case 32:
            printf("%-5s b, v%x","ld",q2);
            break;
        case 33:
            printf("%-5s [i], v%x","ld",q2);
            break;
        case 34:
            printf("%-5s v%x, [i]","ld",q2);
            break;
        default:
            printf("%X",instr->pack);
            break;
    }
    printf("\n");
}



