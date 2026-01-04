# Compiler and flags
CC = gcc
CFLAGS = -O3 -std=c99 -Wall -Wextra -march=native -Iinclude

# Target executable inside build/
TARGET = build/combogen

# Source files
SRC = $(wildcard src/*.c)

# Object files inside build/obj/
OBJ_DIR = build/obj
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Ensure build directories exist
$(shell mkdir -p $(OBJ_DIR))

# Default target
all: $(TARGET)

# Link executable from objects
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compile .c -> .o in obj directory
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf build

.PHONY: all clean
