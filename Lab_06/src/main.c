#include "../inc/structs.h"
#include "../inc/tree.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc"
                         : "=A"(d));
    return d;
}

int main(void)
{
    FILE *src;
    long long unsigned t_start, t_end;

    if (!(src = fopen("in2.txt", "a+")))
    {
        puts(red "Error open file" res);
        return ERROR_BAD_FILE;
    }

    int option, go = 1;
    node_t *temp_n = NULL;
    char temp[100];

    char str[100];

    node_t *root = NULL;
    if (fscanf(src, "%s", str) == 1)
        root = create(root, 1, str);

    while (fscanf(src, "%s", str) == 1)
        add(root, str);

    while (go)
    {
        puts(gr "1. " res " Print tree\n" gr
                "2. " res " Add element to tree\n" gr
                "3. " res " Search element in tree\n" gr
                "4. " res " Search element in file\n" gr
                "5. " res " Remove element in tree\n" gr
                "6. " res " Print node\n" gr
                "0. " res " Leave program\n" gr);
        printf(blue "Enter number of command: " res);

        if (input_number(&option))
            option = -1;

        printf(del del del del del del del del del);

        switch (option)
        {
        case 1:
            if (root != NULL)
                printBT("", root, false);
            else
                puts(red "Tree is empty" res);
            break;
        case 2:
        {
            input_word(str, "Enter your word to add: ");

            if (strcmp(str, "") == 0)
                break;

            add(root, str);
            fprintf(src, "%s\n", str);
            break;
        }
        case 3:
            input_word(str, "Enter your word to search: ");

            if (strcmp(str, "") == 0)
                break;

            if (root == NULL)
            {
                puts(red "Tree is empty" res);
                break;
            }

            t_start = tick();
            temp_n = search(root, str);
            t_end = tick();
            printf("Ticks spent %llu\n", (t_end - t_start));

            if (temp_n != NULL)
                printf("%s, %d\n", temp_n->word, temp_n->key);
            else
            {
                input_word(temp, yel "The specified word was not found\n" res "Would you like to add this word to tree and file? (y/n) ");

                if (strcmp(str, "") == 0)
                    break;

                if ((strcmp(temp, "y\n") == 0) || (strcmp(temp, "yes\n") == 0))
                {
                    add(root, str);
                    fprintf(src, "%s\n", str);
                }
            }

            break;
        case 4:
            input_word(str, "Enter your word to search: ");

            if (strcmp(str, "") == 0)
                break;

            t_start = tick();
            printf("%s %d\n", str, count_in_file(src, str));
            t_end = tick();
            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        case 5:
            input_word(str, "Enter your word to remove: ");

            if (strcmp(str, "") == 0)
                break;

            temp_n = search(root, str);

            if (temp_n != NULL)
            {
                if (temp_n->parent->left == temp_n)
                    temp_n->parent->left = NULL;
                else
                    temp_n->parent->right = NULL;
                // free_tree(temp_n);
                shift_right(temp_n);
                temp_n->parent->left = temp_n->right;
                temp_n->right->left = temp_n->right;
                free(temp_n);
            }
            else
                puts(red "No such node" res);

            break;
        case 6:
            input_word(str, "Enter your word to print: ");

            if (strcmp(str, "") == 0)
                break;

            if (root == NULL)
            {
                puts(red "Tree is empty" res);
                break;
            }
            temp_n = search(root, str);
            printBT("", temp_n, false);
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

    if (fclose(src))
        return ERROR_FILE_CLOSE;

    return EXIT_SUCCESS;
}
