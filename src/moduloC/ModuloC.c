#include "ModuloC.h"

/**
 * @[número_de_blocos]
 * @[tamanho_bloco_1]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_bloco_1)
 * @[...]
 * @[tamanho_último_bloco]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_último_bloco)
 */

void moduloC(char *filename){
    clock_t start_time = clock();
    
    FILE *in, *out;
    in = fopen(filename, "rb");
    out = fopen(strcat(filename, ".shaf"), "wb+");

    print_final_info(start_time);
}

void print_final_info(clock_t start_time){
    clock_t stop_time = clock();
    double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
    printf("André Vaz (a93221) e Rui Alves, MIEI/CD\n"); // TODO Add time
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: _\n"); // TODO
    printf("Tamanho antes/depois & taxa de compressão (bloco _): _/_\n"); // TODO
    printf("Taxa de compressão global: _%%\n"); // TODO
    printf("Tempo de execução do módulo: %fms\n", elapsed);
    printf("Ficheiro gerado: _\n"); // TODO
}