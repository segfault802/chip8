#include <stdio.h>
#include <limits.h>
#include "decs.h"
#include "opcodes.h"
#include "debug.h"



int main(int argc, char* argv[])
{	
	//allocate registers and program memory
	byte  reg[16];
	byte mem[4096];
	printf("Memory start: %p\n",mem);
	byte *ptr = mem + 0x200;
	size_t size;
	FILE *fp;
	if(argc > 1){
		fp = fopen(argv[1],"rb");
		printf("opening %s\n",argv[1]);
	}
	else{
		printf("no file specified!\n");
		return 1;
	}
	while(!feof(fp)){
		//printf("Pointer Address: %p\n",ptr);
		size = fread(ptr,1,2,fp);	
		printf("Read %d bytes, %.2X%.2X\n",size,*ptr,*(ptr+0x1));
		ptr += 0x02;
	}
	fclose(fp);
	printmem(mem,0x200,0x223);	
	return 0;
}
