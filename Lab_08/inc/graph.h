#ifndef SOME_F_H
#define SOME_F_H

#include "../inc/structs.h"

void *input_graph(graph_t *graph);
void *file_input_graph(graph_t *graph);
void show_matrix(int **matrix, int size);
int input_number(int *num);
void show_graph(graph_t *graph);
void find_way(graph_t *graph, bool whole);
void *free_graph(graph_t *graph);

#endif
