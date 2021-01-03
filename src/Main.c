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

#include "moduloC/ModuloC.h"
#include "moduloD/manual.h"
#include "moduloD/moduloD.h"
#include "moduloF/moduloF.h"
#include "moduloT/ModuloT.h"

int main(int argc, char **argv) {
    if (argc == 2 && (!strcmp("--help", argv[1]) || !strcmp("-h", argv[1]))) {
        help_menu();
        return EXIT_SUCCESS;
    }

    if (argc >= 3 && !strcmp("-m", argv[2])) {
        // Modulo F
        if (argc >= 4 && !strcmp("f", argv[3])) {
            unsigned long block_size = 65536;
            int forcecompression = 0;
            char *filename = argv[1];
            if (argc == 4 && !strcmp("f", argv[3])) {
                moduloF(filename, block_size, forcecompression);
            }
            if (argc == 6 && !strcmp("f", argv[3]) && !strcmp("-b", argv[4])) {
                if (!strcmp("K", argv[5])) {
                    printf("entrei\n");
                    block_size = 655360;
                    moduloF(filename, block_size, forcecompression);
                }
                if (!strcmp("m", argv[5])) {
                    block_size = 8388608;
                    moduloF(filename, block_size, forcecompression);
                }
                if (!strcmp("M", argv[5])) {
                    block_size = 67108864;
                    moduloF(filename, block_size, forcecompression);
                }
            }
            if (argc == 6 && !strcmp("f", argv[3]) && !strcmp("-c", argv[4])) {
                forcecompression = 1;
                moduloF(filename, block_size, forcecompression);
            }
            if (argc == 8 && !strcmp("f", argv[3]) && !strcmp("-c", argv[6]) && !strcmp("-b", argv[4])) {
                forcecompression = 1;
                if (!strcmp("K", argv[5])) {
                    block_size = 655360;
                    moduloF(filename, block_size, forcecompression);
                }
                if (!strcmp("m", argv[5])) {
                    block_size = 8388608;
                    moduloF(filename, block_size, forcecompression);
                }
                if (!strcmp("M", argv[5])) {
                    block_size = 67108864;
                    moduloF(filename, block_size, forcecompression);
                }
            }
        }

        // Modulo T
        else if (argc == 4 && !strcmp("t", argv[3])) {
            int r = moduloT(argv[1]);
            switch (r) {
                case 1:
                    printf("Falha ao abrir o ficheiro de input\n");
                    break;
                case 2:
                    printf("Falha ao criar/ler o ficheiro de output\n");
                    break;
                default:
                    break;
            }
            return r;
        }

        // Modulo C
        else if (argc == 4  && !strcmp("c", argv[3])) {
            return moduloC(argc, argv);
        }
        // Moduloc D
        else if ((argc == 4 && !strcmp("d", argv[3])) || (argc == 5 && !strcmp("-d", argv[3]) && (!strcmp("r",argv[4]) || !strcmp("s",argv[4])))) {
            return moduloD(argc, argv);
        }
        else
            error_messages(1,"");
        
    } else
        error_messages(1, "");
    return EXIT_FAILURE;
}
