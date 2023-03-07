#include "../inc/structs.h"
#include "../inc/initialize.h"
#include "../inc/print.h"
#include "../inc/mult.h"
#include "../inc/convert.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc"
                         : "=A"(d));
    return d;
}

int main(int argc, char **argv)
{
    int rc = 0;
    sparce_matrix_t smatrix = {0};
    sparce_vector_t svector = {0};

    long long unsigned t_start, t_end;
    if ((rc = initialize(&smatrix, &svector, argc, &*argv)))
        return rc;

    print_sparce_matrix(&smatrix);
    print_sparce_vector(&svector);

    sparce_vector_t sanswer_vector = {0};
    t_start = tick();

    make_sparce_answer(&smatrix, &svector, &sanswer_vector);
    t_end = tick();
    printf("Ticks spent %llu\n", (t_end - t_start));

    print_sparce_vector(&sanswer_vector);

    matrix_t matrix = {0};
    vector_t vector = {0};

    conver_to_normal_matrix(&matrix, &smatrix);
    conver_to_normal_vector(&vector, &svector);

    print_matrix(&matrix);
    print_vector(&vector);

    vector_t answer_vector = {0};
    t_start = tick();
    make_answer(&matrix, &vector, &answer_vector);
    t_end = tick();
    printf("Ticks spent %llu\n", (t_end - t_start));
    print_vector(&answer_vector);

    return EXIT_SUCCESS;
}
