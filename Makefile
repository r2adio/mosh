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

APP_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(APP_SRC))
MOSH_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(MOSH_LIB_SRC))
CORE_LIB_OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(CORE_LIB_SRC))

ALL_LIB_OBJ := $(MOSH_LIB_OBJ) $(CORE_LIB_OBJ)
TARGET := $(BIN_DIR)/mosh
.PHONY: all run clean compile_commands install uninstall

all: $(TARGET)

run: $(TARGET)
	@echo "Running MOSH..."
	@./$(TARGET)

$(TARGET): $(APP_OBJ) $(ALL_LIB_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

compile_commands:
	@$(MAKE) clean
	bear -- $(MAKE) all

clean:
	@rm -rf $(BUILD_DIR) $(CACHE_DIR) compile_commands.json

install: $(TARGET)
	@sudo cp $(TARGET) /usr/local/bin/mosh

uninstall:
	@sudo rm -f /usr/local/bin/mosh
