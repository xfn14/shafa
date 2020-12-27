#include <stdio.h>
#ifndef _D_ARRAY_
#define _D_ARRAY_

typedef struct {
    unsigned char *array;
    int used;
    int size;
} D_Array;

void initArray(D_Array *a, size_t initialSize);
void insertArray(D_Array *a, unsigned char element);
void freeArray(D_Array *a);
void remove_first(D_Array *a);
void add_first(D_Array *a, unsigned char element);
void clearArray(D_Array *a);
void print_array(D_Array *a, int mode);
#endif