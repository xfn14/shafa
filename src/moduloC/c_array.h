#ifndef C_ARRAY_H
#define C_ARRAY_H

#include <stdio.h>
#include "../moduloD/d_array.h"

typedef struct {
    unsigned char symb;
    D_Array code;
    int offset;
    int index;
    int next;
} code_struct;

typedef struct {
    code_struct *codes;
    int len;
    long block_size;
} code_list_struct;

typedef struct {
    code_list_struct *lists;
    int len;
} codes_lists_struct;

void getSymbCode(code_list_struct *code_list, unsigned char symb, int offset, code_struct *out_code);
void initCode(code_struct *code);
void setCode(code_struct *code, D_Array code_arr);
void setCodeSymb(code_struct *code, unsigned char symb);
void setCodeOffset(code_struct *code, int offset);
void setCodeIndex(code_struct *code, int index);
void setCodeNext(code_struct *code, int next);
void printCode(code_struct *code);
void setListBlockSize(code_list_struct *list, long block_size);
void freeCode(code_struct *code);
void initList(code_list_struct *list);
void insertCodeList(code_list_struct *list, code_struct code);
void printList(code_list_struct *list);
void freeList(code_list_struct *list);
void initCodesLists(codes_lists_struct *codes_lists);
void insertCodesLists(codes_lists_struct *codes_lists, code_list_struct code_list);
void printCodesLists(codes_lists_struct *codes_lists);
void freeCodesLists(codes_lists_struct *codes_lists);

#endif
