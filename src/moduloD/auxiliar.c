#include "auxiliar.h"

int fsize(FILE *fp) {
    fseek(fp, 0, SEEK_END);     // seek to end of file
    int file_size = ftell(fp);  // get current file pointer
    fseek(fp, 0, SEEK_SET);     // seek back to beginning of file
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

int do_size(unsigned char *buffer, int *array) {
    int res = 0, index = array[0], i, size;
    for (size = 0; buffer[index + size] != '@'; size++)
        ;
    for (i = 0; buffer[index + i] != '@'; i++) {
        res += pow(10, size - i - 1) * (buffer[index + i] - '0');
    }
    array[0] += i + 1;
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

void error_messages(int n) {
    switch (n) {
        case 1:
            printf("Argument needed.\nCorrect sintax: shafa m d <file>\n");
            break;
        case 2:
            printf("Too many arguments\n");
            break;
        default:
            break;
    }
}