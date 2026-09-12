#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define TOTAL_INIMIGOS 8
#define DANO_TIRO 25

typedef enum {
    INIMIGO_VIVO,
    INIMIGO_MORTO
} EstadoInimigo;

typedef struct {
    Vector2 pos;
    float raio;
    int vida;
    EstadoInimigo estado;
    double tempoMorte;
    double tempoRespawn;
} Inimigo;

void reconfigurarInimigo(Inimigo *ini) {
    ini->pos = (Vector2){
        (float)GetRandomValue(50, LARGURA_JANELA - 50),
        (float)GetRandomValue(50, ALTURA_JANELA - 50)
    };
    ini->raio = 15.0f;
    ini->vida = GetRandomValue(20, 100);
    ini->estado = INIMIGO_VIVO;
    ini->tempoRespawn = 4.0; // Revive após 4 segundos
}

void inicializarInimigos(Inimigo *vetor, int n) {
    for (int i = 0; i < n; i++) {
        reconfigurarInimigo(vetor + i);
    }
}

void atingirInimigo(Inimigo *inimigo, int dano) {
    if (inimigo == NULL || inimigo->estado == INIMIGO_MORTO) return;
    inimigo->vida -= dano;
    if (inimigo->vida <= 0) {
        inimigo->vida = 0;
        inimigo->estado = INIMIGO_MORTO;
        inimigo->tempoMorte = GetTime(); // Guarda momento em que foi eliminado
    }
}

void atualizarInimigos(Inimigo *vetor, int n) {
    double tempoAtual = GetTime();
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) {
            if (tempoAtual - ini->tempoMorte >= ini->tempoRespawn) {
                reconfigurarInimigo(ini);
            }
        }
    }
}

Inimigo *encontrarInimigoMaisFraco(Inimigo *vetor, int n) {
    Inimigo *maisFraco = NULL;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        if (maisFraco == NULL || ini->vida < maisFraco->vida) {
            maisFraco = ini;
        }
    }
    return maisFraco;
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicio 2 - Inimigo Mais Fraco com Respawn");
    SetTargetFPS(60);

    Vector2 jogador = { 400.0f, 300.0f };
    float velJogador = 4.0f;

    Inimigo *inimigos = (Inimigo *) malloc(TOTAL_INIMIGOS * sizeof(Inimigo));
    inicializarInimigos(inimigos, TOTAL_INIMIGOS);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) jogador.x += velJogador;
        if (IsKeyDown(KEY_LEFT)) jogador.x -= velJogador;
        if (IsKeyDown(KEY_UP)) jogador.y -= velJogador;
        if (IsKeyDown(KEY_DOWN)) jogador.y += velJogador;

        Inimigo *alvoMaisFraco = encontrarInimigoMaisFraco(inimigos, TOTAL_INIMIGOS);

        if (IsKeyPressed(KEY_SPACE)) {
            atingirInimigo(alvoMaisFraco, DANO_TIRO);
        }

        // Processa renascimento dos inimigos
        atualizarInimigos(inimigos, TOTAL_INIMIGOS);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < TOTAL_INIMIGOS; i++) {
            Inimigo *ini = (inimigos + i);
            if (ini->estado == INIMIGO_MORTO) {
                DrawCircleV(ini->pos, ini->raio, GRAY);
            } else {
                if (ini == alvoMaisFraco) {
                    DrawCircleLines((int)ini->pos.x, (int)ini->pos.y, ini->raio + 5, GOLD);
                }
                DrawCircleV(ini->pos, ini->raio, RED);
                DrawText(TextFormat("%d HP", ini->vida), (int)ini->pos.x - 15, (int)ini->pos.y - 30, 15, DARKGRAY);
            }
        }

        DrawCircleV(jogador, 15.0f, BLUE);

        DrawText("Controles:", 10, 10, 20, BLACK);
        DrawText("Espaco: Atacar inimigo MAIS FRACO", 10, 35, 18, DARKGRAY);

        EndDrawing();
    }

    free(inimigos);
    CloseWindow();
    return 0;
}