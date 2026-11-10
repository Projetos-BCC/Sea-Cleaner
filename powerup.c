#include "powerup.h"
#include "lixo.h"
#include "lixeira.h"
#include "configs.h"
#include <string.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

void inicializaPowerUp(struct PowerUp *powerUp) {
	powerUp->ativo = 0;
	powerUp->largura = 30;
	powerUp->altura = 30;
	powerUp->velocidade = 3;
}

void gerarPowerUp(struct PowerUp* powerUp, struct Lixeira *lixeira) {
	if (powerUp->ativo == 0 && rand() % 750 == 0) {
		powerUp->ativo = 1;
		powerUp->y = -40;
		powerUp->x = rand() % (largura_tela - powerUp->largura);
		int tipoRand;

		if (lixeira->vida >= 10) {
			tipoRand = 1 + rand() % 3;
		}
		else {
			tipoRand = rand() % 4;
		}

		if (tipoRand == 0) {
			strcpy_s(powerUp->tipo, sizeof(powerUp->tipo), "Vida");
		} else if (tipoRand == 1) {
			strcpy_s(powerUp->tipo, sizeof(powerUp->tipo), "Lenta");
		}
		else if (tipoRand == 2) {
			strcpy_s(powerUp->tipo, sizeof(powerUp->tipo), "Ima");
		}
		else {
			strcpy_s(powerUp->tipo, sizeof(powerUp->tipo), "Conversao");
		}
	}
}

void moverPowerUp(struct PowerUp* powerUp) {
	if (powerUp->ativo == 1) {
		powerUp->y += powerUp->velocidade;

		if (powerUp->y > altura_tela) {
			powerUp->ativo = 0;
		}
	}
}

void desenhaPowerUp(struct PowerUp powerUp) {
	if (powerUp.ativo == 1) {
		ALLEGRO_COLOR cor;

		if (strcmp(powerUp.tipo, "Vida") == 0) {
			cor = al_map_rgb(255, 0, 0);
		}
		else if (strcmp(powerUp.tipo, "Lenta") == 0) {
			cor = al_map_rgb(0, 120, 255);
		}
		else if (strcmp(powerUp.tipo, "Ima") == 0) {
			cor = al_map_rgb(160, 0, 200);
		}
		else {
			cor = al_map_rgb(0, 200, 0);
		}

		al_draw_filled_circle(powerUp.x + powerUp.largura / 2, powerUp.y + powerUp.altura / 2, powerUp.largura / 2, cor);
	}
}

int colidePowerUp(struct PowerUp powerUp, struct Lixeira lixeira) {
	if (powerUp.ativo == 1 && powerUp.x + powerUp.largura > lixeira.x && powerUp.x < lixeira.x + lixeira.largura &&
		powerUp.y + powerUp.altura > lixeira.y && powerUp.y < lixeira.y + lixeira.altura) {
		return 1;
	}
	return 0;
}

void ativaPowerUp(struct PowerUp powerUp, struct Lixeira* lixeira, int *tempoLento, int *tempoIma) {
	if (strcmp(powerUp.tipo, "Vida") == 0) {
		lixeira->vida += 2;
		if (lixeira->vida > 10) {
			lixeira->vida = 10;
		}
	} else if (strcmp(powerUp.tipo, "Lenta") == 0) {
		*tempoLento = 400;
	}
	else if (strcmp(powerUp.tipo, "Ima") == 0) {
		*tempoIma = 400;
	}
	else if (strcmp(powerUp.tipo, "Conversao") == 0) {
		lixeira->tempoConversao = 30;
		strcpy_s(lixeira->tipoConversao, sizeof(lixeira->tipoConversao), lixeira->tipo);
	}
}