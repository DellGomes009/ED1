#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define QUANTIDADE_MOEDAS 10

typedef enum {
    MOEDA_BRONZE,
    MOEDA_PRATA,
    MOEDA_OURO
} TipoMoeda;

typedef struct {
    Vector2 pos;
    float raio;
    TipoMoeda tipo;
    int valor;
    bool coletada;
    float tempoColeta;
} Moeda;

typedef struct {
    Vector2 pos;
    float raio;
    int pontuacao;
} Jogador;

Color corDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:
            return (Color){160, 90, 40, 255};

        case MOEDA_PRATA:
            return (Color){190, 190, 190, 255};

        case MOEDA_OURO:
            return GOLD;

        default:
            return WHITE;
    }
}

int valorDaMoeda(TipoMoeda tipo) {
    switch (tipo) {
        case MOEDA_BRONZE:
            return 5;

        case MOEDA_PRATA:
            return 10;

        case MOEDA_OURO:
            return 25;

        default:
            return 0;
    }
}

Vector2 novaPosicao() {
    return (Vector2){
        GetRandomValue(30, LARGURA_JANELA - 30),
        GetRandomValue(30, ALTURA_JANELA - 30)
    };
}

Moeda *criarMoedas(int quantidade) {
    Moeda *moedas = malloc(quantidade * sizeof(Moeda));

    if (moedas == NULL) {
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {
        Moeda *m = &moedas[i];

        m->pos = novaPosicao();
        m->raio = 10.0f;

        m->tipo = (TipoMoeda)GetRandomValue(
            MOEDA_BRONZE,
            MOEDA_OURO
        );

        m->valor = valorDaMoeda(m->tipo);
        m->coletada = false;
        m->tempoColeta = 0.0f;
    }

    return moedas;
}

bool tentarColetar(
    Moeda *m,
    Vector2 posJogador,
    float raioJogador
) {
    if (m->coletada) {
        return false;
    }

    float dx = m->pos.x - posJogador.x;
    float dy = m->pos.y - posJogador.y;

    float distancia = dx * dx + dy * dy;

    float somaRaios =
        (m->raio + raioJogador) *
        (m->raio + raioJogador);

    if (distancia <= somaRaios) {
        m->coletada = true;
        m->tempoColeta = GetTime();

        return true;
    }

    return false;
}

void desenharMoeda(Moeda *m) {
    if (!m->coletada) {
        DrawCircleV(
            m->pos,
            m->raio,
            corDaMoeda(m->tipo)
        );
    }
}

int main(void) {
    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Exercicio 1 - Moedas"
    );

    SetTargetFPS(60);

    Moeda *moedas = criarMoedas(QUANTIDADE_MOEDAS);

    if (moedas == NULL) {
        CloseWindow();
        return 1;
    }

    Jogador jogador;

    jogador.pos = (Vector2){
        LARGURA_JANELA / 2.0f,
        ALTURA_JANELA / 2.0f
    };

    jogador.raio = 15.0f;
    jogador.pontuacao = 0;

    while (!WindowShouldClose()) {

        //Movimento do jogador
        if (IsKeyDown(KEY_RIGHT))
            jogador.pos.x += 3;

        if (IsKeyDown(KEY_LEFT))
            jogador.pos.x -= 3;

        if (IsKeyDown(KEY_UP))
            jogador.pos.y -= 3;

        if (IsKeyDown(KEY_DOWN))
            jogador.pos.y += 3;

        //Limites da tela
        if (jogador.pos.x < jogador.raio)
            jogador.pos.x = jogador.raio;

        if (jogador.pos.x > LARGURA_JANELA - jogador.raio)
            jogador.pos.x = LARGURA_JANELA - jogador.raio;

        if (jogador.pos.y < jogador.raio)
            jogador.pos.y = jogador.raio;

        if (jogador.pos.y > ALTURA_JANELA - jogador.raio)
            jogador.pos.y = ALTURA_JANELA - jogador.raio;

        /* Verifica moedas */
        for (int i = 0; i < QUANTIDADE_MOEDAS; i++) {

            Moeda *m = &moedas[i];

            // Tenta coletar
            if (tentarColetar(
                    m,
                    jogador.pos,
                    jogador.raio
                )) {

                jogador.pontuacao += m->valor;
            }

            //Reaparece depois de 3 segundos
            if (m->coletada &&
                GetTime() - m->tempoColeta >= 3.0) {

                m->pos = novaPosicao();
                m->coletada = false;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        /* Desenha moedas */
        for (int i = 0; i < QUANTIDADE_MOEDAS; i++) {
            desenharMoeda(&moedas[i]);
        }

        //Desenha jogador
        DrawCircleV(
            jogador.pos,
            jogador.raio,
            BLUE
        );

        DrawText(
            TextFormat(
                "Pontuacao: %d",
                jogador.pontuacao
            ),
            10,
            10,
            20,
            BLACK
        );

        DrawText(
            "Use as setas para mover",
            10,
            35,
            18,
            DARKGRAY
        );

        EndDrawing();
    }

    free(moedas);

    CloseWindow();

    return 0;
}