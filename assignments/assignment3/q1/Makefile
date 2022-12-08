# -*- MakeFile q1-*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
OBJ = container.o
HDR = container.h
PROG = main

all: $(PROG)

$(PROG): main0.c $(HDR) $(OBJ)
	$(CC) $(CFLAGS) main0.c $(OBJ) -o $(PROG)

$(OBJ): container.c $(HDR)
		$(CC) $(CFLAGS) -c container.c -o $(OBJ)

clean: 
	rm $(OBJ) $(PROG) -f
