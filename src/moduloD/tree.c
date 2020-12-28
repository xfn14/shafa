#include "tree.h"

Abin init_tree() {
    Abin tree = malloc(sizeof(struct nodo));
    tree->data = 0;
    tree->used = 0;
    tree->esq = NULL;
    tree->dir = NULL;
    return tree;
}

void add_new(Abin tree, int lado) {
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

void insert_Tree(Abin *tree, D_Array *code, unsigned char letter) {
    if (code->used == 0) {
        (*tree)->used = 1;
        (*tree)->data = letter;
        return;
    }
    if (code->array[0] == '0') {
        if ((*tree)->esq == NULL) {
            add_new(*tree, 0);
        }
        remove_first(code);
        insert_Tree(&((*tree)->esq), code, letter);
    } else {
        if ((*tree)->dir == NULL) {
            add_new(*tree, 1);
        }
        remove_first(code);
        insert_Tree(&((*tree)->dir), code, letter);
    }
}

int search_tree(Abin tree, D_Array *code, unsigned char *result, int index) {
    if (code->used == index) {
        if (tree->used) {
            *result = tree->data;
            return 1;  //search was successful
        } else
            return 0;  //node not in used -> search fail
    } else {
        unsigned char letter = code->array[index];
        if (letter == 0)
            return search_tree(tree->esq, code, result, index + 1);
        else
            return search_tree(tree->dir, code, result, index + 1);
    }
}

void imprimeAUx(Abin t, char s[]) {
    if (t) {
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
void imprime(Abin t) {
    char s[] = "";
    imprimeAUx(t, s);
}

void freeAB(Abin t) {
    if (t) {
        freeAB(t->esq);
        freeAB(t->dir);
        free(t);
    }
}