#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "d_array.h"

#ifndef _A_BIN_
#define _A_BIN_

typedef struct nodo {
    int used;
    unsigned char data;
    struct nodo *esq, *dir;
} * Abin;

/**
 * @brief Initiate a tree
 *
 * @returns[out] The tree correctly initated
 */
Abin init_tree();
/**
 * @brief Add a new node to the tree
 *
 * @param[in] Tree
 * @param[in] lado The side where to insert the node (0 -> left)(1 ->right)
 */
void add_new(Abin tree, int lado);
/**
 * @brief Insert a letter to Tree given the path
 *
 * @param[in] Tree
 * @param[in] Code Where the path is stored
 * @param[in] letter The letter to be stored 
 */
void insert_Tree(Abin *tree, D_Array *code, unsigned char letter);
/**
 * @brief Print the tree
 *
 * @param[in] Tree
 */
void imprime(Abin t);
/**
 * @brief Free the Tree
 *
 * @param[in] Tree
 */
void freeAB(Abin t);
/**
 * @brief Search if is something stored in a path
 *
 * @param[in] tree
 * @param[in] Code Where the path is stored
 * @param[in] Result Store the information if search was sucessuful
 * @param[in] Index To iterate the path 
 */
int search_tree(Abin tree, D_Array *code, unsigned char *result,size_t index);

#endif
