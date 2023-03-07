#include "structs.h"

void get_field(char *line, student_t *student)
{
    strcpy(student->surname, strtok(line, ";"));
    strcpy(student->name, strtok(NULL, ";"));
    student->sex = atoi(strtok(NULL, ";"));
    student->group = atoi(strtok(NULL, ";"));
    student->age = atoi(strtok(NULL, ";"));
    char *eptr;
    student->average = strtod(strtok(NULL, ";"), &eptr);
    student->date.day = atoi(strtok(NULL, "."));
    student->date.month = atoi(strtok(NULL, "."));
    student->date.year = atoi(strtok(NULL, ";"));
    student->where = atoi(strtok(NULL, ";"));
    if (student->where == 0)
    {
        student->residence.hostel.num_hostel = atoi(strtok(NULL, ";"));
        student->residence.hostel.num_room = atoi(strtok(NULL, ";"));
    }
    else
    {
        strcpy(student->residence.house.street, strtok(NULL, ";"));
        student->residence.house.num_house = atoi(strtok(NULL, ";"));
        student->residence.house.num_flat = atoi(strtok(NULL, ";"));
    }
}

int get_table(student_t *students, int *count)
{
    FILE *f = fopen("table.csv", "r");

    char line[1024];
    while (fgets(line, 1024, f))
    {
        get_field(line, &(students[*count]));
        (*count)++;
    }

    if (fclose(f))
    {
        puts(red "Ошика закрытия файла" res);
        return ERROR_BAD_FCLOSE;
    }

    if (*count == 0)
    {
        puts(red "Пустая таблица" res);
        return ERROR_EMPTY_TABLE;
    }

    return EXIT_SUCCESS;
}

void make_keytable(student_t *students, keystudent_t *keystudents, int count)
{
    for (int i = 0; i < count; i++)
    {
        keystudents[i].id = i;
        keystudents[i].age = students[i].age;
    }
}
