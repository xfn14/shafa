/**
@file ModuloT.h
Main do ModuloT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define CHARS 256

// TODO Comment the code for documentation
int moduloT (char *filename);
void addCodFile(char *name);
void writeOnFile (LISTA l,FILE *file);
int getNumL (char *lista,int start, int *num);
FILE *writeNum(FILE *input,FILE *output,int *ret,LISTA l);
int getArPares (endPar *arPares,char* l,int filePoint);
int decresArray (endPar arPares[]);
int somaArray (endPar arrPares[],int i,int j);
int melhorDiv (endPar arrPares[],int i,int j);
void addBit (LISTA SF[],int i,int j,char b);
void calcularSF (endPar arrPares[],LISTA SF[],int i, int j);
char *getArrayFile (FILE *input);
void ordSF (LISTA SF[],endPar* Par);
void addSFtoOut (LISTA SF[],LISTA out);