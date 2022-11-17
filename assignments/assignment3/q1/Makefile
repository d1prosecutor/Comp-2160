# -*- MakeFile -*-

all: main

main: main.c main.h container.o
	clang -Wall -g main.c container.o -o main

container.o: container.c container.h
	clang -Wall -g -DNDEBUG container.c -o container.o -c 

clean: 
	rm *.o main -f
