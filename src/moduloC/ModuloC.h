#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../utils/Lista.h"

/**
 * @brief Codificação de um ficheiro de símbolos
 * 
 * @param[in] filename Nome do ficheiro a codificar
 */
void moduloC(char *filename);

/**
 * @brief Optimizar a codificação binária SF com matrizes de bytes
 * 
 * @param[in] symbols 
 * @param[in] n_symbols 
 * @param[in] codes 
 * @param[in] index 
 * @param[in] next
 * @param[out] coded_sequence
 */
char* binary_coding(char symbols[], int n_symbols, char codes[], char index[], char next[]);

/**
 * @brief Print no terminal a informação final de execução
 * 
 * @param[in] start_time Tempo de inicio de execução
 * @param[in] shaf_file Nome do ficheiro de output
 */
void print_final_info(clock_t start_time, char *shaf_file);