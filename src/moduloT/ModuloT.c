#include "ModuloT.h"

int moduloT (char *filename) {
    LISTA l = listaVazia();
    endPar *arPares = arParVazio(CHARS);
    endPar *SF = arParVazio(CHARS);
    int numBlocos,zeroAfter;
    // Abrir o file de input
    FILE *input = fopen (filename,"r");
    if (input == NULL) return 1;
    // Criar e abrir o file de output
    char *outName = addCodFile (filename);
    FILE *output = fopen (outName,"w");
    free (outName);
    // Ler se o File está comprimido ou não
    fgetc (input);
    input = writeNum(input,output,NULL,l);
    // Ler nº blocos
    input = writeNum(input,output,&numBlocos,l);
    // For pra ler os blocos e escrever
    for(int i = 0; i < numBlocos; i++){
        //Tamanho do bloco
        input = writeNum(input,output,NULL,l);
        //Passar o bloco pra array onde arPares[n] = end -> (Nº de Simb ,Freq) pra depois ordenar
        // g[] = [121323124,32141412] = 121323124 -> (1,2) = 32141412 -> (2,3)
        input = tilAt(input,l);
        getArPares (arPares,l);
        //Ordenar po ordem dercresente
        zeroAfter = decresArray (arPares);
        cpPar_Snd (arPares,SF,CHARS,1);
        //Shanon fanon
        calcularSF (arPares, SF, 0, zeroAfter);
        //reordenar o array array[n] = codigo shanon fanon desse numero
        //escrever no file
        output = printArParFile (SF, output);
        resetLista (l);
    }
    fprintf(output,"@0");
    return 0;
}

FILE *tilAt (FILE *file,LISTA l){
    int temp = fgetc(file);
    while (temp != 64 && temp >= EOF){
        addToLista (l,(char) (temp));
        temp = fgetc (file);
    } 
    return file;
}

char *addCodFile (char *name){
    int length = strlen (name) + 7;
    char *new = malloc(length * sizeof(char));
    strcpy (new,name);
    strcat (new,".cod");
    return new;
}

void writeOnFile (LISTA l,FILE *file){ 
    fputc('@',file);
    for(int i = 0, last = l -> last; i < last; i++) fputc (l->lista[i],file);
    l -> last = 0;
}

int getNumLL (char *lista,int fst,int lst){
    int result = 0;
    for (int i = fst;i <= lst; i++ ){ 
    result = result * 10 + ((lista[fst]) - '0');
    } 
    return result;

}

FILE *writeNum(FILE *input,FILE *output,int *ret,LISTA l){
    input = tilAt(input,l);
    if(ret != NULL) *ret = getNumLL (l->lista, 0, (l->last)-1);
    writeOnFile (l,output);
    return input;
}

// WIP
void getArPares (endPar *arPares, LISTA l){
    int* num = malloc(sizeof(int));
    int ind = entrePV(l,0, num);
    int last = *num; 
    setPar (arPares[0], 0, *num);
    for (int i = 1; i < CHARS; i++){
        ind = entrePV(l, ind, num);
        if (*num == -1){
            setPar(arPares[i],i,last);
        }else {
            setPar(arPares[i],i,*num);
            last = *num;
        }
    }
    free (num);
}

int entrePV (LISTA l, int start, int *num){
    int i, result = 0;
    for (i = start; l->lista[i] != ';' && i < l ->last; i ++) result = result * 10 + (l->lista[i] - 48);
    if (i == start)*num = -1;
    else *num = result;
    return ++i;
}

// Para testar
int decresArray (endPar *arPares)
{
    int maior = 0,ind = 0,result = 0;
    for (int i = 0; i < CHARS; i++){
        maior = arPares[i] -> snd;
        for(int j=i+1; j<CHARS; j++){
            if ((arPares[j] -> snd) > maior){
            maior = arPares[j]->snd;
            ind = j;
            }
        }
        if (maior != (arPares[i] -> snd)) switchPares(arPares, ind, i);
        if (arPares[i] -> snd != 0) result ++;
    }
    return result - 1;
}

int somaArray (endPar *arrPares,int i,int j) {
    int soma = 0;
    for(; i < j; i++) soma += (arrPares[i] -> snd);
    return soma;
}

int melhorDiv (endPar *arrPares,int i,int j){
    int soma = 0, ind;
    int mtotal = (somaArray (arrPares,i,j)) / 2;
    for (ind = i; ind < j && soma <= mtotal; ind++) soma += (arrPares[ind] -> snd);
    ind --;
    if ((soma - mtotal) > (abs(somaArray (arrPares, ind, j) - mtotal))) ind = ind - 1;
    return ind;
}

void addBit (endPar *SF,int i,int j,int b){
    for (; i <= j; i++){
        (SF [i] -> snd) = (SF [i] -> snd) * 10 + b;
    }
}

void calcularSF (endPar *arrPares,endPar *SF,int i, int j){
    int div;
    if (i != j){
        div = melhorDiv (arrPares,i,j);
        addBit (SF,i,div,0);
        addBit (SF,div+1,j,1);
        calcularSF (arrPares,SF,i,div);
        calcularSF (arrPares,SF,div+1,j);
    }
} 

FILE *printArParFile (endPar *SF,FILE *output){
    int last = CHARS - 1;
    int simb = 0;
    char string[100];
    putc('@',output);
    for (int i = 0;i <= last; i++){
        if (SF[i] -> fst == simb){
            if (SF[i] -> snd != 1){
                numToString (SF[i] -> snd,string);
                fprintf(output,"%s",string);
            }
            switchPares (SF,i,last);
            putc (';', output);
            simb ++; last--; i = -1;
        }
    }  
    return output;
}

void numToString (int num,char *string){
    int size = sizeNum (num);
    string[size - 1] = '\0';
    for (int i = size - 2;i >= 0; i --){
        string[i] = '0' + (num % 10);
        num = num / 10;
    }
}

int sizeNum (int num){
    int i;
    for (i = 0; num  >= 10; i++)num = num / 10;    
    i++;
    return i;
}
