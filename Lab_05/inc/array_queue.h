#ifndef ARRAY_Q_H
#define ARRAY_Q_H

#include "../inc/structs.h"

int isFull(int front, int rear);
int isEmpty(int front);
void enQueue(int element, queue_t *q);
int deQueue(queue_t *q);
void display(queue_t *q);

#endif
