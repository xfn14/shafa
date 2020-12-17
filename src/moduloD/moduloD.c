#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void repeat(unsigned char *res, unsigned char letter, unsigned char num_reps,FILE *fp)
{
    for (;num_reps > 0; num_reps--)
        fprintf(fp,"%c", letter);
}

void rle_decompression(char *filename, char *new_file, int* size_array, int nr_blocks)
{
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb"); //open the file we want to read
    fp = fopen(new_file, "wb+"); //open the file we will write
    for (int i = 0; i < nr_blocks; i++)
    {
        int block_size = size_array[i];
        unsigned char *temp_buffer = malloc(sizeof(unsigned char) * block_size);
        fread(temp_buffer, sizeof(unsigned char), block_size, ptr);
        for (int u = 0; u < block_size;u++)
        {
            if (temp_buffer[u] == 0)
            {
                unsigned char letter = temp_buffer[u+1];
                unsigned char num_reps = temp_buffer[u+2];
                unsigned char *res = malloc(sizeof(unsigned char) * num_reps);
                repeat(res, letter, num_reps,fp);
                printf ("%s",res);
                //fwrite(res, 1, temp_buffer[u+2] * sizeof(unsigned char), stdout);
                free(res);
                u+=2;
            }
            else
                fprintf(fp, "%c", temp_buffer[u]);
        }
        free(temp_buffer);
    }
    fclose(ptr);
    fclose(fp);
}

int main(int argc, char **argv)
{
    //int block_size = , nr_blocks =;  // needed for rle decompression, user has to give the freq file to get the block numbers (TBD)
    clock_t begin = clock();
    int array[2]= {991,431}; //TBD
    int nr_blocks = 2; //TBD
    char *filename = "aaa.txt"; //TBD
    rle_decompression (argv[1],filename,array,nr_blocks);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Módulo: d (descodificação dum ficheiro shaf)\n");
    printf("Número de blocos:%d\n",nr_blocks);
    printf("Tamanho antes/depois do ficheiro gerado (bloco 1):%d/(TBD)\n",array[0]); 
    printf("Tamanho antes/depois do ficheiro gerado (bloco 2):%d/(TBD)\n",array[1]);
    printf("Tempo de execução do módulo (milissegundos):%f\n",time_spent*1000);
    printf("Ficheiro gerado: %s\n",filename);
}