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
    tree->esq = NULL;
    tree->dir = NULL;
    return tree;
}

void add_new(Abin tree, int lado, unsigned char letter)
{
    Abin new;
    new = malloc(sizeof(struct nodo));
    new->data = letter;
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
        (*tree)->data = letter;
        return;
    }
    if (code->array[0] == '0')
    {
        if ((*tree)->esq == NULL)
        {
            add_new(*tree, 0, EMPTY);
        }
        remove_first(code);
        insert_Tree(&((*tree)->esq), code, letter);
    }
    else
    {
        if ((*tree)->dir == NULL)
        {
            add_new(*tree, 1,EMPTY);
        }
        remove_first(code);
        insert_Tree(&((*tree)->dir), code, letter);
    }
}
//TODO: LOOKUP TREE

//void look_up(Abin t, D_Array *code, ..)

    void imprimeAUx(Abin t, char s[])
{
    if (t)
    {
        int length = strlen(s);
        printf("%s%d\n", s, t->data);
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

void freeAB (Abin t){
    if (t){
    freeAB (t->esq);
    freeAB (t->dir);
    free (t);
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
    Abin tree;
    tree = init_tree();
    D_Array arr;
    initArray(&arr, 1);
    insertArray(&arr, '1');
    insertArray(&arr, '0');
    insertArray(&arr, '0');
    insertArray(&arr, '1');
    print_array(&arr);
    insert_Tree(&tree, &arr, 'a');
    insertArray(&arr, '1');
    insertArray(&arr, '0');
    insertArray(&arr, '0');
    print_array(&arr);
    insert_Tree(&tree,&arr,'b');
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
    imprime (tree);
    //print_array(&arr);
}
*/