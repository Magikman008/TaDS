#include "structs.h"

int input_str(char *string, int length)
{
    if (!fgets(string, length + 1, stdin))
    {
        puts(red "Ошибка: пустая строка" res);
        return ERROR_EMPTY_STRING;
    }

    size_t len = strlen(string);

    if (string[0] == '\n')
    {
        puts(red "Ошибка: пустая строка" res);
        return ERROR_TOO_BIG_STR;
    }

    if (string[len - 1] == '\n')
        string[--len] = '\0';

    return EXIT_SUCCESS;
}

int add_field(student_t *students, int *count)
{
    student_t student = {0};

    if (*count + 1 > MAX_NUM_OF_STUDENTS)
    {
        puts(yell "Превышен размер таблицы. Удалите что-нибудь" res);
        return ERROR_MAX_TABLE_SIZE;
    }

    puts(yell "Фамилия и имя должны быть не длиннее 25 символов" res);
    printf("Введите фамилию: ");

    if (input_str(student.surname, MAX_LEN_OF_STR))
        return ERROR_BAD_INPUT;

    printf("Введите имя: ");

    if (input_str(student.name, MAX_LEN_OF_STR))
        return ERROR_BAD_INPUT;

    printf("Введите пол (0 - М, 1 - Ж): ");

    if (scanf("%d", &student.sex) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.sex != 0 && student.sex != 1)
    {
        puts(red "Ошибка: число не соответствует ни одному полу" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите возраст: ");

    if (scanf("%d", &student.age) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.age < 1)
    {
        puts(red "Ошибка: возраст не может быть меньше 1" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите номер группы: ");
    if (scanf("%d", &student.group) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.group < 1)
    {
        puts(red "Ошибка: номер группы должен быть больше 0" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите среднее арифмитическое оценок: ");

    if (scanf("%lf", &student.average) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.average < 0 || student.average > 5)
    {
        puts(red "Ошибка: среднее арифметическое оценок должно быть больше 0 и меньше 5" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите день поступления: ");

    if (scanf("%d", &student.date.day) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.date.day < 1 || student.date.day > 31)
    {
        puts(red "Ошибка: день должен быть от 1 до 31" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите месяц поступления: ");

    if (scanf("%d", &student.date.month) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.date.month < 1 || student.date.month > 12)
    {
        puts(red "Ошибка: месяц должен быть от 1 до 12" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите год поступления от 1970 до 2022: ");

    if (scanf("%d", &student.date.year) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.date.year < 1970 || student.date.year > 2022)
    {
        puts(red "Ошибка: месяц должен быть от 1970 до 2022" res);
        return ERROR_BAD_INPUT;
    }

    printf("Введите где живет студент (0 - Общежитие, 1 - Квартира): ");

    if (scanf("%d", &student.where) != 1)
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (student.where != 0 && student.where != 1)
    {
        puts(red "Ошибка: число не соответствует ни одному месту" res);
        return ERROR_BAD_INPUT;
    }

    if (student.where == 0)
    {
        printf("Введите номер общежития: ");

        if (scanf("%d", &student.residence.hostel.num_hostel) != 1)
        {
            puts(red "Ошибка: введено не число" res);
            return ERROR_BAD_INPUT;
        }

        if (student.residence.hostel.num_hostel < 1)
        {
            puts(red "Ошибка: номер общежития не может быть меньше 1" res);
            return ERROR_BAD_INPUT;
        }

        char line[1024];
        if (!fgets(line, 1024, stdin))
            return 228;

        printf("Введите номер комнаты в общежитии: ");

        if (fgets(line, 1024, stdin) == NULL)
            return ERROR_BAD_INPUT;

        if (line[strlen(line)] == '\n')
            line[strlen(line)] = '\0';

        if (atoi(line) || (atoi(line) == 0 && line[0] == '0'))
            student.residence.hostel.num_room = atoi(line);
        else
        {
            puts(red "Ошибка: введено не число" res);
            return ERROR_BAD_INPUT;
        }

        if (student.residence.hostel.num_room < 1)
        {
            puts(red "Ошибка: номер комнаты не может быть меньше 1" res);
            return ERROR_BAD_INPUT;
        }
    }
    else
    {
        puts(yell "Название улицы должно быть не длиннее 50 символов" res);
        printf("Введите название улицы: ");

        if (input_str(student.residence.house.street, MAX_LEN_OF_STR))
            return ERROR_BAD_INPUT;

        printf("Введите номер дома: ");

        if (scanf("%d", &student.residence.house.num_house) != 1)
        {
            puts(red "Ошибка: введено не число" res);
            return ERROR_BAD_INPUT;
        }

        if (student.residence.house.num_house < 1)
        {
            puts(red "Ошибка: номер общежития не может быть меньше 1" res);
            return ERROR_BAD_INPUT;
        }

        char line[1024];

        if (!fgets(line, 1024, stdin))
            return 228;
        printf("Введите номер квартиры: ");

        if (fgets(line, 1024, stdin) == NULL)
            return ERROR_BAD_INPUT;

        if (line[strlen(line)] == '\n')
            line[strlen(line)] = '\0';

        if (atoi(line) || (atoi(line) == 0 && line[0] == '0'))
            student.residence.house.num_flat = atoi(line);
        else
        {
            puts(red "Ошибка: введено не число" res);
            return ERROR_BAD_INPUT;
        }

        if (student.residence.house.num_flat < 1)
        {
            puts(red "Ошибка: номер комнаты не может быть меньше 1" res);
            return ERROR_BAD_INPUT;
        }
    }

    students[*count] = student;
    (*count)++;

    return EXIT_SUCCESS;
}

int remove_field(student_t *students, int *count)
{
    int id;
    char line[1024];

    printf("Введите номер удаляемого поля: ");

    if (fgets(line, 1024, stdin) == NULL)
        return ERROR_BAD_INPUT;

    if (line[strlen(line)] == '\n')
        line[strlen(line)] = '\0';

    if (atoi(line) || (atoi(line) == 0 && line[0] == '0'))
        id = atoi(line);
    else
    {
        puts(red "Ошибка: введено не число" res);
        return ERROR_BAD_INPUT;
    }

    if (id < 1)
    {
        puts(red "Ошибка: номер поля больше 1" res);
        return ERROR_BAD_INPUT;
    }
    for (int i = id - 1; i < *count; i++)
        students[i] = students[i + 1];

    (*count)--;

    return EXIT_SUCCESS;
}

int save_table(student_t *students, int count)
{
    FILE *f = fopen("table.csv", "w");

    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s;%s;%d;%d;%d;%.1f;%d.%d.%d;", students[i].surname, students[i].name, students[i].sex, students[i].group, students[i].age, students[i].average, students[i].date.day, students[i].date.month, students[i].date.year);

        if (students[i].where == 1)
            fprintf(f, "1;%s;%d;%d;\n", students[i].residence.house.street, students[i].residence.house.num_house, students[i].residence.house.num_flat);
        else
            fprintf(f, "0;%d;%d;\n", students[i].residence.hostel.num_hostel, students[i].residence.hostel.num_room);
    }

    if (fclose(f))
    {
        puts(red "Ошика закрытия файла" res);
        return ERROR_BAD_FCLOSE;
    }

    return EXIT_SUCCESS;
}
