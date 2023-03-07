#include "../inc/structs.h"
#include "../inc/menu.h"
#include "../inc/array_queue.h"
#include "../inc/node_queue.h"
#include "../inc/modeling.h"

int input_number(int *num)
{
    char line[1024];
    if (fgets(line, 1024, stdin) == NULL)
        return EXIT_FAILURE;

    if (line[strlen(line)] == '\n')
        line[strlen(line)] = '\0';

    if (atoi(line))
        *num = atoi(line);
    else if (strchr(line, 48) != NULL)
        *num = 0;
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void array_queue_menu()
{
    int option, go = 1, elem;

    queue_t q = {0};
    q.front = -1;
    q.rear = -1;

    while (go)
    {
        puts(gr "1. " res "Model queue\n" gr
                "2. " res "Add element to queue\n" gr
                "3. " res "Remove element from queue\n" gr
                "4. " res "Show queue\n" gr
                "0. " res "Leave program\n" gr);
        printf(blue "Enter number of command: " res);
        if (input_number(&option))
            option = -1;
        printf(del del del del del del del);
        switch (option)
        {
        case 1:
            model_array_queue();
            break;
        case 2:
        {
            printf("Enter new element: ");
            if (!input_number(&elem))
            {
                printf(del);
                enQueue(elem, &q);
                printf("%d was added successfully\n", elem);
            }
            else
                puts(red "Can not read number" res);
        }
        break;
        case 3:
            printf("%d was removed successfully\n", deQueue(&q));
            break;
        case 4:
            display(&q);
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }
}

void node_queue_menu()
{
    int option, go = 1;

    node_q q = {0};
    q.front = NULL;
    q.rear = NULL;
    node_t *deleted[1000];
    int del_count = 0;

    while (go)
    {
        puts(gr "1. " res "Model queue\n" gr
                "2. " res "Add element to queue\n" gr
                "3. " res "Remove element from queue\n" gr
                "4. " res "Show queue\n" gr
                "5. " res "Show existed pointers\n" gr
                "6. " res "Show deleted pointers\n" gr
                "0. " res "Leave program\n" gr);
        printf(blue "Enter number of command: " res);
        if (input_number(&option))
            option = -1;
        printf(del del del del del del del del del);

        switch (option)
        {
        case 1:
            model_node_queue();
            break;
        case 2:
        {
            int elem;
            printf("Enter new element: ");
            input_number(&elem);
            printf(del);
            if (elem)
            {
                enQueue_n(elem, &q);
                printf("%d was added successfully\n", elem);
            }
            else
                puts(red "Can not read number" res);
        }
        break;
        case 3:
            // printf("%p\n", q.front);
            deleted[del_count] = q.front;
            del_count++;
            printf("%d was removed successfully\n", deQueue_n(&q));
            break;
        case 4:
            display_n(&q);
            break;
        case 5:
            show_pointers(&q);
            break;
        case 6:
            show_deleted(deleted, del_count);
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }
}
