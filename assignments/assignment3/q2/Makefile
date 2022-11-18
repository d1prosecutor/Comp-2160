# -*- MakeFile -*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
PROG = main main1 main2 main3 main4 main5
PRE_REQS = main.c main.h set.h

all: $(PROG)

main: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set.o -o main

main1: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set1.o -o main1

main2: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set2.o -o main2

main3: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set3.o -o main3

main4: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set4.o -o main4
	
main5: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set5.o -o main5

clean: 
	rm $(PROG) -f
