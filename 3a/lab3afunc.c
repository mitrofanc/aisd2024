#include "lab3afunc.h"
#ifndef NDEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif

//Table* Make_Table(uint64_t count){
//    Table* table = calloc(1, sizeof(Table));
//    table->csize = 0;
//    table->msize = count;
//    DBG_PRINT("msize2 %llu\n", table->msize);
//    KeySpace* ks = calloc(count, sizeof(KeySpace));
//    if (!ks) { return NULL; }
//    else{ table->ks = ks; }
//    DBG_PRINT("%s\n", table->ks->key);
//    return table;
//}

Table* D_Make_Table(){
    uint64_t msize = 0;
    printf("Input the max size of table: ");
    msize = get_pos_int();
    DBG_PRINT("msize %llu\n", msize);
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
    uint64_t data = get_pos_int();

    int64_t index = Table_Search_Key(table, key);
    if (index == -1){
        uint64_t check = Table_Insert_New(table, key, &data);
        DBG_PRINT("key hi %s\n", table->ks[0].key);
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

//int64_t Table_Search_Key(Table* table, char* key){ //Binsearch
//    int64_t i = 0, m = table->csize - 1;
//    while (i <= m){
//        uint64_t j = (i + m) / 2;
//        DBG_PRINT("key i %s\n", (table->ks + j)->key);
//        if (strcmp((table->ks + j)->key, key) == 0) { return j; }
//        if (strcmp((table->ks + j)->key, key) > 0) { m = j - 1; }
//        else{ i = j + 1; }
//    }
//    return -1;
//}
//
//uint64_t Table_Insert_New(Table* table, char* key, uint64_t* data){ //for new key
//    int64_t i = 0;
//    DBG_PRINT("1");
//    Node* new = calloc(1, sizeof(Node));
//    uint64_t len = strlen(key) + 1;
//    DBG_PRINT("2");
//    if (!new) return 1;
//    DBG_PRINT("3");
//    if (table->csize){
//        DBG_PRINT("4");
//        i = table->csize - 1;
//        while (i >= 0 && strcmp((table->ks + i)->key, key) > 0){ //key shift
//            DBG_PRINT("5");
//            (table->ks + i + 1)->key = (table->ks + i)->key;
//            (table->ks + i + 1)->node = (table->ks + i)->node;
//            i -= 1;
//        }
//        (table->ks + i + 1)->key = calloc(1, len);
//        strcpy((table->ks + i + 1)->key, key);
//        DBG_PRINT("key in insert %s %s\n", (table->ks + i + 1)->key, key);
//        (table->ks + i + 1)->node = new;
//        DBG_PRINT("6");
////        DBG_PRINT("in insert if %llu\n", *((table->ks + i)->node->info));
//    }
//    else{
//        DBG_PRINT("7");
//        (table->ks + i)->key = calloc(1, len);
//        strcpy((table->ks + i)->key, key);
//        DBG_PRINT("key in insert %s %p %s %p\n", (table->ks + i)->key, (table->ks + i)->key, key, key);
//        table->ks->node = new;
//        DBG_PRINT("8");
//    }
//    new->release = 1;
//    new->info = (InfoType*) calloc(1,sizeof (InfoType));
//    *(new->info) = *data;
//    new->next = NULL;
//    table->csize += 1;
//    DBG_PRINT("9\n");
////    DBG_PRINT("in insert %llu\n", *((table->ks + i)->node->info));
//    return 0;
//}
//
//uint64_t Table_Insert_New_Release(Table* table, uint64_t index, uint64_t* data){ //for new release
//    if (!table) return 1;
//    Node* new = calloc(1, sizeof(Node));
//    new->info = (InfoType*) calloc(1,sizeof (InfoType));
//    *(new->info) = *data;
//    DBG_PRINT("data in func %llu\n", *(new->info));
//    DBG_PRINT("index passed to ins %llu\n", index);
//    new->next = (table->ks + index)->node;
//    new->release = (table->ks + index)->node->release + 1;
//    DBG_PRINT("release in func %llu\n", new->release);
//    (table->ks + index)->node = new;
//    DBG_PRINT("release %llu data %llu\n", (table->ks+index)->node->release, *((table->ks+index)->node->info));
//    return 0;
//}

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
    uint64_t choose = get_pos_int();
    if (choose == 1){
        uint64_t check = Table_Delete_All_Releases(table, index);
        if (check == 1) {
            printf("ERROR\n");
            return 1;
        }
    }
    else{
        printf("Input number of release: ");
        uint64_t release = get_pos_int();
        uint64_t check = Table_Delete_Release(table, index, release);
        if (check == 1){
            printf("ERROR\n");
            return 1;
        }
    }
    return 0;
}

//uint64_t Table_Delete_All_Releases(Table* table, uint64_t index){
//    if (!table) return 1;
//    Node* ptr = (table->ks + index)->node;
//    Node* ptr_prev = NULL;
//    while (ptr){
//        ptr_prev = ptr;
//        ptr = ptr->next;
//        free(ptr_prev->info);
//        free(ptr_prev);
//    }
//    (table->ks + index)->node = calloc(1, sizeof(Node));
//    for (uint64_t i = index; i < table->csize - 1; i++){
//        (table->ks + i)->key = (table->ks + i + 1)->key;
//        *((table->ks + i)->node) = *((table->ks + i + 1)->node);
//    }
//    table->csize -= 1;
//    return 0;
//}
//
//uint64_t Table_Delete_Release(Table* table, uint64_t index, uint64_t release){
//    if (!table) return 1;
//    if ((table->ks + index)->node->release < release){
//        printf("ERROR: Don`t have this release\n");
//        return 1;
//    }
//    Node* ptr = (table->ks + index)->node;
//    if (!ptr->next) {
//        Table_Delete_All_Releases(table, index);
//        return 0;
//    }
//    Node* ptr_prev = NULL;
//    while (ptr->release != release){
//        ptr_prev = ptr;
//        ptr = ptr->next;
//    }
//    if (!ptr_prev) {
//        (table->ks + index)->node = ptr->next;
//    }
//    if (ptr_prev) { ptr_prev->next = ptr->next; }
//    free(ptr->info);
////    free(ptr);
//    return 0;
//}

uint64_t D_Search_Table(Table* table){
    if (!table) return 1;
    printf("Input the key of node to search: ");
    char* key = str_in();
    int64_t index = Table_Search_Key(table, key);
    DBG_PRINT("index: %llu\n", index);
    if (index == -1) {
        printf("ERROR: Don`t have this key\n");
        return 1;
    }
    Table* copy_table = Make_Table(1);
    printf("1. Search all releases with key\n");
    printf("2. Search one release with key\n");
    uint64_t choose = get_pos_int();
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
        release = get_pos_int();
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
    while(str[i] && str[i] != ' '){
        dup = realloc(dup, sizeof(char) * i + 1);
        if (!dup) return NULL;
        dup[i] = str[i];
        i += 1;
    }
    dup = realloc(dup, sizeof(char) * i + 1);
    if (!dup) return NULL;
    dup[i] = '\0';
    *index = i;
    return dup;
}

uint64_t D_Fill_From_File (Table** table) {
//    Table* table = D_Make_Table();
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
            DBG_PRINT("read %s\n",str);
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
            DBG_PRINT("loop of read\n");
        }
        printf("The data successfully extracted from the file\n");
        printf("\n");
        fclose(file);
        return 0;
    }
}
//uint64_t Table_Free(Table* table){
//    for (uint64_t i = 0; i < table->csize; i++){
//        Node* ptr = (table->ks + i)->node;
//        Node* ptr_prev = NULL;
//        while (ptr){
//            ptr_prev = ptr;
//            ptr = ptr->next;
//            free(ptr_prev->info);
//            free(ptr_prev);
//        }
//    }
//    free(table->ks);
//    free(table);
//    return 0;
//}

uint64_t get_pos_int(){
    float tmp = -1;
    int flag = scanf("%f", &tmp);
    printf("\n");
    while ((floor(tmp) - tmp != 0) || (tmp < 0)){
        if (flag == EOF){
            printf("Exit\n");
            return -1;
        }
        clearbuf();
        flag = scanf("%f", &tmp);
    }
    clearbuf();
    return (uint64_t) tmp;
}

void clearbuf(){
    char symbol = ' ';
    symbol = getchar();
    while ((symbol != '\n') && (symbol != EOF))
    {
        symbol = getchar();
    }
}

char* str_in()
{
    char buf[2013] = {0};
    char* res = NULL;
    int len = 0, n;
//    printf("%s", invite);

    do
    {
        n = scanf("%2012[^\n]", buf);
        if (n < 0)
        {
            return NULL;
        }
        else if (n > 0) //Есть символы
        {
            int chunk_len = strlen(buf); //Длина введенной части
            int str_len = len + chunk_len; //Общая длина строки
            res = realloc(res, str_len + 1); //Изменение длины итоговой строки
            strncpy(res + len, buf, chunk_len); // Копирование из chunk_len в res
            len = str_len;
        }
        else
        {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0)
    {
        res[len] = '\0';
    }
    else
    {
        res = calloc(1, sizeof(char));
    }
    return res;
}