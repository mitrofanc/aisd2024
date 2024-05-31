#ifndef INC_5_GRAPH_DIALOG_H
#define INC_5_GRAPH_DIALOG_H
#include "graph_lib.h"
#include <readline/readline.h>

T_Error Graph_Make(Graph** graph);
T_Error Graph_Initialize(Graph* graph);
T_Error Graph_Insert_Vertex(Graph* graph);
T_Error Graph_Insert_Edge(Graph* graph);
T_Error Graph_Erase_Vertex(Graph* graph);
T_Error Graph_Erase_Edge(Graph* graph);
T_Error Graph_Change_Vertex(Graph* graph);
T_Error Graph_Change_Edge(Graph* graph);
T_Error Graph_Output_Adjacency_List(Graph* graph);
T_Error Graph_Output_GraphViz(Graph* graph);
T_Error Graph_Num_Handshakes(Graph* graph);
T_Error Graph_Shortest_Path(Graph* graph);
T_Error Graph_Longest_Path(Graph* graph);
T_Error Graph_Input_From_File(Graph** graph);
uint64_t get_u64();
int get_int();
void clearbuf();
void print_menu();
void print_errors(T_Error error);
#endif //INC_5_GRAPH_DIALOG_H
