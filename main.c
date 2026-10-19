#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Lixeira {
    char tipo[10];
    float x;
    float y;
    int largura;
    int altura;
};

struct Lixo {
    char tipo[10];
    float x;
    float y;
    float velocidade;
    int largura;
    int altura;
};

int largura_tela = 800;
int altura_tela = 900;

int colideHitboxExterna(struct Lixo lixo1, struct Lixo lixo2) {
    int margem = 25;

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

void posicionarLixoSeguro(struct Lixo lixos[], int index, int max_lixos) {
    int colidiu;

    do {
        colidiu = 0;
        lixos[index].x = rand() % (largura_tela - lixos[index].largura);

        for (int j = 0; j < max_lixos; j++) {
            if (index == j) continue;

            if (colideHitboxExterna(lixos[index], lixos[j])) {
                colidiu = 1;
                break;
            }
        }

    } while (colidiu);
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
}

void inicializaLixo(struct Lixo lixos[], int max_lixos) {
    for (int i = 0; i < max_lixos; i++) {
        lixos[i].largura = 30;
        lixos[i].altura = 50;
        lixos[i].velocidade = 3;

        if (i == 0) {
            lixos[i].y = 0;
        }
        else {
            int distancia = 100 + rand() % 301;
            lixos[i].y = lixos[i - 1].y - distancia;
        }
        tipoLixo(&lixos[i]);
        posicionarLixoSeguro(lixos, i, max_lixos);
    }
}

void dropLixo(struct Lixo* lixo) {
    ALLEGRO_COLOR cor;

    if (strcmp(lixo->tipo, "Papel") == 0) {
        cor = al_map_rgb(0, 0, 255);
    }
    else if (strcmp(lixo->tipo, "Plastico") == 0) {
        cor = al_map_rgb(255, 0, 0);
    }
    else if (strcmp(lixo->tipo, "Vidro") == 0) {
        cor = al_map_rgb(0, 255, 0);
    }
    else if (strcmp(lixo->tipo, "Metal") == 0) {
        cor = al_map_rgb(255, 255, 0);
    }
    else if (strcmp(lixo->tipo, "Organico") == 0) {
        cor = al_map_rgb(137, 81, 41);
    }

    al_draw_filled_rectangle(
        lixo->x, lixo->y,
        lixo->x + lixo->largura, lixo->y + lixo->altura,
        cor
    );

    lixo->y += lixo->velocidade;
}

void colisao(struct Lixo lixos[], int i, int max_lixos, struct Lixeira lixeira, int* pontuacao, int* erros, int* rodando) {
    struct Lixo* lixo = &lixos[i];

    if (lixo->x + lixo->largura > lixeira.x && lixo->x < lixeira.x + lixeira.largura &&
        lixo->y + lixo->altura > lixeira.y && lixo->y < lixeira.y + lixeira.altura) {

        if (strcmp(lixo->tipo, lixeira.tipo) == 0) {
            (*pontuacao)++;
        }
        else {
            (*erros)++;
        }

        int distancia = (100 + rand() % 301);
        lixo->y = -distancia;
        tipoLixo(lixo);
        posicionarLixoSeguro(lixos, i, max_lixos);
    }

    if (lixo->y > altura_tela) {
        (*erros)++;
        int distancia = (100 + rand() % 301);
        lixo->y = -distancia;
        tipoLixo(lixo);
        posicionarLixoSeguro(lixos, i, max_lixos);
    }

    if (*erros >= 5) {
        *rodando = 0;
    }
}

int main(void) {
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_image_addon();

    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_FONT* fonte = al_create_builtin_font();
    ALLEGRO_BITMAP* sprite_lixeiras = al_load_bitmap("images/lixeiras2d.png");

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    struct Lixeira lixeira;
    lixeira.largura = 100;
    lixeira.altura = 120;
    lixeira.x = 400;
    lixeira.y = 700;
    strcpy_s(lixeira.tipo, sizeof(lixeira.tipo), "Papel");

    srand(time(NULL));

    int max_lixos = 6;
    struct Lixo lixos[6];
    inicializaLixo(lixos, max_lixos);

    int pontuacao = 0;
    int erros = 0;

    al_start_timer(timer);
    int rodando = 1;
    bool redesenhar = true;

    while (rodando) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            rodando = 0;
        }
        else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            trocarTipoLixeira(&lixeira, evento.keyboard.keycode);
        }
        else if (evento.type == ALLEGRO_EVENT_TIMER) {
            redesenhar = true;
        }

        if (redesenhar && al_is_event_queue_empty(fila_eventos)) {
            redesenhar = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            movimentarLixeira(&lixeira);
            exibeLixeira(lixeira, sprite_lixeiras);

            for (int i = 0; i < max_lixos; i++) {
                dropLixo(&lixos[i]);
                colisao(lixos, i, max_lixos, lixeira, &pontuacao, &erros, &rodando);
            }

            al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 10, 0, "Pontos: %d", pontuacao);
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 30, 0, "Erros: %d/5", erros);

            al_draw_textf(fonte, al_map_rgb(0, 0, 255), 10, 50, 0, "A = Papel");
            al_draw_textf(fonte, al_map_rgb(255, 0, 0), 10, 60, 0, "S = Plastico");
            al_draw_textf(fonte, al_map_rgb(0, 255, 0), 10, 70, 0, "D = Vidro");
            al_draw_textf(fonte, al_map_rgb(255, 255, 0), 10, 80, 0, "F = Metal");
            al_draw_textf(fonte, al_map_rgb(137, 81, 41), 10, 90, 0, "Espaco = Organico");

            al_flip_display();
        }
    }

    printf("Sua pontuacao: %d\n", pontuacao);

    if (sprite_lixeiras) {
        al_destroy_bitmap(sprite_lixeiras);
    }

    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);

    return 0;
}