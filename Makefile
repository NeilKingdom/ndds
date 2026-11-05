CC := gcc
PROFILE ?= DEBUG

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build/obj
TGT_DIR := build/target

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CFLAGS_DEBUG := -ggdb -O0 -fno-builtin -DDEBUG
CFLAGS_RELEASE := -O2

INCLUDES += -I$(INC_DIR)
CFLAGS += $(CFLAGS_$(PROFILE)) -std=c99 -Wall -Wextra
LDFLAGS += -lcheck

BIN := $(TGT_DIR)/ndds

# Default goal
all: $(BIN)

# Clean obj files and binary
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(TGT_DIR)/*

# Clean -> build
rebuild: clean all

# Create dependent build directories
prebuild:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TGT_DIR)

# Binary goal
$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Intermediate obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | prebuild
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.PHONY: all clean rebuild prebuild
