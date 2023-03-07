#ifndef PRINT_H
#define PRINT_H

#include "structs.h"

void print_field(student_t student, int id);
void print_table(student_t *students, int count);
void print_table_filter(student_t *students, int count);
void print_keytable(keystudent_t *keystudents, int count);
void print_table_by_key(student_t *students, keystudent_t *keystudents, int count);
void print_table_using_keytable(student_t *students, keystudent_t *keystudents, int count);

#endif
