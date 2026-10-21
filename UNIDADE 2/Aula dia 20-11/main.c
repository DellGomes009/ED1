#include <stdio.h>
#include "ponto.h"

int main (void) {
    Ponto* p = pto_criar(2.0, 1.0);
    Ponto* q = pto_criar(3.4, 2.1);
    float d = pto_distancia(p, q);
    printf("Distancia entre Pontos: %f\n", d);
    pto_liberar(q);
    pto_liberar(p);
    return 0;
}