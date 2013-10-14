all: ./bin/chip8

tests: ./bin/draw ./bin/logic ./bin/hello ./bin/time

./bin/chip8: ./bin/chip8.o ./bin/debug.o ./bin/opcodes.o ./bin/util.o ./bin/io.o
	gcc -o ./bin/chip8  -lncurses ./bin/chip8.o ./bin/opcodes.o ./bin/debug.o ./bin/util.o ./bin/io.o

./bin/draw: ./bin/draw.o ./bin/io.o
	gcc -o ./bin/draw -lncurses ./bin/draw.o ./bin/io.o

./bin/time: ./src/tests/time.c
	gcc -o ./bin/time ./src/tests/time.c

./bin/bcd: ./bin/bcd.o ./bin/opcodes.o
	gcc -o ./bin/bcd ./bin/opcodes.o ./bin/bcd.o

./bin/hello: ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
	gcc -o ./bin/hello ./bin/hello.o ./bin/debug.o ./bin/opcodes.o

./bin/logic: ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
	gcc -o ./bin/logic ./bin/logic.o ./bin/debug.o ./bin/opcodes.o


./bin/util.o: ./src/util.c
	gcc -o ./bin/util.o -c -g ./src/util.c

./bin/debug.o: ./src/debug.c
	gcc -o ./bin/debug.o -c -g ./src/debug.c

./bin/opcodes.o: ./src/opcodes.c ./src/decs.h
	gcc -o ./bin/opcodes.o -c -g ./src/opcodes.c

./bin/io.o: ./src/io.c ./src/decs.h
	gcc -o./bin/io.o -c -g ./src/io.c

./bin/chip8.o: ./src/chip8.c ./src/decs.h
	gcc -o ./bin/chip8.o -c -g ./src/chip8.c


#Some tests
./bin/bcd.o: ./src/tests/bcd.c
	gcc -o ./bin/bcd.o -c -g ./src/tests/bcd.c

./bin/draw.o: ./src/tests/draw.c
	gcc -o ./bin/draw.o -c ./src/tests/draw.c

./bin/logic.o: ./src/tests/logic.c
	gcc -o ./bin/logic.o -c -g ./src/tests/logic.c

./bin/hello.o: ./src/tests/hello.c
	gcc -o ./bin/hello.o -c -g ./src/tests/hello.c

