# -*- MakeFile q1-*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
OBJ = container.o
HDR = container.h
PROG = main

all: $(PROG)

$(PROG): main.c $(HDR) $(OBJ)
	$(CC) $(CFLAGS) main.c $(OBJ) -o $(PROG)

$(OBJ): $(HDR)
		$(CC) $(CFLAGS) -c container.c -o $(OBJ)

clean: 
	rm $(OBJ) $(PROG) -f
