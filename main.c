#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main(void) {
    al_init();
    al_init_primitives_addon();
    al_install_mouse();

    int largura_tela = 800;
    int altura_tela = 900;

    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(
        fila_eventos,
        al_get_display_event_source(janela)
    );

    al_register_event_source(
        fila_eventos,
        al_get_timer_event_source(timer)
    );

    int rodando = 1;

    struct Lixeira {
        char tipo[10];
        float x;
        float y;
        int largura;
        int altura;
    };

    struct Lixeira lixeira;

    lixeira.largura = 100;
    lixeira.altura = 100;

    lixeira.x = 400;
    lixeira.y = 700;

    ALLEGRO_MOUSE_STATE mouse;

    al_start_timer(timer);

    while (rodando)
    {
        ALLEGRO_EVENT evento;

        if (al_get_next_event(fila_eventos, &evento))
        {
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                rodando = 0;
            }

            if (evento.type == ALLEGRO_EVENT_TIMER)
            {
                al_get_mouse_state(&mouse);

                lixeira.x = mouse.x - lixeira.largura/2;

                if (lixeira.x > largura_tela - lixeira.largura)
                {
                    lixeira.x = largura_tela - lixeira.largura;

                }

                if (lixeira.x < 0) {
                    lixeira.x = 0;
                }
               

                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_draw_filled_rectangle(
                    lixeira.x, lixeira.y,
                    lixeira.x + lixeira.largura, lixeira.y + lixeira.altura,
                    al_map_rgb(0, 255, 0)
                );

                al_flip_display();
            }
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);

    return 0;
}