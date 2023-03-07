#ifndef ARRAY_H
#define ARRAY_H

#include "../inc/structs.h"

stack_t *createStack();
void deleteStack(stack_t **stack);
void push(stack_t *stack, int value);
int pop(stack_t *stack);
int peek(const stack_t *stack);

#endif
