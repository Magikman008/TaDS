#include "../inc/structs.h"
#include "../inc/mult.h"

int find_number(long long *array, int size, int num)
{
    int index = -1;
    for (int i = 0; i < size; i++)
        if (array[i] == num)
        {
            index = i;
            break;
        }

    return index;
}

void make_sparce_answer(sparce_matrix_t *matrix, sparce_vector_t *vector, sparce_vector_t *vector_std)
{
    int t_i = 0;
    int size = 0;

    for (int i = 0; i < matrix->size; i++)
    {
        if (i > 0 && matrix->rows[i] <= matrix->rows[i - 1])
            t_i++;

        // printf("%lld * %lld in %d\n", matrix->nums[i], vector->nums[find_number(vector->columns, vector->size, matrix->rows[i])], t_i);

        if (find_number(vector_std->columns, size, t_i % matrix->n) == -1)
        {
            size++;
            vector_std->columns[size] = t_i % matrix->n + 1;
            vector_std->nums[size] = 0;
        }

        for (int j = 0; j < size; j++)
            if (vector_std->columns[j] == t_i % matrix->n)
                vector_std->nums[j] = vector_std->nums[j] + matrix->nums[i] * vector->nums[find_number(vector->columns, vector->size, matrix->rows[i])];
    }
    vector_std->n = size;
    vector_std->size = size;
}

void make_answer(matrix_t *matrix, vector_t *vector, vector_t *vector_std)
{
    for (int i = 0; i < matrix->n; i++)
        for (int j = 0; j < matrix->m; j++)
            vector_std->nums[i] = vector_std->nums[i] + matrix->nums[j][i] * vector->nums[j];

    vector_std->n = matrix->n;
}
