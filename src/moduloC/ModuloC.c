/**
 * @file ModuloC.c
 * @brief Shannon-Fano Compression
 * @date 2021-1-3
 *
 * @copyright Copyright (c) 2020 - André Vaz, Rui Alves
 */

#include "ModuloC.h"

int moduloC(int argc, char **argv){
    // Tempo de inicio da execuçao da codificaçao
    clock_t start_time = clock();
    char *fileName = argv[1];

    // Nomes dos ficheiros .cod e .shaf
    char *cod_file = malloc(sizeof(char)*MAX_FILENAME);
    strcpy(cod_file, fileName); strcat(cod_file, ".cod");
    char *shaf_file = malloc(sizeof(char)*MAX_FILENAME);
    strcpy(shaf_file, fileName); strcat(shaf_file, ".shaf");

    // Ler os codigos do ficheiro .cod
    codes_lists_struct codes_list;
    initCodesLists(&codes_list);
    int cod_res = readCodFile(cod_file, &codes_list);
    if(cod_res != 0) return EXIT_FAILURE;

    // Fazer a codificaçao SF
    D_Matrix_List out_bytes;
    initMatrixList(&out_bytes);
    int bin_res = binary_encoding(fileName, &codes_list, &out_bytes);
    if(bin_res != 0) return EXIT_FAILURE;

    // Escrever os codigos no ficheiro .shaf
    write_codes_in_file(shaf_file, &out_bytes);

    freeCodesLists(&codes_list);
    freeMatrixList(&out_bytes);

    print_final_info(start_time, shaf_file, &codes_list, &out_bytes);
    return EXIT_SUCCESS;
}

int binary_encoding(char *in_file, codes_lists_struct *codes_lists, D_Matrix_List *out_bytes) {
    FILE *in;
    in = fopen(in_file, "rb");

    if(in == NULL){
        printf(COR_B_VERMELHO"ERROR:"COR_RESET" Can't find %s file\n", in_file);
        return 1;
    }

    fseek(in, 0L, SEEK_SET);

    for (int i = 0; i < codes_lists->len; i++) { // Percorrer os diferentes blocos
        D_Matrix coded_bytes; // bytes for block
        initMatrix(&coded_bytes);

        // Ler os caracteres do bloco atual
        code_list_struct crt_code_list = codes_lists->lists[i];
        unsigned char *crt_block_buffer = malloc(crt_code_list.block_size * sizeof(unsigned char));
        fread(crt_block_buffer, sizeof(unsigned char), crt_code_list.block_size, in);

        // Inicializar byte
        D_Array crt_byte;
        initArray(&crt_byte, 8);
        clear_byte(&crt_byte);

        code_struct code_to_use;
        initCode(&code_to_use);
        int offset = 0;
        for(int j = 0; j < crt_code_list.block_size; j++){
            unsigned char crt_symb = crt_block_buffer[j];
            getSymbCode(&crt_code_list, crt_symb, offset, &code_to_use); // Obter o codigo de determinado simbolos
            or_opp(&crt_byte, &code_to_use.code, 0);
            if(code_to_use.index == 1){ // Caso exceda o primeiro byte guardar e continuar no seguinte
                addLineMatrix(&coded_bytes, crt_byte);
                clear_byte(&crt_byte);
                or_opp(&crt_byte, &code_to_use.code, 1);
            }
            offset = code_to_use.next;

            // Guardar os codigos ja codificados do bloco
            if(j == crt_code_list.block_size-1){
                addLineMatrix(&coded_bytes, crt_byte);
            }
        }
        insertMatrixInList(out_bytes, coded_bytes);
    }
    fclose(in);
    return 0;
}

unsigned char byte_to_char(D_Array *arr){
    int crt = 0, res = 0;
    for(int i = arr->used-1; i >= 0; i--){
        res += (int) pow(2, crt) * (arr->array[i] == '1' ? 1 : 0);
        crt++;
    }
    return (unsigned char) res;
}

void write_codes_in_file(char *out_file, D_Matrix_List *coded_bytes){
    FILE *out;
    out = fopen(out_file, "wb+");

    fprintf(out, "@%d@", coded_bytes->len); // Escreve o numero de blocos

    for(int i = 0; i < coded_bytes->len; i++) {// Escreve cada blocos
        D_Matrix crt_matrix = coded_bytes->list[i];
        fprintf(out, "%d@", crt_matrix.len); // Escreve o tamanho de bloco
        for(int j = 0; j < crt_matrix.len; j++){ // Escreve os diferentes bytes
            unsigned char crt_byte = 0;
            crt_byte = byte_to_char(&crt_matrix.arr[j]);
            fprintf(out, "%c", crt_byte);
        }
        if(i != coded_bytes->len-1) fprintf(out, "@"); // @ final do ficheiro
    }

    fclose(out);
}

int readCodFile(char *filename, codes_lists_struct *codes_lists){
    FILE *in;
    in = fopen(filename, "rb");

    if(in == NULL){
        printf(COR_B_VERMELHO"ERROR:"COR_RESET" Can't find %s file\n", filename);
        return 1;
    }

    // Ver se os codigos sao para RLE ou nao
    char normal_rle;
    fseek(in, 1, SEEK_SET);
    fread(&normal_rle, sizeof(char), 1, in);
    int chars_read = 3;
    fseek(in, chars_read, SEEK_SET);

    // Ler numero do blocos
    long n_blocks = readIntInCod(in);

    initCodesLists(codes_lists);

    // Ler os diferentes codigos
    for(int i = 0; i < n_blocks; i++){
        code_list_struct block_codes;
        initList(&block_codes);
        long block_size = readIntInCod(in); // Ler o tamanho do bloco
        setListBlockSize(&block_codes, block_size);

        unsigned char symb = 0;
        unsigned char crt_char = 0;
        D_Array crt_code;
        initArray(&crt_code, 3);
        while(crt_char != '@'){ // ler ate proximo bloco
            fread(&crt_char, sizeof(unsigned char), 1, in);
            if(crt_char == ';'){ // Ir para o simbolo seguinte
                if(crt_code.used != 0){ // Caso se tenha lido algum codigo
                    for(int j = 0; j < 8; j++){ // Guardar o codigo com os diferentes offset na lista
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
                        for(int p = 0; p < (int) crt_code.used; p++){
                            insertArray(&offset_code, crt_code.array[p]);
                        }

                        // Definir o index e o next do codigo
                        if(offset_code.used > 7){
                            setCodeIndex(&act_code, 1);
                            setCodeNext(&act_code, offset_code.used-8);
                        }else{
                            setCodeIndex(&act_code, 0);
                            setCodeNext(&act_code, offset_code.used);
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
                // Ler o codigo
                if(crt_char != '@'){
                    insertArray(&crt_code, crt_char);
                }
            }
        }
        insertCodesLists(codes_lists, block_codes);
        freeArray(&crt_code);
    }
    return 0;
//    printCodesLists(codes_lists);
}

long readIntInCod(FILE *fp){
    int decimal = 0;
    char crt_char = '0';
    long finalN = 0;
    while(crt_char != '@'){
        fread(&crt_char, sizeof(char), 1, fp); decimal++;
        if(crt_char != '@'){
            int crt_int = atoi(&crt_char);
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

void print_final_info(clock_t start_time, char *shaf_file, codes_lists_struct *code_list, D_Matrix_List *out_bytes){
    clock_t stop_time = clock();
    double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000; // Calculo do tempo de execuçao
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("André Vaz (a93221) e Rui Alves (a93252), MIEI/CD, %d-%02d-%02d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: %d\n", code_list->len);
    int initTotal = 0, endTotal = 0;
    for(int i = 0; i < code_list->len; i++){
        printf("Tamanho antes/depois & taxa de compressão (bloco %d): %ld/%d\n", i+1, code_list->lists[i].block_size, out_bytes->list[i].len);
        initTotal += (int) code_list->lists[i].block_size;
        endTotal += out_bytes->list[i].len;
    }
    int compress = ((double) endTotal / initTotal) * 100; // Calculo da taxa de compressao
    printf("Taxa de compressão global: %d%%\n", compress);
    printf("Tempo de execução do módulo: %fms\n", elapsed);
    printf("Ficheiro gerado: %s\n", shaf_file);
}

//int main(){
//    codes_lists_struct codes_list;
//    initCodesLists(&codes_list);
//    readCodFile("../resources/aaa.txt.cod", &codes_list);
//    printCodesLists(&codes_list);
//
//    printf("\n\n\n");
//
//    D_Matrix_List out_bytes;
//    initMatrixList(&out_bytes);
//    binary_encoding("../resources/aaa.txt", &codes_list, &out_bytes);
//    printMatrixList(&out_bytes);
//
//    write_codes_in_file("out.shaf", &out_bytes);
//}
