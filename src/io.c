#include "io.h"
#include <stdio.h>
#include <ncurses.h>

void printRow(byte row)
{
	int i;
	byte b;
	for(i=0;i<8;i++){
		b = (row>>(8-(i+1))) & 1;
		printf("%d",b);
	}
}

void drawSprite(byte x, byte y, byte n, byte* s)
{
}
