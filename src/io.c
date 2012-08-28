#include "io.h"
#include <stdio.h>
#include <ncurses.h>

void printRow(byte row)
{
	byte i;
	byte b;
	for(i=0;i<8;i++){
		b = (row>>(8-(i+1))) & 1;
		printf("%d",b);
		if(b == 0)
			addch(' ');
		else
			addch(ACS_BLOCK);
	}
}

void drawSprite(byte x, byte y, byte n, byte* s)
{
	byte i;
	move(y,x);
	for(i=0;i<n;i++){
		move(y+i,x);
		printRow(s[i]);
	}
}
