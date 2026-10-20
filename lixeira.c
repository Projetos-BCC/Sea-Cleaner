#include "lixeira.h"
#include "configs.h"
#include <string.h>

void movimentarLixeira(struct Lixeira* lixeira) {
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);

    lixeira->x = mouse.x - lixeira->largura / 2;

    if (lixeira->x > largura_tela - lixeira->largura) {
        lixeira->x = largura_tela - lixeira->largura;
    }

    if (lixeira->x < 0) {
        lixeira->x = 0;
    }
}

void trocarTipoLixeira(struct Lixeira* lixeira, int tecla) {
    if (tecla == ALLEGRO_KEY_A) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Papel");
    }
    else if (tecla == ALLEGRO_KEY_S) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Plastico");
    }
    else if (tecla == ALLEGRO_KEY_D) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Vidro");
    }
    else if (tecla == ALLEGRO_KEY_F) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Metal");
    }
    else if (tecla == ALLEGRO_KEY_SPACE) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Organico");
    }
}

void exibeLixeira(struct Lixeira lixeira, ALLEGRO_BITMAP* sprite_lixeiras) {
    float src_x = 0;
    float src_y = 0;
    float largura_recorte = 291;
    float altura_recorte = 365;

    if (strcmp(lixeira.tipo, "Papel") == 0) {
        src_x = 370; src_y = 147;
    }
    else if (strcmp(lixeira.tipo, "Vidro") == 0) {
        src_x = 798; src_y = 147;
    }
    else if (strcmp(lixeira.tipo, "Metal") == 0) {
        src_x = 144; src_y = 601;
    }
    else if (strcmp(lixeira.tipo, "Plastico") == 0) {
        src_x = 585; src_y = 601;
    }
    else if (strcmp(lixeira.tipo, "Organico") == 0) {
        src_x = 1033; src_y = 601;
    }

    al_draw_scaled_bitmap(
        sprite_lixeiras,
        src_x, src_y,
        largura_recorte, altura_recorte,
        lixeira.x, lixeira.y,
        lixeira.largura, lixeira.altura,
        0
    );
}