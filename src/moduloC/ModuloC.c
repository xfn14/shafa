#include "ModuloC.h"

#define MAX_FILENAME 100

/**
 * @[número_de_blocos]
 * @[tamanho_bloco_1]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_bloco_1)
 * @[...]
 * @[tamanho_último_bloco]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_último_bloco)
 */

void moduloC(char *main_file){
    clock_t start_time = clock();
    
    char shaf_file[MAX_FILENAME] = "", cod_file[MAX_FILENAME] = "";
    strcat(shaf_file, main_file); strcat(shaf_file, ".shaf");
    strcat(cod_file, main_file); strcat(cod_file, ".cod");
    FILE *in, *out;
    in = fopen(cod_file, "rb");
    out = fopen(shaf_file, "wb+");

    print_final_info(start_time, shaf_file);
}

void print_final_info(clock_t start_time, char *shaf_file){
    clock_t stop_time = clock();
    double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
    printf("André Vaz (a93221) e Rui Alves, MIEI/CD\n"); // TODO Add time
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: _\n"); // TODO
    printf("Tamanho antes/depois & taxa de compressão (bloco _): _/_\n"); // TODO
    printf("Taxa de compressão global: _%%\n"); // TODO
    printf("Tempo de execução do módulo: %fms\n", elapsed);
    printf("Ficheiro gerado: %s\n", shaf_file);
}