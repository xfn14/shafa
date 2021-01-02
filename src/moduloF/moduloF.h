#ifndef MOD_F_H
#define MOD_F_H

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../utils/fsize.h"
//#include "fsize.h"

char *dotfreq(char *filename);
char *dotrle(char *filename);
void createfreqfile(long long n_blocks, char *filename, int flagoriginal);
void createrlefile(char *filename);
void freqs(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, int onlyoneblock, char *filename, int flagoriginal);
int simbcount(char *buffer, int sizebuffer);
int rlecheck(char *buffer, int sizebuffer, unsigned long long total);
unsigned char *rlebuffertransformation(unsigned char *buffer, int sizebuffer);
void rlecompressing(char *buffer , int flaginit, int sizebuffer, int simbs, char *filename);
float split (char *filename, unsigned long block_size);
long long number_of_blocks (char *filename, unsigned long block_size);
int main();

#endif //MOD_F_H
