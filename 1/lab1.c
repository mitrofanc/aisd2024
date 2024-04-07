#include <stdio.h>
#include <stdlib.h>
#include "lab1func.h"
#include <limits.h> //Delete
#include <string.h>



int main(){
    Matrix* matrix = input_matrix();
    printf("The original matrix:\n");
    output_matrix(matrix);
    Matrix* matrix2 = change_matrix(matrix);
    printf("The resulting matrix:\n");
    output_matrix(matrix2);
    clean_matrix(matrix);
    return 0;
}