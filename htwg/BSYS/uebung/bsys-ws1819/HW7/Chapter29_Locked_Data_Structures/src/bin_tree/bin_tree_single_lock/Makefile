# Makefile

# Command variables
CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -std=c99 -pthread -g
CPPFLAGS = -I.
RM = rm -f

# Auxiliary variables
TARGET = bin_tree
OBJECTS = bin_tree.o
SOURCES = $(TARGET).c $(OBJECTS: .o=.c)
HEADERS = $(OBJECTS:.o=.h)


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
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@
