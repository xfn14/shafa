#ifndef MODULO_C_H
#define MODULO_C_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "math.h"
#include "../moduloD/d_array.h"
#include "c_array.h"
#include "d_matrix.h"

/**
 * @brief Codificação de um ficheiro de símbolos
 *
 * @param[in] argc
 * @param[in] argv
 */
int moduloC(int argc, char **argv);

/**
 * @brief Shannon-Fano encoding
 *
 * @param[in] in_file
 * @param[in] codes_lists
 * @param[in,out] out_bytes
 */
void binary_encoding(char *in_file, codes_lists_struct *codes_lists, D_Matrix_List *out_bytes);

/**
 * @brief Writes the coded bytes on the .shaf file
 *
 * @param[out] out_file
 * @param[in] coded_bytes
 */
void write_codes_in_file(char *out_file, D_Matrix_List *coded_bytes);

/**
 * @brief Gets the codes from the cod file and stores everything in the codes_lists
 *
 * @param[in] filename
 * @param[in,out] codes_lists
 */
void readCodFile(char *filename, codes_lists_struct *codes_lists);

/**
 * @brief Reads a number in a file until the next '@'
 *
 * @param[in] file
 * @return[out] n
 */
long readIntInCod(FILE *fp);

/**
 * @brief Reverse a number
 *
 * @param[in] n
 * @param[out] reversed
 */
int reverse(int n);

/**
 * @brief Print no terminal a informação final de execução
 *
 * @param[in] start_time Tempo de inicio de execução
 * @param[in] shaf_file Nome do ficheiro de output
 */
void print_final_info(clock_t start_time, char *shaf_file);

#endif
