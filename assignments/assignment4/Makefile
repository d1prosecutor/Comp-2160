# -*- MakeFile -*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
OBJ = ObjectManager.o
HDR = ObjectManager.h
MAIN = main0.c
PROG = ObjectManager

all: $(PROG)

$(PROG): $(MAIN) $(HDR) $(OBJ)
	$(CC) $(CFLAGS) $(MAIN) $(OBJ) -o $(PROG)

$(OBJ): ObjectManager.c $(HDR)
		$(CC) $(CFLAGS) -c ObjectManager.c -o $(OBJ)

clean: 
	rm $(OBJ) $(PROG) -f
