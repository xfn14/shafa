#include <stdio.h>
#ifndef _D_ARRAY_
#define _D_ARRAY_

typedef struct {
    unsigned char *array;
    int used;
    int size;
} D_Array;

/**
 * @brief Initialize the arr
 *
 * @param[in] arr
 * @param[in] initialSize
 */
void initArray(D_Array *a, size_t initialSize);

/**
 * @brief Add and element to the end of the arr
 *
 * @param[in] arr
 * @param[in] element
 */
void insertArray(D_Array *a, unsigned char element);

/**
 * @brief Deletes the arr from memory
 *
 * @param[in] arr
 */
void freeArray(D_Array *a);

/**
 * @brief Remove the first element of the arr
 *
 * @param[in] arr
 */
void remove_first(D_Array *a);

/**
 * @brief Adds an element to the start of the arr
 *
 * @param[in] arr
 * @param[in] element
 */
void add_first(D_Array *a, unsigned char element);

/**
 * @brief Makes the OR operation between to codes of the same size and stores the result in arr1
 *
 * @param[in] arr1
 * @param[in] arr2
 * @param[in] mode
 */
void or_opp(D_Array *arr1, D_Array *arr2, int mode);

/**
 * @brief Clears the contents of an arr
 *
 * @param[in] arr
 */
void clearArray(D_Array *a);

/**
 * @brief Prints an arr on the screen
 *
 * @param[in] arr
 * @param[in] mode (1 - decimal / 0 - char)
 */
void print_array(D_Array *a, int mode);

/**
 * @brief Initialize an arr has a byte
 *
 * @param[in] arr
 */
void initByte(D_Array *arr);

/**
 * @brief Sets a byte size array to 0
 *
 * @param arr
 */
void clear_byte(D_Array *arr);
#endif