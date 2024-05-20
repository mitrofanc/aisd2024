#include "splay_tree_lib.h"

Node* left_rotate(Node* x){
    Node *y = x->right, *p = x->par;
    x->right = y->left;
    if (y->left) y->left->par = x;
    y->par = p;
    if (p){
        if (p->left == x) p->left = y;
        else p->right = y;
    }
    y->left = x;
    x->par = y;
    return y;
}

Node* right_rotate(Node* x){
    Node *y = x->left, *p = x->par;
    x->left = y->right;
    if (y->right) y->right->par = x;
    y->par = p;
    if (p) {
        if (p->left == x) p->left = y;
        else p->right = y;
    }
    y->right = x;
    x->par = y;
    return y;
}

T_Error splay(Node** x, Node** root){
    if (!(*x)) return ERROR_NOT_KEY;
    if (*x == *root) return ERROR_NO;
    if (!(*x)->left && !(*x)->right && (*x)->par == *root && (!(*root)->left || !(*root)->right)) {
        Node* supp = (Node*)calloc(1, sizeof(Node));
        if (!supp) return ERROR_ALLOC_MEM;
        supp->key = (*root)->key;

        supp->list=(*root)->list;
        (*root)->list=NULL;
        if ((*x) == (*root)->right) {
            free(*root);
            *root = *x;
            (*root)->par = NULL;
            (*root)->left = supp;
        }
        else {
            free(*root);
            *root = *x;
            (*root)->par = NULL;
            (*root)->right = supp;
        }
        supp->par = *root;
        return ERROR_NO;
    }
    if (!(*x)->par) return ERROR_NO;
    while ((*x)->par){
        if (!(*x)->par->par){ //child of root?
            if (*x == (*x)->par->left) *x = right_rotate((*x)->par);
            else *x = left_rotate((*x)->par);
        }
        else if (*x == (*x)->par->right && (*x)->par == (*x)->par->par->right){
            *x = left_rotate((*x)->par->par);
            *x = left_rotate(*x);
        }
        else if (*x == (*x)->par->left && (*x)->par == (*x)->par->par->left){
            *x = right_rotate((*x)->par->par);
            *x = right_rotate(*x);
        }
        else if (*x == (*x)->par->right && (*x)->par == (*x)->par->par->left){
            *x = left_rotate((*x)->par);
            *x = right_rotate((*x)->par);
        }
        else if (*x == (*x)->par->left && (*x)->par == (*x)->par->par->right){
            *x = right_rotate((*x)->par);
            *x = left_rotate((*x)->par);
        }
    }
    *root = *x;
    return ERROR_NO;
}

T_Error splay_tree_search(Node** root, KeyType key, Node** ret){
    if (splay_tree_search_wos(*root, key, ret) == ERROR_NO) return splay(ret, root); //Had searched key
    else {
        T_Error error = splay(ret, root);
        if (error) return error;
        return ERROR_NOT_KEY;
    }
}

T_Error splay_tree_search_wos(Node* ptr, KeyType key, Node** ret){ // in start ptr is the root, search without splay
    Node *c = ptr, *ptr_prev = NULL;
    while (ptr){
        if (ptr->key == key){
            *ret = ptr;
            return ERROR_NO;
        }
        if (key < ptr->key) {
            ptr_prev = ptr;
            ptr = ptr->left;
        }
        else {
            ptr_prev = ptr;
            ptr = ptr->right;
        }
    }
    *ret = ptr_prev;
    return ERROR_NOT_KEY;
}

T_Error splay_tree_search_min(Node** root, Node** ret){ // In start ptr = root
    Node* ptr = *root;
    while (ptr->left){ ptr = ptr->left; }
    *ret = ptr;
    return splay(&ptr, root);
}

T_Error splay_tree_insert(Node** root, KeyType key, InfoType info){
    if (*root){
        Node* key_ret = NULL;
        splay_tree_search_wos(*root, key, &key_ret);
        if (key_ret && key_ret->key == key) {
            T_Error error = splay_tree_insert_info(&(key_ret->list), info);
            if (error) return error;
            return splay(&key_ret, root);
        }
    }
    Node* new = (Node*)calloc(1, sizeof(Node));
    if (!new) return ERROR_ALLOC_MEM;
    new->key = key;
    if (splay_tree_insert_info(&(new->list), info)) goto clean_new;
    if (!*root){
        *root = new;
        return ERROR_NO;
    }
    Node *ptr = *root, *par = NULL;
    while (ptr){ // Searching for required node
        par = ptr;
        if (key < ptr->key) { ptr = ptr->left; }
        else {
            ptr = ptr->right;
        }
    }
    if (key < par->key) { par->left = new; } // Parent != NULL!!!
    else { par->right = new; }
    new->par = par;
    return splay(&new, root);

    clean_new:
    free(new);
    return ERROR_ALLOC_MEM;
}

T_Error splay_tree_insert_info(InfoList** ptr, InfoType info){
    InfoList* new = (InfoList*)calloc(1, sizeof(InfoList));
    if (!new) return ERROR_ALLOC_MEM;
    new->info = info;
    if (!*ptr) {
        *ptr = new;
        return ERROR_NO;
    }
    new->next = *ptr;
    *ptr = new;
    return ERROR_NO;
}

T_Error splay_tree_delete(Node** root, KeyType key){
    if (!*root) return ERROR_TREE_NULL;
    Node *ptr = *root, *ptr_prev = NULL;
    while (ptr && key != ptr->key) { //Searching fot the element
        ptr_prev = ptr;
        if (key < ptr->key) ptr = ptr->left;
        else ptr = ptr->right;
    }
    if (!ptr) { //Not key
        T_Error error = splay(&ptr_prev, root);
        return ERROR_NOT_KEY;
    }
    if (!ptr->left || !ptr->right) { // Node has not any child or has only one
        Node* supp = NULL;
        if (!ptr->right) supp = ptr->left;
        else supp = ptr->right;
        if (!ptr_prev) { // Delete root with one child
            splay_tree_free_node(ptr);
            *root = supp;
            return ERROR_NO;
        }
        if (ptr == ptr_prev->left) ptr_prev->left = supp;
        else ptr_prev->right = supp;
        T_Error error = splay(&ptr_prev, root);
        if (error) return error;
        error = splay_tree_free_node(ptr);
        return error;
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
        ptr->key = supp->key;
        T_Error error = splay_tree_free_infolist(&ptr->list);
        if (error) return error;
        error = splay_tree_copy_infolist(supp->list, &ptr->list);
        if (error) return error;
        error = splay(&supp->par, root);
        if (error) return error;
        error = splay_tree_free_node(supp);
        if (error) return error;
    }
    return ERROR_NO;
}

InfoList* splay_tree_delete_oldest_wos(InfoList* head){
    InfoList *ptr = head, *ptr_prev = NULL;
    while (ptr->next) { ptr_prev = ptr; ptr = ptr->next; }
    ptr_prev->next = ptr->next;
    free(ptr);
    return head;
}

T_Error splay_tree_delete_oldest(Node** root, Node* node){
    node->list = splay_tree_delete_oldest_wos(node->list);
    return splay(&node, root);
}

T_Error splay_tree_print(Node* ptr, uint64_t shift){
    if (!ptr) return ERROR_END_OF_TREE;
    shift += 10;
    splay_tree_print(ptr->right, shift);
    printf("\n");
    for (uint64_t i = 10; i < shift; i++) printf(" ");
    printf("%llu\n", ptr->key);
    splay_tree_print(ptr->left, shift);
    return ERROR_NO;
}

T_Error splay_tree_print_infolist(InfoList* ptr){
    if (!ptr) return ERROR_EMPTY_INFOLIST;
    printf("Result of search: ");
    while (ptr){
        printf("%llu ", ptr->info);
        ptr = ptr->next;
    }
    printf("\n");
    return ERROR_NO;
}

T_Error splay_tree_copy_infolist(InfoList* old, InfoList** new){
    if (!old) return ERROR_EMPTY_INFOLIST;
    InfoList* ptr = old;
    T_Error error = ERROR_NO;
    while (ptr){
        error = splay_tree_insert_info(new, ptr->info);
        ptr = ptr->next;

        if (error) return error;
    }
    return error;
}

T_Error splay_tree_free(Node** root){
    if (!*root) return ERROR_END_OF_TREE;
    splay_tree_free(&(*root)->right);
    splay_tree_free(&(*root)->left);
    *root = NULL;
    return ERROR_NO;
}

T_Error splay_tree_free_node(Node* node){
    if (!node) return ERROR_NOT_KEY;
    T_Error error = splay_tree_free_infolist(&node->list);
    if (error) return error;
    free(node);
    return error;
}

T_Error splay_tree_free_infolist(InfoList** list) {
    if (!list) return ERROR_EMPTY_INFOLIST;
    InfoList *ptr = *list, *ptr_prev = NULL;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    *list = NULL;
    return ERROR_NO;
}

T_Error splay_tree_traversal_reverse(Node* ptr){ //ptr in start root
    if (!ptr) return ERROR_TREE_NULL;
    splay_tree_traversal_reverse(ptr->right);
    printf("%llu ", ptr->key);
    splay_tree_traversal_reverse(ptr->left);
    return ERROR_NO;
}

T_Error splay_tree_output_graphviz_links(Node* ptr){ //ptr in start root
    if (!ptr) return ERROR_TREE_NULL;
    splay_tree_output_graphviz_links(ptr->right);
    if (ptr->left) printf("%llu-%%3E%llu%%20", ptr->key, ptr->left->key);
    if (ptr->right) printf("%llu-%%3E%llu%%20", ptr->key, ptr->right->key);
    splay_tree_output_graphviz_links(ptr->left);
    return ERROR_NO;
}

T_Error splay_tree_output_graphviz(Node* ptr){
    if (!ptr) return ERROR_TREE_NULL;
    printf("\n");
    printf("https://dotrend.dozen.mephi.ru/?dot=digraph%%7B");
    splay_tree_output_graphviz_links(ptr);
    printf("%%7D\n");
    return ERROR_NO;
}

T_Error splay_tree_insert_from_file(Node** root, char* file_name){
    T_Error error = ERROR_NO;
    FILE* file = fopen(file_name,"r");
    if (!file) {
        return ERROR_NO_FILE;
    }
    if (*root) splay_tree_free(root);
    KeyType key;
    InfoType info;
    while (fscanf(file, "%llu", &key) == 1 && fscanf(file, "%llu", &info) == 1) {
        error = splay_tree_insert(root, key, info);
        if (error) {
            fclose(file);
            return error;
        }
    }
    printf("The data successfully extracted from the file\n");
    fclose(file);
    return error;
}

T_Error splay_tree_count_zero(int* ptr, char* file_name){
    T_Error error = ERROR_NO;
    FILE* file = fopen(file_name,"r");
    if (!file) {
        return ERROR_NO_FILE;
    }


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
