#ifndef BINTREE_LIB_H
#define BINTREE_LIB_H
#include "bintree_struct.h"
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

T_Error bintree_make(Node** root);
T_Error bintree_search_key(Node* ptr, KeyType key, Node** ret); // Searching key in tree
T_Error bintree_search_info(InfoList* ptr, uint64_t num, InfoList** ret); // Searching certain information
Node* bintree_search_min(Node* ptr);
Node* bintree_search_max(Node* ptr);
T_Error bintree_search_special(Node* root, KeyType key, Node** special_key_ret);
T_Error bintree_insert(Node** root, KeyType key, InfoType info); // Insert in the tree
T_Error bintree_insert_info(InfoList** ptr, InfoType info);
T_Error bintree_delete(Node** root, KeyType key);
T_Error bintree_delete_info(InfoList** head, uint64_t num);
T_Error bintree_traversal_direct(Node* root, KeyType key);
T_Error bintree_print(Node* ptr, uint64_t shift);
T_Error bintree_output_graphviz(Node* root);
T_Error bintree_free_node(Node* node);
T_Error bintree_free_infolist(InfoList* list);
T_Error bintree_free(Node** root);
T_Error bintree_copy_infolist(InfoList* old, InfoList* new);
T_Error bintree_insert_from_file(Node** root, char* file_name);
char* readline_file_text(FILE *file);

void print_errors(T_Error error);
#endif //BINTREE_LIB_H
