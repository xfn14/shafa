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

void or_opp(D_Array *arr1, D_Array *arr2, int mode){
    if((arr1->used)*2 != arr2->used){
        printf("error, invalid arr");
        printf("%d %d\n", arr1->used, arr2->used);
        return;
    }

    for(int i = 0; i < 8; i++){
        if(mode){
            arr1->array[i] = (arr1->array[i] == '1' || arr2->array[i+8] == '1') ? '1' : '0';
        }else{
            arr1->array[i] = (arr1->array[i] == '1' || arr2->array[i] == '1') ? '1' : '0';
        }
    }
}

void initByte(D_Array *arr){
    arr->used = 8;
    arr->size = 9;
    arr->array = malloc(arr->size*sizeof(unsigned char));
    for(int i = 0; i < 8; i++){
        arr->array[i] = '0';
    }
}

void clear_byte(D_Array *arr){
    if(arr->used > 8){
        for(int i = 8; i < arr->used; i++){
            arr->array[i] = 0;
        }
    }
    for(int i = 0; i < 8; i++){
        arr->array[i] = '0';
    }
    arr->used = 8;
}

void print_array(D_Array *a, int mode) {
    //printf ("array with length of %d\n",a->used);
    for (int i = 0; i < a->used; i++) {
        if (mode)
            printf("%d", a->array[i]);
        else
            printf("%c", a->array[i]);
    }
//    putchar('\n');
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