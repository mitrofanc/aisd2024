#ifndef lab1func
#define lab1func
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line {
    int n; // количество элементов в строке
    int* string; // массив 
} Line;

typedef struct Matrix {
    int m; 
    Line* matrix;
} Matrix;

void clearbuf(); // Функция для очистки буфера
int getint(); // Проверка на целое число
int getquantity(); // Проверка на целое положительное число
Matrix* input_matrix(); // Ввод матрицы
void output_matrix(Matrix* matrix); // Вывод матрицы
Matrix* change_matrix(Matrix* head); // Преобразование матрицы
void clean_matrix(Matrix* head); // Очистка
#endif