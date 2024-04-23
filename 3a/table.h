#ifndef _LIB_TABLE_H
#define _LIB_TABLE_H
#include <inttypes.h>
typedef uint64_t IndexType;
typedef char* KeyType;
typedef uint64_t RelType;
typedef uint64_t InfoType;

typedef struct Node{
    RelType release;
    InfoType *info;
    struct Node* next;
} Node;

typedef struct KeySpace{
    KeyType key;
    Node* node;
} KeySpace;

typedef struct Table{
    KeySpace *ks;
    IndexType msize;
    IndexType csize;
} Table;
#endif /* _LIB_TABLE_H */
