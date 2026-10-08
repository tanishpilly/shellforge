CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -Iinclude
DFLAGS = -g -DDEBUG

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/shell.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/builtins.c

OBJS = $(SRCS:.c=.o)

TARGET = shellforge

.PHONY: all clean debug test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DFLAGS)
debug: clean all

test: all
	@echo "=== Running Integration Tests ==="
	bash $(TEST_DIR)/test_shell.sh

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) *.tmp *.log output.txt test.txt
