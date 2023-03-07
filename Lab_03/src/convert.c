#include "../inc/structs.h"

void conver_to_normal_matrix(matrix_t *matrix, sparce_matrix_t *smatrix)
{
    for (int i = 0; i < smatrix->n; i++)
        for (int j = 0; j < smatrix->m; j++)
            matrix->nums[i][j] = 0;

    for (int i = 0; i < smatrix->n; i++)
    {
        for (int j = smatrix->columns[i]; j < smatrix->columns[i + 1]; j++)
            matrix->nums[smatrix->rows[j]][i] = smatrix->nums[j];
    }

    matrix->m = smatrix->m;
    matrix->n = smatrix->n;
}

void conver_to_normal_vector(vector_t *vector, sparce_vector_t *svector)
{
    for (int i = 0; i < svector->n; i++)
            vector->nums[i] = 0;

    for (int i = 0; i < svector->n; i++)
    {
        vector->nums[svector->columns[i]] = svector->nums[i];
    }

    vector->n = svector->n;
}
