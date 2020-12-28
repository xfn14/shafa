#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "d_array.h"


#ifndef _AUXILIAR_
#define _AUXILIAR_

int fsize(FILE *fp);
void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer);
int skip(int index, int stop, unsigned char *buffer); 
int do_size(unsigned char *buffer, int *array);
void int_bin(unsigned char letter, int *bin);
void get_filenames(char *filename, char *cod_file, char *output_file);
void error_messages(int n);
#endif