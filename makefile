CFLAGS=-g
CC=gcc
all: ./bin/chip8

tests: ./bin/draw ./bin/logic ./bin/hello ./bin/time ./bin/inittest

./bin/chip8: ./bin/chip8.o ./bin/debug.o ./bin/opcodes.o ./bin/util.o ./bin/io.o ./bin/emu.o
	$(CC) -o ./bin/chip8  -lncurses ./bin/chip8.o ./bin/opcodes.o ./bin/debug.o ./bin/util.o ./bin/io.o ./bin/emu.o

./bin/draw: ./bin/draw.o ./bin/io.o
	$(CC) -o ./bin/draw -lncurses ./bin/draw.o ./bin/io.o

./bin/time: ./src/tests/time.c
	$(CC) -o ./bin/time ./src/tests/time.c

./bin/bcd: ./bin/bcd.o ./bin/opcodes.o
	$(CC) -o ./bin/bcd ./bin/opcodes.o ./bin/bcd.o

./bin/hello: ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
	$(CC) -o ./bin/hello ./bin/hello.o ./bin/debug.o ./bin/opcodes.o

./bin/logic: ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
	$(CC) -o ./bin/logic ./bin/logic.o ./bin/debug.o ./bin/opcodes.o

./bin/inittest: ./bin/util.o ./bin/inittest.o ./bin/debug.o
	$(CC) -o ./bin/inittest ./bin/util.o ./bin/inittest.o ./bin/debug.o

./bin/%.o: ./src/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

./bin/%.o: ./src/tests/%.c
	$(CC) -o $@ -c $(CFLAGS) $<
