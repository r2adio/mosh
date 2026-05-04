CC ?= cc

CPPFLAGS := -Iinclude -Iextras/unity
CFLAGS := -std=c23 -g -O2 -Wall -Wextra -Wpedantic
LDFLAGS :=

BUILD_DIR := build
CACHE_DIR := .cache
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

APP_SRC := src/main.c
MOSH_LIB_SRC := $(filter-out $(APP_SRC),$(wildcard src/*.c))
CORE_LIB_SRC := $(wildcard utils/*.c)
UNITY_SRC := extras/unity/unity.c
TEST_SRC := $(wildcard tests/*_test.c)

APP_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(APP_SRC))
MOSH_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MOSH_LIB_SRC))
CORE_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(CORE_LIB_SRC))
UNITY_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(UNITY_SRC))
TEST_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

ALL_LIB_OBJ := $(MOSH_LIB_OBJ) $(CORE_LIB_OBJ)
TARGET := $(BIN_DIR)/mosh
TEST_TARGET := $(BIN_DIR)/tests/mosh_tests

.PHONY: all run test test-build clean compile_commands install uninstall

all: $(TARGET)

run: $(TARGET)
	@echo "Running MOSH..."
	@./$(TARGET)

test: $(TEST_TARGET)
	@echo "Running Unity tests..."
	@./$(TEST_TARGET)

test-build: $(TEST_TARGET)

$(TARGET): $(APP_OBJ) $(ALL_LIB_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ) $(ALL_LIB_OBJ) $(UNITY_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

compile_commands:
	@$(MAKE) clean
	bear -- $(MAKE) all test-build

clean:
	@rm -rf $(BUILD_DIR) $(CACHE_DIR) compile_commands.json

install: $(TARGET)
	@sudo cp $(TARGET) /usr/local/bin/mosh

uninstall:
	@sudo rm -f /usr/local/bin/mosh
