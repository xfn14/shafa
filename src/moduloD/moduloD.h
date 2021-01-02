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


/**
 * @brief Main functions
 *
 * @param[in] argc
 * @param[in] argv
 */
int moduloD(int argc, char **argv);
/**
 * @brief Does the rle decompression
 *
 * @param[in] filename The file to decompressed
 * @param[in] new_file Output's file
 * @param[in] input_array Block's size of filename
 * @param[in] output_array Block's size of output file
 * @param[in] block_number Number of blocks
 */
int rle_decompression(char *filename, char *new_file, size_t *input_array, size_t *output_array,size_t block_number);
/**
 * @brief Does the tree of a block
 * @param[in] buffer File's information buffer
 * @param[in] index Pointer to index
 * @param[in] file_size The size of a file
 * @param[in] block_size To store the size of blocks
 * @param[in] block_numer To keep track of block
 * @returns Abin The tree of this block_number
 */
Abin do_tree(unsigned char *buffer, int *index, int file_size, size_t *block_size, int block_index);
/**
 * @brief Read cod file and store information in array_tree
 * @param[in] filename The file to read
 * @param[in] array_tree An array of tree to store the codes
 * @param[in] block_size To store the information about block sizes
 * @param[in] nr_blocks The number of blocks
 */
int read_cod(char *filename, Abin *array_tree, size_t *block_size, size_t *nr_blocks);
/**
 * @brief Does the shaf decompression
 * @param[in] read_file The file to read
 * @param[in] output_file The file to write
 * @param[in] output_size The output size of each block 
 * @param[in] input_size The input size of each block
 * @param[in] array_tree The tree of each block
 */
int shaf_decompression(char *read_file, char *output_file, size_t *output_size, size_t *input_size, Abin *array_tree);
/**
 * @brief Function to get the block's size in a .freq file
 *
 * @param[in] filename Freq file
 * @param[in] nr_blocks The number of blocks
 * @param[in] block_size To store the information about block's size
 */
int get_size(char *filename, size_t *nr_blocks, size_t *block_size);
/**
 * @brief Function for -r option
 *
 * @param[in] filename The rle file
 * @param[in] output_file The original file
 * @param[in] input_array The input size of each block
 * @param[in] output_array The output size of each block
 * @param[in] nr_blocks The number of blocks
 */
int do_only_rle(char *filename, char *output_file, size_t *input_array, size_t *output_array, size_t *nr_blocks);
/**
 * @brief Function to get the nr of blocks
 *
 * @param[in] argc
 * @param[in] argv
 * @returns[out] The number of blocks 
 */
size_t get_nr_blocks(int argc, char **argv);

#endif