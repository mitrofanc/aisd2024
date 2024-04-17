#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define floor(x) ((float)((int)x))
#include "lab3afunc.h"

int main(){
    Table* table = D_Make_Table();
    uint64_t choice = 1;
    while (choice <= 5){
        printf("Select an action:\n");
        printf("0. Make table\n");
        printf("1. Insert new node\n");
        printf("2. Delete node\n");
        printf("3. Search node\n");
        printf("4. Output table\n");
        printf("5. Insert from file\n");
        printf("6. Exit\n");
        printf("\n");
        choice = get_pos_int();
        switch (choice){
            case 0:
                printf("\e[1;1H\e[2J");
                Table_Free(table);
                table = D_Make_Table();
                break;
            case 1:
                printf("\e[1;1H\e[2J");
                D_Insert_Node(table);
                break;
            case 2:
                printf("\e[1;1H\e[2J");
                D_Delete(table);
                break;
            case 3:
                printf("\e[1;1H\e[2J");
                D_Search_Table(table);
                break;
            case 4:
                printf("\e[1;1H\e[2J");
                D_Output_Table(table);
                break;
            case 5:
                printf("\e[1;1H\e[2J");
                D_Fill_From_File(&table);
                break;
        }

    }
    Table_Free(table);
    return 0; //todo freefunc
}
