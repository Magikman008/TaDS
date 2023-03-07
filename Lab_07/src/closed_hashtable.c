#include "../inc/structs.h"

extern int mult;

static int get_hash(char *word)
{
    long long sum = 7;
    for (int i = 0; word[i] != '\0'; i++)
        sum = (sum % CAPACITY) * mult + word[i];
    return sum % CAPACITY;
}

int insertc(itemc_t **table, char *word, int *comp)
{
    int hash = get_hash(word);
    int count = 0;

    if (table[hash] == NULL)
    {
        table[hash] = malloc(sizeof(itemc_t));
        strcpy(table[hash]->word, word);
        table[hash]->key = 1;
        return hash;
    }

    if (strcmp(table[hash]->word, word) == 0)
    {
        table[hash]->key++;
        return hash;
    }

    int result = 0;

    while (count < CAPACITY && result == 0)
    {
        (*comp)++;
        hash = (hash + 1) % CAPACITY;
        count++;

        if (table[hash] == NULL)
            result = 1;
        else if (strcmp(table[hash]->word, word) == 0)
        {
            table[hash]->key++;
            return hash;
        }
    }

    if (result == 0)
        return -1;

    table[hash] = malloc(sizeof(itemc_t));
    strcpy(table[hash]->word, word);
    table[hash]->key = 1;
    return hash;
}

void show_tablec(itemc_t **table)
{
    FILE *f = fopen("temp.gv", "w");
    fprintf(f, "digraph BST {\n");

    for (int i = CAPACITY - 1; i >= 0; i--)
    {
        if (table[i] == NULL)
            fprintf(f, "    \"%d\"->\"%s%d\" [dir=none color=\"blue\"];\n", i, "NULL", i);
        else
        {
            if (i != get_hash(table[i]->word))
            {
                fprintf(f, "    \"%d\"->\"%s %d\" [ label=\"  %d \"dir=none color=\"red\"];\n", i, table[i]->word, table[i]->key, get_hash(table[i]->word));
                // fprintf(f, "    %s %d [color=\"red\"];\n", table[i]->word, table[i]->key);
            }
            else
                fprintf(f, "    \"%d\"->\"%s %d\"  [dir=none];\n", i, table[i]->word, table[i]->key);
        }
    }
    fprintf(f, "rankdir=\"LR\";\n");

    fprintf(f, "}\n");
    fclose(f);

    f = popen("dot -Tsvg temp.gv -ograph.svg", "r");
    pclose(f);
    f = popen("rm -rf temp.gv", "r");
    pclose(f);
    f = popen("xdg-open ./graph.svg", "r");
    pclose(f);
}

itemc_t *search_tablec(itemc_t **table, char *word, int *comp)
{
    *comp = 0;
    int hash = get_hash(word);
    int count = 0;

    while (count < CAPACITY)
    {
        if (table[hash] != NULL && strcmp(table[hash]->word, word) == 0)
            return table[hash];
        (*comp)++;
        hash = (hash + 1) % CAPACITY;
        count++;
    }

    return NULL;
}

void delete_tablec(itemc_t **table, char *word)
{
    int hash = get_hash(word);
    int count = 0;

    while (count < CAPACITY && strcmp(table[hash]->word, word) != 0)
    {
        hash = (hash + 1) % CAPACITY;
        count++;
    }

    if (strcmp(table[hash]->word, word) != 0)
        return;

    free(table[hash]);
    table[hash] = NULL;
}

void free_tablec(itemc_t **table)
{
    for (int i = 0; i < CAPACITY; i++)
        if (table[i] != NULL)
            free(table[i]);

    free(table);
}
