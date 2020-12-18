CFLAGS   = -std=c11 -g -Wall -Wextra -Wpedantic -Werror \
		   -fsanitize=address -fsanitize=undefined

SRC      = $(wildcard *.c)
OBJ      = $(SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	cc -o $@ $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

