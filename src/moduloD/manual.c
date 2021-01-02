#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "manual.h"

//void clrscr(){if(system("@cls||clear")==0)return;}

void n_lines (int n){
    for (int i = 0;i<n;i++) printf(COR"|\t\t\t\t\t\t\t\t\t|\n"COR_RESET);
}


void do_frase(char*str,char *cor,int tabs){
    printf(COR"|"COR_RESET);
    if (tabs) for(int i = 0; i < tabs;i++)putchar('\t');
    int size = strlen(str);
    if (tabs) size+=8 * tabs -1;
    int total = 70 -size;
    printf(" %s%s",cor,str);
    if (total) printf("%*c", total, ' ');
    printf(COR"|"COR_RESET);
    putchar('\n'); 
}

void print_line (){
    printf(COR" -----------------------------------------------------------------------\n"COR_RESET);
}

void help_menu (){
    print_line();
    n_lines(1);
    printf(COR"|                 ███████╗██╗  ██╗ █████╗ ███████╗ █████╗   \t\t|\n");
    printf("|                 ██╔════╝██║  ██║██╔══██╗██╔════╝██╔══██╗  \t\t|\n");
    printf("|                 ███████╗███████║███████║█████╗  ███████║  \t\t|\n");
    printf("|                 ╚════██║██╔══██║██╔══██║██╔══╝  ██╔══██║  \t\t|\n");
    printf("|                 ███████║██║  ██║██║  ██║██║     ██║  ██║  \t\t|\n");
    printf("|                 ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝  \t\t|\n"COR_RESET);
    n_lines(1);
    print_line();
    do_frase("NAME",TIT,1);
    do_frase("Shafa - Compression and decompression",COR_RESET,0);
    print_line();
    do_frase("SYNOPSIS",TIT,1);
    do_frase("shafa <file> m <module> <options>",COR_RESET,0);
    print_line();
    do_frase("DESCRIPTION",TIT,1);
    do_frase("Tool for compressing and decompressing a file.",COR_RESET,0);
    do_frase("It works on the basis of RLE and Shannon Fano compression.",COR_RESET,0);
    print_line();
    do_frase("MODULES",TIT,1);
    n_lines(1);
    do_frase ("-f:",SUB_TIT,1);
    do_frase("Creates a new file that does rle compression to the file",COR_RESET,0);
    do_frase("Creates a file .freq with the number of frequences",COR_RESET,0);
    n_lines(1);
    do_frase ("e.g.: ./shafa example.txt -m f",COR_RESET,0);
    do_frase("OUTPUT: example.txt.rle and example.txt.freq",COR_RESET,0);
    n_lines(1);
    print_line();
    n_lines(1);
    do_frase ("-t:",SUB_TIT,1);
    do_frase("Creates a new file .cod using the .freq to generate Shannon Fano",COR_RESET,0);
    do_frase("coding",COR_RESET,0); 
    do_frase("Creates a file .freq with the number of frequences",COR_RESET,0);
    n_lines(1);
    print_line();
    n_lines(1);
    do_frase ("-c:",SUB_TIT,1);
    do_frase("Uses the codes from cod file to create the compressed file ",COR_RESET,0);
    n_lines(1);
    print_line();
    n_lines(1);
    do_frase ("-d:",SUB_TIT,1);
    do_frase("Decompresses the .shaf file back to the original",COR_RESET,0);
    do_frase("OPTIONS:",TIT,2);
    n_lines(1);
    do_frase("-r:",SUB_TIT,2);
    do_frase("Does the rle decompression",COR_RESET,1);
    n_lines (1);
    do_frase("-s:",SUB_TIT,2);
    do_frase("Does the shaf decompression",COR_RESET,1);
    n_lines(1);
    print_line();
    do_frase ("AUTHORS",TIT,1);
    do_frase("-Andre Vaz",COR_RESET,0);
    do_frase("-Diogo Vieira",COR_RESET,0);
    do_frase("-Eduardo Magalhaes",COR_RESET,0);
    do_frase("-Pedro Sousa",COR_RESET,0);
    do_frase("-Alexandre Soares",COR_RESET,0);
    do_frase("-Antonio Fernandes",COR_RESET,0);
    do_frase("-Daniela Carvalho",COR_RESET,0);
    do_frase("-Rui Alves",COR_RESET,0);
    print_line();

}