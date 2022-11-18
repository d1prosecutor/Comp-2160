# a sample Makefile

CC = clang
CFLAGS = -g -Wall # -DNDEBUG

PROG = stringtest
HDRS = string.h boolean.h
SRCS = main.c string.c

OBJDIR = object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/string.o

# compiling rules

# WARNING: *must* have a tab before each definition
$(PROG): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

$(OBJDIR)/string.o: string.c $(HDRS)
	$(CC) $(CFLAGS) -c string.c -o $(OBJDIR)/string.o

$(OBJDIR)/main.o: main.c $(HDRS)
	$(CC) $(CFLAGS) -c main.c -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)
#	rmdir $(OBJDIR)
