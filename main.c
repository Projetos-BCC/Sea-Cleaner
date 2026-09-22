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

    float largura_lixeira = 100;
    float altura_lixeira = 100;

    float x = 350;
    float y = 650;

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

                x = mouse.x;

                if (x > largura_tela - largura_lixeira)
                {
                    x = largura_tela - largura_lixeira;
                }

                al_clear_to_color(al_map_rgb(0, 0, 0));

                al_draw_filled_rectangle(
                    x, y,
                    x + largura_lixeira, y + altura_lixeira,
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