#include "../inc/structs.h"

node_t *newNode(int item)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    if (node != NULL)
    {
        node->data = item;
        node->next = NULL;
        return node;
    }
    else
    {
        printf("\nHeap Overflow");
        exit(EXIT_FAILURE);
    }
}

int deQueue_n(node_q *q)
{
    if (q->front == NULL)
    {
        printf("\nQueue Underflow");
        exit(EXIT_FAILURE);
    }

    node_t *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    int item = temp->data;
    free(temp);
    return item;
}

void enQueue_n(int item, node_q *q) // вставка в конце
{
    node_t *node = newNode(item);

    if (q->front == NULL)
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
}

int isEmpty_n(node_q *q)
{
    return q->rear == NULL && q->front == NULL;
}

void display_n(node_q *q)
{
    node_t *p = q->front;
    if (isEmpty_n(q))
        printf(yel "Empty Queue\n" res);
    else
    {
        printf("Current queue: ");
        while (p->next != NULL)
        {
            printf("%d ", p->data);
            p = p->next;
        }

        printf("%d ", p->data);
        puts("");
    }
}

void show_pointers(node_q *q)
{
    node_t *p = q->front;
    if (isEmpty_n(q))
        printf(yel "Empty Queue\n" res);
    else
    {
        printf("Current pointers queue: \n");
        while (p->next != NULL)
        {
            printf("%p\n", (void *)p);
            p = p->next;
        }

        printf("%p ", (void *)p);
        puts("");
    }
}

void show_deleted(node_t **deleted, int count)
{
        printf("Current deleted pointers queue: \n");
    for (int i = 0; i < count; i++)
        printf("%p\n", (void *)deleted[i]);

}
