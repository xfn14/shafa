#ifndef D_MATRIX_H
#define D_MATRIX_H

#include <stdio.h>
#include "../moduloD/d_array.h"

typedef struct {
    D_Array *arr;
    int len;
} D_Matrix;

typedef struct {
    D_Matrix *list;
    int len;
} D_Matrix_List;

void initMatrix(D_Matrix *m);
void addLineMatrix(D_Matrix *m, D_Array arr);
void clearMatrix(D_Matrix *m);
void printMatrix(D_Matrix *m);
void freeMatrix(D_Matrix *m);

void initMatrixList(D_Matrix_List *m_list);
void insertMatrixInList(D_Matrix_List *m_list, D_Matrix m);
void clearMatrixList(D_Matrix_List *m_list);
void printMatrixList(D_Matrix_List *m_list);
void freeMatrixList(D_Matrix_List *m_list);

#endif
