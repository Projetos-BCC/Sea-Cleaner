#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
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

void movimentarLixeira(struct Lixeira* lixeira) {

    ALLEGRO_MOUSE_STATE mouse;

    al_get_mouse_state(&mouse);

    lixeira->x = mouse.x - lixeira->largura / 2;

    if (lixeira->x > largura_tela - lixeira->largura)
    {
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

void exibeLixeira(struct Lixeira lixeira) {

    ALLEGRO_COLOR cor;

    if (strcmp(lixeira.tipo, "Papel") == 0) {
        cor = al_map_rgb(0, 0, 255);
    }
    else if (strcmp(lixeira.tipo, "Plastico") == 0) {
        cor = al_map_rgb(255, 0, 0);
    }
    else if (strcmp(lixeira.tipo, "Vidro") == 0) {
        cor = al_map_rgb(0, 255, 0);
    }
    else if (strcmp(lixeira.tipo, "Metal") == 0) {
        cor = al_map_rgb(255, 255, 0);
    }
    else if (strcmp(lixeira.tipo, "Organico") == 0) {
        cor = al_map_rgb(137, 81, 41);
    }

    al_draw_filled_rectangle(
        lixeira.x, lixeira.y,
        lixeira.x + lixeira.largura, lixeira.y + lixeira.altura,
        cor
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
    else
    {
        strcpy_s(lixo->tipo, sizeof(lixo->tipo), "Organico");
    }
}

void inicializaLixo(struct Lixo lixos[], int max_lixos) {
    for (int i = 0; i < max_lixos; i++) {
        lixos[i].largura = 30;
        lixos[i].altura = 50;
        lixos[i].velocidade = 3;
        lixos[i].x = rand() % (largura_tela - lixos[i].largura);

        if (i == 0) {
            lixos[i].y = 0;
        }
        else {
            int distancia = 100 + rand() % 301;
            lixos[i].y = lixos[i - 1].y - distancia;
        }
        tipoLixo(&lixos[i]);
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

void colisao(struct Lixo *lixo, struct Lixeira lixeira, int *pontuacao, int *erros, int *rodando) {
    if (lixo->x + lixo->largura > lixeira.x && lixo->x < lixeira.x + lixeira.largura && lixo->y + lixo->altura > lixeira.y && lixo->y < lixeira.y + lixeira.altura) {
        if (strcmp(lixo->tipo, lixeira.tipo) == 0) {
            (*pontuacao)++;
            int distancia = (100 + rand() % 301);
            lixo->y = -distancia;
            lixo->x = rand() % (largura_tela - lixo->largura);
            tipoLixo(lixo);
        }
        else {   

            (*erros)++;
            int distancia = (100 + rand() % 301);
            lixo->y = -distancia;
            lixo->x = rand() % (largura_tela - lixo->largura);
            tipoLixo(lixo);

            
        }
    }

    if (lixo->y > altura_tela) {
        (*erros)++;
        int distancia = (100 + rand() % 301);
        lixo->y = -distancia;
        lixo->x = rand() % (largura_tela - lixo->largura);
        tipoLixo(lixo);
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

    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_FONT* fonte = al_create_builtin_font();

    al_register_event_source(
        fila_eventos,
        al_get_display_event_source(janela)
    );

    al_register_event_source(
        fila_eventos,
        al_get_timer_event_source(timer)
    );

    al_register_event_source(
        fila_eventos,
        al_get_keyboard_event_source()
    );

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

    while (rodando)
    {
        ALLEGRO_EVENT evento;

        if (al_get_next_event(fila_eventos, &evento))
        {
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

                trocarTipoLixeira(&lixeira, evento.keyboard.keycode);

            }

            if (evento.type == ALLEGRO_EVENT_TIMER)
            {

                al_clear_to_color(al_map_rgb(0, 0, 0));
                
                movimentarLixeira(&lixeira);

                exibeLixeira(lixeira);

                for (int i = 0; i < max_lixos; i++) {
                    dropLixo(&lixos[i]);

                    colisao(&lixos[i], lixeira, &pontuacao, &erros, &rodando);
                }

                al_draw_textf(
                    fonte,
                    al_map_rgb(255, 255, 255),
                    10, 10,
                    0,
                    "Pontos: %d",
                    pontuacao
                ); 

                al_draw_textf(
                    fonte,
                    al_map_rgb(255, 255, 255),
                    10, 30,
                    0,
                    "Erros: %d/5",
                    erros
                );

                al_draw_textf(
                    fonte,
                    al_map_rgb(0, 0, 255),
                    10, 50,
                    0,
                    "A = Papel"
                );
                al_draw_textf(
                    fonte,
                    al_map_rgb(255, 0, 0),
                    10, 60,
                    0,
                    "S = Plastico"
                );
                al_draw_textf(
                    fonte,
                    al_map_rgb(0, 255, 0),
                    10, 70,
                    0,
                    "D = Vidro"
                );
                al_draw_textf(
                    fonte,
                    al_map_rgb(255, 255, 0),
                    10, 80,
                    0,
                    "F = Metal"
                );
                al_draw_textf(
                    fonte,
                    al_map_rgb(137, 81, 41),
                    10, 90,
                    0,
                    "Espaco = Organico"
                );
                
                al_flip_display();
            }
        }
    }

    printf("Sua pontuacao: %d\n", pontuacao);

    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);

    return 0;
}