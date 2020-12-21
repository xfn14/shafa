/**
 * @file Lista.h
 * @brief List Utility
 * @date 2020-12-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdlib.h>

typedef struct LL {
    int size;
    int last;
    char *lista;
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

LISTA listaVazia(){
    LISTA l = malloc(sizeof(struct LL));
    l->size = 0;
    l->last = 0;
    l->lista = NULL;
    return l;
}

void addToLista(LISTA l, char elem){
    if(l->last == l->size){
        l->size = 2*(l->size)+1;
        l->lista = realloc(l->lista,l->size * sizeof(char));
    }
    l->lista[l->last++] = elem;
}

void setSize(LISTA l, int size){
    if(size > l->size){
        realloc(l->lista, size * sizeof(char));
        l->size = size;
    }
}