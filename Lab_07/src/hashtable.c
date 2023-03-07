#include "../inc/structs.h"

extern int mult;

static int get_hash(char *word)
{
    long long sum = 7;
    for (int i = 0; word[i] != '\0'; i++)
        sum = (sum % CAPACITY) * mult  + word[i];
    return sum % CAPACITY;
}

int insert(item_t **table, char *word, int *comp)
{
    int hash = get_hash(word);
    if (table[hash] == NULL)
    {
        table[hash] = malloc(sizeof(item_t));
        strcpy(table[hash]->word, word);
        table[hash]->key = 1;
        table[hash]->next = NULL;
        return hash;
    }

    item_t *temp = table[hash];

    (*comp)++;

    while (strcmp(temp->word, word) != 0 && temp->next != NULL)
    {
        (*comp)++;
        temp = temp->next;
    }

    if (strcmp(temp->word, word) == 0)
    {
        temp->key++;
        return hash;
    }

    temp->next = malloc(sizeof(item_t));
    temp->next->parent = temp;
    strcpy(temp->next->word, word);
    temp->next->key = 1;
    temp->next->next = NULL;
    return -1;
}

void show_table(item_t **table)
{
    item_t *temp;
    FILE *f = fopen("temp.gv", "w");
    fprintf(f, "digraph BST {\n");

    for (int i = CAPACITY - 1; i >= 0; i--)
    {
        if (table[i] == NULL)
            fprintf(f, "    \"%d\"->\"%s%d\";\n", i, "NULL", i);
        else
        {
            temp = table[i];
            fprintf(f, "    \"%d\"->\"%s %d\";\n", i, temp->word, temp->key);
            temp = temp->next;
            while (temp != NULL)
            {
                fprintf(f, "    \"%s %d\"->\"%s %d\";\n", temp->parent->word, temp->parent->key, temp->word, temp->key);
                temp = temp->next;
            }
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

item_t *search_table(item_t **table, char *word, int *comp)
{
    *comp = 0;
    int hash = get_hash(word);
    item_t *result = table[hash];
    while (result != NULL && strcmp(result->word, word) != 0)
    {
        result = result->next;
        (*comp)++;
        if (*comp > 3)
            return NULL;
    }

    return result;
}

void delete_table(item_t **table, char *word)
{
    int hash = get_hash(word);
    item_t *result = table[hash];
    while (result != NULL && strcmp(result->word, word) != 0)
        result = result->next;

    if (result == NULL)
        return;

    if (result->next != NULL && result->parent != NULL)
    {
        result->parent->next = result->next;
        result->next->parent = result->parent;
        free(result);
    }
    else if (result->next == NULL && result->parent == NULL)
    {
        table[hash] = NULL;
        free(result);
    }
    else if (result->next == NULL)
    {
        result->parent->next = NULL;
        free(result);
    }
    else
    {
        table[hash] = result->next;
        result->next->parent = NULL;
        free(result);
    }
}

void free_table(item_t **table)
{
    item_t *tmp;
    item_t *next;
    for (int i = 0; i < CAPACITY; i++)
    {
        if (table[i] != NULL)
        {
            next = NULL;
            tmp = table[i];
            while (tmp)
            {
                next = tmp->next;
                free(tmp);
                tmp = next;
            }
        }
    }

    free(table);
}
