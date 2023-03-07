#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "colors.h"

#define MULTIPLIER 2
#define INIT_SIZE 10

#define ERROR_BAD_FILE -1
#define ERROR_FILE_CLOSE -3
#define ERROR_BAD_INPUT -5

typedef struct
{
    int **matrix;
    int vertices;
} graph_t;

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
