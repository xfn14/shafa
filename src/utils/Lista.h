/**
 * @file Lista.h
 * @brief List Utility
 * @date 2020-12-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>

#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct LL {
    int size;
    int last;
    unsigned char *lista;
} *LISTA;

/**
 * Creates an empty List
 * @param[out] list
*/
LISTA listaVazia();

/**
 * Adds and element to a list
 * @param[in] list
 * @param[in] elem
*/
void addToLista(LISTA l, char elem);

/**
 * Changes the size of a List
 * @param[in] list
 * @param[in] size
*/
void setSize(LISTA l, int size);

void resetLista (LISTA l);

void freeLista (LISTA l);

void copyStrLista (LISTA outputCods, char *fileCont, int fst, int lst);

void switchLista (LISTA SF[],int i,int last);

#endif
