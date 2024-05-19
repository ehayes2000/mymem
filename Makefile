# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -Wall -Wextra -I src/

# Source and object directories
SRC_DIR = src
TEST_DIR = test
TEST_BIN_DIR = test_bin
OBJ_DIR = obj

# Find all .c source files recursively in the src/ directory
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.c)

# Create a list of object files in the obj/ directory, mirroring the directory structure
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TEST_BIN_FILES = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRC_FILES))

# Executable name
TARGET = mymem

# Default target
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN_FILES)

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@
# Clean up build files
run-tests: test
	./run_tests.sh
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_BIN_DIR)

# Phony targets
.PHONY: all clean
