#ifndef INIT_H
#define INIT_H

#include "structs.h"

void get_field(char *line, student_t *student);
int get_table(student_t *students, int *count);
void make_keytable(student_t *students, keystudent_t *keystudents, int count);

#endif
