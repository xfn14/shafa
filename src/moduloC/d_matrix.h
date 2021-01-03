/**
 * @file d_matrix.h
 * @brief Estrutura para armazenar os bytes já codificados
 * @date 2021-1-3
 *
 * @copyright Copyright (c) 2020 - André Vaz, Rui Alves
 */

#ifndef _D_MATRIX_H_
#define _D_MATRIX_H_

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

/**
 * @brief Inicializar uma D_Matrix
 *
 * @param[in] m - Matrix a ser inicializada
 */
void initMatrix(D_Matrix *m);

/**
 * @brief Adiciona uma D_Array à D_Matrix
 *
 * @param[in] m - Matrix onde adicionar
 * @param[in] arr - D_Array a ser adiconada
 */
void addLineMatrix(D_Matrix *m, D_Array arr);

/**
 * @brief Limpar uma D_Matrix
 *
 * @param[in] m - Matrix a ser limpa
 */
void clearMatrix(D_Matrix *m);

/**
 * @brief Imprimir uma D_Matrix no terminal
 *
 * @param[in] m - Matrix a ser impresa
 */
void printMatrix(D_Matrix *m);

/**
 * @brief Liberta da memoria uma D_Matrix
 *
 * @param[in] m - Matrix a ser libertada
 */
void freeMatrix(D_Matrix *m);

/**
 * @brief Inicializar uma D_Matrix_List
 *
 * @param[in] m_list - Lista a ser inicializada
 */
void initMatrixList(D_Matrix_List *m_list);

/**
 * @brief Adiciona uma D_Matrix à D_Matrix_List
 *
 * @param[in] m_list - Lista onde adicionar
 * @param[in] arr - Matrix a ser adiconada
 */
void insertMatrixInList(D_Matrix_List *m_list, D_Matrix m);

/**
 * @brief Limpar uma D_Matrix_List
 *
 * @param[in] m_list - Lista a ser limpa
 */
void clearMatrixList(D_Matrix_List *m_list);

/**
 * @brief Imprime uma D_Matrix_List no terminal
 *
 * @param[in] m_list - Lista a ser impresa
 */
void printMatrixList(D_Matrix_List *m_list);

/**
 * @brief Liberta uma D_Matrix_List da memoria
 *
 * @param[in] m_list - Lista a ser libertada
 */
void freeMatrixList(D_Matrix_List *m_list);

#endif
