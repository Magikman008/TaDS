#include "../inc/structs.h"
#include "../inc/menu.h"

int main(void)
{
    int option, go = 1;

    while (go)
    {
        puts(gr "1. " res " Use array queue\n" gr
                "2. " res " Use node queue\n" gr
                "0. " res " Leave program\n" gr);
        printf(blue "Enter number of command: " res);
        if (input_number(&option))
            option = -1;

        printf(del del del del del);
        switch (option)
        {
        case 1:
            puts(yel "Program ran in array queue mode" res);
            array_queue_menu();
            go = 0;
            break;
        case 2:
            puts(yel "Program ran in node queue mode" res);
            node_queue_menu();
            go = 0;
            break;
        case 0:
            puts("Goodbye");
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
            break;
        }
    }

    return EXIT_SUCCESS;
}
