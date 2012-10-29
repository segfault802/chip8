//these functions handle I/O; displaying graphics and getting keyboard input

#include "decs.h"

//takes a byte and prints the binary representation to the ncurses screen
void printRow(byte row);

//DXYN: draws n rows of the sprite pointed to by s at (x,y) on the screen
void drawSprite(byte x, byte y, byte n, byte* s);

//00E0
void clearScreen();

//simulate 1 tick of the clock, updating the delay timer if necessary
void clockStep(byte* dt);

//EX9E	Skips the next instruction if the key stored in VX is pressed.
void skip(byte* reg);

//EXA1	Skips the next instruction if the key stored in VX isn't pressed.
void skipnp(byte* reg);

//FX0A waits for a key press and stores it in VX
void getkey(byte* reg);
