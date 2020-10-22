# Makefile

# Command variables
CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -std=c99
CPPFLAGS = -I.
RM = rm -f

# Auxiliary variables
TARGET = fork3
OBJECTS = fork3.o
SOURCES = $(TARGET).c $(OBJECTS: .o=.c)


# Pattern rules
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Default targets
.PHONY: all clean
all: $(TARGET)
clean:
	$(RM) $(TARGET) $(TARGET).o $(OBJECTS)

# Targets for program creation
$(TARGET): $(TARGET).o $(OBJECTS)
	$(CC) $^ -o $@
