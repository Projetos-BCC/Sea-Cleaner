#ifndef COLISAO_H
#define COLISAO_H

#include <allegro5/allegro.h>

#include "lixo.h"
#include "lixeira.h"

int colideHitboxExterna(struct Lixo lixo1, struct Lixo lixo2);
void posicionarLixoSeguro(struct Lixo lixos[], int i, int max_lixos, int inicializador);
void colisao(struct Lixo lixos[], int i, int max_lixos, struct Lixeira lixeira, int* pontuacao, int* erros);

#endif