#include "moduloF.h"

int *arrayazeros(){
    int *freqs = malloc (255* sizeof(int));
    for (int i = 0; i < 256; i++)
    {
        *(freqs+i) = 0;
    } 
return freqs;
}

int *array_rle_blocksize_zeros(long long n_blocks){
    int *rle = malloc(n_blocks*sizeof(int));
    for (int i = 0; i < n_blocks; i++)
    {
        *(rle+i) = 0;
    }
return rle; 
}

char *dotfreq(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".freq");
return newfilename;
}

char *dotrle(char *filename){
    int length = strlen(filename) *2;
    char *newfilename = malloc(length* sizeof(char));
    strcpy (newfilename, filename);
    strcat (newfilename, ".rle");
return newfilename;
}

void freqs(unsigned char *buffer, int sizebuffer, long long n_blocks, int flaginit, char *filename, int flagend, int flagoriginal){
    int *size_blocks;
    FILE *fp;
    if (flaginit){
        fp = fopen (filename, "wb");
        if (flagoriginal) fprintf(fp, "@N@%lld@", n_blocks);
        else fprintf (fp, "@R@%lld@", n_blocks);
    }
    else fp = fopen (filename, "ab");  
    fprintf(fp, "%d@", sizebuffer);
    int i, j, z, counterant, *freqs = arrayazeros();
        for (i=0; i<sizebuffer; i++){
            z = *(buffer+i);
            *(freqs+z)+=1;
        }
    for ( int y = 0; y<256; y++)
    {
        int counter = *(freqs+y);
        if (y==0){
            counterant = counter;
            fprintf(fp, "%d;",*(freqs+y));
        }
        else if (counterant==counter){
                 if(y!=255) fprintf(fp, ";");
                 counterant=counter;
        }
        else{ 
            fprintf(fp, "%d", counter);
            if(y!=255) fprintf(fp, ";");
            counterant=counter;
    }
    }
    fprintf(fp, "@");
    if(flagend) fprintf(fp, "0");
    fclose(fp);
}

int simbcount(unsigned char *buffer, int sizebuffer){
    int i, counter=1, simbs=0;
    unsigned char c;
    for (i = 0; i<sizebuffer; i++)
    {
        c= *((buffer)+i);
        while (*((buffer)+i) == *((buffer)+i+1))
        {
            counter++;
            i++;
        }
        if (counter>255){
            while (counter/255 > 0){
                simbs+=3;
                counter-=255;
            }
        }
        if (counter > 3 || c==0)  simbs+=3;
        else simbs += counter;
        counter=1;
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