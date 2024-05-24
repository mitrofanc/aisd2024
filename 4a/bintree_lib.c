#include "bintree_lib.h"

T_Error bintree_make(Node** root){
    *root = calloc(1, sizeof(Node*));
    if (!*root) return ERROR_ALLOC_MEM;
    return ERROR_NO;
}

T_Error bintree_search_key(Node* ptr, KeyType key, Node** ret){ // in start ptr is the root
    while (ptr){
        if (strcmp(ptr->key, key) == 0){
            *ret = ptr;
            return ERROR_NO;
        }
        if (strcmp(key, ptr->key) < 0) ptr = ptr->left;
        else ptr = ptr->right;
    }
    return ERROR_NOT_KEY;
}

T_Error bintree_search_info(InfoList* ptr, uint64_t num, InfoList** ret){
    while (ptr){
        if (num == ptr->num){
            *ret = ptr;
            return ERROR_NO;
        }
        ptr = ptr->next;
    }
    return ERROR_NOT_NUM;
}

Node* bintree_search_min(Node* ptr){ // In start ptr = root
    while (ptr->left){ ptr = ptr->left; }
    return ptr;
}

Node* bintree_search_max(Node* ptr){ // In start ptr = root
    while (ptr->right){ ptr = ptr->right; }
    return ptr;
}

T_Error bintree_search_special(Node* root, KeyType key, Node** special_key_ret){
    if (!root) return ERROR_TREE_NULL;
    Node* key_ret = NULL;
    T_Error error = bintree_search_key(root, key, &key_ret);
    if (error) return error;
    if (!key_ret || !key_ret->thread) return ERROR_NOT_KEY;
    *special_key_ret = key_ret->thread;
    return ERROR_NO;
}

T_Error bintree_insert(Node** root, KeyType key, InfoType info){
    if (*root){
        Node* key_ret = NULL;
        T_Error error = bintree_search_key(*root, key, &key_ret);
        if (error) return error;
        if (key_ret) {
            error = bintree_insert_info(&(key_ret->list), info);
            return error;
        }
    }
    Node* new = (Node*)calloc(1, sizeof(Node));
    if (!new) return ERROR_ALLOC_MEM;
    new->key = strdup(key);
    if (!new->key) goto clean_new;
    if (bintree_insert_info(&(new->list), info)) goto clean_key;
    if (!*root){
        *root = new;
        return ERROR_NO;
    }
    Node *ptr = *root, *par = NULL, *prev = *root;
    while (ptr){ // Searching for required node
        par = ptr;
        if (strcmp(key, ptr->key) < 0) { ptr = ptr->left; }
        else {
            ptr = ptr->right;
            prev = par;
        }
    }
    if (strcmp(key, par->key) < 0) { par->left = new; } // Parent != NULL!!!
    else { par->right = new; }
    new->par = par;
    if (bintree_search_min(*root) == new){ // If new is minimal
        new->thread = par;
        return ERROR_NO;
    }
    if (prev->thread) new->thread = prev->thread;
    prev->thread = new;
    return ERROR_NO;

    clean_key:
    free(new->key);
    clean_new:
    free(new);
    return ERROR_ALLOC_MEM;
}

T_Error bintree_insert_info(InfoList** ptr, InfoType info){
    InfoList* new = (InfoList*)calloc(1, sizeof(InfoList));
    if (!new) return ERROR_ALLOC_MEM;
    new->info = strdup(info);
    if (!new->info){
        free(new);
        return ERROR_ALLOC_MEM;
    }
    if (!*ptr) {
        *ptr = new;
        new->num = 1;
        return ERROR_NO;
    }
    new->num = (*ptr)->num + 1;
    new->next = *ptr;
    *ptr = new;
    return ERROR_NO;
}

T_Error bintree_delete(Node** root, KeyType key){
    if (!*root) return ERROR_TREE_NULL;
    Node *ptr = *root, *ptr_prev = NULL;
    while (ptr && strcmp(key, ptr->key) != 0) {
        ptr_prev = ptr;
        if (strcmp(key, ptr->key) < 0) ptr = ptr->left;
        else {
            ptr = ptr->right;
        }
    }
    if (!ptr) return ERROR_NOT_KEY;
    Node* prev = bintree_search_max(ptr->left);
    if (!ptr->left || !ptr->right) { // Node has not any child or has only one
        Node* supp = NULL;
        if (!ptr->left && !ptr->right) prev = ptr->par;
        if (!ptr->right) supp = ptr->left;
        else supp = ptr->right;
        if (!ptr_prev) { // Delete root with one child
            bintree_free_node(ptr);
            *root = supp;
            return ERROR_NO;
        }
        if (ptr == ptr_prev->left) ptr_prev->left = supp;
        else ptr_prev->right = supp;
        // Thread
        if (supp == bintree_search_min(*root) || supp == bintree_search_max(*root)) return bintree_free_node(ptr);
        if (prev) prev->thread = ptr->thread;
        return bintree_free_node(ptr);
    }
    else {
        // Delete Node with 2 children
        Node *par = NULL, *supp = ptr->right;
        while (supp->left) {
            par = supp;
            supp = supp->left;
        }
        if (par) par->left = supp->right;
        else ptr->right = supp->right;
        // Coping
        free(ptr->key);
        ptr->key = strdup(supp->key);
        if (!ptr->key) return ERROR_ALLOC_MEM;
        T_Error error = bintree_free_infolist(ptr->list);
        if (error) return error;
        error = bintree_copy_infolist(supp->list, ptr->list);
        if (error) return error;
        // Thread
        if (supp == bintree_search_min(*root) || supp == bintree_search_max(*root)) return bintree_free_node(supp);
        if (prev) prev->thread = supp->thread;
        return bintree_free_node(supp);
    }
}

T_Error bintree_delete_info(InfoList** head, uint64_t num){
    InfoList *ptr = *head, *ptr_prev = NULL;
    while (ptr && ptr->num != num) {
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr) return ERROR_NOT_NUM; // Don`t have num
    if (ptr == *head) *head = (*head)->next; // Delete first
    if (ptr_prev) ptr_prev->next = ptr->next; // In the middle
    free(ptr->info);
    free(ptr);
    return ERROR_NO;
}

T_Error bintree_traversal_direct(Node* root, KeyType key){
    if (!root) return ERROR_TREE_NULL;
    Node* key_ret = NULL;
    T_Error error = bintree_search_key(root, key, &key_ret);
    if (error) return error;
    if (!key_ret) { key_ret = bintree_search_max(root); }
    Node* ptr = bintree_search_min(root);
    while (strcmp(ptr->key, key_ret->key) < 0) {
        printf("%s ", ptr->key);
        ptr = ptr->thread;
    }
    printf("%s ", key_ret->key);
    printf("\n");
    return ERROR_NO;
}

T_Error bintree_print(Node* ptr, uint64_t shift) {
    if (!ptr) return ERROR_END_OF_TREE;
    shift += 10;
    bintree_print(ptr->right, shift);
    printf("\n");
    for (uint64_t i = 10; i < shift; i++) printf(" ");
    printf("%s\n", ptr->key);
    bintree_print(ptr->left, shift);
    return ERROR_NO;
}

T_Error bintree_output_graphviz(Node* root){
    if (!root) return ERROR_TREE_NULL;
    printf("https://dotrend.dozen.mephi.ru/?dot=digraph%%7B");
    Node* ptr = bintree_search_min(root);
    while (ptr){
        if (ptr->left) printf("%s-%%3E%s%%20", ptr->key, ptr->left->key);
        if (ptr->right) printf("%s-%%3E%s%%20", ptr->key, ptr->right->key);
        ptr = ptr->thread;
    }
    printf("%%7D\n");
    return ERROR_NO;
}

T_Error bintree_free_node(Node* node){
    if (!node) return ERROR_NOT_KEY;
    free(node->key);
    T_Error error = bintree_free_infolist(node->list);
    if (error) return error;
    free(node);
    return error;
}

T_Error bintree_free_infolist(InfoList* list) {
    if (!list) return ERROR_EMPTY_INFOLIST;
    InfoList *ptr = list, * ptr_prev = NULL;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev->info);
        free(ptr_prev);
    }
    return ERROR_NO;
}

T_Error bintree_free(Node** root){
    if (!*root) return ERROR_NO;
    Node *ptr = bintree_search_min(*root), *ptr_prev = NULL;
    while (ptr){
        ptr_prev = ptr;
        bintree_free_node(ptr_prev);
    }
    *root = NULL;
    return ERROR_NO;
}

T_Error bintree_copy_infolist(InfoList* old, InfoList* new){
    if (!old) return ERROR_EMPTY_INFOLIST;
    InfoList* ptr = old;
    while (ptr->next){
        T_Error error = bintree_insert_info(&new, ptr->info);
        ptr = ptr->next;
        if (error) return error;
    }
    return ERROR_NO;
}

T_Error bintree_insert_from_file(Node** root, char* file_name){
    T_Error error = ERROR_NO;
    FILE* file = fopen(file_name,"r");
    if (!file) {
        return ERROR_NO_FILE;
    }
    if (*root) bintree_free(root);
    KeyType key;
    InfoType info;
    size_t key_size = 0, info_size = 0;
    while (!feof(file)) {
        key = readline_file_text(file);
        if (!key) { bintree_free(root); return ERROR_READING_FILE; }
        info = readline_file_text(file);
        if (!info) { bintree_free(root); free(key); return ERROR_READING_FILE; }
        error = bintree_insert(root, key, info);
        if (error != ERROR_NO) return error;
    }
    printf("The data successfully extracted from the file\n");
    fclose(file);
    return error;
}

char* readline_file_text(FILE *file){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0, n;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0) {
            return NULL;
        }
        else {
            if (n > 0) {
                uint64_t chunk_len = strlen(buf);
                uint64_t str_len = len + chunk_len;
                res = (char*)realloc(res, str_len + 1);
                if (!res) return NULL;
                memcpy(res + len, buf, chunk_len);
                len = str_len;
            }
            else {
                fscanf(file, "%*c");
            }
        }
    } while (n > 0);
    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = (char*)calloc(1, sizeof(char));
        if (res == NULL) {
            return NULL;
        }
        res[0] = '\n';
    }
    return res;
}

void print_errors(T_Error error){
    switch (error){
        case 0:
            break;
        case 1:
            printf("ERROR: Can`t allocate memory\n");
            break;
        case 2:
            printf("ERROR: Don`t have tree\n");
            break;
        case 3:
            printf("ERROR: Don`t have key\n");
            break;
        case 4:
            printf("ERROR: Don`t have this number\n");
            break;
        case 5:
            printf("ERROR: Can`t input\n");
            break;
        case 6:
            printf("ERROR: End of tree\n");
            break;
        case 7:
            printf("ERROR: Don`t have any info\n");
            break;
        case 8:
            printf("ERROR: Don`t have such file\n");
            break;
        case 9:
            printf("ERROR: Can`t read file\n");
            break;
    }
    printf("\n");
}