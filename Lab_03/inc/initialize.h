#ifndef INIT_H
#define INIT_H

#include "../inc/structs.h"

int initialize(sparce_matrix_t *smatrix, sparce_vector_t *svector, int argc, char **argv);
int initialize_matrix(sparce_matrix_t *matrix);
int initialize_vector(sparce_vector_t *vector);
int initialize_matrix_from_file(sparce_matrix_t *matrix, FILE *src);
int initialize_vector_from_file(sparce_vector_t *vector, FILE *src);

#endif
