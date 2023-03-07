#include "../inc/structs.h"

int isFull(int front, int rear)
{
    if ((front == rear + 1) || (front == 0 && rear == SIZE - 1))
        return 1;

    return 0;
}

int isEmpty(int front)
{
    if (front == -1)
        return 1;

    return 0;
}

void enQueue(int element, queue_t *q)
{
    if (!isFull(q->front, q->rear))
    {
        if (q->front == -1)
            q->front = 0;

        q->rear = (q->rear + 1) % SIZE;
        q->items[q->rear] = element;
    }
}

int deQueue(queue_t *q)
{
    int element;
    if (isEmpty(q->front))
        return (-1);
    else
    {
        element = q->items[q->front];
        if (q->front == q->rear)
        {
            q->front = -1;
            q->rear = -1;
        }
        else
        {
            q->front = (q->front + 1) % SIZE;
        }
        return (element);
    }
}

void display(queue_t *q)
{
    int i;
    if (isEmpty(q->front))
        printf(yel "Empty Queue\n" res);
    else
    {
        printf("Current queue: ");
        for (i = q->front; i != q->rear; i = (i + 1) % SIZE)
            printf("%d ", q->items[i]);

        printf("%d\n", q->items[i]);
    }
}
