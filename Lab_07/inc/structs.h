#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "colors.h"

#define MULTIPLIER 2
#define CAPACITY 53

#define ERROR_BAD_FILE -1
#define ERROR_FILE_CLOSE -3
#define ERROR_BAD_INPUT -5

extern int mult;

typedef struct tree
{
    char word[100];
    int key;
    unsigned char height;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} node_t;

typedef struct item
{
    char word[100];
    int key;
    struct item *next;
    struct item *parent;
} item_t;

typedef struct itemc
{
    char word[100];
    int key;
} itemc_t;

#endif
