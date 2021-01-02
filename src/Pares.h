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

endPar *arParVazio (int size);
void switchPares (endPar arPares[], int fsr, int lst);
void setPar (endPar arPares, int simb, int freq);
void cpPar_Snd (endPar source[],endPar dest[],int size,int def);
void freeArPares (endPar ar[],int size);