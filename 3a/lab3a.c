#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        choice = get_u64();
        printf("\e[1;1H\e[2J");
        switch (choice){
            case 0:
                Table_Free(table);
                table = D_Make_Table();
                break;
            case 1:
                D_Insert_Node(table);
                break;
            case 2:
                D_Delete(table);
                break;
            case 3:
                D_Search_Table(table);
                break;
            case 4:
                D_Output_Table(table);
                break;
            case 5:
                D_Fill_From_File(&table);
                break;
        }

    }
    Table_Free(table);
    return 0;
}
