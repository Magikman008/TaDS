#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "colors.h"

#define MAX_NUMBERS 100000
#define MAX_SIDE_LEN 350

#define ERROR_BAD_INPUT -1
#define ERROR_FILE_OPEN -2
#define ERROR_FILE_CLOSE -3

typedef struct
{
    long long nums[MAX_NUMBERS];
    long long rows[MAX_NUMBERS];
    long long columns[MAX_SIDE_LEN];
    int n;
    int m;
    int size;
} sparce_matrix_t;

typedef struct
{
    long long nums[MAX_NUMBERS];
    long long columns[MAX_SIDE_LEN];
    int n;
    int size;
} sparce_vector_t;

typedef struct
{
    long long nums[MAX_SIDE_LEN][MAX_SIDE_LEN];
    int n;
    int m;
} matrix_t;

typedef struct
{
    long long nums[MAX_NUMBERS];
    int n;
} vector_t;

#endif
