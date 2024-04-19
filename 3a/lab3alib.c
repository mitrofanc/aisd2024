#include "lab3alib.h"

#ifndef NDEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

Table* Make_Table(uint64_t count){
    Table* table = calloc(1, sizeof(Table));
    table->csize = 0;
    table->msize = count;
    KeySpace* ks = calloc(count, sizeof(KeySpace));
    if (!ks) { return NULL; }
    else{ table->ks = ks; }
    return table;
}

int64_t Table_Search_Key(Table* table, char* key){ //Binsearch
    int64_t i = 0, m = table->csize - 1;
    while (i <= m){
        uint64_t j = (i + m) / 2;
        if (strcmp((table->ks + j)->key, key) == 0) { return j; }
        if (strcmp((table->ks + j)->key, key) > 0) { m = j - 1; }
        else{ i = j + 1; }
    }
    return -1;
}

uint64_t Table_Insert_New(Table* table, char* key, uint64_t* data){ //for new key
    int64_t i = 0;
    Node* new = calloc(1, sizeof(Node));
    uint64_t len = strlen(key) + 1;
    if (!new) return 1;
    if (table->csize){
        i = table->csize - 1;
        while (i >= 0 && strcmp((table->ks + i)->key, key) > 0){ //key shift
            (table->ks + i + 1)->key = (table->ks + i)->key;
            (table->ks + i + 1)->node = (table->ks + i)->node;
            i -= 1;
        }
        (table->ks + i + 1)->key = calloc(1, len);
        strcpy((table->ks + i + 1)->key, key);
        (table->ks + i + 1)->node = new;
    }
    else{
        (table->ks + i)->key = calloc(1, len);
        strcpy((table->ks + i)->key, key);
        table->ks->node = new;
    }
    new->release = 1;
    new->info = (InfoType*) calloc(1,sizeof (InfoType));
    if (!new->info) return 1;
    *(new->info) = *data;
    new->next = NULL;
    table->csize += 1;
    return 0;
}

uint64_t Table_Insert_New_Release(Table* table, uint64_t index, uint64_t* data){ //for new release
    if (!table) return 1;
    Node* new = calloc(1, sizeof(Node));
    if (!new) return 1;
    new->info = (InfoType*) calloc(1,sizeof (InfoType));
    if (!new->info) return 1;
    *(new->info) = *data;
    new->next = (table->ks + index)->node;
    new->release = (table->ks + index)->node->release + 1;
    (table->ks + index)->node = new;
    return 0;
}

uint64_t Table_Delete_All_Releases(Table* table, uint64_t index){
    if (!table) return 1;
    Node* ptr = (table->ks + index)->node;
    Node* ptr_prev = NULL;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev->info);
        free(ptr_prev);
    }
    (table->ks + index)->node = calloc(1, sizeof(Node));
    for (uint64_t i = index; i < table->csize - 1; i++){
        (table->ks + i)->key = (table->ks + i + 1)->key;
        *((table->ks + i)->node) = *((table->ks + i + 1)->node);
    }
    table->csize -= 1;
    return 0;
}

uint64_t Table_Delete_Release(Table* table, uint64_t index, uint64_t release){
    if (!table) return 1;
    if ((table->ks + index)->node->release < release){
        printf("ERROR: Don`t have this release\n");
        return 1;
    }
    Node* ptr = (table->ks + index)->node;
    if (!ptr->next) {
        Table_Delete_All_Releases(table, index);
        return 0;
    }
    Node* ptr_prev = NULL;
    while (ptr->release != release){
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr_prev) {
        (table->ks + index)->node = ptr->next;
    }
    if (ptr_prev) { ptr_prev->next = ptr->next; }
    free(ptr->info);
    return 0;
}

uint64_t Table_Free(Table* table){
    for (uint64_t i = 0; i < table->csize; i++){
        Node* ptr = (table->ks + i)->node;
        Node* ptr_prev = NULL;
        while (ptr){
            ptr_prev = ptr;
            ptr = ptr->next;
            free(ptr_prev->info);
            free(ptr_prev);
        }
    }
    free(table->ks);
    free(table);
    return 0;
}