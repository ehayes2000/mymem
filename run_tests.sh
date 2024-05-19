#!/bin/bash

# Directory containing test binaries
TEST_BIN_DIR="test_bin"

# Check if the test_bin directory exists
if [ ! -d "$TEST_BIN_DIR" ]; then
  echo "Directory $TEST_BIN_DIR does not exist."
  exit 1
fi

# Run each test binary
for test_bin in "$TEST_BIN_DIR"/*; do
  if [ -x "$test_bin" ]; then
    echo "Running $test_bin"
    "$test_bin"
  else
    echo "Skipping $test_bin (not executable)"
  fi
done
