#include "moduloF.h"

#define E_BAD_DESTINATION -1
/*
  if ( !outputFile )
        {
            printf( "File %s cannot be opened for writing\n", filename );
            return E_BAD_DESTINATION; 
        }*/

void createfreqfile(long long n_blocks){
    FILE *fp;
    fp = fopen ("exaaa.txt.freq", "wb");
    fprintf(fp, "@N@%lld@", n_blocks);
    fclose(fp);
}

void freqsoriginal(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, int onlyoneblock){
    FILE *orifreqs;
    if (flaginit) createfreqfile(n_blocks);
    orifreqs = fopen ("exaaa.txt.freq", "ab");  
    fprintf(orifreqs, "%d@", sizebuffer);
    int i, j, counter=0, counterant;
    for (j=0; j<256; j++){
        for (i=0; i<sizebuffer; i++){
            if (*(buffer+i) == j) counter++;
        }
    if (j==0){
       counterant = counter;
       fprintf(orifreqs, "%d;",counter);
    }
    else if (counterant==counter){
        if(j!=255) fprintf(orifreqs, ";");
        counterant=counter;
    }
    else{ 
        fprintf(orifreqs, "%d", counter);
        if(j!=255) fprintf(orifreqs, ";");
        counterant=counter;
    }
    //if (counter>0) printf("unsigned char nº%d => %d ocorrências\n", j, counter);
    counter=0;
    }
    fprintf(orifreqs, "@");
    if(!flaginit || onlyoneblock) fprintf(orifreqs, "0");
    fclose(orifreqs);
}

int rlecheck(char *buffer, int sizebuffer){
    int i, counter=1, simbs=0, ret = 0;
    float taxacomp;
    for (i = 0; i<sizebuffer; i++)
    {
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter >= 3)  simbs+=3;
        else simbs += counter;
        counter=1;
}
//    printf ("simbs=%d\n", simbs);
    taxacomp =  (sizebuffer-simbs);
    taxacomp /= sizebuffer;
   // printf ("taxa_comp = %f\n",  taxacomp);
    if (taxacomp > 0.05) ret = 1;
    //printf("ret=%d\n", ret);
//fclose (rlecheck);
return ret;
}

int rlecompressing(char *buffer , int flaginit, int sizebuffer, int simbs){
      FILE *rlecheck;
    rlecheck = fopen("exaaa.txt.rle", "wb");
    int i, counter=1;
    unsigned char c, zero=0;
    for (i = 0; i<sizebuffer; i++)
    {
        c= *((buffer)+i);
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter >3){ 
            fprintf (rlecheck, "%c%c%c", zero, c, counter);
            simbs+=3;
        }
        else if (counter == 3){ 
            fprintf (rlecheck, "%c%c%c", c, c, c);
            simbs+=3;
        }
        else if (counter == 2) {
            fprintf (rlecheck, "%c%c", c, c);
            simbs+=2;
        }
        else{
            fprintf (rlecheck, "%c", c);
            simbs++;
        }
        counter=1;
}
fclose (rlecheck);
return simbs;
}

float split (char *filename, unsigned long block_size) {
    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block;
    int bytesRead, flaginit=1, simbs=0; 
    float taxacomp; 
    FILE *exsistingFile;
    exsistingFile = fopen(filename,"rb"); 
    int i = 1, flag = 1, onlyoneblock, flagrle;
    n_blocks = fsize(exsistingFile, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    if (n_blocks==1) onlyoneblock = 1;
    else onlyoneblock = 0;
    do
    {   
        int workSize = total;
        while (workSize)
        {
            int chunkSize = workSize > block_size ? block_size : workSize;
            unsigned char * buffer = (unsigned char *)malloc(chunkSize);
            bytesRead = fread( buffer, sizeof( unsigned char ), chunkSize, exsistingFile );
            workSize -= bytesRead;
            if (bytesRead == 0)
            {
                printf("The reading has finished or the file has no data inside\n");
                return 0;
            } 
            if (flaginit && rlecheck(buffer, chunkSize)){
               simbs += rlecompressing(buffer, flaginit, chunkSize, simbs);
               flagrle = 1;
            }
            else if (flagrle) simbs += rlecompressing (buffer, flaginit, chunkSize, simbs);
            freqsoriginal(buffer, chunkSize, n_blocks, flaginit, onlyoneblock);
            flaginit = 0;
        }
        flag = 0;
} while ( bytesRead > 0 && flag);

taxacomp =  (total-simbs);
taxacomp /= total;

fclose(exsistingFile);
return taxacomp;
}

long long number_of_blocks (char *filename, unsigned long block_size){
    FILE *fp;
    fp = fopen (filename, "rb");
    unsigned long size_of_last_block;
    long long n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    fclose (fp);
return n_blocks;
}


int main(){
   time_t now;
   time(&now);
   struct tm *data = localtime(&now);
   int day, month, year;
   day = data->tm_mday;            
   month = data->tm_mon + 1;       
   year = data->tm_year + 1900;;
   unsigned long block_size=64000;
  
   char *filename = "aaa.txt";

   long long n_blocks = number_of_blocks(filename, block_size);
   float taxacomp;
  

   

   taxacomp = split (filename, block_size)*100;

   printf ("Daniela Carvalho (a93224) e Eduardo Magalhães (a93301), MIEI-CD, %02d/%02d/%d\n", day, month, year);
   printf ("Módulo: f (cálculo das frequências dos símbolos)\n");
   printf ("Número de blocos: %lld\n", n_blocks); // preencher com return da funcao que divide em blocos
   printf ("Tamanho dos blocos analisados no ficheiro original: \n"); // ex = 65536/ 2013 bytes
   printf ("Compressão RLE : %f%c de compressão\n", taxacomp, '%'); // ex = aaaaaa.txt.rle (13% de compressão)
   printf ("Tamanho dos blocos analisados no ficheiro RLE: \n"); // ex = 57444/ 1620 bytes
   printf ("Tempo de execução do módulo (milissegundos) : \n");
   printf ("Ficheiros gerados: \n"); // ex = aaaaaa.txt.freq, aaaaaa.txt.rle.freq 
   return 0;
}