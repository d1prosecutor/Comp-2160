# -*- MakeFile -*-

CC = clang
CFLAGS = -g -Wall # -DNDEBUG

PROG = main
HDRS = common.h industry.h income.h province.h find.h sumFunctions.h processCommands.h
SRCS = main.c common.c industry.c income.c province.c find.c sumFunctions.c processCommands.c

OBJDIR = object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/common.o $(OBJDIR)/industry.o $(OBJDIR)/income.o $(OBJDIR)/province.o $(OBJDIR)/find.o \
$(OBJDIR)/sumFunctions.o $(OBJDIR)/processCommands.o

# compiling rules

# WARNING: *must* have a tab before each definition
$(PROG): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
	
$(OBJDIR)/common.o: common.c $(HDRS)
	$(CC) $(CFLAGS) -c common.c -o $(OBJDIR)/common.o

$(OBJDIR)/industry.o: industry.c $(HDRS)
	$(CC) $(CFLAGS) -c industry.c -o $(OBJDIR)/industry.o
	
$(OBJDIR)/income.o: income.c $(HDRS)
	$(CC) $(CFLAGS) -c income.c -o $(OBJDIR)/income.o
	
$(OBJDIR)/province.o: province.c $(HDRS)
	$(CC) $(CFLAGS) -c province.c -o $(OBJDIR)/province.o

$(OBJDIR)/find.o: find.c $(HDRS)
	$(CC) $(CFLAGS) -c find.c -o $(OBJDIR)/find.o

$(OBJDIR)/sumFunctions.o: sumFunctions.c $(HDRS)
	$(CC) $(CFLAGS) -c sumFunctions.c -o $(OBJDIR)/sumFunctions.o

$(OBJDIR)/processCommands.o: processCommands.c $(HDRS)
	$(CC) $(CFLAGS) -c processCommands.c -o $(OBJDIR)/processCommands.o

$(OBJDIR)/main.o: main.c $(HDRS)
	$(CC) $(CFLAGS) -c main.c -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)
#	rmdir $(OBJDIR)
