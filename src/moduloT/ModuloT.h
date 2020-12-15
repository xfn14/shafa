/**
@file ModuloT.h
Main do ModuloT
*/

#include <stdio.h>
#include <stdlib.h>
#include <inistd.h>
#include <math.h>
#include "../utils/Lista.h"

#define CHARS 255

// TODO Comment the code for documentation
int moduloT(char *filename);
FILE *tilAt(FILE *file, LISTA l);
char *addCodFile(char *name);
void writeOnFile(LISTA l, FILE *file);
int getNumLL(char *lista, int fst, int lst);
FILE *writeNum(FILE *inpu, FILE *output, int *ret, LISTA l);