/**
 * @file auxiliar.h
 * @brief Auxiliar functions of moduloD
 * @date 2021-1-3
 * 
 * @copyright Copyright (c) 2020
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "manual.h"
#include "d_array.h"


#ifndef _AUXILIAR_
#define _AUXILIAR_

/**
 * @brief Calculates the size of a file
 *
 * @param[in] fp
 * @returns[out] file's size
 */
int f_size(FILE *fp);
/**
 * @brief Insert a letter num_reps times in a buffer
 *
 * @param[in] letter that will be inserted
 * @param[in] num_reps how many times will insert the letter
 * @param[in] buffer to insert
 */
void repeat(unsigned char letter, unsigned char num_reps, D_Array *buffer);
/**
 * @brief Skip n '@' in a buffer 
 *
 * @param[in] index where to start looking
 * @param[in] stop number of @ to stop
 * @param[in] buffer
 * @returns The index to skip to
 */
int skip(int index, int stop, unsigned char *buffer); 
/**
 * @brief Converts a string to a number, stops when reach a @
 *
 * @param[in] buffer 
 * @param[in] index pointer to index where to start
 * @returns The number converted
 */
size_t do_size(unsigned char *buffer, int *index);
/**
 * @brief Convert a byte to an array of int
 *
 * @param[in] letter the byte to be converted
 * @param[in] bin array to store the result
 */
void int_bin(unsigned char letter, int *bin);
/**
 * @brief Get the correct filenames
 *
 * @param[in] filename 
 * @param[in] cod_file change .shaf to .cod
 * @param[in] output_file takes .shaf of filename
 */
void get_filenames(char *filename, char *cod_file, char *output_file);
/**
 * @brief Print error messages
 *
 * @param[in] n 
 * @param[in] str string to print in message
 */
void error_messages(int n,char* str);
/**
 * @brief Print the final information
 *
 * @param[in] nr_blocks The number of blocks
 * @param[in] input_array The size of input block's size
 * @param[in] output_array The size of output block's size
 * @param[in] output_file The name of output file
 * @param[in] rle_file The name of rle_file
 * @param[in] time_spent Program execution's time
 * @param[in] do_rle If rle decompression was done
 * @param[in] tm The time for display current day 
 */
void output_text (size_t nr_blocks,size_t* input_array,size_t* output_array,char* output_file,char* rle_file, double time_spent,int do_rle, struct tm tm);
/**
 * @brief Gives the length of a number
 *
 * @param[in] x The number to calculate the length
 * @returns The number's length
 */
int lenHelper(size_t x);
/**
 * @brief Gives the index of last point in the name
 *
 * @param[in] name 
 * @param[in] size Name's length
 * @returns index of last point
 */
int last_point(char *name, int size);
#endif