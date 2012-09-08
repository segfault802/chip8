//these functions handle I/O; displaying graphics and getting keyboard input

#include "decs.h"

//takes a byte and prints the binary representation to the ncurses screen
void printRow(byte row);

//DXYN: draws n rows of the sprite pointed to by s at (x,y) on the screen
void drawSprite(byte x, byte y, byte n, byte* s);

//00E0
void clearScreen();


//EX9E	Skips the next instruction if the key stored in VX is pressed.
//void 

//EXA1	Skips the next instruction if the key stored in VX isn't pressed.
