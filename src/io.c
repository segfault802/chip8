#include "io.h"
#include <stdio.h>
#include <ncurses.h>

/*byte* readRow(byte y,byte x)
{
}*/

void printRow(byte row)
{
	byte i;
	byte b;
    char c;
	for(i=0;i<8;i++){
		b = (row>>(8-(i+1))) & 1;
		//printf("%d",b);
		c = inch();
        if(b == 0 && c == ' '){
            addch(' ');
        }
		else if (b == 0 && c == ACS_BLOCK){
            addch(ACS_BLOCK);
        }
        else if (b == 1 && c == ' '){
            addch(ACS_BLOCK);
        }
        else{
            addch(' ');
        }
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
	refresh();
}

void clearScreen()
{
	clear();
}

void clockStep(byte* dt)
{
    usleep(CLOCK_TICK);
    if((*dt) > 0)
        (*dt)--;
}

byte mapKey(char key)
{
    switch(key){
        case '1':
            return 0x1;
        case '2':
            return 0x2;
        case '3':
            return 0x3;
        case '4':
            return 0xC;
        case 'q':
            return 0x4;
        case 'w':
            return 0x5;
        case 'e':
            return 0x6;
        case 'r':
            return 0xD;
        case 'a':
            return 0x7;
        case 's':
            return 0x8;
        case 'd':
            return 0x9;
        case 'f':
            return 0xE;
        case 'z':
            return 0xA;
        case 'x':
            return 0x0;
        case 'c':
            return 0xB;
        case 'v':
            return 0xF;
    }
}

//EX9E	Skips the next instruction if the key stored in VX is pressed.
void skip(byte* reg, byte** pc)
{
    int key;
    byte val;
    key = getchar();
    if(key != ERR){
        val = mapKey((char)key);
    }
    if(*reg == val)
        *pc+=2;
}

//EXA1	Skips the next instruction if the key stored in VX isn't pressed.
void skipnp(byte* reg, byte** pc)
{
    int key;
    byte val;
    key = getchar();
    if(key != ERR){
        val = mapKey((char)key);
    }
    if(*reg != val)
        *pc+=2;
}

//FX0A waits for a key press and stores it in VX
void getkey(byte* reg)
{
    int key;
    byte val;
    nodelay(stdscr,false);
    key = getchar();
    if(key != ERR){
        val = mapKey((char)key);
    }
    *reg = val;
    nodelay(stdscr,true);
}