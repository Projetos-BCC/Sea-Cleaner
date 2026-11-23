#ifndef ENCICLOPEDIA_H
#define ENCICLOPEDIA_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct Especie {
    char nome[40];
    char habitat[300];
    char ameacas[300];
    char objetivo[300];
    int desbloqueada;     // 1 = já desbloqueada, 0 = bloqueada
};

void inicializaEspecies(struct Especie especies[]);
void textosEnciclopedia(ALLEGRO_FONT* titulo, int maiorFase, int jogoZerado, int highscore);

#endif