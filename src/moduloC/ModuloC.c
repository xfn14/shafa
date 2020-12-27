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

void readCodFile(char *filename){
    FILE *in;
    in = fopen(filename, "rb");

    char normal_rle;
    unsigned long long total;
    unsigned long size_of_last_block;

    fseek(in, 1, SEEK_SET);
    fread(&normal_rle, sizeof(char), 1, in);
//    printf("%c\n", normal_rle);
    int chars_read = 3;
    fseek(in, chars_read, SEEK_SET);

    long n_blocks = readIntInCod(in);
    printf("n_blocks: %ld\n", n_blocks);

    codes_lists_struct codes_lists; // output
    initCodesLists(&codes_lists);

    for(int i = 0; i < n_blocks; i++){
        code_list_struct block_codes;
        initList(&block_codes);
        long block_size = readIntInCod(in);
        setListBlockSize(&block_codes, block_size);

        unsigned char symb = 0;
        unsigned char crt_char = 0;
        D_Array crt_code;
        initArray(&crt_code, 3);
        while(crt_char != '@'){
            fread(&crt_char, sizeof(unsigned char), 1, in);
            if(crt_char == ';'){
                if(crt_code.used != 0){
                    for(int j = 0; j < 8; j++){
                        code_struct act_code;
                        initCode(&act_code);
                        setCodeSymb(&act_code, symb);
                        setCodeOffset(&act_code, j);

                        D_Array offset_code;
                        initArray(&offset_code, 5);
                        // Make offset
                        if(j != 0){
                            for(int p = 0; p < j; p++){
                                insertArray(&offset_code, '0');
                            }
                        }
                        // Put actual code
                        for(int p = 0; p < crt_code.used; p++){
                            insertArray(&offset_code, crt_code.array[p]);
                        }

                        printf("%d\n", offset_code.used);

                        if(offset_code.used > 7){
                            setCodeIndex(&act_code, 1);
                            setCodeNext(&act_code, offset_code.used-8);
                        }else{
                            setCodeIndex(&act_code, 0);
                            setCodeNext(&act_code, 8-offset_code.used);
                        }

                        // Add the bits until 16bit code
                        for(int p = offset_code.used; p < 16; p++){
                            insertArray(&offset_code, '0');
                        }

                        setCode(&act_code, offset_code);
                        insertCodeList(&block_codes, act_code);
                        clearArray(&offset_code);
                    }
                    clearArray(&crt_code);
                }
                symb++;
            }else{
                if(crt_char != '@'){
                    insertArray(&crt_code, crt_char);
                }
            }
        }
        insertCodesLists(&codes_lists, block_codes);
        freeArray(&crt_code);
    }

    printCodesLists(&codes_lists);
}

long readIntInCod(FILE *fp){
    int decimal = 0;
    char crt_char = '0';
    long finalN = 0;
    while(crt_char != '@'){
        fread(&crt_char, sizeof(char), 1, fp); decimal++;
        if(crt_char != '@'){
            int crt_int = atoi(&crt_char);
//            printf("%d", crt_int);
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
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("André Vaz (a93221) e Rui Alves, MIEI/CD, %d-%02d-%02d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: _\n"); // TODO
    printf("Tamanho antes/depois & taxa de compressão (bloco _): _/_\n"); // TODO
    printf("Taxa de compressão global: _%%\n"); // TODO
    printf("Tempo de execução do módulo: %fms\n", elapsed);
    printf("Ficheiro gerado: %s\n", &shaf_file);
}