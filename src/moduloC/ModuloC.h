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
char*[] binary_coding(unsigned char symbols[], int n_symbols, unsigned char codes[], unsigned int index[], unsigned char next[]);

/**
 * @brief Calcular a lista de indexs
 * 
 * @param[in] symbols 
 * @param[in] n_symbols 
 * @param[in] codes 
 * @param[out] index
 */
int[] calculateIndexs(unsigned char symbols[], int n_symbols, unsigned char codes[]);

/**
 * @brief Read a .cod file and store the codes on a array
 * 
 * @param[in] fp_in 
 * @param[in] filename
 * @param[out] codes
 */
unsigned char* readCodFile(FILE *fp_in, unsigned char *filename);

/**
 * @brief Obter maximo de bits do codigo SF
 * 
 * @param[in] codes 
 * @param[in] n_symbols 
 * @param[out] code_max_size 
 */
int code_max_size(unsigned char *codes[], int n_symbols);

/**
 * @brief Print no terminal a informação final de execução
 * 
 * @param[in] start_time Tempo de inicio de execução
 * @param[in] shaf_file Nome do ficheiro de output
 */
void print_final_info(clock_t start_time, char *shaf_file);