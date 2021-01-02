#include "ModuloT.h"

int moduloT (char *filename) {
    // Começa a contar o tempo
    clock_t start = clock ();
    // Abrir os ficheiros de input e output e as respetivas que gyuardam os dados em memoria 
    FILE *input = fopen (filename,"r");
    if (input == NULL) return 1; // Caso não consiga abrir o file de input
    char outName[strlen(filename)];
    strcpy (outName,filename);
    addCodFile (outName);
    FILE *output = fopen (outName,"w");
    if (output == NULL) return 2; // Caso não consiga abrir o file de ouput
    char *fileCont = getArrayFile (input);// String do input
    LISTA outputCods = listaVazia();// String para o output 
    setSize (outputCods,strlen(fileCont));
    // Inicializar oa variaveis que seram usadas pra trabalhar os dados
    endPar *arPares = arParVazio(CHARS);// [(END1),(END2),...] where END->FST = N do Char e END->SND = FREQ do Char em FST
    LISTA SF[CHARS];// [(CHAR Nº0,CODIGO SF),(CHAR Nº1,CODIGO SF),...]
    for(int i = 0;i < CHARS; i++) SF[i] = listaVazia();
    int numBlocos, zeroAfter, readFileF = 0, readFileL = 3; //Variaveis de controlo
    // Obtem o n de blocos e copia do input pro output tudo ate ao tamanho do 1º bloco
    readFileL = getNumL (fileCont,readFileL,&numBlocos);
    copyStrLista (outputCods,fileCont,readFileF,readFileL);
    readFileF = readFileL;
    // blocosSize guarda os tamanhos de todos os blocos
    int blocosSize [numBlocos]; 
    for(int i = 0; i < numBlocos; i++){
        // Guarda o tamanho do bloco i + 1 no blocosSize e copia o valor pro output
        readFileL = getNumL (fileCont,readFileL,blocosSize + i);
        copyStrLista (outputCods,fileCont,readFileF,readFileL);
        readFileF = readFileL;
        // Cria o array de pares de freqs
        readFileL = getArPares (arPares,fileCont,readFileL);
        readFileF = readFileL;
        // Coloca o array por ordem decresente e prepara SF pra guardar os codigos
        zeroAfter = decresArray (arPares); // zeroAfter guarda a quantidade de codigos pra calcular no SF
        ordSF(SF,arPares);
        //  Calcular os codigos
        calcularSF (arPares, SF, 0, zeroAfter);
        //  Escrever os codigos no output 
        addSFtoOut (SF,outputCods);
        addToLista (outputCods,'@'); 
        // Da reset a lista pra poder ser usada 
        for (int g = 0; g < CHARS; g++) resetLista (SF[g]);
    }
    // Escreve o output no Ficheiro de output 
    copyStrLista (outputCods,"0",0,2);
    fprintf (output,"%s",outputCods -> lista);
    // Liberta a memoria alocada 
    freeLista (outputCods);
    freeArPares (arPares,CHARS);
    for (int g = 0; g < CHARS; g++) freeLista (SF[g]);
    fclose (input);
    fclose (output);
    // Termina o relogio e escreve as informação relativas ao execução  
    clock_t end = clock();
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf ("Pedro Sousa A93225, Alexandre Soares A93267, %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf ("Modulo: T\n");
    printf ("Numero de Blocos: %d\n",numBlocos);
    printf ("Tamanho dos Blocos: %d",blocosSize [0]);
    for(int i = 1; i < numBlocos; i++) printf ("/%d",blocosSize[i]);
    putchar ('\n');
    printf ("Tempo de execucao: %f ms\n" , (double)(end - start) / CLOCKS_PER_SEC * 1000);
    printf ("Ficheiro gerado: %s\n", outName);
    return 0;
}
//---------------------------------------------------------------------------------
// Funções que tem como objetivo ler a abrir ficheiros. 

// Cria o nome do ficheior de escrita usando o nome do ficheiro aberto
void addCodFile (char *name){
    char cod[] = "cod";
    int length = strlen (name);
    strcpy (name + (length - 4),cod);
}

// Devolve um array , onde está guardado o conteudo do ficheiro 
char *getArrayFile (FILE *input){
    long int size = 0;
    fseek(input, 0, SEEK_END);
    size = ftell (input);
    char *result = (char *) (malloc (size + 1));
    fseek(input, 0, SEEK_SET);
    fgets(result, size+1, input);
    return (result);
}

//---------------------------------------------------------------------------------

// Função para retirar Int numa string 
int getNumL (char *lista,int start, int *num){
    int i, result = 0;
    for (i = start; isdigit(lista[i]); i ++) result = result * 10 + (lista[i] - 48);
    if (i == start) *num = -1;
    else *num = result;
    return ++i;
}
//---------------------------------------------------------------------------------
// Funções que crião e manipulão Arrays de Pares  

// Função que gera um array de pares a partir do input  
int getArPares (endPar *arPares,char* l,int filePoint){
    int num,last;
    int ind = getNumL (l,filePoint,&num);
    setPar (arPares[0], 0, num);
    last = num;
    for (int i = 1; i < CHARS; i++){
        ind = getNumL (l,ind,&num);
        if (num == -1){
            setPar(arPares[i],i,last);
        }else {
            setPar(arPares[i],i,num);
            last = num;
        }
    }
    return ind;
}

// Ordena um array por ordem decresente 
int decresArray (endPar *arPares){
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

// Cria um array de strings dinamicas que vai conter os codigos SF a partir do
//  arrray de pares gerado das freqs 
void ordSF (LISTA SF[],endPar* Par){
    for (int i = 0; i < CHARS; i++){
        addToLista(SF[i],Par[i] -> fst);    
    }
}
//---------------------------------------------------------------------------------

// Funções pra gerar os codigos SF

// Função principal que calcula os codigos SF
void calcularSF (endPar *arrPares,LISTA *SF,int i, int j){
    int div;
    if (i != j){
        div = melhorDiv (arrPares,i,j);
        addBit (SF,i,div,'0');
        addBit (SF,div+1,j,'1');
        calcularSF (arrPares,SF,i,div);
        calcularSF (arrPares,SF,div+1,j);
    }
} 

// Função que serve pra determinar a melhor divisão
int melhorDiv (endPar *arrPares,int i,int j){
    int soma = 0, ind;
    int mtotal = (somaArray (arrPares,i,j)) / 2;
    for (ind = i; ind < j && soma <= mtotal; ind++) soma += (arrPares[ind] -> snd);
    ind --;
    if (((soma - mtotal) > (abs(somaArray (arrPares, ind, j) - mtotal)))) ind = ind - 1;
    return ind;
}

// Função que devolve a soma os valores das freq nos pares
// entre dois pontos expecificados 
int somaArray (endPar *arrPares,int i,int j) {
    int soma = 0;
    for(; i < j; i++) soma += (arrPares[i] -> snd);
    return soma;
}

// Adiciona um bit aos codigos
void addBit (LISTA *SF,int i,int j,char b){
    for (; i <= j; i++){
        addToLista (SF[i],b);
    }
}
//---------------------------------------------------------------------------------

// Função que passa os codigos para a string de output
// e poê - os por ordem   
void addSFtoOut (LISTA SF[],LISTA out){
    int simb = 0,last = CHARS - 1;
    LISTA temp = SF [0];
    for (int i = 0; i <= last; i++){
        temp = SF [i];
        if (temp -> lista [0] == simb){
            for(int g = 1; g < temp -> last; g ++) addToLista (out,temp->lista[g]);
            switchLista (SF,i,last);
            if (last != 0) addToLista (out,';');
            simb ++;last--;i = -1;
        }
    }
}
