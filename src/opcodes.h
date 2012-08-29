//declaration of all of the various opcode functions

/*Opcode reference (from wikipedia)

Key
NNN:     address
NN:      8-bit constant
N:       4-bit constant
X and Y: 4-bit register identifier

Opcode	Explanation
0NNN	Calls RCA 1802 program at address NNN.
00E0	Clears the screen.
00EE	Returns from a subroutine.
*1NNN	Jumps to address NNN.
2NNN	Calls subroutine at NNN.
*3XNN	Skips the next instruction if VX equals NN.
*4XNN	Skips the next instruction if VX doesn't equal NN.
*5XY0	Skips the next instruction if VX equals VY.
*6XNN	Sets VX to NN.
*7XNN	Adds NN to VX.
*8XY0	Sets VX to the value of VY.
*8XY1	Sets VX to VX or VY.
*8XY2	Sets VX to VX and VY.
*8XY3	Sets VX to VX xor VY.
*8XY4	Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
*8XY5	VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
*8XY6	Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.[2]
*8XY7	Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
*8XYE	Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.[2]
*9XY0	Skips the next instruction if VX doesn't equal VY.
*ANNN	Sets I to the address NNN.
*BNNN	Jumps to the address NNN plus V0.
*CXNN	Sets VX to a random number and NN.

*DXYN	Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. 
		Each row of 8 pixels is read as bit-coded (with the most significant bit of each byte 
		displayed on the left) starting from memory location I; I value doesn't change after the 
		execution of this instruction. As described above, VF is set to 1 if any screen pixels are 
		flipped from set to unset when the sprite is drawn, and to 0 if that doesn't happen.
EX9E	Skips the next instruction if the key stored in VX is pressed.
EXA1	Skips the next instruction if the key stored in VX isn't pressed.
FX07	Sets VX to the value of the delay timer.
FX0A	A key press is awaited, and then stored in VX.
FX15	Sets the delay timer to VX.
FX18	Sets the sound timer to VX.
*FX1E	Adds VX to I.[3]
FX29	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) 
		are represented by a 4x5 font.
FX33	Stores the Binary-coded decimal representation of VX, with the most significant of three 
		digits at the address in I, the middle digit at I plus 1, and the least significant digit at 
		I plus 2.
*FX55	Stores V0 to VX in memory starting at address I.[4]
*FX65	Fills V0 to VX with values from memory starting at address I.[4]
*/
#include "decs.h"

//6XNN: set-immediate
void seti(byte* reg, byte val);

//8XY0: set
void set(byte* regx, byte* regy);

//7XNN: add-immediate
void addi(byte* reg, byte val);

//8XY4: add, VF acts as a carry flag, 1 if carry, 0 if not
void add(byte* regx, byte* regy, byte* vf);

//8XY5: subtract y from x, VF is a *NOT* carry flag
void subyx(byte* regx, byte* regy, byte* vf);

//8XY7: subtract x from y
void subxy(byte* regx, byte* regy, byte* vf);

//FX65: load
void load(byte* reg, byte x,byte* mem, word* I);

//FX55: store
void stor(byte* reg, byte x, byte* mem, word* I);
/************************************************/

//8XY1: bitwise OR
void or(byte* regx, byte* regy);

//8XY2: bitwise AND
void and(byte* regx, byte* regy);

//8XY3: bitwise XOR
void xor(byte* regx, byte* regy);

//8XY6: shifts right by 1, VF is set to the least significant bit in VX
void shr(byte* reg, byte* vf);

//8XYE: //shifts left by 1, VF is set to the most significant bit in VX
void shl(byte* reg, byte* vf);

//ANNN: sets I to NNN
void iset(word* I, word N);
/************************************************/

//CXNN: set VX to a random number anded with NN
void setrand(byte* reg, byte val);

//1NNN: jump to address NNN
void jmp(word n,byte* mem,byte** pc);

//3XNN: skip next instruction if VX = NN
void seq(byte* reg,byte val,byte** pc);

//4XNN: skip next instruction if VX != NN
void sne(byte* reg,byte val,byte** pc);

//5XY0: skip next instruction if VX = VY
void sey(byte* regx,byte* regy,byte** pc);

//9XY0: skip next instruction if VX != VY
void sney(byte* regx, byte* regy, byte** pc);

//BNNN: jump to NNN + V0
void jmp0(byte* reg, word n,byte** pc);

//FX1E: add VX to I
void addaddr(byte* reg, word* I);
