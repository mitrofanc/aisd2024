#include "hash_table_lib.h"

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
    return hash;
}

T_Error table_search(Table* table, char* key, KeySpace** ret){
    if (!table) return ERROR_TABLE_NULL;
    uint64_t shift = hash(key) % table->msize;
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