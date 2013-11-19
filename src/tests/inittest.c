#include <stdio.h>
#include "../decs.h"
#include "../util.h"


    

int main() {
    SystemState a,b;
    
    //initialize the first with the function
    initialize(&a);
    
    //initialize the second manually
    b.vf = &b.reg[15];
    b.pc = b.mem+PROGRAM_START;
    b.sp = b.stack;

    printf("A reg: %p\n",a.reg);
    printf("A vf: %p\n",a.vf);
    printf("A mem: %p\n",a.mem);
    printf("A pc: %p\n",a.pc);
    printf("A stack: %p\n",a.stack);
    printf("A sp: %p\n",a.sp);
    
    printf("B reg: %p\n",b.reg);
    printf("B vf: %p\n",b.vf);
    printf("B mem: %p\n",b.mem);
    printf("B pc: %p\n",b.pc);
    printf("B stbck: %p\n",a.stack);
    printf("B sp: %p\n",b.sp);
    
}
