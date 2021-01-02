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
        l->lista = (unsigned char *) realloc(l->lista,l->size * sizeof(unsigned char));
    }
    l->lista[l->last++] = elem;
}

void setSize(LISTA l, int size){
    if(size > l->size){
        l->lista = (unsigned char *) realloc(l->lista, size * sizeof(unsigned char));
        l->size = size;
    }
}

void resetLista (LISTA l){
    l->last = 0;
}

void freeLista (LISTA l){
    free (l -> lista);
    free (l);
}

void copyStrLista (LISTA outputCods,char *fileCont,int fst,int lst){
    while (fst < lst ){
        addToLista(outputCods,fileCont[fst]);
        fst ++;
    }
}

void switchLista (LISTA SF[],int i,int last){
    LISTA temp;
    temp = SF[i];
    SF[i] = SF[last];
    SF[last] = temp;
}