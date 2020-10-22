# @author Fabian Klopfer
# @author Jannik Bamberger

CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
	-Wconversion -Wwrite-strings -Wstrict-prototypes


sources = $(wildcard *.c)
objects = $(patsubst %.c,%.o,$(sources))
checks = $(addsuffix .check, $(sources) $(wildcard *.h))

.PHONY: all clean precommit check $(checks)
all:	rsh
clean:
	rm -f rsh $(objects)

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

rsh:	$(filter-out testList.o, $(objects))
	gcc -o $@ $(filter-out testList.o, $(objects))

%.o:	%.c
	gcc -c $(CFLAGS) -c $<

rsh.o:		rsh.h builtin.h
builtin.o:	builtin.h