CC := gcc
CFLAGS := -Isrc -std=c11 -Wall
LDFLAGS := -lncurses
BINDIR := bin
OBJDIR := obj
SRCDIR := src
TARGET := Roguelike

# Use wildcard function to compile all .c files in the src directory
SOURCES=$(wildcard $(SRCDIR)/*.c)
# Convert the *.c filenames to *.o to give a list of object files to build
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all test clean

# Default target
all: $(BINDIR)/$(TARGET)

# Link the program
$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile all .c to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# I should change this later to call gdb debugging
test: CFLAGS += -DTESTING
test: $(BINDIR)/$(TARGET)

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/* src/test

run: all
	./$(BINDIR)/$(TARGET)
