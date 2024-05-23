#include "splay_tree_dialog.h"
#define PROMPT ""

T_Error D_Search(Node** root){
    if (!root) return ERROR_TREE_NULL;
    printf("Input the key of node to search: ");
    KeyType key = get_u64();
    Node* node_ret = NULL;
    T_Error check = splay_tree_search(root, key, &node_ret);
    if (check) return check;
    return splay_tree_print_infolist(node_ret->list);
}

T_Error D_Search_Special(Node** root){
    if (!root) return ERROR_TREE_NULL;
    Node* ret = NULL;
    T_Error error = splay_tree_search_min(root, &ret);
    if (error) return error;
    return splay_tree_print_infolist(ret->list);
}

T_Error D_Insert(Node** root){
    printf("Input the key: ");
    KeyType key = get_u64();
    printf("Input the info: ");
    InfoType info = get_u64();
    return splay_tree_insert(root, key, info);
}

T_Error D_Delete(Node** root){
    if (!*root) return ERROR_TREE_NULL;
    printf("Input the key of node to delete: ");
    KeyType key = get_u64();
    Node* node_ret = NULL;
    T_Error check = splay_tree_search_wos(*root, key, &node_ret);
    if (check) return check;
    if (node_ret->key == key) {
        if (node_ret->list->next) check = splay_tree_delete_oldest(root, node_ret);
        else check = splay_tree_delete(root, key);
        if (check) return check;
    }
    else return splay(&node_ret, root);
    return ERROR_NO;
}

T_Error D_Output_Console(Node* root){
    return splay_tree_print(root, 0);
}

T_Error D_Traversal(Node* root){
    T_Error error = splay_tree_traversal_reverse(root);
    printf("\n");
    return error;
}

T_Error D_Output_GraphViz(Node* root){
    return splay_tree_output_graphviz(root);
}

T_Error D_Insert_From_File(Node** root){
    printf("Input file's name: ");
    char* file_name = readline(PROMPT);
    if (!file_name) return ERROR_INPUT;
    return splay_tree_insert_from_file(root, file_name);
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