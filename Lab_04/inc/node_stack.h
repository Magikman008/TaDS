#ifndef NODE_H
#define NODE_H

#include "../inc/structs.h"

void npush(node_t **head, int value);
int npop(node_t **head);
int npeek(const node_t *head);
size_t getSize(const node_t *head);

#endif
