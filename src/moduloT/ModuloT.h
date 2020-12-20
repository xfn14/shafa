/**
@file ModuloT.h
Main do ModuloT
*/

#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils.h"

#define CHARS 256

// TODO Comment the code for documentation
int moduloT (char *filename);
FILE *tilAt (FILE *file,LISTA l);
char *addCodFile(char *name);
void writeOnFile (LISTA l,FILE *file);
int getNumLL (char *lista,int fst,int lst);
FILE *writeNum(FILE *input,FILE *output,int *ret,LISTA l);
void getArPares (endPar arPares[],LISTA l);
