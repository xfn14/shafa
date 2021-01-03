#include"Pares.h"
#include <stdio.h>


endPar *arParVazio(int size){
    endPar *result = malloc(size * sizeof(endPar));
    for (int i = 0; i < size;i++){
        result [i] = malloc(sizeof(Pares));
    }
    return result;
}

void switchPares (endPar arPares[], int fst, int lst){
    endPar temp = arPares[fst];
    arPares[fst] = arPares[lst];
    arPares[lst] = temp;
}

void setPar (endPar arPares, int simb, int freq){
    arPares -> fst = simb;
    arPares -> snd = freq;
}

void  cpPar_Snd (endPar source[], endPar dest[], int size, int def){
    for (int i = 0; i < size; i++){
        setPar(dest[i],source [i] -> fst, def);
    }
}

void freeArPares (endPar ar[],int size){
    for(int i = 0;i < size; i++) free( ar [i]);
    free(ar);
}
