#include "hash_table_func.h"

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
                error = D_Insert(&table);
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
    return 0;
}
