#include <stdio.h>
#ifndef _A_BIN_
#define _A_BIN_

typedef struct nodo
{
    unsigned char data;
    struct nodo *esq, *dir;
} * Abin;

Abin init_tree();
void add_new(Abin tree, int lado, unsigned char letter);
void insert_Tree(Abin *tree, D_Array *code, unsigned char letter);
void imprime(Abin t);
void freeAB (Abin t);

#endif