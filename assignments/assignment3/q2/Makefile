# -*- MakeFile q2-*-
# insert a '#' infront of the DNDEBUG in the compiler flags to enable assertions 
# The executable files are placed in a new folder named programs

CC = clang
CFLAGS = -g -Wall -DNDEBUG
PROG = $(PROGDIR)/main $(PROGDIR)/main1 $(PROGDIR)/main2 $(PROGDIR)/main3 $(PROGDIR)/main4 $(PROGDIR)/main5
PRE_REQS = main.c set.h
PROGDIR = programs

all: $(PROGDIR) $(PROG)

$(PROGDIR)/main: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set.o -o $(PROGDIR)/main

$(PROGDIR)/main1: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set1.o -o $(PROGDIR)/main1

$(PROGDIR)/main2: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set2.o -o $(PROGDIR)/main2

$(PROGDIR)/main3: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set3.o -o $(PROGDIR)/main3

$(PROGDIR)/main4: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set4.o -o $(PROGDIR)/main4
	
$(PROGDIR)/main5: $(PRE_REQS)
	$(CC) $(CFLAGS) main.c set5.o -o $(PROGDIR)/main5

$(PROGDIR):
	mkdir $(PROGDIR)

clean: 
	rm $(PROG) -f
#rm $(OBJDIR)
