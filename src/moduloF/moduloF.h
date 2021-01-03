#ifndef MOD_F_H
#define MOD_F_H

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../utils/fsize.h"

struct sizes {
    long long n_blocks;
    unsigned long size_of_last_block;
    unsigned long long total;
};

struct tcomp_sizerleblocks {
    float taxa_comp;
    int *size_rle_blocks;
};

int *arrayazeros();
char *dotfreq(char *filename);
char *dotrle(char *filename);
void freqs(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, char *filename, int flagend, int flagoriginal);
int rlecheck(unsigned char *buffer, int sizebuffer, unsigned long long total, int forcecompression);
unsigned char *rle(unsigned char *buffer, int sizebuffer, int flaginit, char *filename);
void rlecompressing(unsigned char *buffer , int flaginit, int sizebuffer, int simbs, char *filename);
struct tcomp_sizerleblocks split (char *filename, unsigned long block_size, long long n_blocks, unsigned long long total, int forcecompression);
struct sizes number_of_blocks (char *filename, unsigned long block_size);
void moduloF(char *filename, unsigned long block_size, int forcecompression);
//int main();

#endif //MOD_F_H