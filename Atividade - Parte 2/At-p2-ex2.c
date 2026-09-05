#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define QUANTIDADE_MOEDAS 10

typedef enum {
    MOEDA_BRONZE,
    MOEDA_PRATA,
    MOEDA_OURO,
    MOEDA_DIAMANTE
} TipoMoeda;

typedef struct {
    Vector2 pos;
    float raio;
    TipoMoeda tipo;
    int valor;
    bool coletada;
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

        case MOEDA_DIAMANTE:
            return (Color){0, 220, 255, 255};

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

        case MOEDA_DIAMANTE:
            return 50;

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

TipoMoeda sortearTipoMoeda() {
    //0 = diamante, 1 a 3 = ouro, 4 a 6 = prata, 7 a 9 = bronze, Assim, o diamante tem 10% de chance.

    int sorteio = GetRandomValue(0, 9);

    if (sorteio == 0) {
        return MOEDA_DIAMANTE;
    }

    if (sorteio <= 3) {
        return MOEDA_OURO;
    }

    if (sorteio <= 6) {
        return MOEDA_PRATA;
    }

    return MOEDA_BRONZE;
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

        m->tipo = sortearTipoMoeda();

        m->valor = valorDaMoeda(m->tipo);

        m->coletada = false;
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

        return true;
    }

    return false;
}

void desenharMoeda(Moeda *m) {
    if (m->coletada) {
        return;
    }

    DrawCircleV(
        m->pos,
        m->raio,
        corDaMoeda(m->tipo)
    );

    // Diamante é desenhado como um losango
    if (m->tipo == MOEDA_DIAMANTE) {

        Vector2 cima = {
            m->pos.x,
            m->pos.y - m->raio
        };

        Vector2 direita = {
            m->pos.x + m->raio,
            m->pos.y
        };

        Vector2 baixo = {
            m->pos.x,
            m->pos.y + m->raio
        };

        Vector2 esquerda = {
            m->pos.x - m->raio,
            m->pos.y
        };

        DrawTriangle(
            cima,
            esquerda,
            direita,
            corDaMoeda(m->tipo)
        );

        DrawTriangle(
            baixo,
            esquerda,
            direita,
            corDaMoeda(m->tipo)
        );
    }
}

int main(void) {
    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Exercicio 2 - Moeda Diamante"
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

        //Movimento
        if (IsKeyDown(KEY_RIGHT))
            jogador.pos.x += 3;

        if (IsKeyDown(KEY_LEFT))
            jogador.pos.x -= 3;

        if (IsKeyDown(KEY_UP))
            jogador.pos.y -= 3;

        if (IsKeyDown(KEY_DOWN))
            jogador.pos.y += 3;

        //Limites
        if (jogador.pos.x < jogador.raio)
            jogador.pos.x = jogador.raio;

        if (jogador.pos.x > LARGURA_JANELA - jogador.raio)
            jogador.pos.x = LARGURA_JANELA - jogador.raio;

        if (jogador.pos.y < jogador.raio)
            jogador.pos.y = jogador.raio;

        if (jogador.pos.y > ALTURA_JANELA - jogador.raio)
            jogador.pos.y = ALTURA_JANELA - jogador.raio;

        //Coleta
        for (int i = 0; i < QUANTIDADE_MOEDAS; i++) {

            if (tentarColetar(
                    &moedas[i],
                    jogador.pos,
                    jogador.raio
                )) {

                jogador.pontuacao += moedas[i].valor;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        //Moedas
        for (int i = 0; i < QUANTIDADE_MOEDAS; i++) {
            desenharMoeda(&moedas[i]);
        }

        //Jogador
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
            "Setas: mover jogador",
            10,
            35,
            18,
            DARKGRAY
        );

        DrawText(
            "Diamante = 50 pontos",
            10,
            60,
            18,
            DARKBLUE
        );

        EndDrawing();
    }

    free(moedas);

    CloseWindow();

    return 0;
}