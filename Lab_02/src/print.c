#include "structs.h"

int len(char *s, int i, double d)
{
    int length = 0;
    int c = 0;
    if (strlen(s) != 0)
        while (s[c] != '\0')
        {
            if (s[c] < 0)
            {
                length++;
                c += 2;
            }
            else
            {
                length++;
                c++;
            }
        }
    else if (i > 0)
        while (i != 0)
        {
            length++;
            i /= 10;
        }
    else if (i == 0)
        length++;
    else
    {
        if (fmod(d, 1) > 0.000001)
            return 3;
        else
            return 1;
    }
    return length;
}

char *mf(int a)
{
    if (a == 0)
        return "Мужчина";
    else
        return "Женщина";
}

void print_field(student_t student, int id)
{

    printf(v "%*s%d%*s" v "%*s%s%*s" v "%*s%s%*s" v "%*s%s%*s" v "%*s%d%*s" v "%*s%d%*s" v "%*s%.6g%*s" v "  %.2d.%.2d.%.4d  " v,
           (4 - len("", id, 0)) / 2 + (4 - len("", id, 0)) % 2, "", id, (4 - len("", id, 0)) / 2, "",
           (15 - len(student.surname, -1, 0)) / 2 + (15 - len(student.surname, -1, 0)) % 2, "", student.surname, (15 - len(student.surname, -1, 0)) / 2, "",
           (15 - len(student.name, -1, 0)) / 2 + (15 - len(student.name, -1, 0)) % 2, "", student.name, (15 - len(student.name, -1, 0)) / 2, "",
           (11 - len(mf(student.sex), -1, 0)) / 2 + (11 - len(mf(student.sex), -1, 0)) % 2, "", mf(student.sex), (11 - len(mf(student.sex), -1, 0)) / 2, "",
           (6 - len("", student.group, 0)) / 2 + (6 - len("", student.group, 0)) % 2, "", student.group, (6 - len("", student.group, 0)) / 2, "",
           (8 - len("", student.age, 0)) / 2 + (8 - len("", student.age, 0)) % 2, "", student.age, (8 - len("", student.age, 0)) / 2, "",
           (7 - len("", -1, student.average)) / 2 + (7 - len("", -1, student.average)) % 2, "", student.average, (7 - len("", -1, student.average)) / 2, "",
           student.date.day, student.date.month, student.date.year);
    if (student.where == 0)
        printf("%*sОбщежитие номер %d%*s" v "%*s%d%*s" v "  ———  " v "\n",
               (9 - len("", student.residence.hostel.num_hostel, 0)) / 2 + (9 - len("", student.residence.hostel.num_hostel, 0)) % 2, "", student.residence.hostel.num_hostel, (9 - len("", student.residence.hostel.num_hostel, 0)) / 2, "",
               (7 - len("", student.residence.hostel.num_room, 0)) / 2 + (7 - len("", student.residence.hostel.num_room, 0)) % 2, "", student.residence.hostel.num_room, (7 - len("", student.residence.hostel.num_room, 0)) / 2, "");
    else
        printf("%*s%s%*s" v "%*s%d%*s" v "%*s%d%*s" v "\n",
               (25 - len(student.residence.house.street, -1, 0)) / 2 + (25 - len(student.residence.house.street, -1, 0)) % 2, "", student.residence.house.street, (25 - len(student.residence.house.street, -1, 0)) / 2, "",
               (7 - len("", student.residence.house.num_house, 0)) / 2 + (7 - len("", student.residence.house.num_house, 0)) % 2, "", student.residence.house.num_house, (7 - len("", student.residence.house.num_house, 0)) / 2, "",
               (7 - len("", student.residence.house.num_flat, 0)) / 2 + (7 - len("", student.residence.house.num_flat, 0)) % 2, "", student.residence.house.num_flat, (7 - len("", student.residence.house.num_flat, 0)) / 2, "");
}

void print_table(student_t *students, int count)
{
    puts(header);
    for (int i = 0; i < count; i++)
    {
        puts(between);
        print_field(students[i], i + 1);
    }

    puts(end);
}

void print_table_using_keytable(student_t *students, keystudent_t *keystudents, int count)
{
    puts(header);
    for (int i = 0; i < count; i++)
    {
        puts(between);
        print_field(students[keystudents[i].id], i + 1);
    }

    puts(end);
}

void print_table_filter(student_t *students, int count)
{
    int year;
    char line[1024];

    printf(blue "\nВведите интересующий год: " res);

    if (fgets(line, 1024, stdin) == NULL)
    {
        puts(red "\nОшибка ввода строки\n" res);
        return;
    }

    if (line[strlen(line)] == '\n')
        line[strlen(line)] = '\0';

    if (atoi(line) || (atoi(line) == 0 && line[0] == '0'))
        year = atoi(line);
    else
    {
        puts(red "\nНеправильный ввод\n" res);
        return;
    }

    puts(header);
    int how_many = 0;

    for (int i = 0; i < count; i++)
    {
        if (students[i].date.year == year && students[i].where == 0)
        {
            how_many++;
            puts(between);
            print_field(students[i], i + 1);
        }
    }

    if (how_many == 0)
        puts(cy "├────┴───────────────┴───────────────┴───────────┴──────┴────────┴───────┴──────────────┴─────────────────────────┴───────┴───────┤\n" v "                                                   Указанных студентов не найдено                                                " v "\n" cy "└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n" res);
    else
        puts(end);
}

void print_keytable(keystudent_t *keystudents, int count)
{
    puts(cy "┌────┬────────┐\n" v " Id " v " Возраст" v res);

    for (int i = 0; i < count; i++)
    {
        puts(cy "├────┼────────┤" res);
        printf(cy "│" res "%*s%d%*s" cy "│" res "%*s%d%*s" cy "│" res "\n",
               (4 - len("", keystudents[i].id, 0)) / 2 + (4 - len("", keystudents[i].id, 0)) % 2, "", keystudents[i].id, (4 - len("", keystudents[i].id, 0)) / 2, "",
               (8 - len("", keystudents[i].age, 0)) / 2 + (8 - len("", keystudents[i].age, 0)) % 2, "", keystudents[i].age, (8 - len("", keystudents[i].age, 0)) / 2, "");
    }

    puts(cy "└────┴────────┘\n" res);
}

void print_table_by_key(student_t *students, keystudent_t *keystudents, int count)
{
    puts(header);

    for (int i = 0; i < count; i++)
    {
        puts(between);
        print_field(students[keystudents[i].id], i + 1);
    }

    puts(end);
}
