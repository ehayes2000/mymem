# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -Wall -Wextra -I src/

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Find all .c source files recursively in the src/ directory
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')

# Create a list of object files in the obj/ directory, mirroring the directory structure
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Executable name
TARGET = free_bird 

# Default target
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
