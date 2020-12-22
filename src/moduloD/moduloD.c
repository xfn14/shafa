#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "d_array.h"
#include "tree.h"

void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer)
{
    for (int i = 0; i < num_reps; i++)
        insertArray(buffer, letter);
}

void rle_decompression(char *filename, char *new_file, int *size_array, int nr_blocks, int *size_res)
{
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb");        //open the file we want to read
    fp = fopen(new_file, "wb+");        //open the file we will write
    for (int i = 0; i < nr_blocks; i++) //going through all the blocks
    {
        int block_size = size_array[i]; //keep track of the current size of the block
        D_Array new_buffer;
        initArray(&new_buffer, block_size);                                      //initiate dyanmic array
        unsigned char *temp_buffer = malloc(sizeof(unsigned char) * block_size); //buffer for the reading
        if (fread(temp_buffer, sizeof(unsigned char), block_size, ptr) == 0)     //read the current block
            return;
        for (int u = 0; u < block_size; u++) // going through all bytes of the block
        {
            if (temp_buffer[u] == 0) //for the rle compression case
            {
                unsigned char letter = temp_buffer[u + 1];
                unsigned char num_reps = temp_buffer[u + 2];
                repeat(letter, num_reps, &new_buffer);
                u += 2; //skip to next character outside rle case
            }
            else
                insertArray(&new_buffer, temp_buffer[u]); //normal character
        }
        fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp); //writing the new block in the new file
        free(temp_buffer);
        size_res[i] = new_buffer.used; //keeping track of the size of the new block
        freeArray(&new_buffer);
    }
    fclose(ptr);
    fclose(fp);
}

/*
//return value: is_rle
int cod_file (char *filename, int size){
    FILE*  fp;
    fp = fopen (filename,"r"); 
    unsigned char *buffer = malloc(sizeof(unsigned char) * size);
    for (int i = 3,contagem = 0;contagem < 1;i++){
        
    }
}
*/

// do a binary tree with the codes
// ignorar a head da tree
// 0 -> left || 1 -> right
// guardar o char correspondente na folha da àrvore
//

/*
                    -
                /       \
               0         1
             /   \     /   \
            0     1   0     1
*/
//KINDA DONE
void do_tree(char *filename, Abin *tree)
{
    int file_size = 711; 
    FILE *fp;
    fp = fopen(filename,"rb");
    unsigned char *buffer = malloc (sizeof (unsigned char) * file_size);
    if (fread(buffer,sizeof(unsigned char),file_size,fp) == 0)
        return; //read a block or file (TBD)
    int count,u = 0;
    for (u = 0;;u++){
        if (count == 4)break;
        if (buffer [u] == '@')count++;
    }
    unsigned char element = 0;
    D_Array arr;
    initArray (&arr,5);
    for (int i = u; i < file_size; i++)//doing only one block atm
    {    
        if (buffer[i]== '@'){
            imprime(*tree);
            putchar('\n');
            freeAB(*tree);
            *tree= init_tree();
            element = 0;
            count = 0;
            for (u = i;;u++){
                if (count == 2)break;
                if (buffer [u] == '@')count++;
            }
            i = u;
        }
        if (buffer[i] == ';'){
            if (arr.used != 0){
                insert_Tree(tree,&arr,element); //insert every code in tree
            }
            element++;
        }
        else
            insertArray(&arr,buffer[i]);
    }
}

/*
void shaf_decompression(int code_max_size, int *block_size, int nr_blocks, int *new_size)
{
    FILE *fp, ptr;
    ptr = fopen(file, "rb");
    fp = fopen(new_file, "wb+");
    for (int i = 0; i < nr_blocks; i++)
    {
        D_Array new_buffer; // writing
        initArray(&new_buffer, block_size);
        unsigned char *temp_buffer; //buffer for reading
        fread()                     //read block
        D_Array code;           //to store the code (strncat for when code is not on tree)
        initArray(&code, size);
        for (u = 0; u < block_size; u++) //byte a byte loop
        {
            for (int index = 0; index < 8; index++) //loop to go for every bit of a byte (attention to CODE_MAX_SIZE)
            {
                insertArray (code,b>>index)&1)
                unsigned char letter =look_tree(code);//TBD
                if (letter != 0)                      //sucesseful search
                {
                    insertArray(new_buffer, letter);
                    reset_Array(code); //TBD
                }
            }
        }
        freeArray(&code);
        fwrite(new_buffer);
        new_size[i] = new_buffer.used;
        freeArray(&new_buffer);
    }
}
*/


int main(int argc, char **argv)
{
    Abin tree;
    tree = init_tree();
    do_tree("aaa.txt.rle.cod",&tree);
    /*
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
    */
}