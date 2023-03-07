#include "funs.h"

int main(void)
{
    char string[MAX_LEN_OF_NUM];
    printf("The program multiplies a real number by an integer.\n"
    "You can enter anything, as long as it looks like a number,\n"
    "but length of mantissa must be equal or lover 30.\n");
    printf("%s",
           "\n                          REAL NUMBER\n"
           "               1       10        20          E power\n"
           "             +-|........|.........|..........|.....|\n"
           "Enter a real: ");
    int rc = input_str(string, MAX_LEN_OF_NUM);

    if (rc != EXIT_SUCCESS)
        return rc;

    // printf("Entered num: %s\n", string);
    char mult[MAX_LEN_OF_MULT];
    printf("%s",
           "                              FACTOR\n"
           "                   1       10        20        30\n"
           "                 +-|........|.........|.........|\n"
           "Enter an integer: ");
    rc = input_str(mult, MAX_LEN_OF_MULT);

    if (rc != EXIT_SUCCESS)
        return rc;

    // printf("Entered mult: %s\n", mult);

    rc = validate_nums(string, mult);

    if (rc != EXIT_SUCCESS)
        return rc;

    real_t real = {0};
    int_t factor = {0};
    factor.sign = 1;
    real.expsign = 1;
    real.mantsign = 1;
    int moved = 0;
    int lenafter = 0;

    rc = split_num(mult, &factor, string, &real, &lenafter);

    if (rc)
        return rc;

    int result[MAX_LEN_OF_MULT];
    process_num(factor, result, &moved, &real);
    real.mantsign *= factor.sign;

    print_answer(result, moved, &real, lenafter);

    return EXIT_SUCCESS;
}

// отрицательная большая экспонента
// не 30 символов в целом
// округление только последнего символа
 