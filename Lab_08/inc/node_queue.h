#ifndef NODE_Q_H
#define NODE_Q_H

#include "../inc/structs.h"

int isEmpty_n(node_q *q);
void enQueue_n(int element, node_q *q);
int deQueue_n(node_q *q);
void display_n(node_q *q);
void show_pointers(node_q *q);
void show_deleted(node_t **deleted, int count);

#endif
