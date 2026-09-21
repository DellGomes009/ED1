#include <stdio.h>
#include <stdlib.h>

int main(void){
    int i, j, linhas=3, colunas=3;

    int **matriz = (int**) malloc(linhas * sizeof(int*));
    if (matriz == NULL){
        printf("ERRO NA ALOCAÇÃO");
        exit(1);
    }
    for(i=0; i<linhas; i++){
        matriz[i] = (int*) malloc(colunas * sizeof(int));
        if (matriz[i] == NULL){
            printf("ERRO NA ALOCAÇÃO");
            exit(1);
        }
    }
    printf("MATRIZ ALOCADA\n");
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            matriz[i][j] = i * 3 + j;
            printf("%d \t", matriz[i][j]);
        }
        printf("\n");
    }
    for(i=0; i<linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}