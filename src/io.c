#include "io.h"
#include <stdio.h>
#include <ncurses.h>

void printRow(byte row)
{
	byte i;
	byte b;
	for(i=0;i<8;i++){
		b = (row>>(8-(i+1))) & 1;
		//printf("%d",b);
		if(b == 0)
			addch(' ');
		else
			addch(ACS_BLOCK);
	}
}

void drawSprite(byte x, byte y, byte n, byte* s)
{
	byte i;
	//FILE *fp = fopen("./bin/tmp","a");
	//fprintf(fp,"drawing at %d,%d\n",x,y);
	move(y,x);
	for(i=0;i<n;i++){
		move(y+i,x);
		//fprintf(fp,"row %d: %X\n",i,s[i]);
		printRow(s[i]);
	}
	//fprintf(fp,"@@@@@@@@@\n");
	//fclose(fp);
	refresh();
}

void clearScreen()
{
	clear();
}
