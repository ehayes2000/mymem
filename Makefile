# Compiler
CC = gcc

# Compiler flags
CFLAGS = -std=c11 -Wall -Wextra -I src/

# Directories
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
SRC_OBJ_DIR = $(OBJ_DIR)/src
TEST_OBJ_DIR = $(OBJ_DIR)/test
TEST_BIN_DIR = test_bin

# Source and test source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Object files for source
SRC_OBJ = $(SRC_FILES:$(SRC_DIR)/%.c=$(SRC_OBJ_DIR)/%.o)

# Main program executable
TARGET = $(SRC_OBJ_DIR)/mymem

all: $(TARGET)

# Rule to compile and link the main executable
$(TARGET): $(SRC_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile source .c files into .o files
$(SRC_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

EXCLUDE_OBJ = $(SRC_OBJ_DIR)/main.o  # Specify the object file to exclude

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(filter-out $(EXCLUDE_OBJ), $(SRC_OBJ))
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Test target to build all test binaries
test: $(TEST_FILES:$(TEST_DIR)/%.c=$(TEST_BIN_DIR)/%)

run-tests: test
	@./run_tests.sh

clean:
	@rm -rf $(OBJ_DIR) $(TEST_BIN_DIR)
