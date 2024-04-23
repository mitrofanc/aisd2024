#ifndef lab3alib
#define lab3alib
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table* Make_Table(uint64_t count);
int64_t Table_Search_Key(Table*, char*);//Binsearch
uint64_t Table_Insert_New(Table*, char*, uint64_t*);
uint64_t Table_Insert_New_Release(Table*, uint64_t, uint64_t*);
uint64_t Table_Delete_All_Releases(Table*, uint64_t);
uint64_t Table_Delete_Release(Table*, uint64_t, uint64_t);
uint64_t Table_Free(Table*);

#endif
