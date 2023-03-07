#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "colors.h"

#define MULTIPLIER 2
#define INIT_SIZE 10

#define ERROR_STACK_OVERFLOW -1
#define ERROR_STACK_UNDERFLOW -2
#define ERROR_OUT_OF_MEMORY -3
#define ERROR_MALLOC -4
#define ERROR_BAD_INPUT -5

typedef struct
{
    int *data;
    size_t size;
    size_t top;
} stack_t;

typedef struct node_t
{
    int value;
    struct node_t *next;
} node_t;

#endif
