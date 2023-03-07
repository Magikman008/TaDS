#ifndef FUNS_H
#define FUNS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "colors.h"

#define MAX_LEN_OF_STR 50
#define MAX_NUM_OF_STUDENTS 50

#define ERROR_BAD_FCLOSE 1
#define ERROR_EMPTY_TABLE 2
#define ERROR_BAD_INPUT 3
#define ERROR_EMPTY_STRING 4
#define ERROR_TOO_BIG_STR 5
#define ERROR_MAX_TABLE_SIZE 6

struct date_t
{
    int day;
    int month;
    int year;
};

struct house_t
{
    char street[MAX_LEN_OF_STR * 2 + 2];
    int num_house;
    int num_flat;
};

struct hostel_t
{
    int num_hostel;
    int num_room;
};

typedef struct house_t house_t;
typedef struct hostel_t hostel_t;
typedef struct date_t date_t;

union residence_t
{
    house_t house;
    hostel_t hostel;
};

typedef union residence_t residence_t;

struct student_t
{
    char surname[MAX_LEN_OF_STR+2];
    char name[MAX_LEN_OF_STR+2];
    int sex;
    int group;
    int age;
    double average;
    date_t date;
    int where;
    residence_t residence;
};

typedef struct student_t student_t;

struct keystudent_t
{
    int id;
    int age;
};

typedef struct keystudent_t keystudent_t;

#endif
