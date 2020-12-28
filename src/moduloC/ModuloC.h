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
 * @param[in] filename Nome do ficheiro a codificar
 */
void moduloC(char *filename);

/**
 * @brief Shannon-Fano encoding
 *
 * @param[in] filename
 * @param[in] out_file
 * @param[in] codes_lists
 * @param[in,out] out_bytes
 */
void binary_encoding(char *in_file, char *out_file, codes_lists_struct *codes_lists, D_Matrix *out_bytes);

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