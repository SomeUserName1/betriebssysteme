# @author Fabian Klopfer
# @author Jannik Bamberger

CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast -Wconversion -Wwrite-strings -Wstrict-prototypes -Werror # -DDEBUG

CHECK = ../../pk_code/checkpatch.pl --terse --no-tree --no-signoff -f --ignore NEW_TYPEDEFS,AVOID_EXTERNS,GLOBAL_INITIALISERS,BLOCK_COMMENT_STYLE

.PHONY: all clean distclean test check

all : rsh

clean:
	rm -f *.o

distclean: clean
	rm -f rsh

check :
	$(CHECK) *.c *.h

rsh: main.o builtins.o parser.o
	gcc -o $@ $^

%.o: %.c
	gcc -c $(CFLAGS) -c $<

main.o : builtins.h parser.h
parser.o : parser.h
