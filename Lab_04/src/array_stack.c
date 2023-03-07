#include "../inc/structs.h"
#include "../inc/array_stack.h"

stack_t *createStack()
{
    stack_t *out = NULL;
    out = malloc(sizeof(stack_t));

    if (out == NULL)
        return NULL;

    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(int));

    if (out->data == NULL)
    {
        free(out);
        return NULL;
    }

    out->top = 0;
    return out;
}

void deleteStack(stack_t **stack)
{
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

int resize(stack_t *stack)
{
    stack->size *= MULTIPLIER;
    stack->data = realloc(stack->data, stack->size * sizeof(int));

    if (stack->data == NULL)
        return ERROR_STACK_OVERFLOW;

    return EXIT_SUCCESS;
}

void push(stack_t *stack, int value)
{
    if (stack->top >= stack->size)
        resize(stack);

    stack->data[stack->top] = value;
    stack->top++;
}

int pop(stack_t *stack)
{
    if (stack->top == 0)
        return ERROR_STACK_UNDERFLOW;

    stack->top--;
    return stack->data[stack->top];
}

int peek(const stack_t *stack)
{
    if (stack->top <= 0)
        exit(ERROR_STACK_UNDERFLOW);

    return stack->data[stack->top - 1];
}

void implode(stack_t *stack)
{
    stack->size = stack->top;
    stack->data = realloc(stack->data, stack->size * sizeof(int));
}
