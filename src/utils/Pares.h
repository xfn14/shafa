#include <stdlib.h>

/**
 * @brief Type de um par
 * 
 */
typedef struct Par{
    int fst;
    int snd;
} Pares, *endPar;

/**
 * @brief Troca dois pares num array de pares
 * 
 * @param[in] arPares 
 * @param[in] fsr 
 * @param[in] lst 
 */
void switchPares (endPar arPares[], int fsr, int lst);
void setPar (endPar arPares, int simb, int freq);

void switchPares (endPar arPares[], int fst, int lst){
    endPar temp = arPares[fst];
    arPares[fst] = arPares[lst];
    arPares[lst] = temp;
}

void setPar (endPar arPares, int simb, int freq){
    arPares -> fst = simb;
    arPares -> snd = freq;
}