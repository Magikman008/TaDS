#include "../inc/structs.h"
#include "../inc/tree.h"
#include "../inc/hashtable.h"
#include "../inc/closed_hashtable.h"
#include "../inc/balance_tree.h"

#define file "in.txt"

void input_word(char *str, char *print)
{
    strcpy(str, "");
    printf("%s", print);

    if (fgets(str, 100, stdin) != str)
        puts(red "Couldn't scan the line" res);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void scan_add(node_t *root, char *str)
{
    FILE *src;
    char temp[100];
    input_word(temp, yel "The specified word was not found\n" res "Would you like to add this word to tree and file? (y/n) ");

    if ((strcmp(temp, "y\n") == 0) || (strcmp(temp, "yes\n") == 0))
    {
        src = fopen("in.txt", "a+");
        add(root, str, NULL);
        fprintf(src, "%s\n", str);
    }
}

int input_number(int *num)
{
    char line[1024];
    if (fgets(line, 1024, stdin) == NULL)
        return EXIT_FAILURE;

    if (line[strlen(line)] == '\n')
        line[strlen(line)] = '\0';

    if (atoi(line))
        *num = atoi(line);
    else if (strchr(line, 48) != NULL)
        *num = 0;
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int count_in_file(char *str)
{
    FILE *src = fopen("in.txt", "a+");
    int count = 0;
    rewind(src);
    char temp_str[100];
    while (fscanf(src, "%s", temp_str) == 1)
        if (strcmp(temp_str, str) == 0)
            count++;

    return count;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc"
                         : "=A"(d));
    return d;
}

void init_structs(node_t **root, node_t **balanced, item_t ***table, itemc_t ***tablec)
{
    char str[100];
    int comp = 0;
    int uninserted = 0;
    int collisions = 0;
    int collisionsc = 0;
    FILE *src = fopen(file, "r");
    *table = malloc(sizeof(item_t) * CAPACITY);
    *tablec = malloc(sizeof(itemc_t) * CAPACITY);

    for (int i = 0; i < CAPACITY; i++)
    {
        (*table)[i] = NULL;
        (*tablec)[i] = NULL;
    }

    if (fscanf(src, "%s", str) == 1)
    {
        *root = create(*root, 1, str);
        if (insert(*table, str, &comp) == -1)
            collisions++;
        comp = 0;
        if (insertc(*tablec, str, &comp) == -1)
            uninserted++;
        if (comp > 0)
            collisionsc++;
    }

    while (fscanf(src, "%s", str) == 1)
    {
        add(*root, str, &comp);
        if (insert(*table, str, &comp) == -1)
            collisions++;
        comp = 0;
        if (insertc(*tablec, str, &comp) == -1)
            uninserted++;
        if (comp > 0)
            collisionsc++;
    }

    printf("Collisions in open table: %d\n", collisions);
    printf("Items not inserted in closed table: %d\n", uninserted);
    printf("Collisions in closed table: %d\n", collisionsc);

    fclose(src);

    *balanced = init(*root, *balanced);
}

void remake_tables(item_t ***table, itemc_t ***tablec)
{
    char str[100];
    int comp = 0;
    FILE *src = fopen(file, "a+");

    for (int i = 0; i < CAPACITY; i++)
    {
        (*table)[i] = NULL;
        (*tablec)[i] = NULL;
    }

    if (fscanf(src, "%s", str) == 1)
    {
        insert(*table, str, &comp);
        insertc(*tablec, str, &comp);
    }

    fclose(src);
}
