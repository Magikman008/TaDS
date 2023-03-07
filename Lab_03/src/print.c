#include "../inc/structs.h"
#include "../inc/print.h"

void print_sparce_matrix(sparce_matrix_t *matrix)
{
    puts(gr "Sparce matrix is: " res);
    for (int i = 0; i < matrix->size; i++)
        printf("Elem: %lld, row: %lld\n", matrix->nums[i], matrix->rows[i]);
}

void print_sparce_vector(sparce_vector_t *vector)
{
    puts(gr "Sparce vector is: " res);
    for (int i = 0; i < vector->size; i++)
        printf("Elem: %lld, column: %lld\n", vector->nums[i], vector->columns[i]);
}

void print_matrix(matrix_t *matrix)
{
    puts(gr "Matrix is: " res);
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0; j < matrix->n; j++)
            printf("%lld ", matrix->nums[i][j]);
        puts("");
    }
}

void print_vector(vector_t *vector)
{
    puts(gr "Vector is: " res);
    for (int i = 0; i < vector->n; i++)
        printf("%lld ", vector->nums[i]);
    puts("");
}
