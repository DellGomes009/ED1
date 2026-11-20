#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void exibirMenu(void) {
    printf("\n==============================\n");
    printf("   MENU - FILA COM LISTA\n");
    printf("==============================\n");
    printf("1. Enfileirar (Inserir)\n");
    printf("2. Desenfileirar (Remover)\n");
    printf("3. Consultar inicio\n");
    printf("4. Imprimir fila\n");
    printf("5. Ver tamanho e status\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Fila *fila = criarFila();
    if (fila == NULL) {
        printf("Erro critico: falha ao alocar memoria.\n");
        return 1;
    }

    int opcao, valor;

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor inteiro a inserir: ");
                if (scanf("%d", &valor) == 1) {
                    if (enfileirar(fila, valor)) {
                        printf("Sucesso: %d entrou no fim da fila.\n", valor);
                    } else {
                        printf("Erro: nao foi possivel alocar memoria.\n");
                    }
                } else {
                    while (getchar() != '\n');
                    printf("Entrada invalida.\n");
                }
                break;

            case 2:
                if (desenfileirar(fila, &valor)) {
                    printf("Removido do inicio: %d\n", valor);
                } else {
                    printf("Aviso: a fila ja esta vazia.\n");
                }
                break;

            case 3:
                if (consultarInicioFila(fila, &valor)) {
                    printf("Primeiro elemento da fila: %d\n", valor);
                } else {
                    printf("Aviso: a fila esta vazia.\n");
                }
                break;

            case 4:
                imprimirFila(fila);
                break;

            case 5:
                if (filaVazia(fila)) {
                    printf("Status: Fila VAZIA (0 elementos).\n");
                } else {
                    printf("Status: Fila ATIVA (%d elemento(s)).\n", tamanhoFila(fila));
                }
                break;

            case 0:
                printf("Liberando memoria e encerrando...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    liberarFila(fila);
    return 0;
}