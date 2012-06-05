#./bin/chip8: ./bin/chip8.o
#	gcc -o ./bin/chip8 ./bin/chip8.o
./bin/logic: ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
	gcc -o ./bin/logic ./bin/logic.o ./bin/debug.o ./bin/opcodes.o

#./bin/hello: ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
#	gcc -o ./bin/hello ./bin/hello.o ./bin/debug.o ./bin/opcodes.o

./bin/logic.o: ./src/logic.c
	gcc -o ./bin/logic.o -c -g ./src/logic.c

#./bin/hello.o: ./src/hello.c
#	gcc -o ./bin/hello.o -c -g ./src/hello.c

./bin/debug.o: ./src/debug.c
	gcc -o ./bin/debug.o -c -g ./src/debug.c

./bin/opcodes.o: ./src/opcodes.c
	gcc -o ./bin/opcodes.o -c -g ./src/opcodes.c

clean:
	rm -rf ./bin/*
