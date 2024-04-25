#ifndef LAB3B_AADS_HASH_TABLE_H
#define LAB3B_AADS_HASH_TABLE_H
#include <inttypes.h>

typedef uint64_t IndexType;
typedef char* KeyType;
typedef char* InfoType;

typedef struct KeySpace {
    KeyType key;
    InfoType info;
    struct KeySpace *next;
} KeySpace;

typedef struct Table{
    KeySpace* *ks;
    IndexType msize;
    IndexType csize;
} Table;
#endif //LAB3B_AADS_HASH_TABLE_H
