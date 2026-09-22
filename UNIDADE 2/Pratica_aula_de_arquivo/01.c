#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char matricula[20];
    char nome[50];
    float nota;
} Aluno;

int main() {
    FILE *alunos = fopen("alunos.txt", "w");

    if (alunos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("O arquivo tipo txt esta sendo criado.\n\n");

    Aluno *lista = (Aluno *)malloc(5 * sizeof(Aluno));

    if (lista == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(alunos);
        return 1;
    }

    for (int i = 0; i < 5; i++) {

        printf("Digite a matricula do aluno %d: ", i + 1);
        fgets(lista[i].matricula, sizeof(lista[i].matricula), stdin);

        printf("Digite o nome do aluno %d: ", i + 1);
        fgets(lista[i].nome, sizeof(lista[i].nome), stdin);

        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%f", &lista[i].nota);
        getchar();

        fprintf(alunos, "Matricula: %s", lista[i].matricula);
        fprintf(alunos, "Nome: %s", lista[i].nome);
        fprintf(alunos, "Nota: %.2f\n\n", lista[i].nota);
    }

    free(lista);
    fclose(alunos);

    printf("\nDados dos 5 alunos gravados com sucesso no arquivo alunos.txt!\n");

    return 0;
}