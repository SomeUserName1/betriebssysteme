# @author Fabian Klopfer
# @author Jannik Bamberger

CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast -Wconversion -Wwrite-strings -Wstrict-prototypes -Werror # -DDEBUG

CHECK = ../pk_code/checkpatch.pl --terse --no-tree --no-signoff -f --ignore NEW_TYPEDEFS,AVOID_EXTERNS,GLOBAL_INITIALISERS,BLOCK_COMMENT_STYLE

.PHONY: all clean distclean test check

all : archive

clean:
	rm -f archive.o

distclean: clean
	rm -f archive

check :
	$(CHECK) archive.c

archive: archive.o
	gcc -o $@ $^

archive.o: archive.c
	gcc -c $(CFLAGS) -c $<
