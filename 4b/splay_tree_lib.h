#ifndef SPLAY_TREE_LIB_H
#define SPLAY_TREE_LIB_H
#include "splay_tree_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef enum T_Error{ //todo remake print_errors
    ERROR_NO,
    ERROR_ALLOC_MEM,
    ERROR_TREE_NULL,
    ERROR_NOT_KEY,
    ERROR_NOT_NUM,
    ERROR_INPUT,
    ERROR_END_OF_TREE,
    ERROR_EMPTY_INFOLIST,
    ERROR_NO_FILE,
    ERROR_READING_FILE,
} T_Error;

Node* left_rotate(Node* x);
Node* right_rotate(Node* x);
T_Error splay(Node** x, Node** root);
T_Error splay_tree_search(Node** root, KeyType key, Node** ret);
T_Error splay_tree_search_wos(Node* ptr, KeyType key, Node** ret);
T_Error splay_tree_search_min(Node** root, Node** ret);
T_Error splay_tree_insert(Node** root, KeyType key, InfoType info);
T_Error splay_tree_insert_info(InfoList** ptr, InfoType info);
T_Error splay_tree_delete(Node** root, KeyType key);
InfoList* splay_tree_delete_oldest_wos(InfoList* head);
T_Error splay_tree_delete_oldest(Node** root, Node* node);
T_Error splay_tree_print_infolist(InfoList* ptr);
T_Error splay_tree_print(Node* ptr, uint64_t shift);
T_Error splay_tree_copy_infolist(InfoList* old, InfoList** new);
T_Error splay_tree_free(Node** root);
T_Error splay_tree_free_node(Node* node);
T_Error splay_tree_free_infolist(InfoList** list);
T_Error splay_tree_traversal_reverse(Node* ptr);
T_Error splay_tree_output_graphviz_links(Node* ptr);
T_Error splay_tree_output_graphviz(Node* ptr);
T_Error splay_tree_insert_from_file(Node** root, char* file_name);

void print_errors(T_Error error);
#endif //LAB4B_LIB_H
