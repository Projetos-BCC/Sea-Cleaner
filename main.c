#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>

struct Lixeira {
    char tipo[10];
    float x;
    float y;
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
    if (tecla == ALLEGRO_KEY_Q) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Papel");
    }
    else if (tecla == ALLEGRO_KEY_W) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Plastico");
    }
    else if (tecla == ALLEGRO_KEY_E) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Vidro");
    }
    else if (tecla == ALLEGRO_KEY_R) {
        strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Metal");
    }
    else if (tecla == ALLEGRO_KEY_T) {
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



int main(void) {
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();

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

                al_flip_display();
            }
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);

    return 0;
}