#include "colisao.h"
#include "configs.h"
#include <string.h>
#include <stdlib.h>

int colideHitboxExterna(struct Lixo lixo1, struct Lixo lixo2) {
    int margem = 60;

    float esquerda1 = lixo1.x - margem;
    float direita1 = lixo1.x + lixo1.largura + margem;
    float topo1 = lixo1.y - margem;
    float baixo1 = lixo1.y + lixo1.altura + margem;

    float esquerda2 = lixo2.x - margem;
    float direita2 = lixo2.x + lixo2.largura + margem;
    float topo2 = lixo2.y - margem;
    float baixo2 = lixo2.y + lixo2.altura + margem;

    if (direita1 > esquerda2 &&
        esquerda1 < direita2 &&
        baixo1 > topo2 &&
        topo1 < baixo2) {
        return 1;
    }
    else {
        return 0;
    }
}

void posicionarLixoSeguro(struct Lixo lixos[], int i, int max_lixos, int inicializador) {
    int colidiu;

    do {
        colidiu = 0;
        lixos[i].x = rand() % (largura_tela - lixos[i].largura);

        for (int j = 0; j < max_lixos; j++) {
            if (i == j) continue;

            if (colideHitboxExterna(lixos[i], lixos[j])) {
                colidiu = 1;
                break;
            }
        }

    } while (colidiu);
}

void colisao(struct Lixo lixos[], int i, int max_lixos, struct Lixeira *lixeira, int* pontuacao) {
    struct Lixo* lixo = &lixos[i];

    if (lixo->x + lixo->largura > lixeira->x && lixo->x < lixeira->x + lixeira->largura &&
        lixo->y + lixo->altura > lixeira->y && lixo->y < lixeira->y + lixeira->altura) {

        if (strcmp(lixo->tipo, lixeira->tipo) == 0) {
            *pontuacao += 1 * lixeira->multiplicador;
            (lixeira->combo)++;

            if (lixeira->combo >= 4 && lixeira->multiplicador == 1) {
                lixeira->multiplicador = 2;
                lixeira->combo = 0;
            }

            if (lixeira->combo >= 4 && lixeira->multiplicador == 2) {
                lixeira->multiplicador = 3;
                lixeira->combo = 0;
            }

            if (lixeira->combo >= 4 && lixeira->multiplicador == 3) {
                lixeira->multiplicador = 4;
                lixeira->combo = 0;
            }

            if (lixeira->combo >= 10 && lixeira->multiplicador == 4) {
                lixeira->multiplicador = 8;
                lixeira->combo = 0;
            }
        }
        else {
            lixeira->vida -= 2;
            lixeira->combo = 0;
            lixeira->multiplicador = 1;
        }

        int distancia = (200 + rand() % 251);
        lixo->y = -distancia;
        tipoLixo(lixo);
        posicionarLixoSeguro(lixos, i, max_lixos, i);
    }

    if (lixo->y > altura_tela) {
        lixeira->vida -= 1;
        lixeira->combo = 0;
        lixeira->multiplicador = 1;
        int distancia = (200 + rand() % 251);
        lixo->y = -distancia;
        tipoLixo(lixo);
        posicionarLixoSeguro(lixos, i, max_lixos, i);
    }
}