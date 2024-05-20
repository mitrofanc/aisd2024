#ifndef SPLAY_TREE_STRUCT_H
#define SPLAY_TREE_STRUCT_H
#include <inttypes.h>

typedef uint64_t KeyType;
typedef uint64_t InfoType;

typedef struct InfoList {
    InfoType info;
    struct InfoList* next;
} InfoList;

typedef struct Node {
    KeyType key;
    struct Node* left;
    struct Node* right;
    struct Node* par;
    InfoList* list;
} Node;

#endif //SPLAY_TREE_STRUCT_H
