#ifndef HASH_F
#define HASH_F

#include "../inc/structs.h"

void show_table(item_t **table);
int insert(item_t **table, char *word, int *comp);
item_t *search_table(item_t **table, char *word, int *comp);
void delete_table(item_t **table, char *word);
void free_table(item_t **table);


#endif
