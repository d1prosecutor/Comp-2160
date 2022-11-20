# -*- MakeFile -*-

CC = clang
CFLAGS = -g -Wall # -DNDEBUG

PROG = main

# Not including all the headers in one variable
# so that the makefile recompiles only what is necessary each time 'make' is run
# HDRS = common.h industry.h income.h province.h find.h sumFunctions.h processCommands.h industryStruct.h provinceStruct.h incomeStruct.h
COMMON_HDR =common.h
INDUSTRY_HDR = industry.h
INCOME_HDR = income.h
PROVINCE_HDR = province.h
FIND_HDR = find.h
SUMFUNC_HDR = sumFunctions.h
COMMAND_HDR = processCommands.h
INDSTRUCT_HDR = industryStruct.h
PROVSTRUCT_HDR = provinceStruct.h
INCSTRUCT_HDR = incomeStruct.h

SRCS = lab4main.c common.c industry.c income.c province.c find.c sumFunctions.c processCommands.c

OBJDIR = object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/common.o $(OBJDIR)/industry.o $(OBJDIR)/income.o $(OBJDIR)/province.o $(OBJDIR)/find.o \
$(OBJDIR)/sumFunctions.o $(OBJDIR)/processCommands.o

# compiling rules

# WARNING: *must* have a tab before each definition
$(PROG): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
	
$(OBJDIR)/common.o: common.c $(COMMON_HDR)
	$(CC) $(CFLAGS) -c common.c -o $(OBJDIR)/common.o

$(OBJDIR)/industry.o: industry.c $(INDUSTRY_HDR) $(INDUSTRY_HDR)
	$(CC) $(CFLAGS) -c industry.c -o $(OBJDIR)/industry.o
	
$(OBJDIR)/income.o: income.c $(INCOME_HDR) $(INCSTRUCT_HDR)
	$(CC) $(CFLAGS) -c income.c -o $(OBJDIR)/income.o
	
$(OBJDIR)/province.o: province.c $(PROVINCE_HDR) $(PROVSTRUCT_HDR)
	$(CC) $(CFLAGS) -c province.c -o $(OBJDIR)/province.o

$(OBJDIR)/find.o: find.c $(FIND_HDR) $(INDSTRUCT_HDR) $(INCSTRUCT_HDR)
	$(CC) $(CFLAGS) -c find.c -o $(OBJDIR)/find.o

$(OBJDIR)/sumFunctions.o: sumFunctions.c $(SUMFUNC_HDR) $(INCSTRUCT_HDR) $(PROVSTRUCT_HDR) $(INDSTRUCT_HDR)
	$(CC) $(CFLAGS) -c sumFunctions.c -o $(OBJDIR)/sumFunctions.o

$(OBJDIR)/processCommands.o: processCommands.c $(COMMAND_HDR) $(FIND_HDR) $(SUMFUNC_HDR) 
	$(CC) $(CFLAGS) -c processCommands.c -o $(OBJDIR)/processCommands.o

$(OBJDIR)/main.o: lab4main.c $(PROVINCE_HDR) $(INCOME_HDR) $(INDUSTRY_HDR) $(INCSTRUCT_HDR) $(PROVSTRUCT_HDR) \
$(INDSTRUCT_HDR) $(COMMAND_HDR)
	$(CC) $(CFLAGS) -c lab4main.c -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)
#	rmdir $(OBJDIR)