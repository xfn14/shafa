/**
@file Lista.h
List Utility
*/
#include <stdlib.h>

/**
 * @brief Store Shannon-Fano Codes
 */
typedef struct node{
    char sym;

    float prob;
    int code[20];
    int top;
} codes[256]; // N=256 (8 bits)

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