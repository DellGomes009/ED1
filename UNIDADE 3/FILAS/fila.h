#ifndef FILA_H
#define FILA_H

typedef struct Fila Fila;

Fila* criarFila(void);
void liberarFila(Fila *f);

int filaVazia(Fila *f);
int tamanhoFila(Fila *f);

int enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f, int *valorRemovido);
int consultarInicioFila(Fila *f, int *valor);
void imprimirFila(Fila *f);

#endif