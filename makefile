./bin/chip8: ./bin/chip8.o ./bin/debug.o ./bin/opcodes.o ./bin/util.o
	gcc -o ./bin/chip8 ./bin/chip8.o ./bin/opcodes.o ./bin/debug.o ./bin/util.o

./bin/util.o: ./src/util.c
	gcc -o ./bin/util.o -c -g ./src/util.c

./bin/debug.o: ./src/debug.c
	gcc -o ./bin/debug.o -c -g ./src/debug.c

./bin/opcodes.o: ./src/opcodes.c
	gcc -o ./bin/opcodes.o -c -g ./src/opcodes.c

./bin/chip8.o: ./src/chip8.c
	gcc -o ./bin/chip8.o -c -g ./src/chip8.c

clean:
	rm -rf ./bin/*
