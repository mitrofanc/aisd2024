#ifndef lab3afunc
#define lab3afunc
#include "lab3alib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define floor(x) ((float)((int)x))

//typedef uint64_t IndexType;
//typedef char* KeyType;
//typedef uint64_t RelType;
//typedef uint64_t InfoType;
//
//typedef struct Node{
//    RelType release;
//    InfoType *info;
//    struct Node* next;
//} Node;
//
//typedef struct KeySpace{
//    KeyType key;
//    Node* node;
//} KeySpace;
//
//typedef struct Table{
//    KeySpace *ks;
//    IndexType msize;
//    IndexType csize;
//} Table;


//Table* Make_Table(uint64_t count);
Table* D_Make_Table();
uint64_t D_Insert_Node(Table*);
//int64_t Table_Search_Key(Table*, char*);//Binsearch
//uint64_t Table_Insert_New(Table*, char*, uint64_t*);
//uint64_t Table_Insert_New_Release(Table*, uint64_t, uint64_t*);
uint64_t D_Delete(Table*);
uint64_t D_Output_Table(Table*);
//uint64_t Table_Delete_All_Releases(Table*, uint64_t);
//uint64_t Table_Delete_Release(Table*, uint64_t, uint64_t);
uint64_t D_Search_Table(Table*);
uint64_t D_Fill_From_File (Table** table);
//uint64_t Table_Free(Table*);
uint64_t get_pos_int();
void clearbuf();
char* str_in();

#endif
