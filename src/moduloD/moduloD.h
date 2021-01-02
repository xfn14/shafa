#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "d_array.h"
#include "tree.h"
#include "auxiliar.h"
#include "manual.h"

#ifndef _MODULO_D_
#define _MODULO_D_

int moduloD(int argc, char **argv);
int rle_decompression(char *filename, char *new_file, size_t *input_array, size_t *output_array,size_t block_number);
Abin do_tree(unsigned char *buffer, int *index, int file_size, size_t *block_size, int block_index);
int read_cod(char *filename, Abin *array_tree, size_t *block_size, size_t *nr_blocks);
int shaf_decompression(char *read_file, char *output_file, size_t *block_size, size_t *new_size, Abin *array_tree);
int get_size(char *filename, size_t *nr_blocks, size_t *block_size);
int do_only_rle(char *filename, char *output_file, size_t *input_array, size_t *output_array, size_t *nr_blocks);
size_t get_nr_blocks(int argc, char **argv);

#endif