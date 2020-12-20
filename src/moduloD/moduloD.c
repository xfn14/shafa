#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "d_array.h"

void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer)
{

    for (int i = 0; i < num_reps; i++)
        insertArray(buffer, letter);
}

//change this to only do one write per block
void rle_decompression(char *filename, char *new_file, int *size_array, int nr_blocks, int *size_res)
{
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb"); //open the file we want to read
    fp = fopen(new_file, "wb+"); //open the file we will write
    for (int i = 0; i < nr_blocks; i++)
    {
        int block_size = size_array[i];
        D_Array new_buffer;
        initArray(&new_buffer, block_size);
        unsigned char *temp_buffer = malloc(sizeof(unsigned char) * block_size); //buffer for the reading
        if (fread(temp_buffer, sizeof(unsigned char), block_size, ptr) == 0)
            return;
        for (int u = 0; u < block_size; u++)
        {
            if (temp_buffer[u] == 0)
            {
                unsigned char letter = temp_buffer[u + 1];
                unsigned char num_reps = temp_buffer[u + 2];
                repeat(letter, num_reps, &new_buffer);
                u += 2;
            }
            else
                insertArray(&new_buffer, temp_buffer[u]);
        }
        fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);
        free(temp_buffer);
        size_res[i] = new_buffer.used;
        freeArray(&new_buffer);
    }
    fclose(ptr);
    fclose(fp);
}

int main(int argc, char **argv)
{
    //int block_size = , nr_blocks =;  // needed for rle decompression, user has to give the freq file to get the block numbers (TBD)
    //if (argc == 5){
    clock_t begin = clock();
    int array[2] = {991, 431}; //TBD
    int new_array[2] = {0, 0};
    int nr_blocks = 2;          //TBD
    char *filename = "aaa.txt"; //TBD
    rle_decompression(argv[1], filename, array, nr_blocks, new_array);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Módulo: d (descodificação dum ficheiro shaf)\n");
    printf("Número de blocos:%d\n", nr_blocks);
    printf("Tamanho antes/depois do ficheiro gerado (bloco 1):%d/%d\n", array[0], new_array[0]);
    printf("Tamanho antes/depois do ficheiro gerado (bloco 2):%d/%d\n", array[1], new_array[1]);
    printf("Tempo de execução do módulo (milissegundos):%f milissegundos\n", time_spent * 1000);
    printf("Ficheiro gerado: %s\n", filename);
    //}
    //else
}