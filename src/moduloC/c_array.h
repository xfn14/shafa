#include <stdio.h>

typedef struct {
    unsigned char symb;
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

typedef struct {
    code_list_struct *lists;
    int len;
} codes_lists_struct;

void initCode(code_struct *code);
void insertCharCode(code_struct *code, unsigned char cat);
void setCodeOffset(code_struct *code, int offset);
void setCodeIndex(code_struct *code, int index);
void setCodeNext(code_struct *code, int next);
void printCode(code_struct *code);
void freeCode(code_struct *code);
void initList(code_list_struct *list);
void insertCodeList(code_list_struct *list, code_struct code);
void printList(code_list_struct *list);
void freeList(code_list_struct *list);
void initCodesLists(codes_lists_struct *codes_lists);
void printCodesLists(codes_lists_struct *codes_lists);
void freeCodesLists(codes_lists_struct *codes_lists);

void initCode(code_struct *code){
    code->symb = -1;
    code->code = malloc(16*sizeof(unsigned char));
    code->len = code->offset = code->index = code->next = 0;
}

void initList(code_list_struct *list){
    list->codes = malloc(sizeof(code_struct));
    list->len = 0;
}

void initCodesLists(codes_lists_struct *codes_lists){
    codes_lists->lists = malloc(sizeof(code_list_struct));
    codes_lists->len = 0;
}

void insertCharCode(code_struct *code, unsigned char cat){
    code->len++;
    code->code = realloc(code->code, (code->len+1)*sizeof(unsigned char));
    code->code[code->len-1] = cat;
}

void setCodeSymb(code_struct *code, unsigned char symb){
    code->symb = symb;
}

void setCodeOffset(code_struct *code, int offset){
    code->offset = offset;
}

void setCodeIndex(code_struct *code, int index){
    code->offset = index;
}

void setCodeNext(code_struct *code, int next){
    code->next = next;
}

void insertCodeList(code_list_struct *list, code_struct code){
    list->len++;
    list->codes = realloc(list->codes, (list->len+1)*sizeof(code_struct));
    list->codes[list->len-1] = code;
}

void insertCodesLists(codes_lists_struct *codes_lists, code_list_struct code_list){
    codes_lists->len++;
    codes_lists->lists = realloc(codes_lists->lists, (codes_lists->len+1)*sizeof(codes_lists_struct));
    codes_lists->lists[codes_lists->len-1] = code_list;
}

void printCode(code_struct *code){
    printf("symb: %c; code: ", code->symb);
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

void printCodesLists(codes_lists_struct *codes_lists){
    for(int i = 0; i < codes_lists->len; i++){
        printf("---------------------- v block: %d v ----------------------\n", i);
        printList(&codes_lists->lists[i]);
    }
    printf("----------------------------------------------------------\n");
}

void freeCode(code_struct *code){
    code->symb = -1;
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

void freeCodesLists(codes_lists_struct *codes_lists){
    for(int i = 0; i < codes_lists->len; i++){
        freeList(&codes_lists->lists[i]);
    }
    free(codes_lists->lists);
    codes_lists->lists = NULL;
    codes_lists->len = 0;
}
