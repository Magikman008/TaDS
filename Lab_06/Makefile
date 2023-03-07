.PHONY: clean debug cleano func key
.NOTPARALLEL: debug func key

CC = gcc
CFLAGS :=  -Wall -Werror -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
UFLAGS := -lcheck
DFLAGS :=

ifeq ($(shell hostname), Violet)
	UFLAGS += -lm -lsubunit
endif

ifeq ($(shell uname), Linux)
	UFLAGS += -lpthread -lrt
endif

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src
UNIT_DIR = ./unit_tests

MAIN := main.c
OMAIN := $(MAIN:.c=.o)
FUNCS := tree.c
OFUNCS := $(FUNCS:.c=.o)

SRCS := $(addprefix $(SRC_DIR)/,$(MAIN) $(FUNCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(OMAIN) $(OFUNCS))

EXEC_APP := app.exe
EXEC_DEBUG := debug.exe

$(EXEC_APP): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(DFLAGS) -o $@

key : CFLAGS += -DDEBUG
key : cleano
key : $(EXEC_DEBUG)

debug : CFLAGS += -g3 --coverage
debug : cleano
debug : DFLAGS += --coverage
debug : $(EXEC_APP)

$(EXEC_DEBUG): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

func:
	./collect_coverage.sh

clean:
	rm -f -r $(OBJ_DIR) *.exe *.gcov ./func_tests/scripts/*.txt

cleano:
	rm -f -r $(OBJ_DIR)

include $(wildcard $(addsuffix /*.d, $(OBJ_DIR)))
