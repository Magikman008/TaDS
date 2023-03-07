#include "../inc/graph.h"
#include "../inc/structs.h"
#include "../inc/node_queue.h"

void show_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%3d", matrix[i][j]);
        puts("");
    }
}

void *free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->vertices; i++)
        free(graph->matrix[i]);

    free(graph->matrix);
    free(graph);

    return NULL;
}

void *input_graph(graph_t *graph)
{
    graph = calloc(1, sizeof(graph_t));
    printf("Enter number of vertices: ");

    if (scanf("%d", &graph->vertices) != 1)
    {
        free_graph(graph);
        puts(red "Not a number" res);
        return NULL;
    }

    graph->matrix = calloc(graph->vertices, sizeof(int *));
    if (graph->matrix == NULL)
    {
        free_graph(graph);
        puts(red "Error alloc matrix" res);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        graph->matrix[i] = calloc(graph->vertices, sizeof(int));
        if (graph->matrix[i] == NULL)
        {
            free_graph(graph);
            puts(red "Error alloc matrix" res);
            return NULL;
        }
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
        {
            printf(del "Enter path length from %d and %d: ", i, j);
            if (scanf("%d", &graph->matrix[i][j]) != 1)
            {
                free_graph(graph);
                puts(red "Not a number" res);
                return NULL;
            }
            else
                graph->matrix[j][i] = graph->matrix[i][j];
        }
    }
    printf(del);

    puts(yel "Graph was successfuly initialized" res);
    return graph;
}

void *file_input_graph(graph_t *graph)
{
    graph = calloc(1, sizeof(graph_t));

    FILE *f = fopen("in.txt", "r");

    if (fscanf(f, "%d", &graph->vertices) != 1)
    {
        free_graph(graph);
        puts(red "Not a number" res);
        fclose(f);
        return NULL;
    }

    graph->matrix = calloc(graph->vertices, sizeof(int *));
    if (graph->matrix == NULL)
    {
        free_graph(graph);
        puts(red "Error alloc matrix" res);
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        graph->matrix[i] = calloc(graph->vertices, sizeof(int));
        if (graph->matrix[i] == NULL)
        {
            free_graph(graph);
            puts(red "Error alloc matrix" res);
            fclose(f);
            return NULL;
        }
    }

    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
        {
            if (fscanf(f, "%d", &graph->matrix[i][j]) != 1)
            {
                free_graph(graph);
                puts(red "Not a number" res);
                fclose(f);
                return NULL;
            }
            else
                graph->matrix[j][i] = graph->matrix[i][j];
        }
    }

    puts(yel "Graph was successfuly initialized" res);
    fclose(f);
    return graph;
}

void show_graph(graph_t *graph)
{
    if (graph == NULL)
    {
        puts(red "Graph not initialized" res);
        return;
    }

    FILE *f = fopen("temp.gv", "w");
    fprintf(f, "strict graph {\n");
    for (int i = 0; i < graph->vertices; i++)
        for (int j = i + 1; j < graph->vertices; j++)
            if (graph->matrix[i][j] != 0)
                fprintf(f, "\"%d\"--\"%d\" [label=\"%d\"];\n", i + 1, j + 1, graph->matrix[i][j]);

    fprintf(f, "}\n");
    fclose(f);

    f = popen("dot -Tsvg temp.gv -ograph.svg", "r");
    pclose(f);
    f = popen("rm -rf temp.gv", "r");
    pclose(f);
    f = popen("xdg-open ./graph.svg", "r");
    pclose(f);
}

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

void input_word(char *str, char *print)
{
    strcpy(str, "");
    printf("%s", print);

    if (fgets(str, 100, stdin) != str)
        puts(red "Couldn't scan the line" res);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void find_way(graph_t *graph, bool whole)
{
    if (graph == NULL)
    {
        puts(red "Graph not initialized" res);
        return;
    }

    int from;
    int to;

    bool *lined = calloc(graph->vertices, sizeof(bool));
    if (lined == NULL)
    {
        puts(red "Error alloc lined" res);
        return;
    }

    bool *visided = calloc(graph->vertices, sizeof(bool));
    if (visided == NULL)
    {
        puts(red "Error alloc visided" res);
        return;
    }

    int *weights = calloc(graph->vertices + 1, sizeof(int));
    if (weights == NULL)
    {
        puts(red "Error alloc weights" res);
        return;
    }

    printf("Enter source vert: ");
    if (scanf("%d", &from) != 1)
    {
        puts(red "Not a number" res);
        return;
    }

    if (!whole)
    {
        printf("Enter distanation vert: ");
        if (scanf("%d", &to) != 1)
        {
            puts(red "Not a number" res);
            return;
        }
    }

    input_number(NULL);
    from--;

    node_q q = {0};
    q.front = NULL;
    q.rear = NULL;

    enQueue_n(from, &q);

    for (int i = 0; i < graph->vertices; i++)
        weights[i] = 10000;

    weights[from] = 0;
    lined[from] = true;

    while (!isEmpty_n(&q))
    {
        for (int j = 0; j < graph->vertices; j++)

            if (j != q.front->data && graph->matrix[q.front->data][j] != 0 && visided[j] != true && weights[j] > graph->matrix[q.front->data][j] + weights[q.front->data])
                weights[j] = graph->matrix[q.front->data][j] + weights[q.front->data];

        int index;
        for (int i = 0; i < graph->vertices; i++)
        {
            index = 0;

            for (int j = 0; j < graph->vertices; j++)
                if (graph->matrix[q.front->data][j] > graph->matrix[q.front->data][index])
                    index = j;

            for (int j = 0; j < graph->vertices; j++)
                if (lined[j] != true && graph->matrix[q.front->data][j] != 0 && graph->matrix[q.front->data][j] <= graph->matrix[q.front->data][index])
                    index = j;

            if (lined[index] != true)
            {
                enQueue_n(index, &q);
                lined[index] = true;
            }
        }

        visided[q.front->data] = true;
        deQueue_n(&q);
    }

    if (whole)
        for (int i = 0; i < graph->vertices; i++)
            printf("Way from %d to %d is %d\n", from + 1, i + 1, weights[i]);
    else
        printf("Way from %d to %d is %d\n", from + 1, to, weights[to - 1]);

    free(visided);
    free(lined);
    free(weights);
}
