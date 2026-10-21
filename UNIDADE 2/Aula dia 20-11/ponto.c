#include <stdio.h> //printf
#include <stdlib.h> //maloc free, exit
#include <math.h> //sqrt
#include "ponto.h"

struct ponto {
    float x;
    float y;
};

Ponto* pto_criar(float x, float y) {
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    if (p == NULL) {
        printf("Memoria insuficiente\n");
        exit(1);
    }
    p->x = x;
    p->y = y;
    return p;
}

void pto_liberar(Ponto* p) {
    free(p);
}

void pto_acessar(Ponto* p, float* x, float* y) {
    *x = p->x;
    *y = p->y;
}

void pto_atribuir(Ponto* p, float x, float y) {
    p->x = x;
    p->y = y;
}

float pto_distancia(Ponto* p1, Ponto* p2) {
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    return sqrt(dx * dx + dy * dy);
}

