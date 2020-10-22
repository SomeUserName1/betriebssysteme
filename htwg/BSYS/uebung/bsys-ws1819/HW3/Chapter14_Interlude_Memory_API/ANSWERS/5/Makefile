# Makefile

# Command variables
CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -std=c99 -g
CPPFLAGS = -I.
RM = rm -f

# Auxiliary variables
TARGET = array_of_integers
OBJECTS = array_of_integers.o
SOURCES = $(TARGET).c $(OBJECTS: .o=.c)


# Pattern rules
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Default targets
.PHONY: all clean
all: $(TARGET)
clean:
	$(RM) $(TARGET) $(OBJECTS)

# Targets for program creation
$(TARGET): $(TARGET).o $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
