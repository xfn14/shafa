#include "ModuloC.h"

/**
 * @[número_de_blocos]
 * @[tamanho_bloco_1]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_bloco_1)
 * @[...]
 * @[tamanho_último_bloco]
 * @(sequência_de_bits_resultante_da_codificação_SF_do_último_bloco)
 */

int moduloC(int argc, char **argv){
    clock_t start_time = clock();
    char *fileName = argv[1];

    char *cod_file = malloc(sizeof(char)*MAX_FILENAME);
    strcat(cod_file, fileName); strcat(cod_file, ".cod");
    char *shaf_file = malloc(sizeof(char)*MAX_FILENAME);
    strcat(shaf_file, fileName); strcat(shaf_file, ".shaf");

    codes_lists_struct codes_list;
    initCodesLists(&codes_list);
    int cod_res = readCodFile(cod_file, &codes_list);
    if(cod_res != 0) return EXIT_FAILURE;

    D_Matrix_List out_bytes;
    initMatrixList(&out_bytes);
    int bin_res = binary_encoding(fileName, &codes_list, &out_bytes);
    if(bin_res != 0) return EXIT_FAILURE;

    write_codes_in_file(shaf_file, &out_bytes);

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

    for (int i = 0; i < codes_lists->len; i++) {
        D_Matrix coded_bytes; // bytes for block
        initMatrix(&coded_bytes);

        code_list_struct crt_code_list = codes_lists->lists[i];
        unsigned char *crt_block_buffer = malloc(crt_code_list.block_size * sizeof(unsigned char));
        fread(crt_block_buffer, sizeof(unsigned char), crt_code_list.block_size, in);

        D_Array crt_byte;
        initArray(&crt_byte, 8);
        clear_byte(&crt_byte);

        code_struct code_to_use;
        initCode(&code_to_use);
        int offset = 0;
        for(int j = 0; j < crt_code_list.block_size; j++){
            unsigned char crt_symb = crt_block_buffer[j];
            getSymbCode(&crt_code_list, crt_symb, offset, &code_to_use);
            or_opp(&crt_byte, &code_to_use.code, 0);
            if(code_to_use.index == 1){
                addLineMatrix(&coded_bytes, crt_byte);
                clear_byte(&crt_byte);
                or_opp(&crt_byte, &code_to_use.code, 1);
            }
            offset = code_to_use.next;

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

    fprintf(out, "@%d@", coded_bytes->len);

    for(int i = 0; i < coded_bytes->len; i++){
        D_Matrix crt_matrix = coded_bytes->list[i];
        fprintf(out, "%d@", crt_matrix.len);
        for(int j = 0; j < crt_matrix.len; j++){
            unsigned char crt_byte = 0;
            crt_byte = byte_to_char(&crt_matrix.arr[j]);
            fprintf(out, "%c", crt_byte);
        }
        if(i != coded_bytes->len-1) fprintf(out, "@");
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

    char normal_rle;
    fseek(in, 1, SEEK_SET);
    fread(&normal_rle, sizeof(char), 1, in);
    int chars_read = 3;
    fseek(in, chars_read, SEEK_SET);

    long n_blocks = readIntInCod(in);

    initCodesLists(codes_lists);

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

void print_final_info(clock_t start_time, char *shaf_file, codes_lists_struct *code_list, D_Matrix_List *out_bytes){
    clock_t stop_time = clock();
    double elapsed = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("André Vaz (a93221) e Rui Alves (a93252), MIEI/CD, %d-%02d-%02d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("Módulo: c (Codificação de um ficheiro de símbolos)\n");
    printf("Número de blocos: %d\n", code_list->len);
    int initTotal = 0;
    int endTotal = 0;
    for(int i = 0; i < code_list->len; i++){
        printf("Tamanho antes/depois & taxa de compressão (bloco %d): %ld/%d\n", i+1, code_list->lists[i].block_size, out_bytes->list[i].len);
        initTotal += (int) code_list->lists[i].block_size;
        endTotal += out_bytes->list[i].len;
    }
    int compress = ((double) endTotal / initTotal) * 100;
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
