#include "graph_dialog.h"

int main(){
    Graph* graph = NULL;
    uint64_t choice = 0;
    T_Error error = ERROR_NO;
    while (choice < 15){
        print_menu();
        choice = get_u64();
        printf("\e[1;1H\e[2J");
        switch (choice){
            case 1:
                error = Graph_Make(&graph);
                break;
            case 2:
                error = Graph_Initialize(graph);
                break;
            case 3:
                error = Graph_Insert_Vertex(graph);
                break;
            case 4:
                error = Graph_Insert_Edge(graph);
                break;
            case 5:
                error = Graph_Erase_Vertex(graph);
                break;
            case 6:
                error = Graph_Erase_Edge(graph);
                break;
            case 7:
                error = Graph_Change_Vertex(graph);
                break;
            case 8:
                error = Graph_Change_Edge(graph);
                break;
            case 9:
                error = Graph_Output_Adjacency_List(graph);
                break;
            case 10:
                error = Graph_Output_GraphViz(graph);
                break;
            case 11:
                error = Graph_Num_Handshakes(graph);
                break;
            case 12:
                error = Graph_Shortest_Path(graph);
                break;
            case 13:
                error = Graph_Longest_Path(graph);
                break;
            case 14:
                error = Graph_Input_From_File(&graph);
                break;
            default:
        }
        print_errors(error);
    }
    graph_free(&graph);
    return 0;
}