//Some functions to aid in debugging of the emulator

#include "decs.h"

//print the contents of all registers
void printregs(FILE* fp,byte* reg);

//print contents of memory from start to end
//addresses are chip8 normalized
void printmem(FILE* fp,byte* mem,word start, word end);

