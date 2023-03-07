.PHONY: clean debug cleano

CC = gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src
UNIT_DIR = ./unit_tests

SRCS := edit.c main.c initialize.c print.c sort.c
OBJS := edit.o main.o initialize.o print.o sort.o

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))

EXEC_APP := app.exe
EXEC_DEBUG := debug.exe

$(EXEC_APP): $(OBJ_DIR) | $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

$(EXEC_DEBUG): $(OBJ_DIR) | $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

debug : CFLAGS += -DDEBUG
debug : cleano
debug : $(EXEC_DEBUG)

clean:
	rm -rf $(OBJ_DIR) *.exe *.gcov

cleano:
	rm -f -r $(OBJ_DIR)
