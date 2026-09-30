#include <stdio.h>
#include "conversor.h"

int main(void){

    float metros;
    printf("Digite a quantidade em metros: ");
    scanf("%f", &metros);
    printf("Quantidade em centímetros: %f\n", converter_metros_para_centimetros(metros));
    printf("Quantidade em quilômetros: %f\n", converter_metros_para_quilometros(metros));
    printf("Quantidade em milímetros: %f\n", converter_metros_para_milimetros(metros));
    return 0;
}