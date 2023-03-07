#include "structs.h"

unsigned long long microseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000000ULL + val.tv_usec;
}

void sort_table(student_t *students, int count)
{
    student_t tmp;
    bool noSwap;
    long long unsigned t_beg, t_end;
    t_beg = microseconds_now();

    for (int i = count - 1; i >= 0; i--)
    {
        noSwap = 1;
        for (int j = 0; j < i; j++)
        {
            if (students[j].age > students[j + 1].age)
            {
                tmp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = tmp;
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }

    t_end = microseconds_now();
    printf("Таблица отсортирована за %llu микросекунд\n", (t_end - t_beg));
    printf("Затрачено %ld байт памяти\n", sizeof(student_t) * count);
    puts(yell "\nТаблица отсортирована пузырьком\n" res);
}

void sort_keytable(keystudent_t *keystudents, int count)
{
    keystudent_t tmp;
    bool noSwap;
    long long unsigned t_beg, t_end;
    t_beg = microseconds_now();

    for (int i = count - 1; i >= 0; i--)
    {
        noSwap = 1;
        for (int j = 0; j < i; j++)
        {
            if (keystudents[j].age > keystudents[j + 1].age)
            {
                tmp = keystudents[j];
                keystudents[j] = keystudents[j + 1];
                keystudents[j + 1] = tmp;
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }

    t_end = microseconds_now();
    printf("Таблица отсортирована за %llu микросекунд\n", (t_end - t_beg));
    printf("Затрачено %ld байт памяти\n", sizeof(keystudent_t) * count);
    puts(yell "\nТаблица ключей отсортирована пузырьком\n" res);
}

int comparator_keytable(const void *val1, const void *val2)
{
    return ((keystudent_t *)(val1))->age - ((keystudent_t *)(val2))->age;
}

int comparator_table(const void *val1, const void *val2)
{
    return ((student_t *)(val1))->age - ((student_t *)(val2))->age;
}
