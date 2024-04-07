#include "lab1func.h"
#define floor(x) ((float)((int)x))

void clearbuf(){
    char symbol = ' ';
    symbol = getchar();
    while ((symbol != '\n') && (symbol != EOF)) 
    {
        symbol = getchar();
    }
}

int getint(){
    float tmp;
    scanf("%f", &tmp);
    printf("\n");
    while (floor(tmp) - tmp != 0)
    {
        clearbuf();
        scanf("%f", &tmp);
        printf("\n");
    }
return (int) tmp;
}

int getquantity(){
    float tmp;
    scanf("%f", &tmp);
    printf("\n");
    while ((floor(tmp) - tmp != 0) || (tmp < 0))
    {
        clearbuf();
        scanf("%f", &tmp);
        printf("\n");
    }
    return (int) tmp;
}


Matrix* input_matrix(){
    int m = 0;
    printf("Input the number of strings:\n");
    m = getquantity();
    Matrix* head = calloc(1, sizeof(Matrix));
    if (!head){ // Вынести в отдельную функцию?
        printf("Failed to allocate memory\n");
        return 0;
    }
    Line *lines = calloc(m, sizeof(Line));
    if (!lines){ // Вынести в отдельную функцию?
        printf("Failed to allocate memory\n");
        return 0;
    }
    head->matrix = lines;
    head->m = m; 
    for (int i = 0; i < head->m; i++){ // Движение по строкам
        printf("Input the number of elements in %d string:\n", i + 1);
        (lines + i)->n = getint();
        (lines + i)->string = calloc((lines + i)->n, 4);
        if (!head){ // Вынести в отдельную функцию?
            printf("Failed to allocate memory\n");
            return 0;
        }
        for (int j = 0; j < (lines + i)->n; j++){ // Заполнение строки
            printf("Input the %d element:\n", j + 1);
            ((lines + i)->string)[j] = getint();
        }
    }
    return head;
}

void output_matrix(Matrix* head){
    for(int i = 0; i < head->m; i++){
        for(int j = 0; j < ((head->matrix) + i)->n; j++){
            printf("%d ", (((head->matrix) + i)->string)[j]);
        }
        printf("\n");
    }
}

Matrix* change_matrix(Matrix* head){
    int positive_str = 0, negative_str = 0, max_pos = 0, max_neg = 0;
    for(int i = 0; i < head->m; i++){ // Движение по строкам
        int pnum = 0, nnum = 0;
        for(int j = 0; j < ((head->matrix) + i)->n; j++){ // Движение по строке
            if ((((head->matrix) + i)->string)[j] > 0){ pnum += 1; } // К-во положительных
            else if((((head->matrix) + i)->string)[j] < 0){ nnum += 1; } // К-во отрицательных
        }
        if (pnum > max_pos){
            max_pos = pnum;
            positive_str = i;
        }
        if (nnum > max_neg){
            max_neg = nnum;
            negative_str = i;
        }
    }
    Matrix* new = calloc(1, sizeof(Matrix));
    if (!new){ // Вынести в отдельную функцию?
        printf("Failed to allocate memory\n");
        return 0;
    }
    Line *lines = calloc(head->m, sizeof(Line));
    if (!lines){ // Вынести в отдельную функцию?
        printf("Failed to allocate memory\n");
        return 0;
    }
    new->matrix = lines;
    new->m = head->m;
    for(int k = 0; k < new->m; k++){
        if (k == 0){
            lines->string = calloc(((head->matrix) + positive_str)->n, sizeof(int));
            memcpy(lines->string, ((head->matrix) + positive_str)->string, sizeof(int) * ((head->matrix) + positive_str)->n);
            lines->n = ((head->matrix) + positive_str)->n;
        }
        else if (k == positive_str){
            (lines + positive_str)->string = calloc(head->matrix->n, sizeof(int));
            memcpy((lines + positive_str)->string, head->matrix->string, sizeof(int) * head->matrix->n);
            (lines + positive_str)->n = head->matrix->n;
        }
        else if (k == negative_str){
            (lines + negative_str)->string = calloc(((head->matrix) + (new->m) - 1)->n, sizeof(int));
            memcpy((lines + negative_str)->string, ((head->matrix) + (new->m) - 1)->string, sizeof(int) * ((head->matrix) + (new->m) - 1)->n);
            (lines + negative_str)->n = ((head->matrix) + (new->m) - 1)->n;
        }
        else if (k == new->m - 1){
            (lines + (new->m) - 1)->string = calloc(((head->matrix) + negative_str)->n, sizeof(int));
            memcpy((lines + (new->m) - 1)->string, ((head->matrix) + negative_str)->string, sizeof(int) *((head->matrix) + negative_str)->n);
            (lines + (new->m) - 1)->n = ((head->matrix) + negative_str)->n;
        }
        else{
            (lines + k)->string = calloc(((head->matrix) + k)->n, sizeof(int));
            memcpy((lines + k)->string, ((head->matrix) + k)->string, sizeof(int) *((head->matrix) + k)->n);
            (lines + k)->n = ((head->matrix) + k)->n;
        }
    }
    return new;
}

void clean_matrix(Matrix* head){
    for (int i = 0; i < head->m; i++){
        free(((head->matrix) + i)->string);
    }
    free(head->matrix);
    free(head);
}