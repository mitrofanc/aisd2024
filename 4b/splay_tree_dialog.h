#ifndef SPLAY_TREE_DIALOG_H
#define SPLAY_TREE_DIALOG_H
#include "splay_tree_lib.h"

T_Error D_Search(Node** root);
T_Error D_Search_Special(Node* *root);
T_Error D_Insert(Node** root);
T_Error D_Delete(Node** root);
T_Error D_Output_Console(Node* root);
T_Error D_Traversal(Node* root);
T_Error D_Output_GraphViz(Node* root);
T_Error D_Insert_From_File(Node** root);
uint64_t get_u64();
#endif //LAB4B_DIALOG_H
