#include <stdio.h>
#include <stdlib.h>
//Função abrir arquivo
int main (void){
    FILE * arq;
    arq = fopen("arquivo.txt", "a");
        if(arq == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
        else{
            printf("Arquivo aberto com sucesso.\n");
        }

        //fputc('C', arq);
        //fputs("Hello World", arq);
        //fprintf(arq, "Hello World !!!");

    fclose(arq);
    return 0;
}