#ifndef LAB3B_AADS_HASH_TABLE_FUNC_H
#define LAB3B_AADS_HASH_TABLE_FUNC_H
#include "hash_table_lib.h"

T_Error D_Make(Table** table);
T_Error D_Insert(Table* table);
T_Error D_Delete(Table* table);
T_Error D_Search(Table* table);
T_Error D_Output(Table* table);
T_Error D_Input_Bin(Table** table);
T_Error D_Output_Bin(Table* table);
uint64_t get_u64();

#endif //LAB3B_AADS_HASH_TABLE_FUNC_H
