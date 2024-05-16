#ifndef BINTREE_DIALOG_H
#define BINTREE_DIALOG_H
#include "bintree_lib.h"
#include <readline/readline.h>

T_Error D_Make(Node** root);
T_Error D_Search(Node* root);
T_Error D_Search_Special(Node* root);
T_Error D_Insert(Node** root);
T_Error D_Delete(Node** root);
T_Error D_Traversal(Node* root);
T_Error D_Output_Console(Node* root);
T_Error D_Output_GraphViz(Node* root);
T_Error D_Insert_From_File(Node** root);
uint64_t get_u64();
#endif //BINTREE_DIALOG_H
