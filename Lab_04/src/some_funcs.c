#include "../inc/structs.h"
#include "../inc/some_funcs.h"
#include "../inc/array_stack.h"
#include "../inc/node_stack.h"

int input(char *c)
{
    if (scanf("%c", c) != 1)
        return 0;
    if (*c != ')' && *c != '(' && *c != ']' && *c != '[' && *c != '}' && *c != '{')
        return 0;
    return 1;
}

int check_array_stack()
{
    stack_t *s = createStack();

    if (s == NULL)
        puts(red "Error on creating stack" res);

    char c;

    printf("Enter your string. " yel "Scans char-by-char until the first incorrect simbol or the end of line: " res);

    if (input(&c) == 0)
        return EXIT_FAILURE;

    push(s, c);
    char prev = peek(s);

    while (input(&c) == 1)
    {
        if (c == ')' && prev == '(')
            pop(s);
        else if (c == ']' && prev == '[')
            pop(s);
        else if (c == '}' && prev == '{')
            pop(s);
        else
            push(s, c);

        if (s->top != 0)
            prev = peek(s);
        else
            prev = 'v';
    }

    if (s->top == 0)
        puts("OK");
    else
        puts("NOT OK");

    deleteStack(&s);
    return EXIT_SUCCESS;
}

int check_node_stack()
{
    node_t *s = NULL;

    char c;

    printf("Enter your string. " yel "Scans char-by-char until the first incorrect simbol or the end of line: " res);

    if (input(&c) == 0)
        return EXIT_FAILURE;

    npush(&s, c);
    char prev = npeek(s);

    while (input(&c) == 1)
    {
        if (c == ')' && prev == '(')
            npop(&s);
        else if (c == ']' && prev == '[')
            npop(&s);
        else if (c == '}' && prev == '{')
            npop(&s);
        else
            npush(&s, c);

        if (s != NULL)
            prev = npeek(s);
        else
            prev = 'v';
    }

    if (s == NULL)
        puts("OK");
    else
        puts("NOT OK");

    while (s)
        npop(&s);
    return EXIT_SUCCESS;
}
