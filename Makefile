# Makefile for mosh

CC := cc
CFLAGS := -std=c23 -g -O2 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS :=

# Directories
BUILD_DIR := build
CACHE_DIR := .cache
OBJ_DIR := $(BUILD_DIR)/obj
TARGET_DIR := $(BUILD_DIR)/bin
COMPILE_COMMANDS_DIR := $(BUILD_DIR)/compile_commands

# Source Files:

# Main application sources
APP_SRC := src/main.c
# Library sources that are part of the main application logic
MOSH_LIB_SRC := src/builtin.c src/parser.c
# Core utility library sources
CORE_LIB_SRC := utils/getenv_.c

# Test sources
TEST_SRC := test/builtin_test.c

# Object Files:

# Generate object file paths by replacing .c with .o and prepending the object directory
APP_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(APP_SRC))
MOSH_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MOSH_LIB_SRC))
CORE_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(CORE_LIB_SRC))
TEST_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# All object files for compile_commands.json
ALL_OBJS_FOR_IDE := $(APP_OBJ) $(MOSH_LIB_OBJ) $(CORE_LIB_OBJ) $(TEST_OBJ)

# All library objects needed for linking
ALL_LIB_OBJS := $(MOSH_LIB_OBJ) $(CORE_LIB_OBJ)

# final executable
TARGET := $(TARGET_DIR)/mosh
# using patsubst to replace .c with .o for the test executables
TEST_TARGETS := $(patsubst test/%.c,$(TARGET_DIR)/test/%,$(TEST_SRC))


.PHONY: all clean test compile_commands

# Main Build Rules:
# =================
all: $(TARGET) # to make all, first make $(TARGET)

# Rule to link the main executable
$(TARGET): $(APP_OBJ) $(ALL_LIB_OBJS) # to build target(build/bin/mosh), first need all the object files
	@echo "Linking main executable: $@" # $@ -> target (the name of the target)
	@mkdir -p $(dir $@) # $(dir $@) -> the directory part of the target (build/bin)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) # $^ -> all the object files (prerequisites)

# Test Build Rules:
# The 'test' target depends on the test executables and then runs them
test: $(TEST_TARGETS)
	@echo "\n--- Running Tests ---"
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

# IDE tooling rule
compile_commands: $(ALL_OBJS_FOR_IDE)
	@echo "Generating compile_commands.json..."
	@echo "[" > $(BUILD_DIR)/compile_commands.json
	@sh -c 'find $(COMPILE_COMMANDS_DIR) -name "*.json" -exec cat {} + | paste -sd "," -' >> $(BUILD_DIR)/compile_commands.json
	@echo "]" >> $(BUILD_DIR)/compile_commands.json

# Generic rule to compile any .c file from its source location to the object directory
# This rule also generates a JSON compilation database fragment.
$(OBJ_DIR)/%.o: %.c
	@echo "Compiling: $<" # $< -> the first prerequisite (the source file)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@mkdir -p $(dir $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json))
	@printf '{\n' > $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json)
	@printf '  "directory": "%s",\n' "$(CURDIR)" >> $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json)
	@printf '  "command": "%s",\n' "$(CC) $(CFLAGS) -c $< -o $@" >> $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json)
	@printf '  "file": "%s"\n' "$<" >> $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json)
	@printf '}\n' >> $(addprefix $(COMPILE_COMMANDS_DIR)/, $<.json)


# Rule to clean up all build artifacts
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(CACHE_DIR)
