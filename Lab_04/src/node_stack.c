#include "../inc/structs.h"

void npush(node_t **head, int value)
{
    node_t *tmp = malloc(sizeof(node_t));

    if (tmp == NULL)
        exit(ERROR_STACK_OVERFLOW);

    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

int npop(node_t **head)
{
    node_t *out;
    int value;

    if (*head == NULL)
        exit(ERROR_STACK_UNDERFLOW);

    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

int npeek(const node_t *head)
{
    if (head == NULL)
        exit(ERROR_STACK_UNDERFLOW);

    return head->value;
}

size_t getSize(const node_t *head)
{
    size_t size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return size;
}
