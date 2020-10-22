# @author Fabian Klopfer
# @author Jannik Bamberger

CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast -Wconversion -Wwrite-strings -Wstrict-prototypes -Werror # -DDEBUG

CHECK = ../pk_code/checkpatch.pl --terse --no-tree --no-signoff -f --ignore NEW_TYPEDEFS,AVOID_EXTERNS,GLOBAL_INITIALISERS,BLOCK_COMMENT_STYLE

.PHONY: all clean distclean test check

targets = rsh

all : $(targets)

clean:
	rm -f *.o

distclean: clean
	rm -f $(targets)

test : rsh
	timeout 5 ./rsh <testparser.txt

check :
	$(CHECK) *.c *.h

rsh : main.o parser.o builtins.o
	gcc -o $@ $^

main.o : parser.h builtins.h

%.o: %.c
	gcc -c $(CFLAGS) -c $<
