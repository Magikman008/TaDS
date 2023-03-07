#ifndef SORT_H
#define SORT_H

#include "structs.h"

unsigned long long microseconds_now(void);
void sort_table(student_t *students, int count);
void sort_keytable(keystudent_t *keystudents, int count);
int comparator_keytable(const void *val1, const void *val2);
int comparator_table(const void *val1, const void *val2);

#endif
