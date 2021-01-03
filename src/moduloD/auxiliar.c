#include "auxiliar.h"

int f_size(FILE *fp) {
    fseek(fp, 0, SEEK_END);    
    int file_size = ftell(fp);  
    fseek(fp, 0, SEEK_SET);     
    return file_size;
}

void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer) {
    for (int i = 0; i < num_reps; i++)
        insertArray(buffer, letter);
}

int skip(int index, int stop, unsigned char *buffer) {
    int count = 0;
    for (; count < stop; index++) {
        if (buffer[index] == '@')
            count++;
    }
    return index;
}

size_t do_size(unsigned char *buffer, int *index) {
    int res = 0,i, size;
    for (size = 0; buffer[*index + size] != '@'; size++);
    for (i = 0; buffer[*index + i] != '@'; i++) {
        res += pow(10, size - i - 1) * (buffer[*index + i] - '0');
    }
    *index += i + 1;
    return res;
}

void int_bin(unsigned char letter, int *bin) {
    for (int i = 0; i < 8; i++) {
        bin[7 - i] = (letter >> i) & 1;
    }
}

void get_filenames(char *filename, char *cod_file, char *output_file) {
    int size = strlen(filename);
    memset(cod_file, 0, size - 1);
    memset(output_file, 0, size - 4);
    strncpy(cod_file, filename, size - 5);
    strncpy(output_file, filename, size - 5);
    strcat(cod_file, ".cod");
}

void error_messages(int n,char *str) {
    printf(COR_B_VERMELHO"ERROR:"COR_RESET);
    switch (n) {
        case 0:
            printf(" Can't read the file: \"%s\"\n",str);
            break;
        case 1:
            printf(" Incorrect format\n");
            break;
        case 2:
            printf(" Can't find %s file\n",str);
            break;
        default:
            break;
    }
    printf(" See --help or -h for more information\n");
}

void output_text (size_t nr_blocks,size_t* input_array,size_t* output_array,char* output_file,char* rle_file, double time_spent,int do_rle, struct tm tm){
    printf("José Diogo,a93251, e António Fernandes, a93312, MIEI/CD, %d-%02d-%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("Módulo: d (descodificação dum ficheiro shaf)\n");
    printf("Número de blocos:%zu\n", nr_blocks);
    for (size_t i = 0; i < nr_blocks; i++)
        printf("Tamanho antes/depois do ficheiro gerado (bloco %zu):%zu/%zu\n", i +1, input_array[i], output_array[i]);
    printf("Tempo de execução do módulo (milissegundos):%f milissegundos\n", time_spent * 1000);
    if (!do_rle) printf("Ficheiro gerado: %s\n", output_file);
    else printf("Ficheiros gerados: %s e %s\n",output_file,rle_file);
} 

int lenHelper(size_t x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}

int last_point(char *name, int size) {
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (name[i] == '.') index = i;
    }
    return index;
}
