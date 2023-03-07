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

typedef struct tree
{
    char word[100];
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node_t;

#endif
