#include "splay_tree_dialog.h"

#ifndef NDEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

int main(){
    Node* root = NULL;
    uint64_t choice = 0;
    T_Error error = ERROR_NO;
    while (choice < 9){
        printf("Select an action:\n");
        printf("1. Search node\n");
        printf("2. Special search node (minimal)\n");
        printf("3. Insert node\n");
        printf("4. Delete node\n");
        printf("5. Traversal tree\n");
        printf("6. Output tree to the console\n");
        printf("7. Output tree with GraphViz\n");
        printf("8. Initialize tree from file\n");
        printf("9. Exit\n");
        printf("\n");
        choice = get_u64();
        printf("\e[1;1H\e[2J");
        switch (choice){
            case 1:
                error = D_Search(&root);
                break;
            case 2:
                error = D_Search_Special(&root);
                break;
            case 3:
                error = D_Insert(&root);
                break;
            case 4:
                error = D_Delete(&root);
                break;
            case 5:
                error = D_Traversal(root);
                break;
            case 6:
                error = D_Output_Console(root);
                break;
            case 7:
                error = D_Output_GraphViz(root);
                break;
            case 8:
                error = D_Insert_From_File(&root);
                break;
        }
        print_errors(error);
    }
    splay_tree_free(&root);
    return 0;
}