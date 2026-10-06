#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h" // Inclua a biblioteca da Raylib

// 1. A FUNÇÃO DE DESENHAR FICA AQUI FORA, ANTES DA MAIN
void desenharVetor(int vetor[], int N) {
    int larguraTela = GetScreenWidth();
    int alturaTela = GetScreenHeight();

    int larguraBarra = larguraTela / N;

    for (int i = 0; i < N; i++) {
        // Multiplica o valor por 3 para a barra ter uma altura visível
        int alturaBarra = vetor[i] * 3; 

        int posX = i * larguraBarra;
        int posY = alturaTela - alturaBarra; // Alinha no rodapé

        // Desenha a barra azul
        DrawRectangle(posX, posY, larguraBarra - 2, alturaBarra, BLUE);

        // Desenha o número no topo da barra
        DrawText(TextFormat("%d", vetor[i]), posX + (larguraBarra / 4), posY - 20, 15, BLACK);
    }
}

int main() {
    int N;
    int i;
    srand(time(NULL));

    // --- SUA LÓGICA DE GERAR O ARQUIVO ---
    FILE *arq = fopen("Dados10.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    fprintf(arq, "10\n");
    for (int a = 0; a < 10; a++) {
        fprintf(arq, "%d ", rand() % 100);
    }
    fclose(arq);
    
    // --- SUA LÓGICA DE LER O ARQUIVO ---
    arq = fopen("Dados10.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return 1;
    }

    fscanf(arq, "%d", &N);

    int *vetor = (int *) malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        fclose(arq);
        return 1;
    }

    for (i = 0; i < N; i++) {
        fscanf(arq, "%d", &vetor[i]);
    }
    fclose(arq);

    // =======================================================
    // 2. INÍCIO DA RAYLIB (Desenha os números lidos do arquivo)
    // =======================================================
    InitWindow(800, 450, "Passo 1 - Vetor do Arquivo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Chama a função que desenha as barras do vetor lido
            desenharVetor(vetor, N);

        EndDrawing();
    }

    CloseWindow();

    // Libera a memória antes de encerrar
    free(vetor);

    return 0;
}