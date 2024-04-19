#include "lab3afunc.h"
#ifndef NDEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

Table* D_Make_Table(){
    printf("Input the max size of table: ");
    size_t msize = get_u64();
    printf("\n");
    return Make_Table(msize);
}

uint64_t D_Insert_Node(Table* table){
    if (table->csize == table->msize) {
        printf("ERROR: Can`t insert any node\n");
        return 1;
    }
    printf("Input the key: ");
    char* key = str_in();
    printf("Input the data: ");
    uint64_t data = get_u64();

    int64_t index = Table_Search_Key(table, key);
    if (index == -1){
        uint64_t check = Table_Insert_New(table, key, &data);
        if (check == 1) {
            printf("ERROR\n");
            return 1;
        }
    }
    else{
        uint64_t check = Table_Insert_New_Release(table, index, &data);
        if (check == 1) {
            printf("ERROR\n");
            return 1;
        }
    }
    return 0;
}

uint64_t D_Output_Table(Table* table){
    if (!table){
        printf("ERROR: No any data\n");
        return 1;
    }
    for(int i = 0; i < table->csize; i++){
        printf("Key: ");
        printf("%s\n", (table->ks + i)->key);
        Node* ptr = (table->ks + i)->node;
        do{
            printf("Release, info: ");
            printf("%llu, %llu\n", ptr->release, *(ptr->info));
            ptr = ptr->next;
        } while(ptr);
        printf("\n");
    }
    return 0;
}

uint64_t D_Delete(Table* table){
    printf("Input the key of node to delete: ");
    char* key = str_in();
    uint64_t index = Table_Search_Key(table, key);
    if (index == -1) {
        printf("ERROR: Don`t have this key\n");
        return 1;
    }
    printf("1. Delete all releases\n");
    printf("2. Delete one release\n");
    printf("\n");
    uint64_t choose = get_u64();
    if (choose == 1){
        uint64_t check = Table_Delete_All_Releases(table, index);
        if (check == 1) {
            printf("ERROR\n");
            return 1;
        }
    }
    else{
        printf("Input number of release: ");
        uint64_t release = get_u64();
        uint64_t check = Table_Delete_Release(table, index, release);
        if (check == 1){
            printf("ERROR\n");
            return 1;
        }
    }
    return 0;
}

uint64_t D_Search_Table(Table* table){
    if (!table) return 1;
    printf("Input the key of node to search: ");
    char* key = str_in();
    int64_t index = Table_Search_Key(table, key);
    if (index == -1) {
        printf("ERROR: Don`t have this key\n");
        return 1;
    }
    Table* copy_table = Make_Table(1);
    printf("1. Search all releases with key\n");
    printf("2. Search one release with key\n");
    uint64_t choose = get_u64();
    RelType release = 0;
    InfoType* info = calloc(1, sizeof(InfoType));
    if (choose == 1){
        Node* ptr = (table->ks + index)->node;
        *(info) = *(ptr->info);
        Table_Insert_New(copy_table, key, info);
        ptr = ptr->next;
        while (ptr){
            release = ptr->release;
            *(info) = *(ptr->info);
            Table_Insert_New_Release(copy_table, 0, info);
            ptr = ptr->next;
        }
    }
    else{
        printf("Input release: ");
        release = get_u64();
        printf("\n");
        if ((table->ks + index)->node->release < release){
            printf("ERROR: Don`t have this release\n");
            return 1;
        }
        Node* ptr = (table->ks + index)->node;
        Node* ptr_prev = NULL;
        while (ptr->release != release){
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        *(info) = *(ptr->info);
        Table_Insert_New(copy_table, key, info);
    }
    D_Output_Table(copy_table);
    Table_Free(copy_table);
    free(info);
    return 0;
}

char* getKey(char* str, uint64_t* index){
    uint64_t i = 0;
    char* dup = NULL;
    char* copy = NULL;
    while(str[i] && str[i] != ' '){
        copy = dup;
        dup = realloc(dup, sizeof(char) * i + 1);
        if (!dup) {
            free(copy);
            return NULL;
        }
        dup[i] = str[i];
        i += 1;
    }
    copy = dup;
    dup = realloc(dup, sizeof(char) * i + 1);
    if (!dup){
        free(copy);
        return NULL;
    }
    dup[i] = '\0';
    *index = i;
    return dup;
}

uint64_t D_Fill_From_File (Table** table) {
    printf("Input file's name: ");
    char *file_name = str_in();
    printf("\n");
    char *key;
    uint64_t info;
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("ERROR: No such file\n");
        printf("\n");
        return 1;
    } else {
        if (*table) {
            Table_Free(*table);
        }
        *table = D_Make_Table();
        char *str;
        size_t len;
        while (getline(&str, &len, file) != -1) {
            len = 0;
            uint64_t index;
            key = getKey(str, &index);
            sscanf(str + index, "%llu", &info);
            int64_t check = Table_Search_Key(*table, key);
            if (check == -1) {
                Table_Insert_New(*table, key, &info);
            } else {
                Table_Insert_New_Release(*table, check, &info);
            }
            free(key);
            free(str);
            str = NULL;
            len = 0;
        }
        printf("The data successfully extracted from the file\n");
        printf("\n");
        fclose(file);
        return 0;
    }
}

uint64_t get_u64(){
    char* str = NULL;
    int flag = 1;
    uint64_t num = 0;
    while (flag){
        flag = 0;
        str = str_in();
        if(!str){
            flag = 1;
            continue;
        }
        size_t len = strlen(str);
        for (int i = 0; i < len; i++){
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

char* str_in(){
    char buf[2013] = {0};
    char* res = NULL;
    int len = 0, n;
    do{
        n = scanf("%2012[^\n]", buf);
        if (n < 0)
        {
            return NULL;
        }
        else if (n > 0) //Есть символы
        {
            int chunk_len = strlen(buf); //Длина введенной части
            int str_len = len + chunk_len; //Общая длина строки
            char* copy = res;
            res = realloc(res, str_len + 1); //Изменение длины итоговой строки
            if (!res) {
                free(copy);
                return NULL;
            }
            strncpy(res + len, buf, chunk_len); // Копирование из chunk_len в res
            len = str_len;
        }
        else{
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0){
        res[len] = '\0';
    }
    else{
        res = calloc(1, sizeof(char));
        if (!res) return NULL;
    }
    return res;
}