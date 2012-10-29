#include <stdio.h>
#include "../decs.h"
#include "../opcodes.h"


//debugging the bcd function
//void bcd(byte* reg, byte* mem, word I)

int main()
{
    byte reg = 208;
    byte mem[3];
    word I = 0;
    bcd(&reg,mem,I);
    printf("BCD of %X stored in 3 bytes is %X %X %X\n",reg,mem[0],mem[1],mem[2]);
    return 0;
}
