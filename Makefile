# a sample Makefile


# compiling rules

# WARNING: *must* have a tab before each definition
main: lab4main.c
	clang -Wall lab4main.c -o main

clean:
	rm -f main
#	rmdir $(OBJDIR)
