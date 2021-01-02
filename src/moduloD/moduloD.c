#include "moduloD.h"

int rle_decompression(char *filename, char *new_file, size_t *input_array, size_t *output_array, size_t block_number) {
    FILE *ptr, *fp;
    ptr = fopen(filename, "rb");  //open the file we want to read
    if (ptr == NULL) {
        error_messages(0, filename);
        return 0;
    }
    size_t block = 0;
    fp = fopen(new_file, "wb+");                      //open the file we will write
    size_t output_size = output_array[block], u = 0;  //keep track of the current size of the block
    D_Array new_buffer;
    initArray(&new_buffer, output_size);
    unsigned char *temp_buffer;  //initiate dynamic array
    for (size_t n = 0; n < block_number; n++) {
        size_t block_size = input_array[n];
        temp_buffer = (unsigned char *)calloc(block_size, sizeof(unsigned char));
        if (fread(temp_buffer, sizeof(unsigned char), block_size, ptr) == 0)  //read the current block
            return 0;
        for (u = 0; u < block_size; u++) {
            if (temp_buffer[u] == 0)  //for the rle compression case
            {
                unsigned char letter = temp_buffer[u + 1];
                unsigned char num_reps = temp_buffer[u + 2];
                repeat(letter, num_reps, &new_buffer);
                u += 2;  //skip to next character outside rle case
            } else
                insertArray(&new_buffer, temp_buffer[u]);  //normal character
        }
        output_array[block++] = new_buffer.used;
        fwrite(new_buffer.array, 1, new_buffer.used * sizeof(unsigned char), fp);
        clearArray(&new_buffer);
    }
    output_array[block] = new_buffer.used;  //keeping track of the size of the new block
    freeArray(&new_buffer);
    fclose(ptr);
    fclose(fp);
    return 1;
}

Abin do_tree(unsigned char *buffer, int *index, int file_size, size_t *block_size, int block_index) {
    unsigned char element = 0;
    Abin tree;
    tree = init_tree();
    D_Array arr;
    initArray(&arr, 5);
    int flag = 1;
    for (int i = *index; i < file_size && flag; i++) {
        if (buffer[i] == '@') {
            if (arr.used != 0)
                insert_Tree(&tree, &arr, element);  //insert every code in tree
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
    freeArray(&arr);
    return tree;
}

int read_cod(char *filename, Abin *array_tree, size_t *block_size, size_t *nr_blocks) {
    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        error_messages(2, ".cod");
        return 0;
    }
    int file_size = f_size(fp);
    unsigned char *buffer = (unsigned char *)calloc(file_size, sizeof(unsigned char));
    if (fread(buffer, sizeof(unsigned char), file_size, fp) == 0) return 0;
    int index = skip(0, 2, buffer);
    *nr_blocks = do_size(buffer, &index);
    *block_size = do_size(buffer, &index);
    for (size_t block = 0; block < *nr_blocks; block++) {
        array_tree[block] = do_tree(buffer, &index, file_size, block_size, block + 1);
    }
    free(buffer);
    fclose(fp);
    return 1;
}

int shaf_decompression(char *read_file, char *output_file, size_t *output_size, size_t *input_size, Abin *array_tree) {
    FILE *fp, *ptr;
    ptr = fopen(read_file, "rb");
    if (ptr == NULL) {
        error_messages(0, read_file);
        return 0;
    }
    fp = fopen(output_file, "wb+");
    D_Array new_buffer, array;
    initArray(&array, 8);
    initArray(&new_buffer, output_size[0]);
    Abin tree;  //read block
    int flag = 1, index = 1;
    unsigned char *check_buffer = (unsigned char *)calloc(20, sizeof(unsigned char));
    if (fread(check_buffer, sizeof(unsigned char), 20, ptr) == 0) return 0;
    size_t nr_blocks = do_size(check_buffer, &index), block_i = 0;
    input_size[0] = do_size(check_buffer, &index);
    block_i = index;
    fseek(ptr, index, SEEK_SET);
    for (size_t n = 0; n < nr_blocks; n++) {
        tree = array_tree[n];
        unsigned char *temp_buffer = (unsigned char *)calloc(input_size[n], sizeof(unsigned char));
        if (fread(temp_buffer, sizeof(unsigned char), input_size[n], ptr) == 0) return 0;
        for (block_i = 0; block_i < input_size[n] && flag; block_i++) {
            if (new_buffer.used == output_size[n])
                flag = 0;
            else {
                unsigned char res;
                int bin[8];
                int_bin(temp_buffer[block_i], bin);  //byte into an array
                for (int i = 0; i < 8 && flag; i++) {
                    if (new_buffer.used == output_size[n]) {
                        flag = 0;
                    } else {
                        insertArray(&array, bin[i]);  //insert the bit in the array
                        if (search_tree(tree, &array, &res, 0) == 1) {
                            insertArray(&new_buffer, res);
                            clearArray(&array);
                        }
                    }
                }
            }
        }
        fwrite(new_buffer.array, new_buffer.used, sizeof(unsigned char), fp);
        if (n + 1 < nr_blocks) {
            unsigned char *buffer_size = (unsigned char *)calloc(10, sizeof(unsigned char));
            if (fread(buffer_size, sizeof(unsigned char), 10, ptr) == 0) return 0;
            index = 1;
            input_size[n + 1] = do_size(buffer_size, &index);
            fseek(ptr, -10 + index, SEEK_CUR);
            flag = 1;
        }
        clearArray(&new_buffer);
        clearArray(&array);
        free(temp_buffer);
    }
    fclose(ptr);
    fclose(fp);
    return 1;
}

int get_size(char *filename, size_t *nr_blocks, size_t *block_size) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        error_messages(0, filename);
        return 0;
    }
    int file_size = f_size(fp);
    size_t block = 0;
    int index = 3 + lenHelper(*nr_blocks) + 1;
    unsigned char *buffer = (unsigned char *)calloc(file_size, sizeof(unsigned char));
    if (fread(buffer, sizeof(unsigned char), file_size, fp) == 0) return 0;
    unsigned char element = 0;
    block_size[block++] = do_size(buffer, &index);
    for (; index < file_size && block < *nr_blocks; index++) {
        if (buffer[index] == '@') {
            index++;
            block_size[block++] = do_size(buffer, &index);
            index--;
        }
        if (buffer[index] == ';') element++;
    }
    fclose(fp);
    return 1;
}

int do_only_rle(char *filename, char *output_file, size_t *input_array, size_t *output_array, size_t *nr_blocks) {
    int len = strlen(filename);
    char freq_file[len];
    int point = last_point(filename, len);
    memset(output_file, 0, point + 1);
    strncpy(output_file, filename, point);
    strcpy(freq_file, filename);
    strcat(freq_file, ".freq");
    if (get_size(freq_file, nr_blocks, input_array) == 0) return 0;
    rle_decompression(filename, output_file, input_array, output_array, *nr_blocks);
    return 1;
}

size_t get_nr_blocks(int argc, char **argv) {
    FILE *fp;
    char *filename = argv[1];
    int len = strlen(filename);
    char freq_file[len];
    unsigned char buffer[20];
    if (argc == 5 && argv[4][0] == 'r') {
        int point = last_point(filename, len);
        memset(freq_file, 0, point + 1);
        strncpy(freq_file, filename, point);
        strcat(freq_file, ".freq");
        fp = fopen(freq_file, "rb");
        if (fp == NULL) {
            error_messages(2, ".freq");
            return 0;
        }
        if (fread(buffer, 20, sizeof(unsigned char), fp) == 0) return 0;
        int index = 3;
        return do_size(buffer, &index);
    } else {
        fp = fopen(filename, "rb");
        if (fp == NULL) {
            error_messages(0, filename);
            return 0;
        }
        if (fread(buffer, 20, sizeof(unsigned char), fp) == 0) return 0;
        int index = 1;
        return do_size(buffer, &index);
    }
    fclose(fp);
    return 1;
}

int moduloD(int argc, char **argv) {
    clock_t begin = clock();
    if (argc == 4 || argc == 5) {
        size_t block_number = get_nr_blocks(argc, argv);
        if (block_number == 0) return 1;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int success = 1, do_rle = 0, only_shaf = 0;
        size_t *input_array, *output_array;
        output_array = (size_t *)calloc(block_number, sizeof(size_t));
        input_array = (size_t *)calloc(block_number, sizeof(size_t));
        char *filename = argv[1];
        int size = strlen(filename);
        char cod_file[size - 1], output_file[size - 4], rle_file[size - 4];
        Abin *array_tree = (Abin *)calloc(block_number, sizeof(Abin));
        if (argc == 5) {
            if (argv[4][0] == 'r') {
                if (strstr(filename, ".shaf") != 0) {
                    error_messages(1, "");
                    return 1;
                }
                success = do_only_rle(filename, output_file, input_array, output_array, &block_number);
                for (size_t i = 0; i < block_number; i++) freeAB(array_tree[i]);
                clock_t end = clock();
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                if (success) output_text(block_number, input_array, output_array, output_file, rle_file, time_spent, do_rle, tm);
                return 1;
            }
            if (argv[4][0] == 's') only_shaf = 1;
        }
        get_filenames(filename, cod_file, output_file);
        success = read_cod(cod_file, array_tree, output_array, &block_number);
        if (success == 0) return 0;
        do_rle = strstr(output_file, ".rle") != 0 && !only_shaf ? 1 : 0;
        success = shaf_decompression(filename, output_file, output_array, input_array, array_tree);
        int len = strlen(output_file);
        if (do_rle) {
            strcpy(rle_file, output_file);
            memset(output_file, 0, len);
            strncpy(output_file, rle_file, len - 4);
            size_t *before = (size_t *)calloc(block_number, sizeof(size_t));
            memcpy(before, input_array, block_number * (sizeof(size_t)));
            rle_decompression(rle_file, output_file, output_array, input_array, block_number);
            output_array = input_array;
            input_array = before;
        }
        for (size_t i = 0; i < block_number; i++) freeAB(array_tree[i]);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        if (success) output_text(block_number, input_array, output_array, output_file, rle_file, time_spent, do_rle, tm);
        return 0;
    } else {
        error_messages(1, "");
        return 1;
    }
}

//int main(int argc, char **argv) {
//    return moduloD(argc, argv);
//
//}
