/**
 * @file Shafa
 * @brief Shafa tool for data compression
 * @version 0.1
 * @date 2020-12-19
 * 
 * @copyright Copyright (c) 2020
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moduloD/manual.h"
//#include "moduloT/ModuloT.h"
#include "moduloC/ModuloC.h"
//#include "moduloD/moduloD.h"
#include "moduloF/moduloF.h"

int main(int argc, char **argv){
    if (argc == 2 && (!strcmp("--help", argv[1]) || !strcmp("-h", argv[1]))) {
        help_menu();
        return EXIT_SUCCESS;
    }

    unsigned long block_size= 655360;
    int forcecompression = 0;
    // Modulo F
    if(argc == 4 && !strcmp("-m", argv[2]) && !strcmp("f", argv[3])){ 
        moduloF(argc, argv, block_size, forcecompression);
    }


    // Modulo T
    if(argc == 4 && !strcmp("-m", argv[2]) && !strcmp("t", argv[3])){
    }


    // Modulo C
    if((argc == 4 || argc == 5) && !strcmp("-m", argv[2]) && !strcmp("c", argv[3])){
        return moduloC(argc, argv);
    }


    // Moduloc D
    if((argc == 4 || argc == 5) && !strcmp("-m", argv[2]) && !strcmp("d", argv[3])){
    }

    help_menu();
    return EXIT_FAILURE;
}
