# -*- MakeFile -*-
CC = clang
CFLAGS = -g -Wall # -DNDEBUG


all: main

main: main.c main.h container.o
	$(CC) $(CFLAGS) main.c container.o -o main

container.o: container.c container.h
	$(CC) $(CFLAGS) container.c -o container.o -c 

clean: 
	rm *.o main -f
