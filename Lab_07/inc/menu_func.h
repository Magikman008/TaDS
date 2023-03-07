#ifndef MENU_F
#define MENU_F

#include "../inc/structs.h"

int count_in_file(char *str);
void input_word(char *str, char *print);
int input_number(int *num);
void scan_add(node_t *root, char *str);
unsigned long long tick(void);
void init_structs(node_t **root, node_t **balanced, item_t ***table, itemc_t ***tablec);
void remake_tables(item_t ***table, itemc_t ***tablec);

#endif
