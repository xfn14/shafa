#include <stdio.h>
#include <stdlib.h>
#include "d_array.h"


void initArray(D_Array *a, size_t initialSize) {
  a->array= malloc(initialSize * sizeof(unsigned char));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(D_Array *a, unsigned char element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(unsigned char));
  }
  a->array[a->used++] = element;
}

void freeArray(D_Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
