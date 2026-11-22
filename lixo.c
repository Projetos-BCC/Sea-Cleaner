#include "lixo.h"
#include "configs.h"
#include "lixeira.h"
#include <string.h>
#include <stdlib.h>

void tipoLixo(struct Lixo* lixo) {
    int tipoRand = rand() % 5;

    if (tipoRand == 0) {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Papel");
    }
    else if (tipoRand == 1) {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Plastico");
    }
    else if (tipoRand == 2) {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Vidro");
    }
    else if (tipoRand == 3) {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Metal");
    }
    else {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Organico");
    }
    lixo->variacao_item = 1 + (rand() % 4);
}

void inicializaLixo(struct Lixo lixos[], int max_lixos) {
    for (int i = 0; i < max_lixos; i++) {
        lixos[i].largura = 40;
        lixos[i].altura = 40;
        lixos[i].velocidade = 3;

        if (i == 0) {
            lixos[i].y = 0;
        }
        else {
            int distancia = 200 + rand() % 251;
            lixos[i].y = lixos[i - 1].y - distancia;
        }
        tipoLixo(&lixos[i]);
        posicionarLixoSeguro(lixos, i, max_lixos, i);
    }
}

void dropLixo(struct Lixo* lixo, ALLEGRO_BITMAP* sprite_lixos) {
    float escala = al_get_bitmap_width(sprite_lixos) / 1500.0f;
    float x_ini = 0, x_fim = 0, y_ini = 0, y_fim = 0;

    if (strcmp(lixo->tipo, "Papel") == 0) {
        if (lixo->variacao_item == 1) { x_ini = 60;   x_fim = 238;  y_ini = 42;   y_fim = 206; }
        else if (lixo->variacao_item == 2) { x_ini = 67;   x_fim = 231;  y_ini = 298;  y_fim = 451; }
        else if (lixo->variacao_item == 3) { x_ini = 93;   x_fim = 206;  y_ini = 578;  y_fim = 671; }
        else if (lixo->variacao_item == 4) { x_ini = 96;   x_fim = 202;  y_ini = 830;  y_fim = 918; }
    }
    else if (strcmp(lixo->tipo, "Plastico") == 0) {
        if (lixo->variacao_item == 1) { x_ini = 389;  x_fim = 509;  y_ini = 19;   y_fim = 229; }
        else if (lixo->variacao_item == 2) { x_ini = 365;  x_fim = 533;  y_ini = 303;  y_fim = 446; }
        else if (lixo->variacao_item == 3) { x_ini = 360;  x_fim = 539;  y_ini = 534;  y_fim = 715; }
        else if (lixo->variacao_item == 4) { x_ini = 375;  x_fim = 524;  y_ini = 818;  y_fim = 930; }
    }
    else if (strcmp(lixo->tipo, "Vidro") == 0) {
        if (lixo->variacao_item == 1) { x_ini = 685;  x_fim = 814;  y_ini = 10;   y_fim = 239; }
        else if (lixo->variacao_item == 2) { x_ini = 679;  x_fim = 821;  y_ini = 282;  y_fim = 467; }
        else if (lixo->variacao_item == 3) { x_ini = 697;  x_fim = 801;  y_ini = 579;  y_fim = 669; }
        else if (lixo->variacao_item == 4) { x_ini = 692;  x_fim = 807;  y_ini = 826;  y_fim = 923; }
    }
    else if (strcmp(lixo->tipo, "Metal") == 0) {
        if (lixo->variacao_item == 1) { x_ini = 974;  x_fim = 1124; y_ini = 35;   y_fim = 214; }
        else if (lixo->variacao_item == 2) { x_ini = 989;  x_fim = 1109; y_ini = 323;  y_fim = 426; }
        else if (lixo->variacao_item == 3) { x_ini = 980;  x_fim = 1118; y_ini = 555;  y_fim = 693; }
        else if (lixo->variacao_item == 4) { x_ini = 983;  x_fim = 1116; y_ini = 814;  y_fim = 934; }
    }
    else if (strcmp(lixo->tipo, "Organico") == 0) {
        if (lixo->variacao_item == 1) { x_ini = 1241; x_fim = 1457; y_ini = 28;   y_fim = 221; }
        else if (lixo->variacao_item == 2) { x_ini = 1258; x_fim = 1440; y_ini = 311;  y_fim = 437; }
        else if (lixo->variacao_item == 3) { x_ini = 1247; x_fim = 1451; y_ini = 542;  y_fim = 705; }
        else if (lixo->variacao_item == 4) { x_ini = 1283; x_fim = 1416; y_ini = 831;  y_fim = 918; }
    }

    float largura_recorte = (x_fim - x_ini) * escala;
    float altura_recorte = (y_fim - y_ini) * escala;

    al_draw_scaled_bitmap(
        sprite_lixos,
        x_ini * escala, y_ini * escala,
        largura_recorte, altura_recorte,
        lixo->x, lixo->y,
        lixo->largura, lixo->altura,
        0
    );

}

void moverLixo(struct Lixo* lixo) {
    lixo->y += lixo->velocidade;
}

void atrairLixo(struct Lixo* lixo, struct Lixeira lixeira) {
    if (strcmp(lixo->tipo, lixeira.tipo) == 0 && lixo->y > lixeira.y - 250 && lixo->y < lixeira.y + lixeira.altura) {
        int lixeiraC = lixeira.x + lixeira.largura / 2;
        int lixoC = lixo->x + lixo->largura / 2;

        if (lixoC < lixeiraC) {
            lixo->x += 5;
        }
        else if (lixoC > lixeiraC) {
            lixo->x -= 5;
        }
    }
}