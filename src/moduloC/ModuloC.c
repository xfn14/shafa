#include "ModuloC.h"

#define MAX_FILENAME 100
#define BLOCK_MAX_SIZE 2048
#define CODE_MAX_SIZE 8

/**
 * @[número_de_blocos]
 * @[tamanho_bloco_1]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_bloco_1)
 * @[...]
 * @[tamanho_último_bloco]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_último_bloco)
 */

 // CODE_MAX_SIZE = length_code_max/8 em excesso + 1

void moduloC(char *main_file){
    clock_t start_time = clock();
    
    unsigned char shaf_file[MAX_FILENAME] = "", cod_file[MAX_FILENAME] = "";
    strcat(shaf_file, main_file); strcat(shaf_file, ".shaf");
    strcat(cod_file, main_file); strcat(cod_file, ".cod");
    FILE *in, *out;
    in = fopen(cod_file, "rb");
    out = fopen(shaf_file, "wb+");

    int n_blocks = 2; // TODO
    int block_size[n_blocks]; // TODO

    print_final_info(start_time, shaf_file);
}

// TODO
void binary_encoding(char *filename, char *out_file, codes_lists_struct codes_lists){
    // Open in and out files
    FILE *in = fopen(filename, "rb"), *out = fopen(out_file, "wb+");

    // Get in file size info

//    block_size = 2048; // default block_size (amend)
//    n_blocks = fsize(in, NULL, &block_size, &size_of_last_block);
//    total = (n_blocks-1)*block_size+size_of_last_block;

    // Iterate all blocks
//    for(int crt_block = 0; crt_block < n_blocks; crt_block++){
//        code_list_struct block_code_list = codes_lists->lists[crt_block];
//        unsigned long crt_block_size = (crt_block+1)==n_blocks ? size_of_last_block : block_size;
//        unsigned char *crt_block_buffer = malloc(sizeof(unsigned char)*crt_block_size);
//        fread(crt_block_buffer, sizeof(unsigned char), crt_block_size, in);
//
//
//        for(int i = 0; i < crt_block_size; i++){
//            unsigned char crt_symb = crt_block_buffer[i];
//            code_struct code_to_use;
//            for(int j = 0; j < block_code_list.len; j++){
//                if(block_code_list.codes[j] == crt_symb);
//            }
//        }
//    }

    fclose(in); fclose(out); // Close in and out files
}

long readIntInCod(FILE *fp){
    int decimal = 0;
    char crt_char = '0';
    long finalN = 0;
    while(crt_char != '@'){
        fread(&crt_char, sizeof(char), 1, fp); decimal++;
        if(crt_char != '@'){
            int crt_int = atoi(&crt_char);
            printf("%d", crt_int);
            finalN = (long) pow(10, decimal)*crt_int + finalN;
        }
    }
    return reverse(finalN/10);
}

int reverse(int n){
    int rev = 0, remainder;
    while(n != 0){
        remainder = n % 10;
        rev = rev * 10 + remainder;
        n /= 10;
    }
    return rev;
}

void print_final_info(clock_t start_time, char shaf_file[]){
    clock_t stop_time = clock();
    double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
    printf("André Vaz (a93221) e Rui Alves, MIEI/CD\n"); // TODO Add time
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: _\n"); // TODO
    printf("Tamanho antes/depois & taxa de compressão (bloco _): _/_\n"); // TODO
    printf("Taxa de compressão global: _%%\n"); // TODO
    printf("Tempo de execução do módulo: %fms\n", elapsed);
    printf("Ficheiro gerado: %s\n", &shaf_file);
}