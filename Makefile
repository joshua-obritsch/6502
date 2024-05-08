# Directories
BIN_DIR      := ./.bin
OBJ_DIR      := ./.obj
OBJ_TEST_DIR := ./.obj/test
INCLUDE_DIR  := ./include
SRC_DIR      := ./src
TEST_DIR     := ./test

# Files
SRC_FILES    := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJECTS  := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_FILES   := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c, $(OBJ_TEST_DIR)/%.o, $(TEST_FILES))

# Compiler settings
CC     := gcc
CFLAGS := -I$(INCLUDE_DIR) -I$(SRC_DIR)

# Tests
test: build $(OBJ_TEST_DIR)/$(TEST_OBJECTS)
	@$(CC) $(SRC_OBJECTS) $(TEST_OBJECTS) -lm -o $(BIN_DIR)/run_tests
	@$(BIN_DIR)/run_tests $(ARGS)

$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@$(CC) $(CFLAGS) -I./test -c $< -o $@

# Source code
build: setup $(OBJ_DIR)/$(SRC_OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

setup:
	@mkdir -p $(OBJ_DIR) $(OBJ_TEST_DIR) $(BIN_DIR)

# Clean up
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: build clean test
