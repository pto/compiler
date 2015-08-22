CCFLAGS=-std=ANSI -Wall -Wextra -Wpedantic

OBJS=main.o lex.o name.o

retval: retval.o $(OBJS)

main.o name.o retval.o: trace.h

clean:
	rm $(OBJS) retval.o
