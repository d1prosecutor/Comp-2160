# -*- MakeFile -*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
PROG = main

all: $(PROG)

main: main.c main.h container.o
	$(CC) $(CFLAGS) main.c container.o -o $(PROG)

container.o: container.h

clean: 
	rm *.o main -f
