#include "../inc/structs.h"
#include "../inc/graph.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__("rdtsc"
                         : "=A"(d));
    return d;
}

int main(void)
{
    long long unsigned t_start, t_end;
    graph_t *graph = NULL;
    int option, go = 1;

    while (go)
    {
        puts(gr "1. " res " Init graph\n" gr
                "2. " res " Init graph from file\n" gr
                "3. " res " Find way from to\n" gr
                "4. " res " Find all ways from\n" gr
                "5. " res " Show graph\n" gr
                "0. " res " Leave program\n" gr);
        printf(blue "Enter number of command: " res);

        if (input_number(&option))
            option = -1;

        printf(del del del del del del del del);

        switch (option)
        {
        case 1:
            graph = input_graph(graph);
            break;
        case 2:
            graph = file_input_graph(graph);
            break;
        case 3:
            find_way(graph, false);
            break;
        case 4:
            t_start = tick();
            find_way(graph, true);
            t_end = tick();
            printf("Ticks spent: %lld\n", t_end - t_start);
            break;
        case 5:
            show_graph(graph);
            break;
        case 0:
            puts("Goodbye");
            if (graph != NULL)
                graph = free_graph(graph);
            go = 0;
            break;
        default:
            puts(red "No such option or wrong input" res);
        }
    }

    return EXIT_SUCCESS;
}
