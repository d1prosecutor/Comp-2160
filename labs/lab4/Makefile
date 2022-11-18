CC = clang
CFLAGS = -g -Wall # -DNDEBUG
PROG = main
OBJECTS = common.o province.o industry.o income.o processCommands.o sumFunctions.o find.o


all: $(PROG)

$(PROG): lab4main.c lab4main.h $(OBJECTS)
	$(CC) $(CFLAGS) lab4main.c $(OBJECTS) -o $(PROG)

common.o: common.h
province.o: province.h
industry.o: industry.h
income.o: income.h
processCommands.o: processCommands.h
sumFunctions.o: sumFunctions.h
find.o: find.h

clean:
	rm -f $(OBJECTS) $(PROG) 
