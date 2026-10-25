#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//ARQUIVOS
#include "configs.h"
#include "lixeira.h"
#include "lixo.h"
#include "colisao.h"

estadoJogo estado = ESTADO_MENU;

int largura_tela = 800;
int altura_tela = 900;

void reiniciarPartida(int *pontuacao, int *erros, struct Lixeira *lixeira, struct Lixo lixos[], int max_lixos) {
    *pontuacao = 0;
    *erros = 0;

    strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Papel");

    inicializaLixo(lixos, max_lixos);
}

int main(void) {
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_image_addon();

    ALLEGRO_BITMAP* sprite_lixeiras = al_load_bitmap("images/lixeiras2d.png");
    ALLEGRO_BITMAP* sprite_lixos = al_load_bitmap("images/lixos2d.png");

    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_FONT* fonte = al_create_builtin_font();
    

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
            if (estado == ESTADO_MENU) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    estado = ESTADO_JOGANDO;
                    printf("Mudou para JOGANDO\n");
                }
            }
            else if (estado == ESTADO_JOGANDO) {
                trocarTipoLixeira(&lixeira, evento.keyboard.keycode);
            }
            else if (estado == ESTADO_GAMEOVER) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    reiniciarPartida(&pontuacao, &erros, &lixeira, lixos, max_lixos);
                    estado = ESTADO_JOGANDO;
                    printf("Mudou para JOGANDO\n");
                }
            }
            
        }
        else if (evento.type == ALLEGRO_EVENT_TIMER) {
            redesenhar = true;
        }

        if (redesenhar && al_is_event_queue_empty(fila_eventos)) {
            redesenhar = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (estado == ESTADO_MENU) {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela/2, altura_tela/2, ALLEGRO_ALIGN_CENTER, "SEA CLEANER");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 30, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para jogar");
            }
            else if (estado == ESTADO_JOGANDO) {
                movimentarLixeira(&lixeira);
                exibeLixeira(lixeira, sprite_lixeiras);

                for (int i = 0; i < max_lixos; i++) {
                    dropLixo(&lixos[i], sprite_lixos);
                    colisao(lixos, i, max_lixos, lixeira, &pontuacao, &erros);
                }

                if (erros >= 5) {
                    estado = ESTADO_GAMEOVER;
                }

                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 10, 0, "Pontos: %d", pontuacao);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 30, 0, "Erros: %d/5", erros);

                al_draw_textf(fonte, al_map_rgb(0, 0, 255), 10, 50, 0, "A = Papel");
                al_draw_textf(fonte, al_map_rgb(255, 0, 0), 10, 60, 0, "S = Plastico");
                al_draw_textf(fonte, al_map_rgb(0, 255, 0), 10, 70, 0, "D = Vidro");
                al_draw_textf(fonte, al_map_rgb(255, 255, 0), 10, 80, 0, "F = Metal");
                al_draw_textf(fonte, al_map_rgb(137, 81, 41), 10, 90, 0, "Espaco = Organico");
            }
            else if (estado == ESTADO_GAMEOVER) {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 30, ALLEGRO_ALIGN_CENTER, "Pontuação: %d", pontuacao);
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2 + 50, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para jogar novamente");
            }

            al_flip_display();
        }
    }

    printf("Sua pontuacao: %d\n", pontuacao);

    al_destroy_font(fonte);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    al_destroy_bitmap(sprite_lixeiras);
    al_destroy_bitmap(sprite_lixos);

    return 0;
}