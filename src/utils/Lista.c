#include "Lista.h"

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
        l->lista = (char *) realloc(l->lista,l->size * sizeof(char));
    }
    l->lista[l->last++] = elem;
}

void setSize(LISTA l, int size){
    if(size > l->size){
        l->lista = (char *) realloc(l->lista, size * sizeof(char));
        l->size = size;
    }
}

void resetLista (LISTA l){
    l->last = 0;
}
