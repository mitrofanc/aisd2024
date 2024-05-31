#include "graph_lib.h"

T_Error graph_make(Graph** graph, uint64_t count){
    *graph = calloc(1, sizeof(Graph));
    if (!*graph) return ERROR_ALLOC_MEM;
    (*graph)->m_size = count;
    (*graph)->vertex_vector = calloc(count, sizeof(Vertex*));
    if (!(*graph)->vertex_vector){
        free(*graph);
        *graph = NULL;
        return ERROR_ALLOC_MEM;
    }
    return ERROR_NO;
}

Vertex* graph_search_vertex(Graph* graph, char* name, uint64_t* index){
    if (!graph || !graph->vertex_vector || !name) return NULL;
    for (uint64_t i  = 0; i < graph->m_size; i++){
        if (graph->vertex_vector[i] && strcmp(graph->vertex_vector[i]->name, name) == 0) {
            *index = i;
            return graph->vertex_vector[i];
        }
    }
    return NULL;
}

T_Error graph_insert_vertex(Graph* graph, char* name){
    if (!graph || !graph->vertex_vector || !name) return ERROR_GRAPH_NULL;
    if (graph->c_size == graph->m_size){
        Vertex* *ptr = graph->vertex_vector;
        ptr = realloc(ptr, (graph->m_size + 1) * sizeof(Vertex*));
        if (ptr) graph->vertex_vector = ptr;
        else return ERROR_ALLOC_MEM;
        graph->m_size += 1;
    }
    uint64_t i;
    Vertex* vertex = calloc(1, sizeof(Vertex));
    if (!vertex) return ERROR_ALLOC_MEM;
    vertex->name = strdup(name);
    if (!vertex->name){
        free(vertex);
        return ERROR_ALLOC_MEM;
    }
    vertex->path = -1;
    graph->vertex_vector[graph->c_size] = vertex;
    graph->c_size += 1;
    return ERROR_NO;
}

T_Error graph_insert_edge(Graph* graph, char* name_from, char* name_to, int mark){
    if(!graph || !graph->vertex_vector || !name_from || !name_to) return ERROR_GRAPH_NULL;
    uint64_t i;
    Vertex* from = graph_search_vertex(graph, name_from, &i);
    if (!from) return ERROR_NOT_VERTEX;
    Vertex* to = graph_search_vertex(graph, name_to, &i);
    if (!to) return ERROR_NOT_VERTEX;
    Edge* link_from = (Edge*)calloc(1, sizeof(Edge));
    if (!link_from) return ERROR_ALLOC_MEM;
    link_from->mark = mark;
    link_from->next = from->edges;
    from->edges = link_from;
    link_from->to = to;
    Edge* link_to = (Edge*)calloc(1, sizeof(Edge));
    if (!link_to) return ERROR_ALLOC_MEM;
    link_to->mark = mark;
    link_to->next = to->edges;
    to->edges = link_to;
    link_to->to = from;
    return ERROR_NO;
}

T_Error graph_erase_vertex(Graph* graph, char* name){
    uint64_t index = 0;
    Vertex* vertex = graph_search_vertex(graph, name, &index);
    if (!vertex) return ERROR_NOT_VERTEX;
    Edge *ptr = vertex->edges, *ptr_prev = NULL;
    T_Error error = ERROR_NO;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        error = graph_erase_edge(graph, name, ptr_prev->to->name);
        if (error) return error;
    }
    free(vertex->name);
    free(vertex);
    for (uint64_t i = index; i < graph->m_size - 1; i++){
        graph->vertex_vector[i] = graph->vertex_vector[i + 1];
    }
    graph->m_size -= 1;
    graph->c_size -= 1;
    Vertex* *tmp = graph->vertex_vector;
    tmp = (Vertex**) realloc(graph->vertex_vector, (graph->m_size) * sizeof(Vertex*));
    if (tmp) graph->vertex_vector = tmp;
    else return ERROR_ALLOC_MEM;
    return ERROR_NO;
}

T_Error graph_erase_edge(Graph* graph, char* name_from, char* name_to){
    uint64_t i;
    Vertex* from = graph_search_vertex(graph, name_from, &i);
    if (!from) return ERROR_NOT_VERTEX;
    Vertex* to = graph_search_vertex(graph, name_to, &i);
    if (!to) return ERROR_NOT_VERTEX;
    Edge *ptr_from = from->edges, *ptr_prev_from = NULL, *ptr_to = to->edges, *ptr_prev_to = NULL;
    while (ptr_from && ptr_from->to != to){
        ptr_prev_from = ptr_from;
        ptr_from = ptr_from->next;
    }
    if (!ptr_from) return ERROR_NOT_EDGE;
    if (!ptr_prev_from) from->edges = ptr_from->next;
    else ptr_prev_from->next = ptr_from->next;
    free(ptr_from);
    while (ptr_to && ptr_to->to != from){
        ptr_prev_to = ptr_to;
        ptr_to = ptr_to->next;
    }
    if (!ptr_to) return ERROR_NOT_EDGE;
    if (!ptr_prev_to) to->edges = ptr_to->next;
    else ptr_prev_to->next = ptr_to->next;
    free(ptr_to);
    return ERROR_NO;
}

T_Error graph_change_vertex(Graph* graph, char* old_name, char* new_name){
    if (!graph || !graph->vertex_vector || !old_name || !new_name) return ERROR_GRAPH_NULL;
    uint64_t i;
    Vertex* vertex = graph_search_vertex(graph, old_name, &i);
    if (!vertex) return ERROR_NOT_VERTEX;
    free(vertex->name);
    vertex->name = strdup(new_name);
    if (!vertex->name) return ERROR_ALLOC_MEM;
    return ERROR_NO;
}

T_Error graph_change_edge(Graph* graph, char* name_from, char* name_to, int new_mark){
    if (!graph || !graph->vertex_vector || !name_from || !name_to) return ERROR_GRAPH_NULL;
    uint64_t i;
    Vertex* from = graph_search_vertex(graph, name_from, &i);
    if (!from) return ERROR_NOT_VERTEX;
    Vertex* to = graph_search_vertex(graph, name_to, &i);
    if (!to) return ERROR_NOT_VERTEX;
    Edge *ptr_from = from->edges, *ptr_to = to->edges;
    while (ptr_from && ptr_from->to != to) ptr_from = ptr_from->next;
    if (!ptr_from) return ERROR_NOT_EDGE;
    ptr_from->mark = new_mark;
    while (ptr_to && ptr_to->to != from) ptr_to = ptr_to->next;
    if (!ptr_to) return ERROR_NOT_EDGE;
    ptr_to->mark = new_mark;
    return ERROR_NO;
}

T_Error graph_output_adjacency_list(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    for (uint64_t i = 0; i < graph->m_size; i++){
        printf("%s    ", graph->vertex_vector[i]->name);
        Edge* ptr = graph->vertex_vector[i]->edges;
        while (ptr){
            printf("%s  ", ptr->to->name);
            ptr = ptr->next;
        }
        printf("\n");
    }
    return ERROR_NO;
}

T_Error graph_output_graphviz(Graph* graph){
    printf("https://dotrend.dozen.mephi.ru/?dot=digraph%%7B");
    for (uint64_t i = 0; i < graph->m_size; i++){
        Edge* ptr = graph->vertex_vector[i]->edges;
        while (ptr){
            printf("%%22%s%%22-%%3E%%22%s%%22%%20%%5Blabel%%3D%%22%%20%%20%d%%20%%22%%5D", graph->vertex_vector[i]->name, ptr->to->name, ptr->mark);
            ptr = ptr->next;
        }
        if (!graph->vertex_vector[i]->edges) printf("%%22%s%%22%%20", graph->vertex_vector[i]->name);
    }
    printf("%%7D\n");
    return ERROR_NO;
}

T_Error graph_BFS(Graph* graph, char* source_name){
    if (!graph || !graph->vertex_vector || !source_name) return ERROR_GRAPH_NULL;
    for (uint64_t i = 0; i < graph->m_size; i++){
        graph->vertex_vector[i]->path = -1;
    }
    Queue* queue = NULL;
    if (make_queue(&queue, graph->m_size) == 1) return ERROR_ALLOC_MEM;
    uint64_t index;
    Vertex* source = graph_search_vertex(graph, source_name, &index);
    if (!source) return ERROR_NOT_VERTEX;
    graph->vertex_vector[index]->path = 0;
    Edge* ptr = graph->vertex_vector[index]->edges;
    while (ptr){
        push_back(queue, ptr->to);
        ptr->to->path = 1;
        ptr = ptr->next;
    }
    int path = 0;
    Vertex* curr_vertex;
    while (empty(queue) == 0){
        printf("\n");
        curr_vertex = pop_front(queue);
        ptr = curr_vertex->edges;
        path += 1;
        while (ptr){
            if (ptr->to->path == -1){
                push_back(queue, ptr->to);
                ptr->to->path = path;
            }
            ptr = ptr->next;
        }
    }
    return ERROR_NO;
}

T_Error graph_search_handshakes(Graph* graph, int num, char* source_name){
    if (!graph || !graph->vertex_vector || !source_name) return ERROR_GRAPH_NULL;
    T_Error error = graph_BFS(graph, source_name);
    if (error) return error;
    printf("Result of search:\n");
    for (uint64_t i = 0; i < graph->m_size; i++){
        if (graph->vertex_vector[i]->path <= num) printf("%s\n", graph->vertex_vector[i]->name);
    }
    return ERROR_NO;
}

T_Error graph_Bellman_Ford(Graph* graph, char* source_name){
    if (!graph || !graph->vertex_vector || !source_name) return ERROR_GRAPH_NULL;
    uint64_t index;
    Vertex* source = graph_search_vertex(graph, source_name, &index);
    if (!source) return ERROR_NOT_VERTEX;
    for (uint64_t i = 0; i < graph->m_size; i++){
        graph->vertex_vector[i]->path = INT32_MAX;
    }
    graph->vertex_vector[index]->path = 0;
    for (uint64_t j = 0; j < graph->m_size - 1; j++){
        Vertex* from = graph->vertex_vector[j];
        Edge* ptr = from->edges;
        while (ptr){
            Vertex* to = ptr->to;
            if (to->path > (ptr->mark + from->path) && from->path != INT32_MAX) to->path = from->path + ptr->mark;
            ptr = ptr->next;
        }
    }
    for (uint64_t j = 0; j < graph->m_size; j++) {
        printf("%s: %d\n", graph->vertex_vector[j]->name, graph->vertex_vector[j]->path);
    }
    return ERROR_NO;
}

T_Error graph_shortest_path(Graph* graph, char* first_name, char* second_name, int* ret){
    if (!graph || !graph->vertex_vector || !first_name || !second_name) return ERROR_GRAPH_NULL;
    T_Error error = graph_Bellman_Ford(graph, first_name);
    if (error) return error;
    uint64_t index;
    Vertex* second = graph_search_vertex(graph, second_name, &index);
    if (!second) return ERROR_NOT_VERTEX;
    *ret = graph->vertex_vector[index]->path;
    return ERROR_NO;
}

T_Error graph_longest_path(Graph* graph, char* source_name){
    if (!graph || !graph->vertex_vector || !source_name) return ERROR_GRAPH_NULL;
    uint64_t index;
    Vertex* source = graph_search_vertex(graph, source_name, &index);
    if (!source) return ERROR_NOT_VERTEX;
    for (uint64_t i = 0; i < graph->m_size; i++){
        graph->vertex_vector[i]->path = INT32_MIN;
    }
    graph->vertex_vector[index]->path = 0;
    for (uint64_t j = 0; j < graph->m_size - 1; j++){
        Vertex* from = graph->vertex_vector[j];
        Edge* ptr = from->edges;
        while (ptr){
            Vertex* to = ptr->to;
            if (to->path < (ptr->mark + from->path) && from->path != INT32_MIN) to->path = from->path + ptr->mark;
            ptr = ptr->next;
        }
    }
    for (uint64_t j = 0; j < graph->m_size; j++) {
        printf("%s: %d\n", graph->vertex_vector[j]->name, graph->vertex_vector[j]->path);
    }
    return ERROR_NO;
}

T_Error graph_longest_path_external(Graph* graph, char* first_name, char* second_name, int* ret){
    if (!graph || !graph->vertex_vector || !first_name || !second_name) return ERROR_GRAPH_NULL;
    T_Error error = graph_longest_path(graph, first_name);
    if (error) return error;
    uint64_t index;
    Vertex* second = graph_search_vertex(graph, second_name, &index);
    if (!second) return ERROR_NOT_VERTEX;
    *ret = graph->vertex_vector[index]->path;
    return ERROR_NO;
}

T_Error graph_free(Graph** graph){
    if (!*graph || !(*graph)->vertex_vector) return ERROR_GRAPH_NULL;
    for (uint64_t i = 0; i < (*graph)->m_size; i++){
        Edge *ptr = (*graph)->vertex_vector[i]->edges, *ptr_prev = NULL;
        while (ptr){
            ptr_prev = ptr;
            ptr = ptr->next;
            free(ptr_prev);
        }
        free((*graph)->vertex_vector[i]->name);
        free((*graph)->vertex_vector[i]);
    }
    free((*graph)->vertex_vector);
    free(*graph);
    *graph = NULL;
    return ERROR_NO;
}

T_Error graph_input_from_file(Graph** graph, char* file_name){
    T_Error error = ERROR_NO;
    FILE* file = fopen(file_name,"r");
    if (!file) {
        fclose(file);
        return ERROR_NO_FILE;
    }
    if (*graph) {
        error = graph_free(graph);
        if (error) return error;
    }
    char from[100], to[100];
    int mark = 0;
    uint64_t num_vertex = 0, num_edge = 0;
    fscanf(file, "%llu", &num_vertex);
    fscanf(file, "%llu", &num_edge);
    error = graph_make(graph, num_vertex);
    if (error) return error;
    for (uint64_t i = 0; i < (*graph)->m_size; i++){
        fscanf(file, "%s", from);
        error = graph_insert_vertex(*graph, from);
        if (error) return error;
    }
    for (uint64_t j = 0; j < num_edge; j++){
        fscanf(file, "%s %s %d", from, to, &mark);
        error = graph_insert_edge(*graph, from, to, mark);
        if (error) {
            fclose(file);
            return error;
        }
    }
    return ERROR_NO;
}



void print_funcv(void* data){
    Vertex* vertex = data;
    printf("%s ", vertex->name);
}