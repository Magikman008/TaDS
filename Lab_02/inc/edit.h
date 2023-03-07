#ifndef EDIT_H
#define EDIT_H

#include "structs.h"

int add_field(student_t *students, int *count);
int remove_field(student_t *students, int *count);
int save_table(student_t *students, int count);

#endif
