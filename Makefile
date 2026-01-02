# Makefile for mosh

CC := cc
CFLAGS := -std=c23 -g -O2 -Wall -Wextra -Wpedantic -Werror -Iinclude
LDFLAGS :=

# Directories
BUILD_DIR := build
CACHE_DIR := .cache
OBJ_DIR := $(BUILD_DIR)/obj
TARGET_DIR := $(BUILD_DIR)/bin

# Source Files:

# Main application sources
APP_SRC := src/main.c
# Library sources that are part of the main application logic
MOSH_LIB_SRC := src/builtin.c src/parser.c
# Core utility library sources
CORE_LIB_SRC := lib_/getenv_.c lib_/strcmp_.c lib_/strlen_.c

# Test sources
TEST_SRC := test/builtin_test.c test/lib_test.c

# Object Files:

# Generate object file paths by replacing .c with .o and prepending the object directory
APP_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(APP_SRC))
MOSH_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MOSH_LIB_SRC))
CORE_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(CORE_LIB_SRC))
TEST_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# All library objects needed for linking
ALL_LIB_OBJS := $(MOSH_LIB_OBJ) $(CORE_LIB_OBJ)

# Targets:
TARGET := $(TARGET_DIR)/mosh
# TEST_TARGETS := $(patsubst %.c,$(TARGET_DIR)/%,$(TEST_SRC))
TEST_TARGETS := $(patsubst test/%.c,$(TARGET_DIR)/test/%,$(TEST_SRC))


# Phony targets are actions, not files
.PHONY: all clean test

# Main Build Rules:

# Default target: build the main application
all: $(TARGET)

# Rule to link the main executable
$(TARGET): $(APP_OBJ) $(ALL_LIB_OBJS)
	@echo "Linking main executable: $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Test Build Rules:

# The 'test' target depends on the test executables and then runs them
test: $(TEST_TARGETS)
	@echo "--- Running Tests ---"
	@for test_exe in $(TEST_TARGETS); do \
		echo "=> Running $$test_exe"; \
		./$$test_exe; \
	done
	@echo "--- Tests Finished ---"

# Generic rule to link any test executable
# A test executable depends on its own object file plus all library object files
$(TARGET_DIR)/test/%: $(OBJ_DIR)/test/%.o $(ALL_LIB_OBJS)
	@echo "Linking test executable: $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule to compile any .c file from its source location to the object directory
$(OBJ_DIR)/%.o: %.c
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up all build artifacts
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(CACHE_DIR)
