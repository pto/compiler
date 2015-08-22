CCFLAGS=-std=ANSI -Wall -Wextra -Wpedantic

OBJS=main.o lex.o name.o

all: retval args

retval: retval.o $(OBJS)

args: args.o $(OBJS)

main.o: retval.h trace.h

lex.o: lex.h

name.o: name.h trace.h

retval.o: retval.h name.h lex.h

args.o: args.h name.h lex.h

clean:
	rm $(OBJS) retval.o args.o
