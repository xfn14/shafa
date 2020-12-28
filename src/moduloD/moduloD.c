#include "moduloD.h"


int rle_decompression(char *filename, char *new_file, int *input_array, int* output_array, int only_rle) {
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb");  //open the file we want to read
    if (ptr == NULL) {
        printf("can't read the file: %s\n", filename);
        return 0;
    }
    int file_size = fsize(ptr), block = 0, u,anterior = 0;
    fp = fopen(new_file, "wb+");         //open the file we will write
    int block_size = output_array[block];  //keep track of the current size of the block
    D_Array new_buffer;
    initArray(&new_buffer, block_size);                                       //initiate dynamic array
    unsigned char *temp_buffer = malloc(sizeof(unsigned char) * file_size);  //buffer for the reading
    if (fread(temp_buffer, sizeof(unsigned char), file_size, ptr) == 0)      //read the current block
        return 0;
    for (u = 0; u < file_size; u++) {
        if (only_rle){
            if (new_buffer.used == output_array[block]){
                input_array[block++] = u - anterior;
                anterior = input_array[block -1];
                fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);
                clearArray(&new_buffer);
                }
        }
        else {
            if (u == output_array[block]){
                output_array[block++] = new_buffer.used;
                anterior = input_array[block -1];
                fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);
                clearArray(&new_buffer);
            }
        }
        if (temp_buffer[u] == 0)  //for the rle compression case
        {
            unsigned char letter = temp_buffer[u + 1];
            unsigned char num_reps = temp_buffer[u + 2];
            repeat(letter, num_reps, &new_buffer);
            u += 2;  //skip to next character outside rle case
        } else
            insertArray(&new_buffer, temp_buffer[u]);  //normal character
    }
    fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);  //writing the new block in the new file
    free(temp_buffer);
    if (only_rle )input_array[block] = u -anterior; 
    else output_array[block] = new_buffer.used;  //keeping track of the size of the new block
    freeArray(&new_buffer);
    fclose(ptr);
    fclose(fp);
    return 1;
}

//KINDA DONE
Abin do_tree(unsigned char *buffer, int *index, int file_size, int *block_size, int block_index) {
    unsigned char element = 0;
    Abin tree;
    tree = init_tree();
    D_Array arr;
    initArray(&arr, 5);
    int flag = 1;
    for (int i = *index; i < file_size && flag; i++) {
        if (buffer[i] == '@') {
            if (buffer[i + 1] == '0') return tree;
            *index = i + 1;
            block_size[block_index] = do_size(buffer, index);
            flag = 0;
        } else if (buffer[i] == ';') {
            if (arr.used != 0)
                insert_Tree(&tree, &arr, element);  //insert every code in tree
            element++;
        } else
            insertArray(&arr, buffer[i]);
    }
    return tree;
}

int read_cod(const char *filename, Abin *array_tree, int *block_size, int *nr_blocks) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Can't open %s file\n", filename);
        return 0;
    }
    int file_size = fsize(fp);
    unsigned char *buffer = malloc(sizeof(unsigned char) * file_size);
    if (fread(buffer, sizeof(unsigned char), file_size, fp) == 0) return 0;
    int index = skip(0, 2, buffer);
    *nr_blocks = do_size(buffer, &index);
    *block_size = do_size(buffer, &index);
    if (realloc(block_size, *nr_blocks) == 0) return 0;
    for (int block = 0; block < *nr_blocks; block++) {
        array_tree[block] = do_tree(buffer, &index, file_size, block_size, block + 1);
    }
    fclose(fp);
    return 1;
}
int shaf_decompression(char *read_file, char *output_file, int *block_size, int *new_size, Abin *array_tree) {
    FILE *fp, *ptr;
    ptr = fopen(read_file, "rb");
    if (ptr == NULL){
        printf("Can't open the file: %s\n",read_file);
        return 0;
    }    
    int file_size = fsize(ptr);
    fp = fopen(output_file, "wb+");
    D_Array new_buffer, array;
    initArray(&array, 8);
    initArray(&new_buffer, block_size[0]);
    Abin tree = array_tree[0];
    unsigned char *temp_buffer = malloc(sizeof(unsigned char) * file_size);        //buffer for reading
    if (fread(temp_buffer, sizeof(unsigned char), file_size, ptr) == 0) return 0;  //read block
    int index = 1, nr_blocks = do_size(temp_buffer, &index), block = 0, flag = 1;
    new_size[block] = do_size(temp_buffer, &index);
    for (; index < file_size; index++) {
        if (new_buffer.used == block_size[block]) {
            if (++block < nr_blocks) {
                index++;
                new_size[block] = do_size(temp_buffer, &index);
            }
            index--;
            flag = 1;
            fwrite(new_buffer.array, new_buffer.used, sizeof(unsigned char), fp);
            clearArray(&new_buffer);
            clearArray(&array);
            tree = array_tree[block];
        } else {
            unsigned char res;
            int bin[8];
            int_bin(temp_buffer[index], bin);  //byte into an array
            for (int i = 0; i < 8 && flag; i++) {
                if (new_buffer.used == block_size[block])
                    flag = 0;
                else {
                    insertArray(&array, bin[i]);  //insert the bit in the array
                    if (search_tree(tree, &array, &res, 0) == 1) {
                        insertArray(&new_buffer, res);
                        clearArray (&array);
                    }
                }
            }
        }
    }
    fwrite(new_buffer.array, new_buffer.used, sizeof(unsigned char), fp);
    freeArray(&new_buffer);
    freeArray(&array);
    fclose(ptr);
    fclose(fp);
    return 1;
}


int get_size (char* filename,int *nr_blocks, int *block_size){
    FILE *fp = fopen (filename,"r");
    if (fp == NULL){
        printf("can't read %s\n",filename);
        return 0;
    }
    int file_size = fsize (fp), index = 3, block = 0;
    unsigned char *buffer = malloc (sizeof (unsigned char) * file_size);
    if (fread (buffer,sizeof(unsigned char), file_size, fp) == 0)return 0;
    *nr_blocks = do_size (buffer,&index);
    if (realloc (block_size,*nr_blocks * sizeof(int)) == 0)return 0;
    unsigned char element = 0;
    block_size[block++] = do_size (buffer,&index);
    for (; index < file_size && block < *nr_blocks;index++){
        if (element == 255) {
            index++;
            block_size[block++] = do_size (buffer,&index);
            index--;
        }
        if (buffer[index] == ';') element++;
    }
    fclose (fp);
    return 1;
}

int only_rle (char* filename, char *output_file,int *input_array,int *output_array, int *nr_blocks){
    int len = strlen (filename);
    char freq_file[len];
    memset (output_file,0,len-4);
    strncpy(output_file,filename,len-4);
    strcpy (freq_file,output_file);
    strcat (freq_file,".freq");
    if (get_size (freq_file,nr_blocks, output_array) == 0) return 0;
    rle_decompression (filename,output_file,input_array,output_array,1);
    return 1;
}



int moduloD(int argc, char **argv) {
    clock_t begin = clock();
        int *output_array, nr_blocks, success = 1,*input_array = malloc (sizeof (int) *2), do_rle = 0, only_shaf = 0;
        output_array = malloc(sizeof(int) * 2);
        char *filename = argv[1];
        int size = strlen(filename);
        char cod_file[size - 1], output_file[size - 4],rle_file[size-4];
        Abin *array_tree = malloc(sizeof(Abin) * 2);
        if (argc == 4 && argv[3][0] == 'r'){
                success = only_rle (filename,output_file,input_array,output_array,&nr_blocks);
        }
        else{
            if (argc == 4 && argv[3][0] == 's') only_shaf = 1;
            get_filenames(filename, cod_file, output_file);
            success = read_cod(cod_file, array_tree, output_array, &nr_blocks);
            input_array = malloc (sizeof (int) *nr_blocks);
            do_rle = strstr(output_file, "rle") != 0 && !only_shaf ? 1 : 0;
            success = shaf_decompression(filename, output_file, output_array, input_array, array_tree);
            int len = strlen(output_file);
            if (do_rle) {
                strcpy(rle_file, output_file);
                memset(output_file, 0, len);
                strncpy(output_file, rle_file, len - 4);
                rle_decompression(rle_file,output_file, input_array,output_array,0);
            }
        }
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        if (success) {
            printf("José Diogo,a93251, e António Fernandes, a93312, MIEI/CD, %d-%02d-%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            printf("Módulo: d (descodificação dum ficheiro shaf)\n");
            printf("Número de blocos:%d\n", nr_blocks);
            for (int i = 1; i <= nr_blocks; i++)
                printf("Tamanho antes/depois do ficheiro gerado (bloco %d):%d/%d\n", i, input_array[i - 1], output_array[i - 1]);
            printf("Tempo de execução do módulo (milissegundos):%f milissegundos\n", time_spent * 1000);
            if (!do_rle) printf("Ficheiro gerado: %s\n", output_file);
            else printf("Ficheiros gerados: %s e %s\n",output_file,rle_file);
        }

    return 1;
}


int main (int argc, char **argv){
    moduloD (argc,argv);
    return 1; 
}