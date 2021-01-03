/**
 * @file c_array.h
 * @brief Estrutura para armazenar os codigos Shannon-Fano
 * @date 2021-1-3
 *
 * @copyright Copyright (c) 2020 - André Vaz, Rui Alves
 */

#ifndef _C_ARRAY_H_
#define _C_ARRAY_H_

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

/**
 * @brief Obter o codigo de determinado simbolo
 *
 * @param[in] code_list - Lista de codigos onde o simbolo esta guardado
 * @param[in] symb - Simbolo a procurar
 * @param[in] offset - Offset do simbolo
 * @param[out] out_code - Codigo obtido
 */
void getSymbCode(code_list_struct *code_list, unsigned char symb, int offset, code_struct *out_code);

/**
 * @brief Inicializa um codigo
 *
 * @param[in] code - Codigo a inicializar
 */
void initCode(code_struct *code);

/**
 * @brief Mete o codigo de um code_struct
 *
 * @param[in] code - Codigo onde ser inserido
 * @param[in] code_arr - Codigo a inserir
 */
void setCode(code_struct *code, D_Array code_arr);

/**
 * @brief Definir o simbolo de determinado codigo
 *
 * @param[in] code - Codigo onde definir
 * @param[in] symb - Simbolo a definir
 */
void setCodeSymb(code_struct *code, unsigned char symb);

/**
 * @brief Definir o offset de determinado codigo
 *
 * @param[in] code - Codigo onde definir
 * @param[in] offset - Offset a definir
 */
void setCodeOffset(code_struct *code, int offset);

/**
 * @brief Definir o index de determinado codigo
 *
 * @param[in] code - Codigo onde definir
 * @param[in] index - Index a definir
 */
void setCodeIndex(code_struct *code, int index);

/**
 * @brief Definir o next de determinado codigo
 *
 * @param[in] code - Codigo onde definir
 * @param[in] next - Next a definir
 */
void setCodeNext(code_struct *code, int next);

/**
 * @brief Imprimir certo codigo no terminal
 *
 * @param[in] code - Codigo a imprimir
 */
void printCode(code_struct *code);

/**
 * @brief Define o tamanho do bloco de determinada lista de codigos
 *
 * @param[in] list - Lista onde definir
 * @param[in] block_size - Tamanho do bloco
 */
void setListBlockSize(code_list_struct *list, long block_size);

/**
 * @brief Liberta da memoria determinado codigo
 *
 * @param[in] code - Codigo a ser libertado
 */
void freeCode(code_struct *code);

/**
 * @brief Inicializar uma lista de codigos
 *
 * @param[in] list - Lista a inicializar
 */
void initList(code_list_struct *list);

/**
 * @brief Insere um codigo numa lista
 *
 * @param[in] list - Lista onde inserir
 * @param[in] code - Codigo a inserir
 */
void insertCodeList(code_list_struct *list, code_struct code);

/**
 * @brief Imprime um lista de codigos no terminal
 *
 * @param[in] list - Lista a imprimir
 */
void printList(code_list_struct *list);

/**
 * @brief Liberta de memoria uma lista de codigos
 *
 * @param[in] list - Lista a ser libertada
 */
void freeList(code_list_struct *list);

/**
 * @brief Inicializa uma lista de blocos de codigo
 *
 * @param[in] codes_lists - Lista do bloco a ser inicializada
 */
void initCodesLists(codes_lists_struct *codes_lists);

/**
 * @brief Insere uma lista de codigos numa lista de codigos do bloco
 *
 * @param[in] codes_lists - Lista on inserir a lista
 * @param[in] code_list - Lista de codigos a ser inserida
 */
void insertCodesLists(codes_lists_struct *codes_lists, code_list_struct code_list);

/**
 * @brief Imprime a lista de codigos de um bloco
 *
 * @param[in] codes_lists - Lista a ser impresa
 */
void printCodesLists(codes_lists_struct *codes_lists);

/**
 * @brief Liberta de memoria uma lista de codigos de um bloco
 *
 * @param[in] codes_lists - Lista de codigos a ser libertada
 */
void freeCodesLists(codes_lists_struct *codes_lists);

#endif
