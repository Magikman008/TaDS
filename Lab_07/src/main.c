#include "../inc/structs.h"
#include "../inc/tree.h"
#include "../inc/balance_tree.h"
#include "../inc/hashtable.h"
#include "../inc/closed_hashtable.h"
#include "../inc/menu_func.h"

int mult = 7;

// * Оценить эффективность поиска в хеш-таблице при различном количестве коллизий и при различных методах их разрешения.
// * Подсчитать среднее количество сравнений для поиска данных в указанных структурах.
// * Сравнить время поиска, объем памяти и количество сравнений при использовании ДДП, сбалансированных деревьев и хеш-таблиц.
// * Сравнить эффективность добавления ключа в таблицу или ее реструктуризацию для различной степени заполненности таблицы.

int main(void)
{
    long long unsigned t_start, t_end;
    int option, go = 1, comp;
    node_t *temp_n2 = NULL, *temp_n = NULL;
    item_t *temp_table = NULL;
    itemc_t *temp_tablec = NULL;

    char str[100];

    item_t **table = NULL;
    itemc_t **tablec = NULL;
    node_t *root = NULL;
    node_t *balanced = NULL;
    init_structs(&root, &balanced, &table, &tablec);

    while (go)
    {
        puts(MENU);
        printf(blue "Enter number of command: " res);

        if (input_number(&option))
            option = -1;

        printf(del del del del del del del del del del del del del del del del del del del del del del del del del del del del);

        switch (option)
        {
        case 1:
            if (root != NULL)
                show_tree(root);
            else
                puts(red "Tree is empty" res);
            break;
        case 2:
            input_word(str, "Enter your word to add: ");

            add(root, str, &comp);
            break;
        case 3:
            input_word(str, blue "Enter your word to search: " res);

            t_start = tick();
            comp = 0;
            temp_n = search(root, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (temp_n != NULL)
                printf("%s, %d\n", temp_n->word, temp_n->key);
            else
                scan_add(root, str);

            break;
        case 4:
            input_word(str, blue "Enter your word to search: " res);

            t_start = tick();
            printf("%s %d\n", str, count_in_file(str));
            t_end = tick();
            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        case 5:
            input_word(str, blue "Enter your word to remove: " res);

            t_start = tick();
            comp = 0;
            temp_n = search(root, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (temp_n != NULL)
                delete_node(temp_n);
            else
                puts(red "No such node" res);

            break;
        case 6:
            free_tree(balanced);
            balanced = NULL;
            balanced = init(root, balanced);
            break;
        case 7:
            if (balanced != NULL)
                show_tree(balanced);
            else
                puts(red "Tree is empty" res);
            break;
        case 8:
            input_word(str, blue "Enter your word to search: " res);

            t_start = tick();
            comp = 0;
            temp_n = search(balanced, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (temp_n != NULL)
                printf("%s, %d\n", temp_n->word, temp_n->key);
            else
                scan_add(balanced, str);
            break;
        case 9:
            input_word(str, blue "Enter your word to remove: " res);

            t_start = tick();
            comp = 0;
            temp_n = search(balanced, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (temp_n != NULL)
            {
                delete_node(temp_n);
                temp_n2 = init(balanced, temp_n2);
                balanced = temp_n2;
            }
            else
                puts(red "No such node" res);

            break;
        case 10:
            show_table(table);
            break;
        case 11:
            input_word(str, blue "Enter your word to search: " res);
            t_start = tick();
            temp_table = search_table(table, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (comp > 4)
            {
                free_table(table);
                table = malloc(sizeof(item_t) * CAPACITY);
                printf(red "Error comparison.\n" res "Enter new ratio for hash func. Previos ratio was %d. ", mult);
                input_number(&mult);
                remake_tables(&table, &tablec);
                puts(yel "Restructurisation finished" res);
            }
            else if (temp_table)
                printf("%s, %d\n", temp_table->word, temp_table->key);
            else
                puts(red "No such element" res);
            break;
        case 12:
            input_word(str, blue "Enter your word to remove: " res);
            delete_table(table, str);
            break;
        case 13:
            show_tablec(tablec);
            break;
        case 14:
            input_word(str, blue "Enter your word to search: " res);
            printf("%s\n", str);
            t_start = tick();
            temp_tablec = search_tablec(tablec, str, &comp);
            t_end = tick();
            printf("Ticks spent %llu\nComparisons %d\n", (t_end - t_start), comp);

            if (temp_tablec)
                printf("%s, %d\n", temp_tablec->word, temp_tablec->key);
            else
                puts(red "No such element" res);
            break;
        case 15:
            input_word(str, blue "Enter your word to remove: " res);
            delete_tablec(tablec, str);
            break;
        case 16:
            input_word(str, blue "Enter your word to add: " res);
            t_start = tick();
            comp = 0;
            add(root, str, &comp);
            t_end = tick();
            printf("Ticks spent to add in normal tree %llu\n", (t_end - t_start));
            printf("Comparisons in normal tree %d\n", comp);

            t_start = tick();
            comp = 0;
            add(balanced, str, &comp);
            temp_n2 = NULL;
            temp_n2 = init(balanced, temp_n2);
            free(balanced);
            balanced = temp_n2;
            t_end = tick();
            printf("Ticks spent to add in balanced tree %llu\n", (t_end - t_start));
            printf("Comparisons in balanced tree %d\n", comp);

            t_start = tick();
            comp = 0;
            insert(table, str, &comp);
            t_end = tick();
            printf("Ticks spent to add in open table %llu\n", (t_end - t_start));
            printf("Comparisons in open table %d\n", comp);

            t_start = tick();
            comp = 0;
            insertc(tablec, str, &comp);
            t_end = tick();
            printf("Ticks spent to add in closed table %llu\n", (t_end - t_start));
            printf("Comparisons in closed table %d\n", comp);
            break;
        case 17:
            input_word(str, blue "Enter your word to delete: " res);
            t_start = tick();
            comp = 0;
            temp_n = search(root, str, &comp);
            delete_node(temp_n);
            t_end = tick();
            printf("Ticks spent to find in tree %llu\n", (t_end - t_start));
            printf("Comparisons %d\n", comp);

            t_start = tick();
            comp = 0;
            temp_n = search(balanced, str, &comp);
            delete_node(temp_n);
            temp_n2 = NULL;
            temp_n2 = init(balanced, temp_n2);
            free(balanced);
            balanced = temp_n2;
            t_end = tick();
            printf("Ticks spent to find in balanced tree %llu\n", (t_end - t_start));
            printf("Comparisons %d\n", comp);

            t_start = tick();
            comp = 0;
            delete_table(table, str);
            t_end = tick();
            printf("Ticks spent to find in open table %llu\n", (t_end - t_start));
            printf("Comparisons %d\n", comp);

            t_start = tick();
            comp = 0;
            delete_tablec(tablec, str);
            t_end = tick();
            printf("Ticks spent to find in closed table %llu\n", (t_end - t_start));
            printf("Comparisons %d\n", comp);
            break;
        case 18:
            free_tree(root);
            free_table(table);
            free_tree(balanced);
            table = NULL;
            root = NULL;
            balanced = NULL;
            init_structs(&root, &balanced, &table, &tablec);
            break;
        case 19:
            input_word(str, blue "Enter your word to add: " res);
            t_start = tick();
            comp = 0;
            insert(table, str, &comp);
            t_end = tick();
            printf("Ticks spent to add in open table %llu\n", (t_end - t_start));
            printf("Comparisons in open table %d\n", comp);
            break;
        case 20:
            input_word(str, blue "Enter your word to add: " res);
            t_start = tick();
            comp = 0;
            insertc(tablec, str, &comp);
            t_end = tick();
            printf("Ticks spent to add in open table %llu\n", (t_end - t_start));
            printf("Comparisons in open table %d\n", comp);
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }

    free_tree(root);
    free_table(table);
    free_tablec(tablec);
    free_tree(balanced);

    return EXIT_SUCCESS;
}
