#ifndef SOME_F_H
#define SOME_F_H

#include "../inc/structs.h"

node_t *create(node_t *root, int key, char *str);
node_t *add(node_t *root, char *str);
void free_tree(node_t *root);
void printBT(char *prefix, const node_t *node, bool isLeft);
node_t *search(node_t *root, char *str);
int count_in_file(FILE *src, char *str);
void input_word(char *str, char *print);
int input_number(int *num);
int shift_right(node_t *root);

#endif
