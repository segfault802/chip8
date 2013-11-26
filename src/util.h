#include <stdio.h>
#include "decs.h"



byte getQuartet(word w, byte i);

void preload(byte* mem);

void initialize(SystemState* state);

void loadFile(char* file, SystemState* state);
