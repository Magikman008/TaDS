#include "../inc/structs.h"
#include "../inc/menu.h"
#include "../inc/array_stack.h"
#include "../inc/some_funcs.h"
#include "../inc/node_stack.h"

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

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc"
                         : "=A"(d));
    return d;
}

void array_stack_menu()
{
    int option, go = 1, rc;

    long long unsigned t_start, t_end;

    stack_t *s = createStack();

    while (go)
    {
        puts(gr "1. " res " Check string for correction\n" gr
                "2. " res " Add element to stack\n" gr
                "3. " res " Remove top element from stack\n" gr
                "4. " res " Print stack from top\n" gr
                "5. " res " Clear stack\n" gr
                "0. " res " Leave program\n" gr);
        printf(blue "Enter number of command: " res);
        if (input_number(&option))
            option = -1;

        printf(del del del del del del del del);

        switch (option)
        {
        case 1:
            if ((rc = check_array_stack()))
            {
                puts(red "No bracket" res);
                input_number(&option);
            }
            break;
        case 2:
        {
            int temp;
            printf(blue "Enter a  number: " res);
            input_number(&temp);
            if (temp)
            {
                t_start = tick();
                push(s, temp);
                t_end = tick();
                puts(yel "Item was succesfulle added to top" res);
            }
            else
                puts(red "Not a number" res);

            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        }
        case 3:
            t_start = tick();
            pop(s);
            t_end = tick();
            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        case 4:
            if (s->top == 0)
            {
                puts("Stack empty");
                break;
            }
            while (s->top != 0)
                printf("%d ", pop(s));
            puts("");
            break;
        case 5:
            while (s->top != 0)
                pop(s);
            puts(yel "Stack was succesfulle cleared" res);
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }

    deleteStack(&s);
}

void node_stack_menu()
{
    int option, go = 1, rc;
    long long unsigned t_start, t_end;

    node_t *s = NULL;

    while (go)
    {
        puts(gr "1. " res " Check string for correction\n" gr
                "2. " res " Add element to stack\n" gr
                "3. " res " Remove top element from stack\n" gr
                "4. " res " Print stack from top\n" gr
                "5. " res " Clear stack\n" gr
                "0. " res " Leave program\n" gr);
        printf(blue "Enter number of command: " res);
        input_number(&option);

        printf(del del del del del del del del);

        switch (option)
        {
        case 1:
            if ((rc = check_node_stack()))
            {
                puts(red "No bracket" res);
                input_number(&option);
            }
            break;
        case 2:
        {
            int temp;
            printf(blue "Enter a  number: " res);
            input_number(&temp);
            if (temp)
            {
                t_start = tick();
                npush(&s, temp);
                t_end = tick();
                puts(yel "Item was succesfulle added to top" res);
            }
            else
                puts(red "Not a number" res);

            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        }
        case 3:
            t_start = tick();
            npop(&s);
            t_end = tick();
            printf("Ticks spent %llu\n", (t_end - t_start));
            break;
        case 4:
            if (s == NULL)
            {
                puts("Stack empty");
                break;
            }
            while (s)
                printf("%d ", npop(&s));
            puts("");
            break;
        case 5:
            while (s)
                npop(&s);
            puts(yel "Stack was succesfulle cleared" res);
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        case -1:
            puts(red "\nWrong input\n" res);
            break;
        default:
            puts(red "\nNo such option\n" res);
        }
    }

    while (s)
        npop(&s);
}
