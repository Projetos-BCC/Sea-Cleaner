#ifndef LIXEIRA_H
#define LIXEIRA_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

struct Lixeira {
    char tipo[10];
    float x;
    float y;
    int largura;
    int altura;
    int vida;
    int combo;
    int multiplicador;
    int acertos;
    int tempoConversao;
    char tipoConversao[10];
};

void inicializarLixeira(struct Lixeira* lixeira);
void movimentarLixeira(struct Lixeira* lixeira);
void trocarTipoLixeira(struct Lixeira* lixeira, int tecla);
void exibeLixeira(struct Lixeira lixeira, ALLEGRO_BITMAP* sprite_lixeiras);
void spriteLixeira(const char* tipo, float* src_x, float* src_y);
void exibeBarraLixeiras(struct Lixeira lixeira, ALLEGRO_BITMAP* sprite_lixeiras, ALLEGRO_FONT* fonte);

#endif