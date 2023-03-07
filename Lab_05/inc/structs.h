#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "colors.h"

#define SIZE 10000

#define ERROR_STACK_OVERFLOW -1
#define ERROR_STACK_UNDERFLOW -2
#define ERROR_OUT_OF_MEMORY -3
#define ERROR_MALLOC -4
#define ERROR_BAD_INPUT -5

typedef struct queue
{
    int items[SIZE];
    int rear, front;
} queue_t;

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct node_q
{
    node_t *rear, *front;
} node_q;

#endif
