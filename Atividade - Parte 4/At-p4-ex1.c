#include "raylib.h"
#include <stdlib.h>
#include <math.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define TOTAL_INIMIGOS 8
#define DANO_TIRO 25
#define VIDA_MAXIMA 60

typedef enum {
    INIMIGO_VIVO,
    INIMIGO_MORTO
} EstadoInimigo;

typedef struct {
    Vector2 pos;
    float raio;
    int vida;
    EstadoInimigo estado;
    double tempoMorte;   // Registra o tempo em que o inimigo morreu
    double tempoRespawn; // Tempo para reaparecer (em segundos)
} Inimigo;

// Configura ou restaura um inimigo no vetor
void reconfigurarInimigo(Inimigo *ini) {
    ini->pos = (Vector2){
        (float)GetRandomValue(50, LARGURA_JANELA - 50),
        (float)GetRandomValue(50, ALTURA_JANELA - 50)
    };
    ini->raio = 15.0f;
    ini->vida = VIDA_MAXIMA;
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
        inimigo->tempoMorte = GetTime(); // Guarda o momento do abate
    }
}

// Atualiza o estado dos inimigos mortos, revivendo-os após o tempo estipulado
void atualizarInimigos(Inimigo *vetor, int n) {
    double tempoAtual = GetTime();
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) {
            if (tempoAtual - ini->tempoMorte >= ini->tempoRespawn) {
                reconfigurarInimigo(ini); // Restaura vida e gera nova posição
            }
        }
    }
}

Inimigo *encontrarInimigoMaisProximo(Inimigo *vetor, int n, Vector2 posJogador) {
    Inimigo *maisProximo = NULL;
    float menorDistancia = 0.0f;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        float dx = ini->pos.x - posJogador.x;
        float dy = ini->pos.y - posJogador.y;
        float distancia = sqrtf(dx * dx + dy * dy);

        if (maisProximo == NULL || distancia < menorDistancia) {
            maisProximo = ini;
            menorDistancia = distancia;
        }
    }
    return maisProximo;
}

void curarTodos(Inimigo *vetor, int n, int cura) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        ini->vida += cura;
        if (ini->vida > VIDA_MAXIMA) {
            ini->vida = VIDA_MAXIMA;
        }
    }
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicio 1 - Cura em Area com Respawn");
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

        if (IsKeyPressed(KEY_SPACE)) {
            Inimigo *alvo = encontrarInimigoMaisProximo(inimigos, TOTAL_INIMIGOS, jogador);
            atingirInimigo(alvo, DANO_TIRO);
        }

        if (IsKeyPressed(KEY_C)) {
            curarTodos(inimigos, TOTAL_INIMIGOS, 20);
        }

        // Checa se algum inimigo morto deve ser revivido
        atualizarInimigos(inimigos, TOTAL_INIMIGOS);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < TOTAL_INIMIGOS; i++) {
            Inimigo *ini = (inimigos + i);
            if (ini->estado == INIMIGO_MORTO) {
                DrawCircleV(ini->pos, ini->raio, GRAY);
            } else {
                DrawCircleV(ini->pos, ini->raio, RED);
                DrawText(TextFormat("%d HP", ini->vida), (int)ini->pos.x - 15, (int)ini->pos.y - 30, 15, DARKGRAY);
            }
        }

        DrawCircleV(jogador, 15.0f, BLUE);

        DrawText("Controles:", 10, 10, 20, BLACK);
        DrawText("Espaco: Atacar mais proximo", 10, 35, 18, DARKGRAY);
        DrawText("Tecla C: Curar vivos", 10, 55, 18, DARKGREEN);

        EndDrawing();
    }

    free(inimigos);
    CloseWindow();
    return 0;
}