#include "bintree_dialog.h"
#define PROMPT ""

#ifndef NDEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

T_Error D_Make(Node** root){
    return bintree_make(root);
}

T_Error D_Search(Node* root){
    if (!root) return ERROR_TREE_NULL;
    printf("Input the key of node to search: ");
    KeyType key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    Node* node_ret = NULL;
    T_Error check = bintree_search_key(root, key, &node_ret);
    if (check) return check;
    if (node_ret->list->num == 1){
        printf("Result of the search: ");
        printf("%s\n", node_ret->list->info);
        return ERROR_NO;
    }
    printf("Input the number of info with this key: ");
    uint64_t num = get_u64();
    InfoList* info_ret = NULL;
    check = bintree_search_info(node_ret->list, num, &info_ret);
    if (check) return check;
    printf("Result of the search: %s\n", info_ret->info);
    return ERROR_NO;
}

T_Error D_Search_Special(Node* root){
    if (!root) return ERROR_TREE_NULL;
    printf("The key for which need to find the minimum key after it: ");
    KeyType key = readline(PROMPT);
    Node* special_key_ret = NULL;
    T_Error error = ERROR_NO;
    error = bintree_search_special(root, key, &special_key_ret);
    if (error) return error;
    printf("Result of the search: %s\n", special_key_ret->key);
    return ERROR_NO;
}

T_Error D_Insert(Node** root){
    printf("Input the key: ");
    KeyType key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    printf("Input the info: ");
    InfoType info = readline(PROMPT);
    if (!info) return ERROR_INPUT;
    return bintree_insert(root, key, info);
}

T_Error D_Delete(Node** root){
    printf("Input the key of node to delete: ");
    KeyType key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    Node* node_ret = NULL;
    T_Error check = ERROR_NO;
    check = bintree_search_key(*root, key, &node_ret);
    if (check) return check;
    if (node_ret->list->num == 1) return bintree_delete(root, key);
    printf("Input the number of info to delete: ");
    uint64_t num = get_u64();
    check = bintree_delete_info(&(node_ret->list), num);
    return check;
}

T_Error D_Traversal(Node* root){
    printf("Output keys less then this key: ");
    KeyType key = readline(PROMPT);
    return bintree_traversal_direct(root, key);
}

T_Error D_Output_Console(Node* root){
    return bintree_print(root, 0);
}

T_Error D_Output_GraphViz(Node* root){
    return bintree_output_graphviz(root);
}

T_Error D_Insert_From_File(Node** root){
    printf("Input file's name: ");
    char* file_name = readline(PROMPT);
    if (!file_name) return ERROR_INPUT;
    return bintree_insert_from_file(root, file_name);
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
        if(flag){
            continue;
        }
        num = strtoull(str, NULL, 10);
        free(str);
    }
    return num;
}