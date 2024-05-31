#include "graph_dialog.h"
#define PROMPT ""
#define floor(x) ((float)((int)x))

T_Error Graph_Make(Graph** graph){
    printf("Input number of vertexes: ");
    uint64_t count = get_u64();
    return graph_make(graph, count);
}

T_Error Graph_Initialize(Graph* graph){
    char* name = NULL;
    T_Error error = ERROR_NO;
    for (uint64_t i = 0; i < graph->m_size; i++){
        printf("Enter %llu vertex: ", i + 1);
        name = readline(PROMPT);
        error = graph_insert_vertex(graph, name);
        if (error) return error;
        free(name);
    }
    char *name_from = NULL, *name_to = NULL;
    int mark = 0;
    printf("1. Add edge\n2. Exit\n");
    uint64_t choice = get_u64();
    while (choice == 1){
        printf("Enter FROM vertex: ");
        name_from = readline(PROMPT);
        printf("Enter TO vertex: ");
        name_to = readline(PROMPT);
        printf("Enter the mark of relationship between people: ");
        mark = get_int();
        error = graph_insert_edge(graph, name_from, name_to, mark);
        if (error) return error;
        printf("1. Add edge\n2. Exit\n");
        choice = get_u64();
    }
    free(name_from);
    free(name_to);
    return ERROR_NO;
}

T_Error Graph_Insert_Vertex(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the vertex to insert: ");
    char *name = readline(PROMPT);
    T_Error error = graph_insert_vertex(graph, name);
    free(name);
    return error;
}

T_Error Graph_Insert_Edge(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter FROM vertex: ");;
    char* name_from = readline(PROMPT);
    printf("Enter TO vertex: ");
    char* name_to = readline(PROMPT);
    printf("Enter the mark of relationship between people: ");
    int mark = get_int();
    T_Error error = graph_insert_edge(graph, name_from, name_to, mark);
    free(name_to);
    free(name_from);
    return error;
}

T_Error Graph_Erase_Vertex(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter name of the vertex to erase: ");
    char* name = readline(PROMPT);
    T_Error error = graph_erase_vertex(graph, name);
    free(name);
    return error;
}

T_Error Graph_Erase_Edge(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter FROM vertex: ");;
    char* name_from = readline(PROMPT);
    printf("Enter TO vertex: ");
    char* name_to = readline(PROMPT);
    T_Error error = graph_erase_edge(graph, name_from, name_to);
    free(name_from);
    free(name_to);
    return error;
}

T_Error Graph_Change_Vertex(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the name of vertex to change: ");
    char *old_name = readline(PROMPT);
    printf("Enter the changed name: ");
    char *new_name = readline(PROMPT);
    T_Error error = graph_change_vertex(graph, old_name, new_name);
    free(old_name);
    free(new_name);
    return error;
}

T_Error Graph_Change_Edge(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the first vertex: ");
    char* name_first = readline(PROMPT);
    printf("Enter the second vertex: ");
    char* name_second = readline(PROMPT);
    printf("Enter new mark: ");
    int new_mark = get_int();
    T_Error error = graph_change_edge(graph, name_first, name_second, new_mark);
    free(name_first);
    free(name_second);
    return error;
}

T_Error Graph_Output_Adjacency_List(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    return graph_output_adjacency_list(graph);
}

T_Error Graph_Output_GraphViz(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    return graph_output_graphviz(graph);
}

T_Error Graph_Num_Handshakes(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the source for BFS: ");
    char* source_name = readline(PROMPT);
    printf("Number of handshakes: ");
    int num = get_int();
    T_Error error = graph_search_handshakes(graph, num, source_name);
    free(source_name);
    return error;
}

T_Error Graph_Shortest_Path(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the first vertex: ");
    char* first_name = readline(PROMPT);
    printf("Enter the second vertex: ");
    char* second_name = readline(PROMPT);
    int ret;
    T_Error error = graph_shortest_path(graph, first_name, second_name, &ret);
    printf("Shortest path: %d\n", ret);
    free(first_name);
    free(second_name);
    return error;
}

T_Error Graph_Longest_Path(Graph* graph){
    if (!graph || !graph->vertex_vector) return ERROR_GRAPH_NULL;
    printf("Enter the first vertex: ");
    char* first_name = readline(PROMPT);
    printf("Enter the second vertex: ");
    char* second_name = readline(PROMPT);
    int ret;
    T_Error error = graph_longest_path_external(graph, first_name, second_name, &ret);
    printf("Longest path: %d\n", ret);
    free(first_name);
    free(second_name);
    return error;
}

T_Error Graph_Input_From_File(Graph** graph){
    printf("Input file's name: ");
    char* file_name = readline(PROMPT);
    if (!file_name) return ERROR_NO_FILE;
    return graph_input_from_file(graph, file_name);
}

uint64_t get_u64(){
    char* str = NULL;
    int flag = 1;
    uint64_t num = 0;
    while (flag){
        flag = 0;
        str = readline(PROMPT);
        if(!str){
            flag = 1;
            continue;
        }
        size_t len = strlen(str);
        for (size_t i = 0; i < len; i++){
            if (str[i] < '0' || str[i] > '9') {flag = 1; free(str); break;}
        }
        if (flag) {
            continue;
        }
        num = strtoull(str, NULL, 10);
        free(str);
    }
    return num;
}

int get_int(){
    float tmp;
    scanf("%f", &tmp);
    printf("\n");
    while (floor(tmp) - tmp != 0){
        clearbuf();
        printf("Введите данный элемент заново:\n");
        scanf("%f", &tmp);
        printf("\n");
    }
    return (int) tmp;
}

void clearbuf(){
    char symbol = ' ';
            symbol = getchar();
    while ((symbol != '\n') && (symbol != EOF))
    {
        symbol = getchar();
    }

}

void print_menu(){
    printf("Select an action:\n");
    printf("1. Make graph\n");
    printf("2. Graph initialization\n");
    printf("3. Add vertex\n");
    printf("4. Add edge\n");
    printf("5. Erase vertex\n");
    printf("6. Erase edge\n");
    printf("7. Change vertex name\n");
    printf("8. Change edge information\n");
    printf("9. Output graph like adjacency list\n");
    printf("10. Output graph with GraphViz\n");
    printf("11. Graph traversal\n");
    printf("12. The shortest path between vertexes\n");
    printf("13. Path with maximum rating\n");
    printf("14. Input graph from file\n");
    printf("15. Exit\n");
    printf("\n");
}

void print_errors(T_Error error){
    switch (error){
        case 0:
            break;
        case 1:
            printf("ERROR: Can`t allocate memory\n");
            break;
        case 2:
            printf("ERROR: Don`t have graph\n");
            break;
        case 3:
            printf("ERROR: Don`t have this vertex\n");
            break;
        case 4:
            printf("ERROR: Don`t have this edge\n");
            break;
        case 5:
            printf("ERROR: Don`t have this file\n");
            break;
        case 6:
            printf("ERROR: Already have this key\n");
            break;
    }
    printf("\n");
}