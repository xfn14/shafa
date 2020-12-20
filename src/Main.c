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
//#include "moduloT/ModuloT.h"
#include "moduloC/ModuloC.h"

int main(int argc, char *argv[]){
    if(argc == 4){
        char *fileName = argv[1];
        if(argv[2][1] == 'm'){
            switch(argv[3][0]){
                case 't':
                    // TODO
                    break;
                case 'c':
                    moduloC(fileName);
                    break;
                default:
                    printf("Modulo inválido. Disponíveis: t,c");
                    return 0;
            }
        }
    }else{
        printf("Error in syntax: shafa <file> -m <modulo>\n");
        return 0;
    }
    return 1;
}
