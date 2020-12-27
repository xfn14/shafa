#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "c_array.h"
#include "math.h"
#include "../moduloD/d_array.h"

/**
 * @brief Codificação de um ficheiro de símbolos
 * 
 * @param[in] filename Nome do ficheiro a codificar
 */
void moduloC(char *filename);

/**
 * @brief Shannon-Fano encoding
 *
 * @param filename
 * @param out_file
 * @param codes_lists
 */
void binary_encoding(char *filename, char *out_file, codes_lists_struct codes_lists);

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