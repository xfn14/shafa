#include "ModuloC.h"

#define FILENAME_MAX 100
#define CODE_MAX_SIZE 8

/**
 * @[número_de_blocos]
 * @[tamanho_bloco_1]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_bloco_1)
 * @[...]
 * @[tamanho_último_bloco]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_último_bloco)
 */

 // CODE_MAX_SIZE = length_code_max/8 em excesoo + 1

void moduloC(char *main_file){
    clock_t start_time = clock();
    
    char shaf_file[MAX_FILENAME] = "", cod_file[MAX_FILENAME] = "";
    strcat(shaf_file, main_file); strcat(shaf_file, ".shaf");
    strcat(cod_file, main_file); strcat(cod_file, ".cod");
    FILE *in, *out;
    in = fopen(main_file, "rb");
    out = fopen(shaf_file, "wb+");

    int nr_blocks
    int block_size[nr_blocks];

    print_final_info(start_time, shaf_file);
}

char* binary_coding(char symbols[], int n_symbols, char codes[], char index[], char next[]){
    char *coded_sequence;
    int offset = 0, ind_in = 0, ind_out = 0;
    while(ind_in < n_symbols){
        char symbol = symbols[ind_in] + offset;
        int n_bytes_in_code = index[symbol];
        char code = codes[symbol];
        int ind_code = 0;
        while (ind_code <= n_bytes_in_code){
            coded_sequence[ind_out] = or_bin(coded_sequence[ind_out], code[ind_code]);
            if(ind_code < n_bytes_in_code){
                ind_out = ind_out + 1;
                ind_code = ind_code + 1;
            }
        }
        offset = next[symbol];
        ind_in = ind_in + 1;
    }
    return coded_sequence;
}

// TODO
bool or_bin(char byte_a, char byte_b){

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