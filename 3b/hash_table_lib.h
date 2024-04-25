#ifndef LAB3B_AADS_HASH_TABLE_LIB_H
#define LAB3B_AADS_HASH_TABLE_LIB_H
#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>

typedef enum T_Error{
    ERROR_NO,
    ERROR_ALLOC_MEM,
    ERROR_TABLE_NULL,
    ERROR_SAME_KEY,
    ERROR_NOT_KEY,
    ERROR_INPUT,
    ERROR_OUTPUT_TO_BIN,
    ERROR_NO_FILE,
    ERROR_INPUT_FROM_BIN,
} T_Error;

T_Error table_make(Table** table, uint64_t count);
unsigned long long hash(char* key);
T_Error table_search(Table* table, char* key, KeySpace** ret);
T_Error table_insert(Table* table, char* key, char* info);
T_Error table_delete(Table* table, char* key);
T_Error table_print(Table* table);
T_Error table_free(Table** table);
T_Error table_output_bin(Table* table, char* file_name);
T_Error table_input_bin(Table** table, char* file_name);
void print_errors(T_Error error);

#endif //LAB3B_AADS_HASH_TABLE_LIB_H
