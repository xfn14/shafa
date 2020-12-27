#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "d_array.h"
#include "tree.h"

#define EMPTY -1
Abin init_tree()
{
    Abin tree = malloc(sizeof(struct nodo));
    tree->data = 0;
    tree->used = 0;
    tree->esq = NULL;
    tree->dir = NULL;
    return tree;
}

void add_new(Abin tree, int lado)
{
    Abin new;
    new = malloc(sizeof(struct nodo));
    tree->data = 0;
    tree->used = 0;
    new->esq = NULL;
    new->dir = NULL;
    if (lado)
        tree->dir = new;
    else
        tree->esq = new;
}

void insert_Tree(Abin *tree, D_Array *code, unsigned char letter)
{
    if (code->used == 0)
    {
        (*tree)->used = 1;
        (*tree)->data = letter;
        return;
    }
    if (code->array[0] == '0')
    {
        if ((*tree)->esq == NULL)
        {
            add_new(*tree, 0);
        }
        remove_first(code);
        insert_Tree(&((*tree)->esq), code, letter);
    }
    else
    {
        if ((*tree)->dir == NULL)
        {
            add_new(*tree, 1);
        }
        remove_first(code);
        insert_Tree(&((*tree)->dir), code, letter);
    }
}

int search_tree(Abin tree, D_Array *code, unsigned char *result, int index)
{
    if (code->used == index){
        if (tree->used)
        {
            *result = tree->data;
            return 1; //search was sucesseful
        }
        else
            return 0; //node not in used -> search fail
    }
    else
    {
        unsigned char letter = code->array[index];
        if (letter == 0)
            return search_tree(tree->esq, code, result,index +1);
        else
            return search_tree(tree->dir, code, result,index +1);
    }
}

void imprimeAUx(Abin t, char s[])
{
    if (t)
    {
        int length = strlen(s);
        printf("%s(%d,%d)\n", s, t->data, t->used);
        char left[length + 2];
        strcpy(left, s);
        char right[length + 2];
        strcpy(right, s);
        char r = '>';
        char l = '<';
        imprimeAUx(t->dir, strncat(right, &r, 1));
        imprimeAUx(t->esq, strncat(left, &l, 1));
    }
}
//
void imprime(Abin t)
{
    char s[] = "";
    imprimeAUx(t, s);
}

void freeAB(Abin t)
{
    if (t)
    {
        freeAB(t->esq);
        freeAB(t->dir);
        free(t);
    }
}
/*
void main()
{
    FILE*fp;
    fp = fopen ("test.txt","r");
    char *buffer = malloc (sizeof (unsigned char) * 4);
    fread (buffer,4,sizeof(unsigned char),fp);
    D_Array arr; 
    initArray(&arr,4);
    for (int i = 0; i < 4;i++){
        insertArray(&arr,buffer[i]);
    }
    Abin tree; 
    tree = init_tree();
    insert_Tree(&tree,&arr,'a');
    imprime (tree);
}
*/
/*
int main()
{
    Abin tree;
    tree = init_tree();
    D_Array arr;
    initArray(&arr, 1);
    insertArray(&arr, '1');
    insertArray(&arr, '1');
    insertArray(&arr, '0');
    //print_array(&arr);
    insert_Tree(&tree, &arr, 'a');
    insertArray(&arr, '0');
    //print_array(&arr);
    insert_Tree(&tree, &arr, 'b');
    insertArray(&arr, '1');
    Abin *array_tree = malloc(sizeof(Abin)*2);
    //memcpy(array_tree[0],&tree,sizeof(Abin));
    Abin tree2;
    tree2 = init_tree();
    insert_Tree(&tree2, &arr,'c');
    array_tree[0] = tree;
    array_tree[1] = tree2;
    unsigned char c=  255;
    printf("%d\n",c);
    //print_array(&arr);
    //unsigned char *res = malloc(sizeof(unsigned char));
    //int i = search_tree(tree, &arr, res);
    //if (i)
    //    printf("is %c\n", res[0]);
    //else
    //    printf("Search was failed\n");
    //free(res);
    unsigned char *file = malloc (sizeof (unsigned char) *3);
    file[0] = 216;
    file[1] = 54; 
    file[2] = 0; 
    D_Array array;
    initArray(&array, 2);
    //CONVERT BYTE TO AN INT ARRAY OF 1 AND 0
    D_Array result;
    initArray(&result, 5);
    int *bin = malloc(sizeof(int) * 8);
    for (int n = 0; n < 3; n++){
        unsigned char letter = file [n]; 
        for (int i = 0; i < 8; i++)
        {
            bin[7 - i] = (letter >> i) & 1;
        }
        for (int i = 0; i < 8; i++)
        printf("%d", bin[i]);
        for (int i = 0; i < 8; i++)
        {
            insertArray(&array, bin[i]); //insert the bit in the array
            //printf("used = %d\n",array.used);
            D_Array temp;
            int temp_size = array.used;
            memcpy(&temp, &array, sizeof(D_Array));
            print_array(&temp, 1);
            if (search_tree(tree, &array, res) == 1)
            {
                insertArray(&result, res[0]);
                printf("write on %d ->", i);
                print_array(&temp, 0);
            }
            else
                memcpy(&array, &temp, sizeof(D_Array));
        }
    }
    print_array(&result, 0);
    putchar('\n');
    //freeArray(&array);
    freeArray(&result);
    free(res);
    free(bin);
    //insertArray(&arr, '1');
    //print_array(&arr);
    //insert_Tree(&tree, &arr, 'b');
    //insertArray(&arr, '1');
    //insertArray(&arr, '1');
    //print_array(&arr);
    //insert_Tree(&tree, &arr, 'c');
    //insertArray(&arr, '1');
    //insertArray(&arr, '1');
    //insertArray(&arr, '1');
    //print_array(&arr);
    //insert_Tree(&tree, &arr, 'd');
    imprime(array_tree[0]);
    putchar ('\n');
    imprime(array_tree[1]);
    freeAB(tree);
    //print_array(&arr);
}
*/