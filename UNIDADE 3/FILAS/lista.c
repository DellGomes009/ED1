#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct No {
    int dado;
    struct No *ant;
    struct No *prox;
} No;

struct Lista {
    No *inicio;
    No *fim;
    int tamanho;
};

Lista* criarLista(void) {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

int listaVazia(Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return 1;
    }
    return 0;
}

int tamanhoLista(Lista *l) {
    if (l == NULL) return 0;
    return l->tamanho;
}

int inserirFimLista(Lista *l, int valor) {
    if (l == NULL) return 0;

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->dado = valor;
    novo->prox = NULL;

    if (listaVazia(l)) {
        novo->ant = NULL;
        l->inicio = novo;
    } else {
        novo->ant = l->fim;   // Novo nó aponta para trás (antigo fim)
        l->fim->prox = novo;  // Antigo fim aponta para frente (novo nó)
    }

    l->fim = novo;
    l->tamanho++;
    return 1;
}

int removerInicioLista(Lista *l, int *valorRemovido) {
    if (listaVazia(l)) return 0;

    No *remover = l->inicio;
    if (valorRemovido != NULL) {
        *valorRemovido = remover->dado;
    }

    l->inicio = l->inicio->prox;

    if (l->inicio != NULL) {
        // O novo primeiro nó não tem ninguém antes dele
        l->inicio->ant = NULL;
    } else {
        // A lista ficou completamente vazia
        l->fim = NULL;
    }

    free(remover);
    l->tamanho--;
    return 1;
}

int consultarInicioLista(Lista *l, int *valor) {
    if (listaVazia(l)) return 0;

    if (valor != NULL) {
        *valor = l->inicio->dado;
    }
    return 1;
}

void imprimirLista(Lista *l) {
    if (listaVazia(l)) {
        printf("\n[Fila vazia]\n");
        return;
    }

    No *atual = l->inicio;
    printf("\nINICIO: NULL <- ");
    while (atual != NULL) {
        printf("[%d]", atual->dado);
        if (atual->prox != NULL) {
            printf(" <-> ");
        }
        atual = atual->prox;
    }
    printf(" -> NULL (FIM)\n");
}

void liberarLista(Lista *l) {
    if (l == NULL) return;

    while (!listaVazia(l)) {
        removerInicioLista(l, NULL);
    }
    free(l);
}