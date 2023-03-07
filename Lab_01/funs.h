#ifndef _FUNS_H_
#define _FUNS_H_

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LEN_OF_NUM 40 + 1
#define MAX_LEN_OF_MULT 30 + 1

#define ERROR_EMPTY_STRING 1
#define ERROR_TOO_BIG_WORD 2
#define ERROR_WRONG_NUM 3
#define ERROR_WRONG_MULT 4
#define ERROR_TOO_BIG_STR 5

struct real_t
{
    int mantsign;
    int mant[MAX_LEN_OF_MULT];
    int expsign;
    int exp;
    int length;
};

struct int_t
{
    int sign;
    int digits[MAX_LEN_OF_MULT];
    int length;
};

typedef struct real_t real_t;
typedef struct int_t int_t;

int input_str(char *string, int length);
int split_num(char *mult, int_t *factor, char *string, real_t *real, int *lenafter);
void print_answer(int *result, int moved, real_t *real, int lenafter);
void process_num(int_t factor, int *result, int *moved, real_t *real);
int validate_nums(char *string, char *mult);

#endif
