#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Fruta conforme solicitado
typedef struct {
    char nome[50];
    float preco;
} Fruta;

int main() {
    FILE *arquivo;
    Fruta *frutas = NULL;
    int capacidade = 2; // Capacidade inicial do vetor dinâmico
    int total = 0;      // Contador de frutas cadastradas
    char opcao;

    // Aloca memória inicial para o vetor de frutas
    frutas = (Fruta *) malloc(capacidade * sizeof(Fruta));
    if (frutas == NULL) {
        printf("Erro ao alocar memoria inicial!\n");
        return 1;
    }

    printf("--- Cadastro de Frutas com Realocacao ---\n");

    do {
        // Se o número de frutas atingir a capacidade atual, redimensiona o vetor usando realloc
        if (total >= capacidade) {
            capacidade *= 2; // Dobra a capacidade
            Fruta *temp = (Fruta *) realloc(frutas, capacidade * sizeof(Fruta));
            if (temp == NULL) {
                printf("Erro ao realocar memoria!\n");
                free(frutas);
                return 1;
            }
            frutas = temp;
        }

        // Solicita o nome da fruta
        printf("Digite o nome da fruta: ");
        scanf(" %[^\n]s", frutas[total].nome);

        // Solicita o preço da fruta
        printf("Digite o preco da fruta: ");
        scanf("%f", &frutas[total].preco);

        total++;

        // Pergunta se o usuário deseja continuar cadastrando
        printf("Deseja cadastrar outra fruta? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    // Abre o arquivo "frutas.txt" no modo de escrita
    arquivo = fopen("frutas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        free(frutas);
        return 1;
    }

    // Salva todas as frutas cadastradas no arquivo de texto
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s, %.2f\n", frutas[i].nome, frutas[i].preco);
    }

    // Fecha o arquivo e libera a memória alocada dinamicamente
    fclose(arquivo);
    free(frutas);

    printf("Cadastro encerrado. Os dados foram salvos em 'frutas.txt'.\n");

    return 0;
}