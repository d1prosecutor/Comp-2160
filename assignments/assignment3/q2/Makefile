# -*- MakeFile -*-
CC = clang
CFLAGS = -g -Wall # -DNDEBUG

all: main

main: main.c main.h set.h
	clang -Wall -g main.c set.o -o main

clean: 
	rm main.o main -f
