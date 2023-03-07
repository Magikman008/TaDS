#include "../inc/structs.h"
#include "../inc/initialize.h"

int initialize(sparce_matrix_t *smatrix, sparce_vector_t *svector, int argc, char **argv)
{
    int rc = 0;
    if (argc == 2)
    {
        FILE *src;
        if (!(src = fopen(argv[1], "r")))
        {
            puts("Error open file. Please enter all data manualy");

            if ((rc = initialize_matrix(smatrix)))
                return rc;

            if ((rc = initialize_vector(svector)))
                return rc;
        }
        else
        {
            if ((rc = initialize_matrix_from_file(smatrix, src)))
                return rc;

            if ((rc = initialize_vector_from_file(svector, src)))
                return rc;

            if (fclose(src))
                return ERROR_FILE_CLOSE;
        }
    }
    else
    {
        if ((rc = initialize_matrix(smatrix)))
            return rc;

        if ((rc = initialize_vector(svector)))
            return rc;
    }

    if (smatrix->m != svector->n)
    {
        puts("Size of vector and rows in matrix must be equal");
        return ERROR_BAD_INPUT;
    }

    return EXIT_SUCCESS;
}
int initialize_matrix(sparce_matrix_t *matrix)
{
    printf("Enter number of colums: ");

    if (scanf("%d", &matrix->n) != 1)
    {
        puts(red "This is not a number" res);
        return ERROR_BAD_INPUT;
    }

    if (matrix->n > 10000)
    {
        puts(red "Number of columns must be under or equal 10000" res);
        return ERROR_BAD_INPUT;
    }

    printf("Enter number of rows: ");

    if (scanf("%d", &matrix->m) != 1)
    {
        puts(red "This is not a number" res);
        return ERROR_BAD_INPUT;
    }

    if (matrix->m > 10000)
    {
        puts(red "Number of rows must be under or equal 10000" res);
        return ERROR_BAD_INPUT;
    }

    int temp_i = 0;
    matrix->columns[0] = 0;

    for (int i = 0; i < matrix->n; i++)
    {
        int temp = 0;
        printf("Input number of non-zero numbers in %d column: ", i);

        if (scanf("%d", &temp) != 1)
        {
            puts(red "This is not a number" res);
            return ERROR_BAD_INPUT;
        }

        printf("Input number and column index for %d times", temp);
        for (int j = 0; j < temp; j++)
        {
            if (scanf("%lld %lld", &matrix->nums[temp_i], &matrix->rows[temp_i]) != 2)
            {
                puts(red "This is not a number" res);
                return ERROR_BAD_INPUT;
            }

            if (matrix->nums[temp_i] == 0)
            {
                puts(red "This is zero" res);
                return ERROR_BAD_INPUT;
            }

            temp_i++;
        }

        matrix->columns[i + 1] = temp_i;
    }

    matrix->size = temp_i;

    puts(yel "Matrix was succesfully initialized" res);
    return EXIT_SUCCESS;
}

int initialize_vector(sparce_vector_t *vector)
{
    printf("Enter number of colums: ");

    if (scanf("%d", &vector->n) != 1)
    {
        puts("This is not a number");
        return ERROR_BAD_INPUT;
    }

    int temp = 0;
    printf("Input number of non-zero numbers: ");

    if (scanf("%d", &temp) != 1)
    {
        puts("This is not a number");
        return ERROR_BAD_INPUT;
    }

    printf("Input number and column index for %d times", temp);
    for (int i = 0; i < temp; i++)
    {
        if (scanf("%lld %lld", &vector->nums[i], &vector->columns[i]) != 2)
        {
            puts("This is not a number");
            return ERROR_BAD_INPUT;
        }

        if (vector->nums[i] == 0)
        {
            puts(red "This is zero" res);
            return ERROR_BAD_INPUT;
        }
    }

    vector->size = temp;

    puts(yel "Vector was succesfully initialized" res);
    return EXIT_SUCCESS;
}

#include "../inc/structs.h"
#include "../inc/initialize.h"

int initialize_matrix_from_file(sparce_matrix_t *matrix, FILE *src)
{
    if (fscanf(src, "%d", &matrix->n) != 1)
    {
        puts(red "Number of columns not a number" res);
        return ERROR_BAD_INPUT;
    }

    if (matrix->n > 10000)
    {
        puts(red "Number of columns must be under or equal 10000" res);
        return ERROR_BAD_INPUT;
    }

    if (fscanf(src, "%d", &matrix->m) != 1)
    {
        puts(red "Number of rows not a number" res);
        return ERROR_BAD_INPUT;
    }

    if (matrix->m > 10000)
    {
        puts(red "Number of rows must be under or equal 10000" res);
        return ERROR_BAD_INPUT;
    }

    int temp_i = 0;
    matrix->columns[0] = 0;

    for (int i = 0; i < matrix->n; i++)
    {
        int temp = 0;

        if (fscanf(src, "%d", &temp) != 1)
        {
            puts(red "Number of non-zero numbers in row not a number" res);
            return ERROR_BAD_INPUT;
        }

        for (int j = 0; j < temp; j++)
        {
            if (fscanf(src, "%lld %lld", &matrix->nums[temp_i], &matrix->rows[temp_i]) != 2)
            {
                puts(red "Number of column or non-zero number not a number" res);
                return ERROR_BAD_INPUT;
            }

            if (matrix->nums[temp_i] == 0)
            {
                puts(red "Non-zero number in row must be not a zero" res);
                return ERROR_BAD_INPUT;
            }

            temp_i++;
        }

        matrix->columns[i + 1] = temp_i;
    }

    matrix->size = temp_i;

    puts(yel "Matrix was succesfully initialized" res);
    return EXIT_SUCCESS;
}

int initialize_vector_from_file(sparce_vector_t *vector, FILE *src)
{
    if (fscanf(src, "%d", &vector->n) != 1)
    {
        puts(red "Number of columns not a number" res);
        return ERROR_BAD_INPUT;
    }

    int temp = 0;

    if (fscanf(src, "%d", &temp) != 1)
    {
        puts(red "Number of non-zero numbers in row not a number" res);
        return ERROR_BAD_INPUT;
    }

    for (int i = 0; i < temp; i++)
    {
        if (fscanf(src, "%lld %lld", &vector->nums[i], &vector->columns[i]) != 2)
        {
            puts(red "Number of column or non-zero number not a number" res);
            return ERROR_BAD_INPUT;
        }

        if (vector->nums[i] == 0)
        {
            puts(red "Non-zero number in row must be not a zero" res);
            return ERROR_BAD_INPUT;
        }
    }

    vector->size = temp;

    puts(yel "Vector was succesfully initialized" res);
    return EXIT_SUCCESS;
}
