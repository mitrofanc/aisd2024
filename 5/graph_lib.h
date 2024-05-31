#ifndef INC_5_GRAPH_LIB_H
#define INC_5_GRAPH_LIB_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph_struct.h"
#include "queue.h"

typedef enum T_Error{
    ERROR_NO,
    ERROR_ALLOC_MEM,
    ERROR_GRAPH_NULL,
    ERROR_NOT_VERTEX,
    ERROR_NOT_EDGE,
//    ERROR_INPUT,
//    ERROR_END_OF_TREE,
//    ERROR_EMPTY_INFOLIST,
    ERROR_NO_FILE,
    ERROR_HAVE_VERTEX,
//    ERROR_READING_FILE,
} T_Error;

T_Error graph_make(Graph** graph, uint64_t count);
Vertex* graph_search_vertex(Graph* graph, char* name, uint64_t* index);
T_Error graph_insert_vertex(Graph* graph, char* name);
T_Error graph_erase_vertex(Graph* graph, char* name);
T_Error graph_insert_edge(Graph* graph, char* name_from, char* name_to, int mark);
T_Error graph_erase_edge(Graph* graph, char* name_from, char* name_to);
T_Error graph_change_vertex(Graph* graph, char* old_name, char* new_name);
T_Error graph_change_edge(Graph* graph, char* name_from, char* name_to, int new_mark);
T_Error graph_output_adjacency_list(Graph* graph);
T_Error graph_output_graphviz(Graph* graph);
T_Error graph_BFS(Graph* graph, char* source_name);
T_Error graph_search_handshakes(Graph* graph, int num, char* source_name);
T_Error graph_Bellman_Ford(Graph* graph, char* source_name);
T_Error graph_shortest_path(Graph* graph, char* first_name, char* second_name, int* ret);
T_Error graph_longest_path(Graph* graph, char* source_name);
T_Error graph_longest_path_external(Graph* graph, char* first_name, char* second_name, int* ret);
T_Error graph_free(Graph** graph);
T_Error graph_input_from_file(Graph** graph, char* file_name);
void print_funcv(void* data);

#endif //INC_5_GRAPH_LIB_H
