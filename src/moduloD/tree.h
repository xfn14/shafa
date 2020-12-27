#include <stdio.h>

#include "d_array.h"
#ifndef _A_BIN_
#define _A_BIN_

typedef struct nodo {
    int used;
    unsigned char data;
    struct nodo *esq, *dir;
} * Abin;

Abin init_tree();
void add_new(Abin tree, int lado);
void insert_Tree(Abin *tree, D_Array *code, unsigned char letter);
void imprime(Abin t);
void freeAB(Abin t);
int search_tree(Abin tree, D_Array *code, unsigned char *result,int index);

#endif