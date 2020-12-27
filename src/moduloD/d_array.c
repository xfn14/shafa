#include "d_array.h"

#include <stdio.h>
#include <stdlib.h>

void initArray(D_Array *a, size_t initialSize) {
    a->array = malloc(initialSize * sizeof(unsigned char));
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

void remove_last(D_Array *a) {
    a->used--;
}

void remove_first(D_Array *a) {
    a->used = a->used - 1;
    for (int i = 0; i < a->used; i++) {
        a->array[i] = a->array[i + 1];
    }
}

void freeArray(D_Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void print_array(D_Array *a, int mode) {
    //printf ("array with length of %d\n",a->used);
    for (int i = 0; i < a->used; i++) {
        if (mode)
            printf("%d", a->array[i]);
        else
            printf("%c", a->array[i]);
    }
    putchar('\n');
}
/*
void main (){
  D_Array a;
  initArray(&a,5);
  insertArray (&a,'i');
  insertArray (&a,'o');
  insertArray (&a,'g');
  insertArray (&a,'o');
  insertHArray(&a,'d'); 
  print_array(&a);
}*/