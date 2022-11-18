# -*- MakeFile -*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 

CC = clang
CFLAGS = -g -Wall -DNDEBUG
PROG = main
OBJECTS = common.o province.o industry.o income.o processCommands.o sumFunctions.o find.o
PRE_REQS = lab4main.c lab4main.h processCommands.h find.h sumFunctions.h province.h industry.h income.h common.h

all: $(PROG)

$(PROG): $(PRE_REQS) $(OBJECTS)
	$(CC) $(CFLAGS) lab4main.c $(OBJECTS) -o $(PROG)

common.o: common.h
province.o: province.h common.h
industry.o: industry.h common.h
income.o: income.h common.h
sumFunctions.o: sumFunctions.h province.h industry.h income.h common.h
find.o: find.h test.h
	clang -Wall find.c -o find.o -c
processCommands.o: processCommands.h find.h sumFunctions.h province.h industry.h income.h common.h

clean:
	rm -f $(OBJECTS) $(PROG) 
