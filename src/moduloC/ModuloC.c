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

char*[] formatCodes(unsigned char *codes[], unsigned int n_codes){
    unsigned char *out_codes[] = malloc(sizeof(char)*n_codes);
    int crt = 0;
    for(int i = 0; i < n_codes; i++){
        char temp_char[] = malloc(sizeof(char)*strlen(codes[i]));
        strcat(temp_char, codes[i]);
        for(int j = 0; j < (8 - strlen(temp_char)); j++){
            strcat(temp_char, "0");
        }
        strcat(temp_char, ".00000000");
        strcat(out_codes, &temp_char);
        free(temp_char);
    }
    return &out_codes;
}

// // TODO
// char*[] binary_coding(unsigned char *symbols[], unsigned int n_symbols, unsigned char *codes[], unsigned int index[], unsigned char next[]){
//     unsigned char *form_codes[];
//     formatCodes(codes, &form_codes);
    
//     unsigned char *coded_sequence[];
//     int offset = 0, ind_in = 0, ind_out = 0;
//     while(ind_in < n_symbols){
//         char symbol = symbols[ind_in] + offset;
//         int n_bytes_in_code = index[symbol];
//         char code = codes[symbol];
//         int ind_code = 0;
//         while (ind_code <= n_bytes_in_code){
//             coded_sequence[ind_out] = coded_sequence[ind_out]|code[ind_code];
//             if(ind_code < n_bytes_in_code){
//                 ind_out++; ind_code++;
//             }
//         }
//         offset = next[symbol];
//         ind_in = ind_in + 1;
//     }
//     return coded_sequence;
// }

int code_max_size(unsigned char *codes[], int n_symbols){
    int i = 0, max = 0;
    while(i < n_symbols){
        if(max < strlen(codes[i])) max = strlen(codes[i]);
        i++;
    }
    return max;
}

// TODO
int[] calculateIndexs(unsigned char symbols[], int n_symbols, unsigned char codes[]){
    unsigned int *index;
    return index;
}

// TODO
unsigned char* readCodFile(FILE *fp_in, unsigned char *filename){
    unsigned char *codes, *temp_buffer;
    unsigned long long total;

    FILE *fp;
    if(filename == NULL || *filename == 0){
        fp = fp_in;
    }else{
        fp = fopen(filename, "rb");
        if(fp == NULL) return NULL;
    }

    // TODO fseek tem de percorrer 2 vezes o ficheiro
    fseek(fp, 0L, SEEK_END);
    total = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    temp_buffer = malloc(sizeof(unsigned char) * total);

    fread(temp_buffer, sizeof(temp_buffer)*total, 1, fp);
    for(int i = 0; i < total; i++){
        printf("%d ", temp_buffer[i]);
    }

    // N(78); R(82)
    // TODO RLE 
    // if(temp_buffer[1] = 82){

    return codes;
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