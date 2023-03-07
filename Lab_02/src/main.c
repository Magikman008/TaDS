#include "structs.h"
#include "print.h"
#include "sort.h"
#include "initialize.h"
#include "edit.h"
#include "colors.h"

int main(void)
{
    student_t students[MAX_NUM_OF_STUDENTS];
    keystudent_t keystudents[MAX_NUM_OF_STUDENTS];
    int count = 0;
    int rc = get_table(students, &count);
    long long unsigned t_beg, t_end;

    if (rc)
        return rc;

    make_keytable(students, keystudents, count);

    puts(yell "\nТаблица загружена в память, таблица ключей инициализирована\n" res);
    int input = -1;
    int go = 1;
    char line[1024];

    while (go)
    {
        puts(gr "1. " res " Вывести всю таблицу\n" gr
                "2. " res " Вывести всю таблицу используя таблицу ключей\n" gr
                "3. " res " Вывести поля с определенным годом поступления для студентов живущих в общежитии\n" gr
                "4. " res " Сортировка таблицы пузырьком\n" gr
                "5. " res " Сортировка таблицы быстрой сортировкой\n" gr
                "6. " res " Сортировка таблицы ключей пузырьком\n" gr
                "7. " res " Сортировка таблицы ключей быстрой сортировкой\n" gr
                "8. " res " Вывод таблицы ключей\n" gr
                "9. " res " Вывод основной таблицы по таблице ключей\n" gr
                "10." res " Обновить таблицу из файла\n" gr
                "11." res " Обновить таблицу ключей по основной таблице\n" gr
                "12." res " Добавить элемент\n" gr
                "13." res " Удалить элемент по номеру\n" gr
                "14." res " Сохранить таблицу в файл\n" gr
                "0. " res " Остановить программу\n");

        printf(blue "Введите номер команды: " res);
        if (fgets(line, 1024, stdin) == NULL)
            return ERROR_BAD_INPUT;

        if (line[strlen(line)] == '\n')
            line[strlen(line)] = '\0';

        if (atoi(line) || (atoi(line) == 0 && line[0] == '0'))
            input = atoi(line);
        else
            input = -1;

        switch (input)
        {
        case 1:
            print_table(students, count);
            break;
        case 2:
            print_table_using_keytable(students, keystudents, count);
            break;
        case 3:
            print_table_filter(students, count);
            break;
        case 4:
            sort_table(students, count);
            break;
        case 5:
            t_beg = microseconds_now();
            qsort(students, count, sizeof(students[0]), comparator_table);
            t_end = microseconds_now();
            printf("Таблица отсортирована за %llu микросекунд\n", (t_end - t_beg));
            printf("Затрачено %ld байт памяти\n", sizeof(students));
            puts(yell "\nТаблица отсортирована быстрой сортировкой\n" res);
            break;
        case 6:
            sort_keytable(keystudents, count);
            break;
        case 7:
            t_beg = microseconds_now();
            qsort(keystudents, count, sizeof(keystudents[0]), comparator_keytable);
            t_end = microseconds_now();
            printf("Таблица отсортирована за %llu микросекунд\n", (t_end - t_beg));
            printf("Затрачено %ld байт памяти\n", sizeof(keystudents));
            puts(yell "\nТаблица ключей отсортирована быстрой сортировкой\n" res);
            break;
        case 8:
            print_keytable(keystudents, count);
            break;
        case 9:
            print_table_by_key(students, keystudents, count);
            break;
        case 10:
            count = 0;
            rc = get_table(students, &count);
            if (rc)
                return rc;
            puts(yell "\nТаблица обновлена\n" res);
            break;
        case 11:
            make_keytable(students, keystudents, count);
            puts(yell "\nТаблица ключей обновлена\n" res);
            break;
        case 12:
            rc = add_field(students, &count);
            if (rc)
                printf(red "Поле не добавлено\n" res);
            else
                puts(yell "\nЭлемент добавлен\n" res);
            break;
        case 13:
            rc = remove_field(students, &count);
            if (rc)
                return rc;
            puts(yell "\nЭлемент удалён\n" res);
            break;
        case 14:
            rc = save_table(students, count);
            if (rc)
                return rc;
            puts(yell "\nТаблица сохранена\n" res);
            break;
        case 0:
            puts("Покеда");
            go = 0;
            break;
        case -1:
            puts(red "\nНеправильный ввод\n" res);
            break;
        default:
            puts(red "\nТакой пункт отсутствует\n" res);
        }
    }

    return EXIT_SUCCESS;
}
