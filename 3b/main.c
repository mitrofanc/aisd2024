#include "hash_table_func.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//#include <string.h>
//#include <readline/readline.h>
//#define PROMPT ""

//#ifndef NDEBUG
//#define DBG_PRINT(...) printf(__VA_ARGS__)
//#else
//#define DBG_PRINT(...)
//#endif
/*
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



//liba
T_Error table_make(Table** table, uint64_t count);
unsigned long long hash(char* key);
T_Error table_search(Table* table, char* key, KeySpace** ret);
T_Error table_insert(Table* table, char* key, char* info);
T_Error table_delete(Table* table, char* key);
T_Error table_print(Table* table);
T_Error table_free(Table** table);
T_Error table_output_bin(Table* table, char* file_name);
T_Error table_input_bin(Table** table, char* file_name);
*/
//dialog
/*
T_Error D_Make(Table** table);
T_Error D_Insert(Table* table);
T_Error D_Delete(Table* table);
T_Error D_Search(Table* table);
T_Error D_Output(Table* table);
T_Error D_Input_Bin(Table** table);
T_Error D_Output_Bin(Table* table);
uint64_t get_u64();
//void print_errors(T_Error error);
*/
int main() {
    Table* table = NULL;
    uint64_t choice = 1;
    T_Error error = 0;
    while (choice <= 7){
        printf("Select an action:\n");
        printf("1. Make table\n");
        printf("2. Insert new node\n");
        printf("3. Delete node\n");
        printf("4. Search node\n");
        printf("5. Output table to the console\n");
        printf("6. Insert table from bin file\n");
        printf("7. Output table to bin file\n");
        printf("8. Exit\n");
        printf("\n");
        choice = get_u64();
        printf("\e[1;1H\e[2J");
        switch (choice){
            case 1:
                error = D_Make(&table);
                break;
            case 2:
                error = D_Insert(table);
                break;
            case 3:
                error = D_Delete(table);
                break;
            case 4:
                error = D_Search(table);
                break;
            case 5:
                error = D_Output(table);
                break;
            case 6:
                error = D_Input_Bin(&table);
                break;
            case 7:
                error = D_Output_Bin(table);
                break;
        }
        print_errors(error);
    }
//    table_make(&table, 5);
//    table_insert(table, "yama", "hi");
//    table_insert(table, "cat", "bye");
//    table_insert(table, "yamau", "hi");
//    table_insert(table, "mom", "hi");
//    table_print(table);
//    table_delete(table,"cat");
//    table_print(table);
////    D_Insert(table);
////    table_print(table);
////    D_Delete(table);
////    table_print(table);
////    D_Search(table);
//    D_Output_Bin(table);
//    table_output_bin(table, "/Users/dandreev/Documents/aisd2024/3b/test.bin");
//    table_input_bin(&table, "/Users/dandreev/Documents/aisd2024/3b/test.bin");
//    D_Input_Bin(&table);
//    printf("err: %s\n", strerror(errno));
//    D_Output(table);
    printf("Hello, World!\n");
    return 0;
}
/*
void print_errors(T_Error error){
    switch (error){
        case 0:
            break;
        case 1:
            printf("ERROR: Can`t allocate memory\n");
            break;
        case 2:
            printf("ERROR: Don`t have table\n");
            break;
        case 3:
            printf("ERROR: Don`t have key\n");
            break;
        case 4:
            printf("ERROR: Don`t have this key\n");
            break;
        case 5:
            printf("ERROR: Incorrect data\n");
            break;
        case 6:
            printf("ERROR: Can`t output to bin file\n");
            break;
        case 7:
            printf("ERROR: Don`t have file with this name\n");
            break;
        case 8:
            printf("ERROR: Can`t input table from file\n");
            break;
    }
    printf("\n");
}
*/
//liba
/*
T_Error table_make(Table** table, uint64_t count){
    if (!(*table)) {
        *table = calloc(1, sizeof(Table));
        if (!*table) return ERROR_ALLOC_MEM;
    }
    (*table)->ks = calloc(count, sizeof(KeySpace*));
    if (!(*table)->ks){
        free(*table);
        *table = NULL;
        return ERROR_ALLOC_MEM;
    }
    (*table)->msize = count;
    (*table)->csize = 0;
    return ERROR_NO;
}

unsigned long long hash(char* key){
    uint64_t hash = INT_MAX;
//    while(*key){
    for (int i = 0; key[i] != '\0'; i++){
        hash = 57 * hash + *key;
//        key++;
    }
    DBG_PRINT("hash %llu\n", hash);
    return hash;
}

T_Error table_search(Table* table, char* key, KeySpace** ret){
    if (!table) return ERROR_TABLE_NULL;
    uint64_t shift = hash(key) % table->msize;
    DBG_PRINT("shift in find %llu\n", shift);
    KeySpace* ptr = table->ks[shift];
    while (ptr){
        if (strcmp(ptr->key, key) == 0) {
            *ret = ptr;
            return ERROR_NO;
        }
        ptr = ptr->next;
    }
    return ERROR_NOT_KEY;
}

T_Error table_insert(Table* table, char* key, char* info){
    uint64_t index = hash(key) % table->msize;
    DBG_PRINT("index in insert %llu\n", index);
    KeySpace* ret = NULL;
    table_search(table, key, &ret);
    if (ret) return ERROR_SAME_KEY;
    KeySpace* new = (KeySpace*) calloc(1, sizeof(KeySpace));
    if (!new) return ERROR_ALLOC_MEM;
    new->key = strdup(key);
    if (!new->key) goto clean_new;
    new->info = strdup(info);
    if (!new->info) goto clean_key;
    new->next = table->ks[index];
    table->ks[index] = new;
    return ERROR_NO;

    clean_key:
        free(new->key);
    clean_new:
        free(new);
        return ERROR_ALLOC_MEM;
}

T_Error table_delete(Table* table, char* key){
    uint64_t index = hash(key) % table->msize;
    KeySpace* ptr = table->ks[index];
    KeySpace* ptr_prev = NULL;
    while (ptr && strcmp(ptr->key, key) != 0){
        ptr_prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr) return ERROR_NOT_KEY;
    if (ptr == table->ks[index]) { table->ks[index] = ptr->next; }
    if (ptr_prev) { ptr_prev->next = ptr->next; }
    free(ptr->key);
    free(ptr->info);
    free(ptr);
    return ERROR_NO;
}

T_Error table_print(Table* table){
    if (!table) return ERROR_TABLE_NULL;
    printf("Index\n");
    for (uint64_t i = 0; i < table->msize; i++){
        if (table->ks[i]){
            printf("%llu:\n", i);
            KeySpace* tmp = table->ks[i];
            while (tmp){
                printf("     Key: %s, Info: %s\n", tmp->key, tmp->info);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    return ERROR_NO;
}

T_Error table_free(Table** table){
    if (!*table) return ERROR_TABLE_NULL;
    for (uint64_t i = 0; i < (*table)->msize; i++){
        if ((*table)->ks[i]){
            KeySpace *ptr = (*table)->ks[i], *ptr_prev = NULL;
            while (ptr){
                ptr_prev = ptr;
                ptr = ptr->next;
                free(ptr_prev->key);
                free(ptr_prev->info);
                free(ptr_prev);
            }
        }
    }
    free((*table)->ks);
    free(*table);
    *table = NULL;
    return ERROR_NO;
}

T_Error table_output_bin(Table* table, char* file_name){
    if (!table) return ERROR_TABLE_NULL;
    FILE* file = fopen(file_name,"wb");
    char separator = '^';
    if (!fwrite((void*) &(table->msize), sizeof(uint64_t), 1, file)){
        goto close_file_output;
    }
//    if (!fwrite((void*) &separator, sizeof(char), 1, file)){
//        goto close_file_output;
//    }
    for (uint64_t i = 0; i < table->msize; i++){
        if (table->ks[i]){
            KeySpace* tmp = table->ks[i];
            while (tmp){
                if (!fwrite((void*) tmp->key, sizeof(char), strlen(tmp->key), file)){ // +1
                    goto close_file_output;
                }
                if (!fwrite((void*) &separator, sizeof(char), 1, file)){
                    goto close_file_output;
                }
                if (!fwrite((void*) tmp->info, sizeof(char), strlen(tmp->info), file)){ //+1
                    goto close_file_output;
                }
                if (!fwrite((void*) &separator, sizeof(char), 1, file)){
                    goto close_file_output;
                }
                tmp = tmp->next;
            }
        }
    }
    fclose(file);
    return ERROR_NO;

    close_file_output:
        fclose(file);
        return ERROR_OUTPUT_TO_BIN;
}

T_Error table_input_bin(Table** table, char* file_name){
    T_Error error = ERROR_NO;
    FILE* file = fopen(file_name,"rb");
    if (!file) {
        error = ERROR_NO_FILE;
        goto close_file_input;
    }
    if (*table) table_free(table);
    uint64_t msize;
    if (!fread(&msize, sizeof(uint64_t), 1, file)){
        error = ERROR_INPUT_FROM_BIN;
        goto close_file_input;
    }
    if (table_make(table, msize) == ERROR_ALLOC_MEM) return ERROR_ALLOC_MEM;
    char symbol;
    int key_len = 0, info_len = 0;
    char *key = NULL, *info = NULL;
    char* tmp;
    fseek(file, 0, SEEK_END);
    uint64_t size = ftell(file);
    fseek(file, 8, SEEK_SET);
    while (size > (uint64_t)ftell(file)) {
        while (1) {
            printf("b %d\n",feof(file));
            if (!fread(&symbol, sizeof(char), 1, file)){
                error = ERROR_INPUT_FROM_BIN;
                goto close_file_input;
            }
            printf("read %c\n",symbol);
            if (symbol == '^') {
                break;
            }
            key_len += 1;
//            char* dup = key;
            tmp = realloc(key, key_len * sizeof(char));
            if (!tmp){
                free(key);
                error = ERROR_ALLOC_MEM;
                goto close_file_input;
            }
            key = tmp;
            key[key_len - 1] = symbol;
        }

        tmp = realloc(key, (key_len + 1) * sizeof(char));
        if (!tmp){
            free(key);
            error = ERROR_ALLOC_MEM;
            goto close_file_input;
        }
        key = tmp;
        key[key_len] = '\0';
        while (1) {
            printf("bb %d\n",feof(file));
            if (!fread(&symbol, sizeof(char), 1, file)){
                error = ERROR_INPUT_FROM_BIN;
                goto close_file_input;
            }
            printf("read2 %c\n",symbol);
            if (symbol == '^') {
                break;
            }
            info_len += 1;
            tmp = realloc(info, info_len * sizeof(char));
            if (!tmp){
                free(info);
                error = ERROR_ALLOC_MEM;
                goto close_file_input;
            }
            info = tmp;
            info[info_len - 1] = symbol;
        }
        tmp = realloc(info, (info_len + 1) * sizeof(char));
        if (!tmp){
            free(info);
            error = ERROR_ALLOC_MEM;
            goto close_file_input;
        }
        info = tmp;
        info[info_len] = '\0';
        char *key_copy = strdup(key);
        char *info_copy = strdup(info);
        table_insert(*table, key_copy, info_copy);
        key = NULL;
        info = NULL;
        key_len = 0, info_len = 0;
    }
    fclose(file);
    return ERROR_NO;

    close_file_input:
    table_free(table);
    fclose(file);
    return error;
}
*/
//dialog
/*
T_Error D_Make(Table** table){
    printf("Input the size of table: ");
    uint64_t size = get_u64();
    return table_make(table, size);
}

T_Error D_Insert(Table* table){
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
    if (table_insert(new_table, ret->key, ret->info) == ERROR_ALLOC_MEM) return ERROR_ALLOC_MEM;
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
 */