#include "moduloF.h"

/*Esta função cria um array com 255 posições e inicializa-o com todas as posiçoes a 0*/
/*A funçao será usada mais à frente pela função freqs para guardar as frequências de cada um dos 255 códigos ASCII*/
int *arrayazeros(){
    int *freqs = malloc (255* sizeof(int)); //Cria o array com 255 posições
    for (int i = 0; i < 256; i++) //Percorrer as 255 posções do array
    {
        *(freqs+i) = 0; //Inicializa as posições a 0
    } 
return freqs; //Devolve o array com 0 em todas as posições
}

/*Função que cria um array com tantas posições quantas o número de blocos do ficheiro rle (argumento passado à função) e inicializa cada uma dessas posições a zero*/
/*Esta função é usada para guardar os tamanhos de cada bloco do ficheiro rle, para mais tarde dar printf na função moduloF*/
int *array_rle_blocksize_zeros(long long n_blocks){
    int *rle = malloc(n_blocks*sizeof(int)); //Cria um array com n_blocks posições
    for (int i = 0; i < n_blocks; i++) //Percorre as n_blocks posições
    {
        *(rle+i) = 0; //Inicializa as posições a 0
    }
return rle; //Devolve o array com 0 em todas as posições
}

/*Acrescenta ".freq" no final do nome do ficheiro de frequências*/
char *dotfreq(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".freq");
return newfilename;
}

/*Acrescenta ".rle" no final do nome do ficheiro rle*/
char *dotrle(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".rle");
return newfilename;
}

/*Cria um ficheiro de frequências e escreve lá a frequência de cada um dos códigos ASCII no ficheiro*/
void freqs(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, char *filename, int flagend, int flagoriginal){
    int *size_blocks;
    FILE *fp;
    if (flaginit){ //Esta flag permite-nos saber se já existia algum ficheiro com o mesmo nome, se sim então vai abri-lo, apagar o que lá havia e começar a escrever no ínicio do ficheiro
        fp = fopen (filename, "wb");
        if (flagoriginal) fprintf(fp, "@N@%lld@", n_blocks); //Esta flag diz-nos se vamos criar o ficheiro das frequências referente ao ficheiro orginal (filename.freq) ou referente ao ficheiro rle (filename.rle.freq)
        else fprintf (fp, "@R@%lld@", n_blocks); //Isto acontece quando a flagorinal é igual a 0 e portanto o ficheiro das frequências é referente ao ficheiro rle
    }
    else fp = fopen (filename, "ab"); //Vimos para esta condição quando a flaginit é 0 o que significa que já existia um ficheiro com este nome
    fprintf(fp, "%d@", sizebuffer);
    int i, j, z, counterant, *freqs = arrayazeros();
        for (i=0; i<sizebuffer; i++){ //Este ciclo vai guardar em freqs, array criado pela função arrayzeros, as frequências de cada símbolo
            z = *(buffer+i);
            *(freqs+z)+=1;
        }
    for ( int y = 0; y<256; y++) //Neste ciclo percorremos o array onde estão guardadas as frequências para as imprimir no ficheiro freq
    {
        int counter = *(freqs+y);
        if (y==0){ //Se estiver na primeira posição do array vai apenas imprimir o que lá está seguido dum ";"
            counterant = counter; //Guarda o valor que se encontra nessa posição na variável couterant
            fprintf(fp, "%d;",*(freqs+y));
        }
        else if (counterant==counter){ //Se as duas frequências consecutivas forem iguais então escreve apenas um ";"
                 if(y!=255) fprintf(fp, ";");
                 counterant=counter; //Atualiza o valor de counterant
        }
        else{ //Se nenhuma das condições anteriores se verificar exreve no ficheiro o valor que se encontra na posição y do array freqs
            fprintf(fp, "%d", counter);
            if(y!=255) fprintf(fp, ";"); //Se não se encontrar na última posição do array então vai escrever um ";"
            counterant=counter; //Atualiza a variável counterant
    }
    }
    fprintf(fp, "@"); //Escreve no ficheiro um "@"
    if(flagend) fprintf(fp, "0"); //Caso a flangend seja verdadeira, o que signfica que o ficheiro original chegou aoo fim, escreve no ficheiro freq um "0"
    fclose(fp); //Fecha o ficheiro freq
}

/*Esta função devolve o número de símbolos do ficheiro rle*/
int simbcount(unsigned char *buffer, int sizebuffer){
    int i, counter=1, simbs=0;
    unsigned char c;
    for (i = 0; i<sizebuffer; i++) //Percorre o bloco que está a ser analisado
    {
        c= *((buffer)+i); //É atribuido à variável c o valor que se encontra na posição i do buffer
        while (*((buffer)+i) == *((buffer)+i+1)) //Enquanto os valores nas posições consecutivas do array são iguais o counter vai aumentando
        {
            counter++; //A variável counter armazena o número de símbolos iguais que se encontram seguidos
            i++;
        }
        if (counter>255){ //Quando a variável counter tiver um valor superior a 255 (o máximo que se pode comprimir duma vez)  
            while (counter/255 > 0){ //Dividimos por 255 para ver quantas vezes temo e realizar o ciclo, enquanto for maior que 255 temos sempre que repetir
                simbs+=3; //Por cada 255 símbolos no ficheiro rle ficam apenas 3 (por causa deste formato {0}1{símbolo}1{número_de_repetições}1)
                counter-=255; 
            }
        }
        if (counter > 3 || c==0)  simbs+=3; //Se o counter for maior que 3 (e menor que 255) ou se o caracter for o caracter nulo então passa-se para o formato {0}1{símbolo}1{número_de_repetições}1
        else simbs += counter; //Se não se verificar nenhuma das condições anteriores então o número de símbolos é igual ao counter
        counter=1; //O counter volta a ser 1 para analisar o próximo bloco
}
return simbs; 
}

int rlecheck(unsigned char *buffer, int sizebuffer, unsigned long long total, int forcecompression){
    int ret = 0, simbs;
    float taxacomp;
    if (total>=1024)
    {
        simbs = simbcount (buffer, sizebuffer);
        taxacomp =  (sizebuffer-simbs);
        taxacomp /= sizebuffer;
        if (taxacomp > 0.05 || forcecompression) ret = 1;
        else printf ("Rle compression was not done because the compression rate of the first block < 0.05\n\n");
    }
    else
    {
         printf("RLE compression was not done because file size < 1Kbyte\n\n");
    }
return ret;
}

unsigned char *rle(unsigned char *buffer, int sizebuffer, int flaginit, char *filename){
    FILE *fp;
    if (flaginit) fp = fopen (filename, "wb");
    else fp = fopen (filename, "ab"); 
    int i, j=0, counter = 1;
    unsigned char *rlebuffer = malloc (sizebuffer* sizeof(unsigned char)*2);
    unsigned char c, zero=0, cont;
    for (i = 0; i < sizebuffer; i++)
    {
        c= *((buffer)+i);
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter > 255) {
            while (counter/255 > 0)
            {
                cont = 255;
                *(rlebuffer + j)=zero;
                *(rlebuffer + j+1)=c;
   float taxacomp;
                *(rlebuffer + j+2)=cont;
                j+=3;  
                counter -= 255; 
            }         
        }
        if (counter >3 || c==0){ 
                cont = counter;
                *(rlebuffer + j)=zero;
                *(rlebuffer + j+1)=c;
                *(rlebuffer + j+2)=cont;
                j+=3;  
        }
        else{
            for ( int z=0; z < counter; z++)
            {
                *(rlebuffer + j)=c;
                j++;
            } 
        }
        counter=1;
    }
    fwrite(rlebuffer, sizeof(unsigned char), j, fp);
    fclose(fp);
return rlebuffer;
}

struct tcomp_sizerleblocks split (char *filename, unsigned long block_size, long long n_blocks, unsigned long size_of_last_block, unsigned long long total, int forcecompression){
    struct tcomp_sizerleblocks ret;
    ret.taxa_comp=0;
    int bytesRead, flaginit=1, simbs=0, flagrle=0, flagend=0, *arrayrleblocks = array_rle_blocksize_zeros(n_blocks), bloco = 0;
    float taxacomp = 0; 
    char *filenamefreq = dotfreq(filename), *filenamerle = dotrle(filename), *filenamerlefreq = dotfreq(filenamerle);
    FILE *exsistingFile;
    exsistingFile = fopen(filename,"rb");        
    int workSize = total;
        while (workSize)
        {
            int chunkSize ;
            if (workSize<= block_size+1024)
            {
                chunkSize = workSize;
            }
            else
            {
                chunkSize= workSize > block_size ? block_size : workSize;
            }
            unsigned char *buffer = (unsigned char *)malloc(chunkSize);
            bytesRead = fread( buffer, sizeof(unsigned char), chunkSize, exsistingFile );
            workSize -= bytesRead;
            if (!workSize) flagend = 1;
            if (flaginit && rlecheck(buffer, chunkSize, total, forcecompression)){
                rle(buffer, chunkSize, flaginit, filenamerle);
                unsigned char *rlebuff = rle(buffer, chunkSize, flaginit, filenamerle);
                int rlesimbs = simbcount(buffer, chunkSize);
                simbs += simbcount(buffer, chunkSize);
                *(arrayrleblocks+bloco) = rlesimbs;
                freqs(rlebuff, rlesimbs, n_blocks, flaginit, filenamerlefreq, flagend, 0);
                flagrle = 1;
                free(rlebuff);
            }  
            else if (flagrle){
                unsigned char *rlebuff = rle(buffer, chunkSize, flaginit, filenamerle);
                int rlesimbs = simbcount(buffer, chunkSize);
                simbs += simbcount(buffer, chunkSize);
                *(arrayrleblocks+bloco) = rlesimbs;
                freqs(rlebuff, rlesimbs, n_blocks, flaginit, filenamerlefreq, flagend, 0);
                free(rlebuff);
            }
            freqs(buffer, chunkSize, n_blocks, flaginit, filenamefreq, flagend, 1);
            flaginit = 0;
            free(buffer);
            bloco++;
        }
if (flagrle){
taxacomp =  total;
taxacomp -= simbs;
taxacomp /= total;
ret.taxa_comp = taxacomp;
ret.size_rle_blocks = arrayrleblocks;
}

fclose(exsistingFile);
return ret;
}

struct sizes number_of_blocks (char *filename, unsigned long block_size){
    FILE *fp;
    struct sizes sizes;
    fp = fopen (filename, "rb");
    unsigned long long total;
    unsigned long size_of_last_block;
    long long n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    sizes.total = total;
    if (size_of_last_block < 1024 && n_blocks!=1) sizes.n_blocks = n_blocks--;
    else sizes.n_blocks = n_blocks;
    sizes.size_of_last_block = size_of_last_block;
    fclose (fp);
return sizes;
}

void moduloF(char *filename, unsigned long block_size, int forcecompression){
   clock_t start_time = clock();
   time_t now;
   time(&now);
   struct tm *data = localtime(&now);
   int day, month, year;
   day = data->tm_mday;            
   month = data->tm_mon + 1;       
   year = data->tm_year + 1900;
   unsigned long size_of_last_block;
   struct tcomp_sizerleblocks tcomp_rlebsizes;
   struct sizes sizes = number_of_blocks(filename, block_size);
   
   tcomp_rlebsizes = split(filename, block_size, sizes.n_blocks, sizes.size_of_last_block, sizes.total, forcecompression);

   clock_t stop_time = clock();
   double execution_time = (double)(stop_time-start_time)/CLOCKS_PER_SEC*1000;
   time_t t = time(NULL);

   printf ("Daniela Carvalho (a93224) e Eduardo Magalhães (a93301), MIEI-CD, %02d/%02d/%d\n", day, month, year);
   printf ("Módulo: f (cálculo das frequências dos símbolos)\n");
   printf ("Número de blocos: %lld\n", sizes.n_blocks); // preencher com return da funcao que divide em blocos
   if (sizes.n_blocks > 1) printf ("Tamanho dos blocos analisados no ficheiro original: %ld bytes/ .../ %ld bytes \n", block_size, sizes.size_of_last_block); // ex = 65536/ 2013 bytes
   else printf ("Tamanho dos blocos analisados no ficheiro original: %ld bytes\n", sizes.size_of_last_block);
   if (tcomp_rlebsizes.taxa_comp == 0)
   {
       printf ("Compressão RLE : %f%c de compressão -> não foi feita a compressão rle\n", tcomp_rlebsizes.taxa_comp*100, '%');
       printf ("Ficheiros gerados: %s\n", dotfreq(filename)); // ex = aaaaaa.txt.freq

   }
   else
   {
   printf ("Compressão RLE : %f%c de compressão\n", tcomp_rlebsizes.taxa_comp*100, '%'); // ex = aaaaaa.txt.rle (13% de compressão)
   printf ("Tamanho dos blocos analisados no ficheiro RLE: "); // ex = 57444/ 1620 bytes1
   for (int i = 0; i < sizes.n_blocks; i++)
   {
       printf("%d bytes", *(tcomp_rlebsizes.size_rle_blocks+i));
       if (i!=sizes.n_blocks-1) printf("/ ");
   }
   printf ("\n");
   printf ("Ficheiros gerados: %s | %s | %s\n", dotfreq(filename), dotfreq(dotrle(filename)), dotrle(filename)); // ex = aaaaaa.txt.freq, aaaaaa.txt.rle.freq 
   }   
   printf ("Tempo de execução do módulo (milissegundos) : %fms\n", execution_time);
}

int main(){
    unsigned long block_size= 8388608;//655360;
    char *filename = "bbb.zip";//"Shakespeare.txt";
    moduloF(filename, block_size, 1);
return 1;
}
