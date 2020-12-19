/**
@file ModuloC.h
Main do ModuloC
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * @brief Codificação de um ficheiro de símbolos
 * 
 * @param[in] filename Nome do ficheiro a codificar
 */
void moduloC(char *filename);

/**
 * @brief Print no terminal a informação final de execução
 * 
 * @param[in] start_time Tempo de inicio de execução
 * @param[in] shaf_file Nome do ficheiro de output
 */
void print_final_info(clock_t start_time, char *shaf_file);