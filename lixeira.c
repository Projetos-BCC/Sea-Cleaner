#include "lixeira.h"
#include "configs.h"
#include <string.h>
#include <allegro5/allegro_primitives.h>

void inicializarLixeira(struct Lixeira* lixeira) {
    lixeira->largura = 100;
    lixeira->altura = 120;
    lixeira->x = 400;
    lixeira->y = 700;
    strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Papel");
    lixeira->vida = 10;
    lixeira->combo = 0;
    lixeira->multiplicador = 1;
    lixeira->acertos = 0;
    lixeira->tempoConversao = 0;
}

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

void obterRecorteLixeira(const char* tipo, float* src_x, float* src_y) {
    *src_x = 0;
    *src_y = 0;

    if (strcmp(tipo, "Papel") == 0) {
        *src_x = 370; *src_y = 147;
    }
    else if (strcmp(tipo, "Vidro") == 0) {
        *src_x = 798; *src_y = 147;
    }
    else if (strcmp(tipo, "Metal") == 0) {
        *src_x = 144; *src_y = 601;
    }
    else if (strcmp(tipo, "Plastico") == 0) {
        *src_x = 585; *src_y = 601;
    }
    else if (strcmp(tipo, "Organico") == 0) {
        *src_x = 1033; *src_y = 601;
    }
}

void exibeLixeira(struct Lixeira lixeira, ALLEGRO_BITMAP* sprite_lixeiras) {
    float escala = al_get_bitmap_width(sprite_lixeiras) / 1470.0f;

    float src_x = 0;
    float src_y = 0;
    float largura_recorte = 291;
    float altura_recorte = 365;

    obterRecorteLixeira(lixeira.tipo, &src_x, &src_y);

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
        src_x * escala, src_y * escala,
        largura_recorte * escala, altura_recorte * escala,
        lixeira.x, lixeira.y,
        lixeira.largura, lixeira.altura,
        0
    );
}

void exibeBarraLixeiras(struct Lixeira lixeira, ALLEGRO_BITMAP* sprite_lixeiras, ALLEGRO_FONT* fonte) {
    char* tipos[5] = { "Papel", "Plastico", "Vidro", "Metal", "Organico" };
    char* teclas[5] = { "A", "S", "D", "F", "Espaco" };

    float escala = al_get_bitmap_width(sprite_lixeiras) / 1470.0f;
    float src_x, src_y;

    for (int i = 0; i < 5; i++) {
        float x = 180 + i * 100;
        float y = 830;

        obterRecorteLixeira(tipos[i], &src_x, &src_y);

        al_draw_scaled_bitmap(
            sprite_lixeiras,
            src_x * escala, src_y * escala,
            291 * escala, 365 * escala,
            x, y, 40, 48,
            0
        );

        if (strcmp(tipos[i], lixeira.tipo) == 0) {
            al_draw_rectangle(x - 5, y - 5, x + 45, y + 53, al_map_rgb(255, 255, 0), 2);
        }

        al_draw_text(fonte, al_map_rgb(255, 255, 255), x + 20, y + 58, ALLEGRO_ALIGN_CENTER, teclas[i]);
    }
}