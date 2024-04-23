#ifndef lab3afunc
#define lab3afunc
#include "lab3alib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Table* D_Make_Table();
uint64_t D_Insert_Node(Table*);
uint64_t D_Delete(Table*);
uint64_t D_Output_Table(Table*);
uint64_t D_Search_Table(Table*);
uint64_t D_Fill_From_File (Table** table);
uint64_t get_u64();
char* str_in();

#endif
