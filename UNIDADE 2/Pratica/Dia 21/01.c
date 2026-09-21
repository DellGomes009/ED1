#include <stdio.h>
#include <stdlib.h>
//Função abrir arquivo
int main (void){
    FILE * arq;
    //int c;
    char linha[100];
    arq = fopen("arquivo.txt", "r");
        if(arq == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }
        else{
            printf("Arquivo aberto com sucesso.\n");
        }

        //feof
        while(!feof(arq)){
            fscanf(arq, "%s", linha);
            printf("A linha lida foi: %s\n", linha);
        }


        //fputc('C', arq);
        //fputs("Hello World", arq);
        //fprintf(arq, "Hello World !!!");

       //c = fgetc(arq);
       //printf("O caractere lido foi: %c\n", c);

        //fgets(linha, 100, arq);
        fscanf(arq, "%s", linha);
        printf("A linha lida foi: %s\n", linha);
   
   
        fclose(arq);

    return 0;
}