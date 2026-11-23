#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
#include "powerup.h"
#include "enciclopedia.h"

estadoJogo estado = ESTADO_MENU;

int largura_tela = 800;
int altura_tela = 900;

void reiniciarPartida(int *pontuacao, struct Lixeira *lixeira, struct Lixo lixos[], int max_lixos, int *highScore, int *aviso, struct PowerUp *powerUp, int *tempoIma, int *tempoLento) {

       if (*pontuacao > *highScore) {
            *highScore = *pontuacao;
        }
    
    *pontuacao = 0;
    lixeira->vida = 10;
    lixeira->combo = 0;
    lixeira->multiplicador = 1;
    lixeira->acertos = 0;
    *aviso = 0;
    powerUp->ativo = 0;
    *tempoLento = 0;
    *tempoIma = 0;
    lixeira->tempoConversao = 0;

    strcpy_s(lixeira->tipo, sizeof(lixeira->tipo), "Papel");

    inicializaLixo(lixos, max_lixos);
}

void definirFase(struct Lixeira* lixeira, int *fase, int *inicio, int *fim, int *velocidade) {
    *fase = 1;
    *inicio = 0;
    *fim = 30;
    *velocidade = 3;

    if (lixeira->acertos >= 30) {
        *fase = 2;
        *inicio = 30;
        *fim = 70;
        *velocidade = 4;
    }
    if (lixeira->acertos >= 70) {
        *fase = 3;
        *inicio = 70;
        *fim = 120;
        *velocidade = 5;
    }
    if (lixeira->acertos >= 120) {
        *fase = 4;
        *inicio = 120;
        *fim = 180;
        *velocidade = 5.5;
    }
    if (lixeira->acertos >= 180) {
        *fase = 5;
        *inicio = 180;
        *fim = 250;
        *velocidade = 6;
    }
}

int main(void) {

    //INICIACAO ADDONS DO ALLEGRO
    al_init();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);

    //INICIALIZACAO DOS SPRITES
    ALLEGRO_BITMAP* sprite_lixeiras = al_load_bitmap("images/lixeiras2d.png");
    ALLEGRO_BITMAP* sprite_lixos = al_load_bitmap("images/lixos2d.png");
    ALLEGRO_BITMAP* fundo_menu = al_load_bitmap("images/seaCleanerMenu.png");
    ALLEGRO_BITMAP* pause = al_load_bitmap("images/seaCleanerPause.png");
    ALLEGRO_BITMAP* sprite_powerUps = al_load_bitmap("images/powerUps.png");
    ALLEGRO_BITMAP* icone_vida = al_load_bitmap("images/iconeVida.png");
    ALLEGRO_BITMAP* gameOver = al_load_bitmap("images/seaCleanerGameOver.png");
    ALLEGRO_BITMAP* fundo_enciclopedia = al_load_bitmap("images/enciclopedia.png");
    ALLEGRO_BITMAP* peixes1 = al_load_bitmap("images/peixes1.png");
    ALLEGRO_BITMAP* peixes2 = al_load_bitmap("images/peixes2.png");


    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //TAMANHO DOS TEXTOS
    ALLEGRO_FONT* fonte = al_load_ttf_font("font/fonte.ttf", 8, 0);
    ALLEGRO_FONT* peixes = al_load_ttf_font("font/fonte.ttf", 10, 0);
    ALLEGRO_FONT* pontos = al_load_ttf_font("font/fonte.ttf", 16, 0);
    ALLEGRO_FONT* titulo = al_load_ttf_font("font/fonte.ttf", 24, 0);

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());


    //INICIALIZACAO DA LIXEIRA
    struct Lixeira lixeira;
    inicializarLixeira(&lixeira);

    srand(time(NULL));

    //INICIALIZACAO DOS LIXOS
    int max_lixos = 6;
    struct Lixo lixos[6];
    inicializaLixo(lixos, max_lixos);

    //INICIALIZACAO DOS POWERUPS
    struct PowerUp powerUp;
    inicializaPowerUp(&powerUp);

    //INICIALIZACAO DOS PEIXES
    struct Especie especies[9];

    int pontuacao = 0;
    int highScore = 1;
    int fase = 1;
    int inicio = 0;
    int fim = 30;
    int velocidade = 3;
    int fase_anterior = 1;
    int aviso = 0;
    int tempoLento = 0;
    int tempoIma = 0;
    int jogoZerado = 0;
    int maiorFase = 1;

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
            if (estado == ESTADO_JOGANDO) {
                trocarTipoLixeira(&lixeira, evento.keyboard.keycode);
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    estado = ESTADO_PAUSADO;
                }
            }
            else if (estado == ESTADO_PAUSADO) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    estado = ESTADO_JOGANDO;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    pontuacao = 0;
                    estado = ESTADO_MENU;
                }
            } 
            else if (estado == ESTADO_VITORIA) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    reiniciarPartida(&pontuacao, &lixeira, lixos, max_lixos, &highScore, &aviso, &powerUp, &tempoLento, &tempoIma);
                    estado = ESTADO_JOGANDO;
                }
                else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    estado = ESTADO_MENU;
                }
            }
            else if (estado == ESTADO_ENCICLOPEDIA) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    estado = ESTADO_MENU;
                }
            }
            
        }
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (estado == ESTADO_MENU) {
                if (evento.mouse.x > 192 && evento.mouse.x < 607 && evento.mouse.y > 463 && evento.mouse.y < 531) {
                    if (evento.mouse.button == 1) {
                        reiniciarPartida(&pontuacao, &lixeira, lixos, max_lixos, &highScore, &aviso, &powerUp, &tempoLento, &tempoIma);
                        estado = ESTADO_JOGANDO;
                    }
                } else if (evento.mouse.x > 192 && evento.mouse.x < 607 && evento.mouse.y > 550 && evento.mouse.y < 618) {
                    if (evento.mouse.button == 1) {
                        reiniciarPartida(&pontuacao, &lixeira, lixos, max_lixos, &highScore, &aviso, &powerUp, &tempoLento, &tempoIma);
                        estado = ESTADO_ENCICLOPEDIA;
                    }
                }
                
            }
            else if (estado == ESTADO_GAMEOVER) {
                if (evento.mouse.x > 213 && evento.mouse.x < 360 && evento.mouse.y > 564 && evento.mouse.y < 605) {
                    if (evento.mouse.button == 1) {
                        reiniciarPartida(&pontuacao, &lixeira, lixos, max_lixos, &highScore, &aviso, &powerUp, &tempoLento, &tempoIma);
                        estado = ESTADO_JOGANDO;
                    }
                } else if (evento.mouse.x > 365 && evento.mouse.x < 493 && evento.mouse.y > 564 && evento.mouse.y < 605) {
                    if (evento.mouse.button == 1) {
                        estado = ESTADO_MENU;
                    }
                }
                else if (evento.mouse.x > 500 && evento.mouse.x < 616 && evento.mouse.y > 564 && evento.mouse.y < 605) {
                    if (evento.mouse.button == 1) {
                        estado = ESTADO_ENCICLOPEDIA;
                    }
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
                al_draw_bitmap(fundo_menu, 0, 0, 0);
            }
            else if (estado == ESTADO_JOGANDO) {

                
                 /*al_draw_scaled_bitmap(
                    fundo_rio,
                    0, 0,       // Posição inicial dentro do recorte
                    250, 664,     // Tamanho original do recorte
                    0, 0,   // Posição na tela
                    800, 900,   // Tamanho desejado na tela
                    0
                );*/
                
                
                exibeLixeira(lixeira, sprite_lixeiras);

                definirFase(&lixeira, &fase, &inicio, &fim, &velocidade);

                if (fase > fase_anterior) {
                    aviso = 180;
                    inicializaLixo(lixos, max_lixos);
                }
                fase_anterior = fase;

                if (tempoLento > 0) {
                    if (fase == 1) {
                        velocidade = 2;
                    }
                    velocidade = velocidade / 2;
                    if (aviso == 0) {
                        tempoLento--;
                    }
                }

                if (tempoIma > 0 && aviso == 0) {
                    tempoIma--;
                }

                if (lixeira.tempoConversao > 0) {
                    for (int i = 0; i < max_lixos; i++) {
                        strcpy_s(lixos[i].tipo, sizeof(lixos[i].tipo), lixeira.tipoConversao);
                    }
                    lixeira.tempoConversao--;
                }

                for (int i = 0; i < max_lixos; i++) {
                    lixos[i].velocidade = velocidade;

                    if (aviso == 0) {
                        movimentarLixeira(&lixeira);
                        if (tempoIma > 0) {
                            atrairLixo(&lixos[i], lixeira);
                        }
                        moverLixo(&lixos[i]);
                        colisao(lixos, i, max_lixos, &lixeira, &pontuacao);
                        
                    }
                    
                    dropLixo(&lixos[i], sprite_lixos);
                    
                }

                if (aviso == 0) {
                    gerarPowerUp(&powerUp, &lixeira, fase);
                    powerUp.velocidade = velocidade;
                    moverPowerUp(&powerUp);
                    if (colidePowerUp(powerUp, lixeira)) {
                        powerUp.ativo = 0;

                        ativaPowerUp(powerUp, &lixeira, &tempoLento, &tempoIma);

                    }
                }

                desenhaPowerUp(powerUp, sprite_powerUps);

                exibeBarraLixeiras(lixeira, sprite_lixeiras, fonte);

                if (lixeira.vida <= 0) {
                    estado = ESTADO_GAMEOVER;
                    if (fase > maiorFase) {
                        maiorFase = fase;
                    }
                } else if (fase == 5 && lixeira.acertos >= fim) {
                    estado = ESTADO_VITORIA;
                    jogoZerado = 1;
                    if (fase > maiorFase) {
                        maiorFase = fase;
                    }
                }

                exibeVida(lixeira, icone_vida);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 10, 0, "Fase: %d", fase);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 670, 10, 0, "HighScore: %d", highScore);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 50, 0, "Pontos: %d", pontuacao);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 70, 0, "Lixos reciclados: %d/%d", lixeira.acertos-inicio, fim-inicio);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 80, 0, "Acertos consecutivos: %d", lixeira.combo);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 10, 90, 0, "Multiplicador: %dX", lixeira.multiplicador);

                if (aviso > 0) {
                    al_draw_filled_rectangle(0, 0, largura_tela, altura_tela, al_map_rgba(0, 0, 0, 150));
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2, ALLEGRO_ALIGN_CENTER, "STAGE %d", fase);
                    aviso--;
                }

            }
            else if (estado == ESTADO_GAMEOVER) {
                al_draw_bitmap(gameOver, 180, 210, 0);

                if (pontuacao > highScore) {
                    al_draw_textf(pontos, al_map_rgb(255, 255, 255), 398, 413, ALLEGRO_ALIGN_CENTER, "%d", pontuacao);
                    al_draw_textf(pontos, al_map_rgb(255, 255, 255), 488, 441, ALLEGRO_ALIGN_CENTER, "%d", pontuacao);
                }
                else {
                    al_draw_textf(pontos, al_map_rgb(255, 255, 255), 398, 413, ALLEGRO_ALIGN_CENTER, "%d", highScore);
                    al_draw_textf(pontos, al_map_rgb(255, 255, 255), 488, 441, ALLEGRO_ALIGN_CENTER, "%d", pontuacao);
                }          
              
                
            }
            else if (estado == ESTADO_PAUSADO) {
                exibeLixeira(lixeira, sprite_lixeiras);

                for (int i = 0; i < max_lixos; i++) {
                    dropLixo(&lixos[i], sprite_lixos);
                }

                desenhaPowerUp(powerUp, sprite_powerUps);

                exibeBarraLixeiras(lixeira, sprite_lixeiras, fonte);

                exibeVida(lixeira, icone_vida);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 10, 0, "Fase: %d", fase);
                al_draw_textf(fonte, al_map_rgb(255, 255, 255), 670, 10, 0, "HighScore: %d", highScore);

                al_draw_filled_rectangle(0, 0, largura_tela, altura_tela, al_map_rgba(0, 0, 0, 150));
                al_draw_bitmap(pause, 150, 361, 0);

            }
            else if (estado == ESTADO_VITORIA) {
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2, ALLEGRO_ALIGN_CENTER, "PARABÉNS, VOCE VENCEU!!!");
                al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 10, ALLEGRO_ALIGN_CENTER, "Voce ajudou a limpar o rio, agora as especies podem viver sem medo da extincao");
                if (pontuacao > highScore) {
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 30, ALLEGRO_ALIGN_CENTER, "Pontuação: %d", pontuacao);
                    al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 50, ALLEGRO_ALIGN_CENTER, "NOVO RECORDE");
                    al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2 + 70, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para jogar novamente");
                    al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2 + 90, ALLEGRO_ALIGN_CENTER, "Pressione ESC para voltar ao menu");
                }
                else {
                    al_draw_textf(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, (altura_tela / 2) + 30, ALLEGRO_ALIGN_CENTER, "Pontuação: %d", pontuacao);
                    al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2 + 50, ALLEGRO_ALIGN_CENTER, "Pressione ENTER para jogar novamente");
                    al_draw_text(fonte, al_map_rgb(255, 255, 255), largura_tela / 2, altura_tela / 2 + 70, ALLEGRO_ALIGN_CENTER, "Pressione ESC para voltar ao menu");
                }
            }
            else if (estado == ESTADO_ENCICLOPEDIA) {
                al_draw_scaled_bitmap(
                    fundo_enciclopedia,
                    0, 0, 
                    500, 550, 
                    0, 0,
                    800, 900,
                    0
                );

                al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 30, ALLEGRO_ALIGN_CENTER, "ENCICLOPEDIA");
                al_draw_text(pontos, al_map_rgb(0, 0, 0), 400, 880, ALLEGRO_ALIGN_CENTER, "Pressione ESC para voltar ao menu");

                textosEnciclopedia(peixes, maiorFase, jogoZerado, highScore, peixes1, peixes2);
            }

            al_flip_display();
        }
    }

    al_destroy_font(fonte);
    al_destroy_font(pontos);
    al_destroy_font(titulo);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    al_destroy_bitmap(sprite_lixeiras);
    al_destroy_bitmap(sprite_lixos);
    al_destroy_bitmap(fundo_menu);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(icone_vida);
    al_destroy_bitmap(gameOver);
    al_destroy_bitmap(fundo_enciclopedia);
    al_destroy_bitmap(peixes1);
    al_destroy_bitmap(peixes2);

    return 0;
}