#include "d_array.h"

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

void add_first(D_Array *a, unsigned char element){
    a->used = a->used + 1;
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(unsigned char));
    }
    for(int i = a->used; i > 0; i--){
        a->array[i] = a->array[i-1];
    }
    a->array[0] = element;
}

void clearArray(D_Array *a){
    for(int i = 0; i < a->used; i++){
        a->array[i] = 0;
    }
    a->used = 0;
}


void freeArray(D_Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}
void or_opp(D_Array *arr1, D_Array arr2){
    if(arr1->used != arr2.used) return;
    for(int i = 0; i < arr1->used; i++){
        arr1->array[i] = (arr1->array[i] == '1' || arr2.array[i] == '1') ? '1' : '0';
    }
}

void print_array(D_Array *a, int mode) {
    for (int i = 0; i < a->used; i++) {
        if (mode)
            printf("%d", a->array[i]);
        else
            printf("%c", a->array[i]);
    }
//    putchar('\n');
}
