#include <ncurses.h>
#include "../io.h"


//test it
int main()
{
	byte two[5] = {0xf0,0x10,0xf0,0x80,0xf0};
	byte one[5] = {0x20,0x60,0x20,0x20,0x70};
	byte zero[5] = {0xf0,0x90,0x90,0x90,0xf0};
	byte three[5] = {0xf0,0x10,0xf0,0x10,0xf0};
	byte four[5] = {0x90,0x90,0xf0,0x10,0x10};
	byte five[5] = {0xf0,0x80,0xf0,0x10,0xf0};
	byte six[5] = {0xf0,0x80,0xf0,0x90,0xf0};
	byte seven[5] = {0xf0,0x10,0x20,0x40,0x40};
	byte eight[5] = {0xf0,0x90,0xf0,0x90,0xf0};
	byte nine[5] = {0xf0,0x90,0xf0,0x10,0xf0};
	byte A[5] = {0xf0,0x90,0xf0,0x90,0x90};
	byte B[5] = {0xe0,0x90,0xe0,0x90,0xe0};
	byte C[5] = {0xf0,0x80,0x80,0x80,0xf0};
	byte D[5] = {0xe0,0x90,0x90,0x90,0xe0};
	byte E[5] = {0xf0,0x80,0xf0,0x80,0xf0};
	byte F[5] = {0xf0,0x80,0xf0,0x80,0x80};
	byte smiley[5] = {0x18,0x24,0x42,0x81};	
	
	initscr();
	//code
	move(0,25);
	printw("Printing some sprites!");
	drawSprite(0,2,5,zero);
	drawSprite(8,2,5,one);
	drawSprite(16,2,5,two);
	drawSprite(24,2,5,three);
	drawSprite(32,2,5,four);
	drawSprite(40,2,5,five);
	drawSprite(48,2,5,six);
	drawSprite(56,2,5,seven);
	drawSprite(0,10,5,eight);
	drawSprite(8,10,5,nine);
	drawSprite(16,10,5,A);
	drawSprite(24,10,5,B);
	drawSprite(32,10,5,C);
	drawSprite(40,10,5,D);
	drawSprite(48,10,5,E);
	drawSprite(56,10,5,F);
	//drawSprite(28,15,4,smiley);
	getch();
	clearScreen();
	getch();
	endwin();
	return 0;
}