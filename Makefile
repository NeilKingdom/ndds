CC ?= gcc
PROFILE ?= DEBUG

CCFLAGS_DEBUG := -ggdb -O0 -fno-builtin -DDEBUG
CCFLAGS_RELEASE := -Ofast

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CCFLAGS += $(CCFLAGS_$(PROFILE)) -I$(INC_DIR) -Wall -Wextra -std=c99
LDFLAGS += -lc -lcheck

BIN := ndds

all: prebuild $(BIN)

prebuild:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BIN) $(OBJ_DIR)/*.o

$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: all prebuild clean
