#include <stdio.h>

typedef struct {
    unsigned char *code;
    int len;
    int offset;
    int index;
    int next;
} code_struct;

typedef struct {
    code_struct *codes;
    int len;
} code_list_struct;

void initCode(code_struct *code);
void insertCharCode(code_struct *code, unsigned char cat);
void printCode(code_struct *code);
void freeCode(code_struct *code);
void initList(code_list_struct *list);
void insertCodeList(code_list_struct *list, code_struct code);
void printList(code_list_struct *list);
void freeList(code_list_struct *list);

void initCode(code_struct *code){
    code->code = malloc(16*sizeof(unsigned char));
    code->len = code->offset = code->index = code->next = 0;
}

void initList(code_list_struct *list){
    list->codes = malloc(sizeof(code_struct));
    list->len = 0;
}

void insertCharCode(code_struct *code, unsigned char cat){
    code->len++;
    code->code = realloc(code->code, (code->len+1)*sizeof(unsigned char));
    code->code[code->len-1] = cat;
}

void insertCodeList(code_list_struct *list, code_struct code){
    list->len++;
    list->codes = realloc(list->codes, (list->len+1)*sizeof(code_struct));
    list->codes[list->len-1] = code;
}

void printCode(code_struct *code){
    printf("code: ");
    for(int i = 0; i < code->len; i++){
        printf("%c", code->code[i]);
    }
    printf("; len = %d; offset: %d; index: %d; next: %d\n", code->len, code->offset, code->index, code->next);
}

void printList(code_list_struct *list){
    for(int i = 0; i < list->len; i++){
        printCode(&list->codes[i]);
    }
}

void freeCode(code_struct *code){
    free(code->code);
    code->code = NULL;
    code->len = code->offset = code->index = code->next = 0;
}

void freeList(code_list_struct *list){
    for(int i = 0; i < list->len; i++){
        freeCode(&list->codes[i]);
    }
    free(list->codes);
    list->codes = NULL;
    list->len = 0;
}