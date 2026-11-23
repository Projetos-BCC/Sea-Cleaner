#include "enciclopedia.h"
#include "configs.h"
#include <string.h>
#include <stdlib.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void inicializaEspecies(struct Especie especies[]) {

    //peixe 1
    strcpy_s(especies[0].nome, sizeof(especies[0].nome), "Andira");
    strcpy_s(especies[0].habitat, sizeof(especies[0].habitat), "Rio Santo Antônio (MG)");
    strcpy_s(especies[0].ameacas, sizeof(especies[0].ameacas), "Poluição, mineração e construção de barragens.");
    strcpy_s(especies[0].objetivo, sizeof(especies[0].objetivo), "Chegar ao stage 2");
    especies[0].desbloqueada = 0;

    // peixe 2
    strcpy_s(especies[1].nome, sizeof(especies[1].nome), "BarrigudO");
    strcpy_s(especies[1].habitat, sizeof(especies[1].habitat), "Rios e riachos do Paraná");
    strcpy_s(especies[1].ameacas, sizeof(especies[1].ameacas), "Poluição e destruição do habitat.");
    strcpy_s(especies[1].objetivo, sizeof(especies[1].objetivo), "");
    especies[1].desbloqueada = 0;

    // peixe 3
    strcpy_s(especies[2].nome, sizeof(especies[2].nome), "Canivete");
    strcpy_s(especies[2].habitat, sizeof(especies[2].habitat), "Rios Piquiri e Ivaí (PR)");
    strcpy_s(especies[2].ameacas, sizeof(especies[2].ameacas), "Construção de hidrelétricas.");
    strcpy_s(especies[2].objetivo, sizeof(especies[2].objetivo), "");
    especies[2].desbloqueada = 0;

    // peixe 4
    strcpy_s(especies[3].nome, sizeof(especies[3].nome), "Lambari");
    strcpy_s(especies[3].habitat, sizeof(especies[3].habitat), "Rios e riachos de água doce");
    strcpy_s(especies[3].ameacas, sizeof(especies[3].ameacas), "Poluição e desmatamento das margens.");
    strcpy_s(especies[3].objetivo, sizeof(especies[3].objetivo), "");
    especies[3].desbloqueada = 0;

    // peixe 5
    strcpy_s(especies[6].nome, sizeof(especies[6].nome), "Dourada (Apapá)");
    strcpy_s(especies[6].habitat, sizeof(especies[6].habitat), "Rio Araguaia e seus afluentes");
    strcpy_s(especies[6].ameacas, sizeof(especies[6].ameacas), "Pesca excessiva e degradação dos rios.");
    strcpy_s(especies[6].objetivo, sizeof(especies[6].objetivo), "");
    especies[6].desbloqueada = 0;

    // peixe 6
    strcpy_s(especies[7].nome, sizeof(especies[7].nome), "Pirarara");
    strcpy_s(especies[7].habitat, sizeof(especies[7].habitat), "Rios da Amazônia e do Araguaia");
    strcpy_s(especies[7].ameacas, sizeof(especies[7].ameacas), "Pesca excessiva e destruição do habitat.");
    strcpy_s(especies[7].objetivo, sizeof(especies[7].objetivo), "");
    especies[7].desbloqueada = 0;

    // peixe 7
    strcpy_s(especies[8].nome, sizeof(especies[8].nome), "Piraíba");
    strcpy_s(especies[8].habitat, sizeof(especies[8].habitat), "Rios profundos da Amazônia e do Araguaia");
    strcpy_s(especies[8].ameacas, sizeof(especies[8].ameacas), "Pesca predatória e degradação dos rios.");
    strcpy_s(especies[8].objetivo, sizeof(especies[8].objetivo), "");
    especies[8].desbloqueada = 0;

    // peixe 8
    strcpy_s(especies[8].nome, sizeof(especies[8].nome), "Pintado");
    strcpy_s(especies[8].habitat, sizeof(especies[8].habitat), "Rios das bacias do Paraná e do São Francisco.");
    strcpy_s(especies[8].ameacas, sizeof(especies[8].ameacas), "Barragens, poluição e pesca excessiva.");
    strcpy_s(especies[8].objetivo, sizeof(especies[8].objetivo), "");
    especies[8].desbloqueada = 0;

    // peixe 9
    strcpy_s(especies[8].nome, sizeof(especies[8].nome), "Pirarucu");
    strcpy_s(especies[8].habitat, sizeof(especies[8].habitat), "Rios e lagos da região amazônica.");
    strcpy_s(especies[8].ameacas, sizeof(especies[8].ameacas), "Pesca excessiva e destruição do habitat.");
    strcpy_s(especies[8].objetivo, sizeof(especies[8].objetivo), "");
    especies[8].desbloqueada = 0;

}

void textosEnciclopedia(ALLEGRO_FONT* titulo, int maiorFase, int jogoZerado, int highscore) {
    //TEXTO PEIXES
    if (maiorFase >= 2) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 338, ALLEGRO_ALIGN_CENTER, "ANDIRA");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 338, ALLEGRO_ALIGN_CENTER, "FASE 2");
    }
    
    if (maiorFase >= 3) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 338, ALLEGRO_ALIGN_CENTER, "BARRIGUDO");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 338, ALLEGRO_ALIGN_CENTER, "FASE 3");
    }

    if (maiorFase >= 4) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 338, ALLEGRO_ALIGN_CENTER, "CANIVETE");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 338, ALLEGRO_ALIGN_CENTER, "FASE 4");
    }

    if (jogoZerado == 1) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 575, ALLEGRO_ALIGN_CENTER, "LAMBARI");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 575, ALLEGRO_ALIGN_CENTER, "ZERAR");
    }

    if (highscore >= 128) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 575, ALLEGRO_ALIGN_CENTER, "DOURADA");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 575, ALLEGRO_ALIGN_CENTER, "128 PONTOS");
    }

    if (highscore >= 128) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 575, ALLEGRO_ALIGN_CENTER, "DOURADA");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 575, ALLEGRO_ALIGN_CENTER, "128 PONTOS");
    }

    if (highscore >= 448) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 575, ALLEGRO_ALIGN_CENTER, "PIRARARA");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 575, ALLEGRO_ALIGN_CENTER, "448 PONTOS");
    }

    if (highscore >= 848) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 816, ALLEGRO_ALIGN_CENTER, "PIRAIBA");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 178, 816, ALLEGRO_ALIGN_CENTER, "848 PONTOS");
    } 
    
    if (highscore >= 1328) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 816, ALLEGRO_ALIGN_CENTER, "PINTADO");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 400, 816, ALLEGRO_ALIGN_CENTER, "1328 PONTOS");
    }

    if (highscore >= 1888) {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 816, ALLEGRO_ALIGN_CENTER, "PIRARUCU");
    }
    else {
        al_draw_text(titulo, al_map_rgb(0, 0, 0), 622, 816, ALLEGRO_ALIGN_CENTER, "1888 PONTOS");
    }
}