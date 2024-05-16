#ifndef BINTREE_STRUCT_H
#define BINTREE_STRUCT_H
#include <inttypes.h>

typedef char* KeyType;
typedef char* InfoType;

typedef struct InfoList {
    uint64_t num;
    InfoType info;
    struct InfoList* next;
} InfoList;

typedef struct Node {
    KeyType key;
    struct Node* left;
    struct Node* right;
    struct Node* thread;
    struct Node* par;
    InfoList* list;
} Node;



#endif //BINTREE_STRUCT_H
