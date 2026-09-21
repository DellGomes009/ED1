#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

typedef struct {
    Vector2 pos;
    float velocidade;
    int vida;
    float dano;
    int armadura;
} Jogador;

typedef struct {
    float dano;
    int alcance;
} DadosArma;

typedef struct {
    int cura;
} DadosPocao;

typedef struct {
    int absorcao;
} DadosEscudo;

typedef union {
    DadosArma arma;
    DadosPocao pocao;
    DadosEscudo escudo;
} DadosItem;

typedef enum {
    ITEM_ARMA,
    ITEM_POCAO,
    ITEM_ESCUDO
} TipoItem;

typedef struct {
    Vector2 pos;
    float raio;
    bool coletado;
    double tempoColeta;  // Registra o tempo em que foi coletado
    double tempoRespawn; // Tempo necessário para reaparecer (em segundos)
    TipoItem tipo;
    DadosItem dados;
} Item;

// Configura os dados de um item específico (usado na criação e no respawn)
void reconfigurarItem(Item *it) {
    it->pos = (Vector2) { 
        (float)GetRandomValue(30, LARGURA_JANELA - 30), 
        (float)GetRandomValue(30, ALTURA_JANELA - 30) 
    };
    it->raio = 12.0f;
    it->coletado = false;
    it->tempoRespawn = 3.0; // Reaparece em 3 segundos
    it->tipo = (TipoItem) GetRandomValue(ITEM_ARMA, ITEM_ESCUDO);
    
    if (it->tipo == ITEM_ARMA) {
        it->dados.arma.dano = (float) GetRandomValue(2, 8);
        it->dados.arma.alcance = GetRandomValue(1, 3);
    } else if (it->tipo == ITEM_POCAO) {
        it->dados.pocao.cura = GetRandomValue(10, 30);
    } else if (it->tipo == ITEM_ESCUDO) {
        it->dados.escudo.absorcao = GetRandomValue(5, 15);
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
            break;
        case ITEM_ESCUDO:
            j->armadura += item->dados.escudo.absorcao;
            break;
    }
    item->coletado = true;
    item->tempoColeta = GetTime(); // Guarda o momento exato do impacto
}

// Verifica se os itens coletados já cumpriram o tempo para reaparecer
void atualizarItens(Item *itens, int quantidade) {
    double tempoAtual = GetTime();
    for (int i = 0; i < quantidade; i++) {
        if (itens[i].coletado) {
            if (tempoAtual - itens[i].tempoColeta >= itens[i].tempoRespawn) {
                reconfigurarItem(&itens[i]); // Gera nova posição e tipo ao restaurar
            }
        }
    }
}

void desenharItem(Item *item) {
    if (item->coletado) return;
    
    Color cor = GRAY;
    if (item->tipo == ITEM_ARMA) cor = RED;
    else if (item->tipo == ITEM_POCAO) cor = GREEN;
    else if (item->tipo == ITEM_ESCUDO) cor = BLUE;

    DrawCircleV(item->pos, item->raio, cor);
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicio 1 - Escudo com Respawn");
    SetTargetFPS(60);

    Jogador jogador = { {400, 300}, 4.0f, 100, 10.0f, 0 };
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

        // Processa o timer de restauração dos itens
        atualizarItens(itens, totalItens);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < totalItens; i++) {
            desenharItem(&itens[i]);
        }

        DrawCircleV(jogador.pos, 15, BLACK);
        DrawText(TextFormat("Vida: %d | Dano: %.1f | Armadura: %d", jogador.vida, jogador.dano, jogador.armadura), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    free(itens);
    CloseWindow();
    return 0;
}