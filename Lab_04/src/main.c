#include "../inc/structs.h"
#include "../inc/some_funcs.h"
#include "../inc/menu.h"

int main(void)
{
    int option, go = 1;

    puts(gr "1. " res " Use array stack\n" gr
            "2. " res " Use node stack\n" gr
            "0. " res " Leave program\n" gr);

    while (go)
    {
        printf(blue "Enter number of command: " res);

        if (input_number(&option))
            option = -1;

        printf(del del del del del);
        switch (option)
        {
        case 1:
            puts(yel "Program ran in array stack mode" res);

            array_stack_menu();
            go = 0;
            break;
        case 2:
            puts(yel "Program ran in node stack mode" res);
            node_stack_menu();
            go = 0;
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }

    return EXIT_SUCCESS;
}
