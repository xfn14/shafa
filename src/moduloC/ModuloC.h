/**
 * @file ModuloC.h
 * @brief Shannon-Fano Compression
 * @date 2021-1-3
 *
 * @copyright Copyright (c) 2020 - André Vaz, Rui Alves
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "math.h"
#include "../moduloD/d_array.h"
#include "c_array.h"
#include "d_matrix.h"
#include "../moduloD/manual.h"

#ifndef _MODULO_C_H_
#define _MODULO_C_H_

#define MAX_FILENAME 200

/**
 * @brief Codificação de um ficheiro de símbolos
 *
 * @param[in] argc - Numero de argumentos na execuçao do comando
 * @param[in] argv - Argumentos passados
 */
int moduloC(int argc, char **argv);

/**
 * @brief Shannon-Fano encoding.
 *
 * @param[in] in_file - Nome do ficheiro de entrada
 * @param[in] codes_lists - Lista de codigos SF
 * @param[in,out] out_bytes - Lista de bytes finais (por blocos)
 */
int binary_encoding(char *in_file, codes_lists_struct *codes_lists, D_Matrix_List *out_bytes);

/**
 * @brief Writes the coded bytes on the .shaf file
 *
 * @param[out] out_file - Nome do ficheiro onde escrever
 * @param[in] coded_bytes - Lista de bytes a escrever (por blocos)
 */
void write_codes_in_file(char *out_file, D_Matrix_List *coded_bytes);

/**
 * @brief Gets the codes from the cod file and stores everything in the codes_lists
 *
 * @param[in] filename - Nome do ficheiro a ler
 * @param[in,out] codes_lists - Lista de codigos lidos (por blocos)
 */
int readCodFile(char *filename, codes_lists_struct *codes_lists);

/**
 * @brief Le um numero num ficheiro até ao proximo '@'
 *
 * @param[in] file - Pointer do ficheiro a ler
 * @return[out] n - Valor lido
 */
long readIntInCod(FILE *fp);

/**
 * @brief Inverte um numero
 *
 * @param[in] n - Numero a inverter
 * @param[out] reversed - Numero inverso
 */
int reverse(int n);

/**
 * @brief Print no terminal a informação final de execução
 *
 * @param[in] start_time - Tempo de inicio de execução
 * @param[in] shaf_file - Nome do ficheiro de output
 * @param[in] code_list - Lista de codigos lidos (contem os tamanhos iniciais dos blocos)
 * @param[in] out_bytes - Lista final de bytes (contem os tamanhos finais dos blocos)
 */
void print_final_info(clock_t start_time, char *shaf_file, codes_lists_struct *code_list, D_Matrix_List *out_bytes);

#endif
