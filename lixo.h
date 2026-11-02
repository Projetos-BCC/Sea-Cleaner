#ifndef LIXO_H
#define LIXO_H

#include <allegro5/allegro.h>

struct Lixo {
    char tipo[10];
    float x;
    float y;
    float velocidade;
    int largura;
    int altura;
    int variacao_item;
};

void tipoLixo(struct Lixo* lixo);
void inicializaLixo(struct Lixo lixos[], int max_lixos);
void dropLixo(struct Lixo* lixo, ALLEGRO_BITMAP* sprite_lixos);
void moverLixo(struct Lixo* lixo);

#endif 