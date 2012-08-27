./bin/draw: ./tests/draw.c
	gcc -o ./bin/draw -lncurses ./tests/draw.c

./bin/hello: ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
	gcc -o ./bin/hello ./bin/hello.o ./bin/debug.o ./bin/opcodes.o

./bin/logic: ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
	gcc -o ./bin/logic ./bin/logic.o ./bin/debug.o ./bin/opcodes.o

./bin/logic.o: ./tests/logic.c
	gcc -o ./bin/logic.o -c -g ./tests/logic.c

./bin/hello.o: ./tests/hello.c
	gcc -o ./bin/hello.o -c -g ./tests/hello.c

