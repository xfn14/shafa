#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "d_array.h"
#include "tree.h"
//#include "fsize.h"

void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer) {
    for (int i = 0; i < num_reps; i++)
        insertArray(buffer, letter);
}

void rle_decompression(char *filename, char *new_file, int *size_array, int nr_blocks, int *size_res) {
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb");         //open the file we want to read
    fp = fopen(new_file, "wb+");         //open the file we will write
    for (int i = 0; i < nr_blocks; i++)  //going through all the blocks
    {
        int block_size = size_array[i];  //keep track of the current size of the block
        D_Array new_buffer;
        initArray(&new_buffer, block_size);                                       //initiate dynamic array
        unsigned char *temp_buffer = malloc(sizeof(unsigned char) * block_size);  //buffer for the reading
        if (fread(temp_buffer, sizeof(unsigned char), block_size, ptr) == 0)      //read the current block
            return;
        for (int u = 0; u < block_size; u++) {
            if (temp_buffer[u] == 0)  //for the rle compression case
            {
                unsigned char letter = temp_buffer[u + 1];
                unsigned char num_reps = temp_buffer[u + 2];
                repeat(letter, num_reps, &new_buffer);
                u += 2;  //skip to next character outside rle case
            } else
                insertArray(&new_buffer, temp_buffer[u]);  //normal character
        }
        fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);  //writing the new block in the new file
        free(temp_buffer);
        size_res[i] = new_buffer.used;  //keeping track of the size of the new block
        freeArray(&new_buffer);
    }
    fclose(ptr);
    fclose(fp);
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
    for (size = 0; buffer[index + size] != '@'; size++);
    for (i = 0; buffer[index + i] != '@'; i++) {
        res += pow(10, size - i - 1) * (buffer[index + i] - '0');
    }
    array[0] += i + 1;
    return res;
}

//KINDA DONE
Abin do_tree(unsigned char *buffer, int *index, int file_size, int *block_size, int block_index) {
    unsigned char element = 0;
    Abin tree;
    tree = init_tree();
    D_Array arr;
    initArray(&arr, 5);
    int flag = 1;
    for (int i = *index; i < file_size && flag; i++) {
        if (buffer[i] == '@') {
            if (buffer[i + 1] == '0') return tree;
            *index = i + 1;
            block_size[block_index] = do_size(buffer, index);
            flag = 0;
        } else if (buffer[i] == ';') {
            if (arr.used != 0)
                insert_Tree(&tree, &arr, element);  //insert every code in tree
            element++;
        } else
            insertArray(&arr, buffer[i]);
    }
    //imprime(tree);
    return tree;
}

void read_cod(char *filename, Abin *array_tree, int *block_size) {
    int file_size = 545; //TBD (use fsize)
    FILE *fp;
    fp = fopen(filename, "rb");
    unsigned char *buffer = malloc(sizeof(unsigned char) * file_size);
    if (fread(buffer, sizeof(unsigned char), file_size, fp) == 0)
        return;  //read a block or file (TBD)
    int index = skip(0, 2, buffer), nr_blocks = do_size(buffer, &index);
    block_size[0] = do_size(buffer, &index);
    for (int block = 0; block < nr_blocks; block++) {
        array_tree[block] = do_tree(buffer, &index, file_size, block_size, block + 1);
    }
    fclose(fp);
}

void int_bin(unsigned char letter, int *bin) {
    for (int i = 0; i < 8; i++) {
        bin[7 - i] = (letter >> i) & 1;
    }
}

void shaf_decompression(int *block_size, int *new_size, Abin *array_tree, int file_size) {
    FILE *fp, *ptr;
    ptr = fopen("aaa.txt.shaf", "rb"); //TBD
    fp = fopen("bbb.txt", "wb+"); //TBD
    D_Array new_buffer, array;
    initArray(&array, 8);
    initArray(&new_buffer, block_size[0]);
    Abin tree = array_tree[0];
    unsigned char *temp_buffer = malloc(sizeof(unsigned char) * file_size);  //buffer for reading
    if (fread(temp_buffer, sizeof(unsigned char), file_size, ptr) == 0)
        return;  //read block
    int index = 1, nr_blocks = do_size(temp_buffer, &index), block = 0, next = 1;
    new_size[block] = do_size(temp_buffer, &index);
    for (; index < file_size; index++) {
        if (new_buffer.used == block_size[block]) {
            if (++block < nr_blocks) {
                index++;
                new_size[block] = do_size(temp_buffer, &index);
            }
            index--;
            next = 1;
            fwrite(new_buffer.array, new_buffer.used, sizeof(unsigned char), fp);
            freeArray(&new_buffer);
            freeArray(&array);
            initArray(&new_buffer, block_size[block]);
            initArray(&array, 8);
            tree = array_tree[block];
        } else {
            unsigned char res;
            int bin[8];
            int_bin(temp_buffer[index], bin);
            for (int i = 0; i < 8 && next; i++) {
                if (new_buffer.used == block_size[block]) {
                    next = 0;
                } else {
                    insertArray(&array, bin[i]);  //insert the bit in the array
                    if (search_tree(tree, &array, &res, 0) == 1) {
                        insertArray(&new_buffer, res);
                        freeArray(&array);
                        initArray(&array, 8);
                    }
                }
            }
        }
    }
    fwrite(new_buffer.array, new_buffer.used, sizeof(unsigned char), fp);
    //printf("new size is %d\n", new_buffer.used);
    freeArray(&new_buffer);
    freeArray(&array);
    fclose(ptr);
    fclose(fp);
}

int main(int argc, char **argv) {
    //int block_size = , nr_blocks =;  // needed for rle decompression, user has to give the freq file to get the block numbers (TBD)
    //if (argc == 5){
    clock_t begin = clock();
    //int array[2] = {459, 212}; //TBD
    //int block_size[2] = {991, 431};  //TBD
    int shaf_array[2] = {0, 0};
    int new[2] = {0, 0};
    //int rle_array[2]= {0,0};
    int file_size = 683;  //TBD (use fsize)
    char *filename = "aaa.txt.cod";//TBD
    Abin *array_tree = malloc(sizeof(Abin) * 2);
    //do_tree(filename, array_tree);
    read_cod(filename, array_tree, shaf_array);
    shaf_decompression(shaf_array, new, array_tree, file_size);
    //rle_decompression("try_shaf.txt","try_rle.txt", block_size,2, rle_array);
    //D_Array arr;
    //initArray(&arr,8);
    //insertArray(&arr, '0');
    //insertArray(&arr, '0');
    //unsigned char *res = malloc(sizeof(unsigned char));
    //printf("the search is: %d\n",search_tree(array_tree[1],&arr,res,0));
    //imprime(array_tree[1]);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("José Diogo,a93251 e António Fernandes, a93312, MIEI/CD, %d-%02d-%02d\n", tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
    printf("Módulo: d (descodificação dum ficheiro shaf)\n");
    printf("Número de blocos:%d\n", 2);
    printf("Tamanho antes/depois do ficheiro gerado (bloco 1):%d/%d\n", new[0], shaf_array[0]);
    printf("Tamanho antes/depois do ficheiro gerado (bloco 2):%d/%d\n", new[1], shaf_array[1]);
    printf("Tempo de execução do módulo (milissegundos):%f milissegundos\n", time_spent * 1000);
    printf("Ficheiro gerado: bbb.txt\n");
    //}
    //else
}