#include <stdio.h>
#include "geometria.h"

int main(void){

    float raio, base, altura;
    printf("Digite o raio do círculo: ");
    scanf("%f", &raio);
    printf("Área do círculo: %f\n", calcular_area_circulo(raio));

    printf("Digite a base e a altura do triângulo: ");
    scanf("%f %f", &base, &altura);
    printf("Área do triângulo: %f\n", calcular_area_triangulo(base, altura));

    printf("Digite a base e a altura do retângulo: ");
    scanf("%f %f", &base, &altura);
    printf("Área do retângulo: %f\n", calcular_area_retangulo(base, altura));

    return 0;
}