#include "hash_table_func.h"
#define PROMPT ""

T_Error D_Make(Table** table){
    printf("Input the size of table: ");
    uint64_t size = get_u64();
    return table_make(table, size);
}

T_Error D_Insert(Table** table){
    if (!table) return ERROR_TABLE_NULL;
    printf("Input the key to insert: ");
    char* key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    printf("Input the info: ");
    char* info = readline(PROMPT);
    if (!info) return ERROR_INPUT;
    return table_insert(table, key, info);
}

T_Error D_Delete(Table* table){
    if (!table) return ERROR_TABLE_NULL;
    printf("Input the key to delete: ");
    char* key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    return table_delete(table, key);
}

T_Error D_Search(Table* table){
    if (!table) return ERROR_TABLE_NULL;
    printf("Input key to search: ");
    char* key = readline(PROMPT);
    if (!key) return ERROR_INPUT;
    Table* new_table = NULL;
    if (table_make(&new_table, 1) == ERROR_ALLOC_MEM) return ERROR_ALLOC_MEM;
    KeySpace* ret = NULL;
    T_Error check = table_search(table, key, &ret);
    if (check == ERROR_NOT_KEY) return ERROR_NOT_KEY;
    if (table_insert(&new_table, ret->key, ret->info) == ERROR_ALLOC_MEM) return ERROR_ALLOC_MEM;
    table_print(new_table);
    table_free(&new_table);
    return ERROR_NO;
}

T_Error D_Output(Table* table){
    if (!table) return ERROR_TABLE_NULL;
    return table_print(table);
}

T_Error D_Input_Bin(Table** table){
    printf("Input the name of file fill from: ");
    char* file = readline(PROMPT);
    if (!file) return ERROR_INPUT;
    return table_input_bin(table, file);
}

T_Error D_Output_Bin(Table* table){
    if (!table) return ERROR_TABLE_NULL;
    printf("Input the name of file add to: ");
    char* file = readline(PROMPT);
    return table_output_bin(table, file);
}

uint64_t get_u64(){
    char* str = NULL;
    int flag = 1;
    uint64_t num = 0;
    while (flag){
        flag = 0;
        str = readline(PROMPT);
        if(!str){
            flag = 1;
            continue;
        }
        size_t len = strlen(str);
        for (size_t i = 0; i < len; i++){
            if (str[i] < '0' || str[i] > '9') {flag = 1; free(str); break;}
        }
        if(flag){
            continue;
        }
        num = strtoull(str, NULL, 10);
        free(str);
    }
    return num;
}