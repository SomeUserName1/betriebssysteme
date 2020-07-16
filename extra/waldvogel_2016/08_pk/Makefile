# @author Fabian Klopfer
# @author Jannik Bamberger

CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
	-Wconversion -Wwrite-strings -Wstrict-prototypes



sources = $(wildcard *.c)
objects = $(patsubst %.c,%.o,$(sources))

checks = $(addsuffix .check, $(sources) $(wildcard *.h))

.PHONY: all clean precommit html cleandoc check $(checks)
all:	calc
clean:
	rm -f calc test $(objects)

check: test
	@echo "Running Test:"
	@./test

test: testList.o list.o
	gcc -o $@ $^

html:
	doxygen docs.cfg

cleandoc:
	rm -rf html

precommit: $(checks)
	@echo "\nprecommit checks finished\n"

$(checks):
	@../pk_code/checkpatch.pl \
		--no-tree --no-signoff -f --ignore \
		NEW_TYPEDEFS,AVOID_EXTERNS,GLOBAL_INITIALISERS,BLOCK_COMMENT_STYLE \
		$(basename $@)
	@if ! grep -L "Fabian Klopfer" $(basename $@);\
		then echo '\033[0;31m $(basename $@) missing name\033[0m'; fi
	@if ! grep -L "Jannik Bamberger" $(basename $@);\
		then echo '\033[0;31m $(basename $@) missing name\033[0m'; fi

calc:	$(filter-out testList.o, $(objects))
	gcc -o $@ $(filter-out testList.o, $(objects))

%.o:	%.c
	gcc -c $(CFLAGS) -c $<

calc.o:		list.h token.h
list.o:		list.h
token.o:	token.h
testList.o:	list.h
