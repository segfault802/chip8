./bin/draw: ./bin/draw.o ./bin/io.o
	gcc -o ./bin/draw -lncurses ./bin/draw.o ./bin/io.o

./bin/draw.o: ./tests/draw.c
	gcc -o ./bin/draw.o -c ./tests/draw.c

./bin/io.o: ./io.c
	gcc -o ./bin/io.o -c ./io.c

#./bin/hello: ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
#	gcc -o ./bin/hello ./bin/hello.o ./bin/debug.o ./bin/opcodes.o
#
#./bin/logic: ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
#	gcc -o ./bin/logic ./bin/logic.o ./bin/debug.o ./bin/opcodes.o
#
#./bin/logic.o: ./tests/logic.c
#	gcc -o ./bin/logic.o -c -g ./tests/logic.c
#
#./bin/hello.o: ./tests/hello.c
#	gcc -o ./bin/hello.o -c -g ./tests/hello.c
#

