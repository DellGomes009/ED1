#include <stdio.h>
#include "calculadora.h"

int main(void){

int num1, num2;
    printf("Digite os dois números: ");
    scanf("%d %d", &num1, &num2);

    int soma_resultado = soma(num1, num2);
    printf("Soma: %d\n", soma_resultado);


    return 0;
}