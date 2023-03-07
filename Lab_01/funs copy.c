#include "funs.h"

int input_str(char *string, int length)
{
    if (!fgets(string, length + 1, stdin))
    {
        puts("Error: Empty string");
        return ERROR_EMPTY_STRING;
    }

    size_t len = strlen(string);

    if (string[len - 1] != '\n')
    {
        puts("Error: too big str");
        return ERROR_TOO_BIG_STR;
    }

    if (string[len - 1] == '\n')
        string[--len] = '\0';

    return EXIT_SUCCESS;
}

int split_num(char *mult, int_t *factor, char *string, real_t *real, int *lenafter)
{
    // factor split
    factor->sign = 1;
    if (mult[0] == '-')
    {
        factor->sign = -1;
        for (size_t i = 1; mult[i] != '\0' || i < strlen(mult) - 1; i++)
            factor->digits[MAX_LEN_OF_MULT - strlen(mult) + i] = (int)mult[i] - 48;
    }
    else if (mult[0] == '+')
        for (size_t i = 1; mult[i] != '\0' || i < strlen(mult) - 1; i++)
            factor->digits[MAX_LEN_OF_MULT - strlen(mult) + i] = (int)mult[i] - 48;
    else
        for (size_t i = 0; mult[i] != '\0' || i < strlen(mult) - 1; i++)
            factor->digits[MAX_LEN_OF_MULT - strlen(mult) + i] = (int)mult[i] - 48;

    while (factor->digits[factor->length] == 0)
        factor->length++;

    printf("Factor arr:\n");
    for (int i = 0; i < MAX_LEN_OF_MULT; i++)
        printf("%d ", factor->digits[i]);
    puts("");

    // number split

    char beforedot[MAX_LEN_OF_MULT];
    char afterdot[MAX_LEN_OF_MULT];
    char exponent[MAX_LEN_OF_MULT];
    char mant[MAX_LEN_OF_MULT];
    int ptr = 0;

    for (int i = 0; i < MAX_LEN_OF_MULT; i++)
    {
        beforedot[i] = '\0';
        afterdot[i] = '\0';
        exponent[i] = '\0';
        mant[i] = '\0';
    }

    if (string[ptr] == '+' || string[ptr] == '-')
    {
        if (string[ptr] == '-')
            real->mantsign = -1;
        ptr++;
    }

    while (string[ptr] != 'E' && string[ptr] != 'e' && string[ptr] != '.' && string[ptr] != '\0')
    {
        beforedot[strlen(beforedot)] = string[ptr];
        ptr++;
    }

    if (string[ptr] == '.')
        ptr++;

    while (string[ptr] != 'E' && string[ptr] != 'e' && string[ptr] != '\0')
    {
        afterdot[strlen(afterdot)] = string[ptr];
        ptr++;
    }

    if (string[ptr] != 'E' || string[ptr] != 'e')
        ptr++;

    while (string[ptr] != '\0')
    {
        exponent[strlen(exponent)] = string[ptr];
        ptr++;
    }

    if (strlen(exponent) == 0)
        exponent[0] = '0';

    if (strlen(beforedot) + strlen(afterdot) > 30)
    {
        puts("Error: wrong real number");
        return ERROR_WRONG_NUM;
    }


    printf("Num by parts: %s %s %s\n", beforedot, afterdot, exponent);
    printf("Signs: %d %d\n", real->mantsign, real->expsign);

    strcat(mant, beforedot);
    regex_t reegex;
    regcomp(&reegex, "^0+$", REG_EXTENDED);
    int value = regexec(&reegex, afterdot, 0, NULL, 0);

    if (value == REG_NOMATCH)
        strcat(mant, afterdot);
    regfree(&reegex);

    // regcomp(&reegex, "^0+$", REG_EXTENDED);
    // value = regexec(&reegex, mant, 0, NULL, 0);

    // if (value != REG_NOMATCH)
    // {
    //     puts("Error: wrong number");
    //     return ERROR_WRONG_NUM;
    // }

    printf("Final mant: %s\n", mant);

    real->exp = atoi(exponent);
    real->length = strlen(mant);
    *lenafter = strlen(afterdot);

    printf("Exponent: %d\n", real->exp);

    for (int i = 0; i < MAX_LEN_OF_MULT; i++)
        real->mant[i] = 0;

    for (size_t i = 0; i < strlen(mant); i++)
        real->mant[MAX_LEN_OF_MULT - strlen(mant) + i] = (int)mant[i] - 48;

    printf("Mant array: \n");

    for (int i = 0; i < MAX_LEN_OF_MULT; i++)
        printf("%d ", real->mant[i]);

    puts("\nInput and sep completed\n");

    return EXIT_SUCCESS;
}

void print_answer(int *result, int moved, real_t *real, int lenafter)
{
    int count = 0;
    while (result[count] == 0)
        count++;

    int fromend = MAX_LEN_OF_MULT;

    while (result[fromend] == 0)
        fromend--;

    int resexp = real->exp + moved + MAX_LEN_OF_MULT - count - lenafter;

    if (resexp > 99999)
    {
        puts("Error: too big exponent");
        return;
    }

    if (count < 32)
    {
        if (real->mantsign == -1)
            printf("Answer: -0.");
        else
            printf("Answer: +0.");
        while (count < fromend)
            printf("%d", result[count++]);

        if (result[0] == 0)
            printf("%d", result[count]);

        printf("E%+d\n", resexp);
    }
    else
    {
        puts("+0E0");
    }
}

void process_num(int_t factor, int *result, int *moved, real_t *real)
{
    int carry = 0;
    int ismoved = 0;
    int lastdig = 0;

    for (int i = MAX_LEN_OF_MULT - 1; i > factor.length - 1; i--)
    {
        if (result[0] != 0)
        {
            ismoved = 1;
            lastdig = result[30];

            for (int z = 30; z > 0; z--)
                result[z] = result[z - 1];

            result[0] = carry;
            (*moved)++;
        }

        carry = 0;
        int temp[MAX_LEN_OF_MULT];

        printf("Step: %d and factor: %d\nWhat will be multiplied: \n", MAX_LEN_OF_MULT - i, factor.digits[i]);

        if (factor.digits[i] == 0)
        {
            if (ismoved == 1)
            {
                lastdig = result[29];
                for (int z = 29; z > 0; z--)
                    result[z] = result[z - 1];
                (*moved)++;
            }
        }

        for (int j = 0; j < MAX_LEN_OF_MULT; j++)
            temp[j] = 0;

        for (int j = 30; j >= MAX_LEN_OF_MULT - real->length; j--)
            temp[j - (MAX_LEN_OF_MULT - 1 - i) + *moved] = real->mant[j];

        for (int j = 0; j < MAX_LEN_OF_MULT; j++)
            printf("%d ", temp[j]);

        carry = 0;

        for (int j = 0; j < MAX_LEN_OF_MULT; j++)
            temp[j] = 0;

        int tempsum = 0;
        for (int j = 30; j - (MAX_LEN_OF_MULT - 1 - i) + *moved >= 0; j--)
        {
            tempsum = real->mant[j] * factor.digits[i] + carry;
            temp[j - (MAX_LEN_OF_MULT - 1 - i) + *moved] = tempsum % 10;
            carry = tempsum / 10;
        }

        puts("\nTempmult: ");
        for (int j = 0; j < MAX_LEN_OF_MULT; j++)
            printf("%d ", temp[j]);

        carry = 0;
        tempsum = 0;

        for (int j = 30; j >= 0; j--)
        {
            int tempsum = result[j] + temp[j] + carry;
            result[j] = tempsum % 10;
            carry = tempsum / 10;
        }
        puts("\nResult:");
        for (int j = 0; j < MAX_LEN_OF_MULT; j++)
            printf("%d ", result[j]);
        puts("\n");
    }

    if (lastdig >= 5)
        result[MAX_LEN_OF_MULT - 1] = result[MAX_LEN_OF_MULT - 1] + 1;
}

int validate_nums(char *string, char *mult)
{
    regex_t reegex;
    regcomp(&reegex, "^([+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]{0,5})?||[.][0-9]+([eE][+-]?[0-9]{0,5})?)$)", REG_EXTENDED);
    int value = regexec(&reegex, string, 0, NULL, 0);

    if (value != 0)
    {
        puts("Error: number doesn`t match regular expression");
        return ERROR_WRONG_NUM;
    }

    regfree(&reegex);

    regcomp(&reegex, "^([+-]?[0-9]+)$", REG_EXTENDED);
    value = regexec(&reegex, mult, 0, NULL, 0);

    if (value != 0)
    {
        puts("Error: number doesn`t match regular expression");
        return ERROR_WRONG_MULT;
    }

    regfree(&reegex);
    return EXIT_SUCCESS;
}
