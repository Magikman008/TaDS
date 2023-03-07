#ifndef CHASH_F
#define CHASH_F

#include "../inc/structs.h"

void show_tablec(itemc_t **table);
int insertc(itemc_t **table, char *word, int *comp);
itemc_t *search_tablec(itemc_t **table, char *word, int *comp);
void delete_tablec(itemc_t **table, char *word);
void free_tablec(itemc_t **table);


#endif
