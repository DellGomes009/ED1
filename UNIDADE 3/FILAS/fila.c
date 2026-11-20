#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"

struct Fila {
    Lista *lista;
};

Fila* criarFila(void) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->lista = criarLista();
        if (f->lista == NULL) {
            free(f);
            return NULL;
        }
    }
    return f;
}

int filaVazia(Fila *f) {
    if (f == NULL) return 1;
    return listaVazia(f->lista);
}

int tamanhoFila(Fila *f) {
    if (f == NULL) return 0;
    return tamanhoLista(f->lista);
}

int enfileirar(Fila *f, int valor) {
    if (f == NULL) return 0;
    return inserirFimLista(f->lista, valor);
}

int desenfileirar(Fila *f, int *valorRemovido) {
    if (f == NULL) return 0;
    return removerInicioLista(f->lista, valorRemovido);
}

int consultarInicioFila(Fila *f, int *valor) {
    if (f == NULL) return 0;
    return consultarInicioLista(f->lista, valor);
}

void imprimirFila(Fila *f) {
    if (f == NULL) return;
    imprimirLista(f->lista);
}

void liberarFila(Fila *f) {
    if (f == NULL) return;
    liberarLista(f->lista);
    free(f);
}