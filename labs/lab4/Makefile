all: main

main: lab4main.c lab4main.h common.o province.o industry.o income.o processCommands.o sumFunctions.o find.o
	clang -Wall lab4main.c common.o province.o industry.o income.o processCommands.o sumFunctions.o find.o -o main

common.o: common.c common.h
	clang -Wall common.c -o common.o -c

province.o: province.c province.h
	clang -Wall province.c -o province.o -c

industry.o: industry.c industry.h
	clang -Wall industry.c -o industry.o -c

income.o: income.c income.h
	clang -Wall income.c -o income.o -c

processCommands.o: processCommands.c processCommands.h
	clang -Wall processCommands.c -o processCommands.o -c

sumFunctions.o: sumFunctions.c sumFunctions.h
	clang -Wall sumFunctions.c -o sumFunctions.o -c

find.o: find.c find.h
	clang -Wall find.c -o find.o -c

clean:
	rm -f *.o main
