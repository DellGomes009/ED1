#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef struct {
    Vector2 pos;
    float velocidade;
    int vida;
    float dano;
} Jogador;

typedef struct {
    float dano;
    int alcance;
} DadosArma;

typedef struct {
    int cura;
} DadosPocao;

typedef union {
    DadosArma arma;
    DadosPocao pocao;
} DadosItem;

typedef enum {
    ITEM_ARMA,
    ITEM_POCAO
} TipoItem;

typedef struct {
    Vector2 pos;
    float raio;
    bool coletado;
    double tempoColeta;
    double tempoRespawn;
    TipoItem tipo;
    DadosItem dados;
} Item;

void reconfigurarItem(Item *it) {
    it->pos = (Vector2) { 
        (float)GetRandomValue(30, LARGURA_JANELA - 30), 
        (float)GetRandomValue(30, ALTURA_JANELA - 30) 
    };
    it->raio = 12.0f;
    it->coletado = false;
    it->tempoRespawn = 3.0; // Reaparece em 3 segundos
    it->tipo = (TipoItem) GetRandomValue(ITEM_ARMA, ITEM_POCAO);
    
    if (it->tipo == ITEM_ARMA) {
        it->dados.arma.dano = (float) GetRandomValue(2, 8);
        it->dados.arma.alcance = GetRandomValue(1, 3);
    } else {
        int chanceVeneno = GetRandomValue(0, 9);
        int valorCura = GetRandomValue(10, 30);

        if (chanceVeneno < 3) { // 30% de chance de vir envenenada
            it->dados.pocao.cura = -valorCura;
        } else {
            it->dados.pocao.cura = valorCura;
        }
    }
}

Item *criarItens(int quantidade) {
    Item *itens = (Item *) malloc(quantidade * sizeof(Item));
    for (int i = 0; i < quantidade; i++) {
        reconfigurarItem(&itens[i]);
    }
    return itens;
}

void aplicarItem(Jogador *j, Item *item) {
    switch (item->tipo) {
        case ITEM_ARMA:
            j->dano += item->dados.arma.dano;
            break;
        case ITEM_POCAO:
            j->vida += item->dados.pocao.cura;
            if (j->vida < 0) { // Garante vida mínima 0
                j->vida = 0;
            }
            break;
    }
    item->coletado = true;
    item->tempoColeta = GetTime();
}

void atualizarItens(Item *itens, int quantidade) {
    double tempoAtual = GetTime();
    for (int i = 0; i < quantidade; i++) {
        if (itens[i].coletado) {
            if (tempoAtual - itens[i].tempoColeta >= itens[i].tempoRespawn) {
                reconfigurarItem(&itens[i]);
            }
        }
    }
}

void desenharItem(Item *item) {
    if (item->coletado) return;
    
    Color cor = GRAY;
    if (item->tipo == ITEM_ARMA) {
        cor = RED;
    } else if (item->tipo == ITEM_POCAO) {
        if (item->dados.pocao.cura < 0) {
            cor = PURPLE; // Cor roxa para poções nocivas
        } else {
            cor = GREEN;
        }
    }

    DrawCircleV(item->pos, item->raio, cor);
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicio 2 - Pocao Envenenada com Respawn");
    SetTargetFPS(60);

    Jogador jogador = { {400, 300}, 4.0f, 100, 10.0f };
    int totalItens = 10;
    Item *itens = criarItens(totalItens);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) jogador.pos.x += jogador.velocidade;
        if (IsKeyDown(KEY_LEFT)) jogador.pos.x -= jogador.velocidade;
        if (IsKeyDown(KEY_UP)) jogador.pos.y -= jogador.velocidade;
        if (IsKeyDown(KEY_DOWN)) jogador.pos.y += jogador.velocidade;

        for (int i = 0; i < totalItens; i++) {
            if (!itens[i].coletado && CheckCollisionCircles(jogador.pos, 15, itens[i].pos, itens[i].raio)) {
                aplicarItem(&jogador, &itens[i]);
            }
        }

        // Atualiza a checagem de respawn a cada frame
        atualizarItens(itens, totalItens);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < totalItens; i++) {
            desenharItem(&itens[i]);
        }

        DrawCircleV(jogador.pos, 15, BLACK);
        DrawText(TextFormat("Vida: %d | Dano: %.1f", jogador.vida, jogador.dano), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    free(itens);
    CloseWindow();
    return 0;
}