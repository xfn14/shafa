#include <stdlib.h>

//Type de um par
typedef struct Par{
    int fst;
    int snd;
} Pares, *endPar;

// Troca dois pares num arr de pares
void switchPares (endPar arPares[], int fsr, int lst);