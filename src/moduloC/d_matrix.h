#include <stdio.h>
#include "../moduloD/d_array.h"

typedef struct {
    D_Array *arr;
    int len;
} D_Matrix;

void initMatrix(D_Matrix *m);
void addLineMatrix(D_Matrix *m, D_Array arr);
void printMatrix(D_Matrix *m);
void freeMatrix(D_Matrix *m);

void initMatrix(D_Matrix *m){
    m->arr = malloc(2*sizeof(D_Array));
    m->len = 0;
}

void addLineMatrix(D_Matrix *m, D_Array arr){
    m->len++;
    m->arr = realloc(m->arr, (m->len+1)*sizeof(D_Matrix));

    D_Array copy;
    initArray(&copy, arr.size);
    for(int i = 0; i < arr.used; i++){
        insertArray(&copy, arr.array[i]);
    }

    m->arr[m->len] = copy;
}

void printMatrix(D_Matrix *m){
    for(int i = 0; i < m->len; i++){
        print_array(&m->arr[i], 0);
        printf("\n");
    }
}

void freeMatrix(D_Matrix *m){
    for(int i = 0; i < m->len; i++){
        freeArray(&m->arr[i]);
    }
    free(m->arr);
    m->arr = NULL;
    m->len = 0;
}