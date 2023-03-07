#include "../inc/structs.h"
#include "../inc/array_queue.h"
#include "../inc/node_queue.h"

float pogr(float l1, float r1, float l2, float r2)
{
    float work_time = 1000 * (r2 - l2) / 2 * 5;
    float in_time = 1000 * (r1 - l1) / 2;
    float wait_time = in_time - work_time;

    return wait_time;
}

int input_ranges(int *l1, int *r1, int *l2, int *r2)
{
    printf("Enter integer range time entering to queue(in format: 0 6): ");
    if (scanf("%d%d", l1, r1) == 0)
    {
        printf(red "Incorrect input" res);
        return ERROR_BAD_INPUT;
    }

    printf("Enter integer range time processing(in format: 0 1): ");
    if (scanf("%d%d", l2, r2) == 0)
    {
        printf(red "Incorrect input" res);
        return ERROR_BAD_INPUT;
    }

    if ((*l1 == 0 && *r1 == 0) || (*l2 == 0 && *r2 == 0))
    {
        printf(red "Zero interval\n" res);
        return ERROR_BAD_INPUT;
    }

    char line[1024];
    fgets(line, 1024, stdin);

    return EXIT_SUCCESS;
}

void model_array_queue()
{
    queue_t q = {0};
    q.front = -1;
    q.rear = -1;

    srand(time(NULL));
    float r;
    int l1 = 0, r1 = 2, l2 = 0, r2 = 1;

    float in, proc;                   // общее время входа и обработки
    float in_prev = 0, proc_prev = 0; // время входа и обработки предыдущего элемента
    float t_in, t_proc;               // текущее время прихода и обработки заявки
    float downtime = 0;               // время простоя
    int worked = 0;                   // количество срабатываний ОА
    int exited = 0;                   // счетчик вышедших из ОА (1000 = завершение программы)
    int p;                            // вероятность выхода из ОА
    int queue_len = 1;                // длина очереди
    float average_len = 0;
    float average_time = 0;
    float time_in_queue = 0;
    int len_amount = 0;
    float time_amount = 0;
    float ideal_wait;

    if (input_ranges(&l1, &r1, &l2, &r2))
        return;

    ideal_wait = pogr(l1, r1, l2, r2);

    while (exited != 1000)
    {
        len_amount += queue_len;

        enQueue(1, &q);

        worked += 1;
        r = (float)rand() / (float)RAND_MAX;
        t_in = l1 + (r1 - l1) * r;

        r = (float)rand() / (float)RAND_MAX;
        t_proc = l2 + (r2 - l2) * r;

        in += t_in;
        proc += t_proc;

        if (worked != 1)
        {

            time_in_queue += abs((int)(t_in - in_prev));

            if (t_in >= proc_prev)
            {
                if (queue_len > 1)
                {
                    deQueue(&q);
                    queue_len -= 1;
                }
                else
                {
                    if (downtime < ideal_wait && ideal_wait > 0)
                        downtime += (t_in - proc_prev);
                }
            }
            else if (t_in < proc_prev)
            {
                time_amount += proc_prev - t_in;
                enQueue(1, &q);
                queue_len += 1;
            }
        }

        p = rand() % 5;

        if (p == 4)
        {
            deQueue(&q);
            exited += 1;
            if (exited != 0 && exited % 100 == 0)
            {
                average_len = len_amount / worked;
                average_time = time_amount / worked;
                printf(blue "─────────────────────────────────────────────\n" res);
                printf("Current queue len: %d\n", queue_len);
                printf("Average queue len: %f\n", average_len);
                printf("Average time in queue: %f\n", average_time);
                printf("Number items left queue: %d\n", exited);
            }
        }

        in_prev = t_in;
        proc_prev = t_proc;
    }

    float modeling = proc + downtime;
    int in_elements = (int)(modeling / (((float)r1 - (float)l1) / 2));
    printf(blue "─────────────────────────────────────────────\n\n" res);
    printf(blue "                     RESULT                  \n" res);
    printf(blue "─────────────────────────────────────────────\n" res);
    printf("OA workes %d times\n", worked);
    printf("Modeling time: %f\n", modeling);
    printf("OA downtime %f\n", downtime);
    printf("Count of in elemnts: %d\n", in_elements);
    printf("Count of out elements: 1000\n");
    printf(blue "─────────────────────────────────────────────\n" res);
}

void model_node_queue()
{
    node_q q = {0};
    q.front = NULL;
    q.rear = NULL;

    srand(time(NULL));
    float r;
    int l1 = 0, r1 = 1, l2 = 0, r2 = 6;

    float in, proc;                   // общее время входа и обработки
    float in_prev = 0, proc_prev = 0; // время входа и обработки предыдущего элемента
    float t_in, t_proc;               // текущее время прихода и обработки заявки
    float downtime = 0;               // время простоя
    int worked = 0;                   // количество срабатываний ОА
    int exited = 0;                   // счетчик вышедших из ОА (1000 = завершение программы)
    int p;                            // вероятность выхода из ОА
    int queue_len = 1;                // длина очереди
    float average_len = 0;
    float average_time = 0;
    float time_in_queue = 0;
    int len_amount = 0;
    float time_amount = 0;
    float ideal_wait;

    if (input_ranges(&l1, &r1, &l2, &r2))
        return;

    ideal_wait = pogr(l1, r1, l2, r2);

    while (exited != 1000)
    {
        len_amount += queue_len;
        enQueue_n(1, &q);

        worked += 1;
        r = (float)rand() / (float)RAND_MAX;
        t_in = l1 + (r1 - l1) * r;

        r = (float)rand() / (float)RAND_MAX;
        t_proc = l2 + (r2 - l2) * r;

        in += t_in;
        proc += t_proc;

        if (worked != 1)
        {

            time_in_queue += abs((int)(t_in - in_prev));

            if (t_in >= proc_prev)
            {
                if (queue_len > 1)
                {
                    deQueue_n(&q);
                    queue_len -= 1;
                }
                else
                {
                    if (downtime < ideal_wait && ideal_wait > 0)
                        downtime += (t_in - proc_prev);
                }
            }
            else if (t_in < proc_prev)
            {
                time_amount += proc_prev - t_in;
                enQueue_n(1, &q);
                queue_len += 1;
            }
        }

        p = rand() % 5;

        if (p == 4)
        {
            deQueue_n(&q);
            exited += 1;
            if (exited != 0 && exited % 100 == 0)
            {
                average_len = len_amount / worked;
                average_time = time_amount / worked;
                printf(blue "─────────────────────────────────────────────\n" res);
                printf("Current queue len: %d\n", queue_len);
                printf("Average queue len: %f\n", average_len);
                printf("Average time in queue: %f\n", average_time);
                printf("Number items left queue: %d\n", exited);
            }
        }

        in_prev = t_in;
        proc_prev = t_proc;
    }

    float modeling = proc + downtime;
    int in_elements = (int)(modeling / (((float)r1 - (float)l1) / 2));
    printf(blue "─────────────────────────────────────────────\n\n" res);
    printf(blue "                     RESULT                  \n" res);
    printf("OA workes %d times\n", worked);
    printf("Modeling time: %f\n", modeling);
    printf("OA downtime %f\n", downtime);
    printf("Count of in elemnts: %d\n", in_elements);
    printf("Count of out elements: 1000\n");
    printf(blue "─────────────────────────────────────────────\n" res);
}
