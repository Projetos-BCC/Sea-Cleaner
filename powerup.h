#ifndef POWERUP_H
#define POWERUP_H

#include "lixeira.h"

struct PowerUp {
	float x, y;
	int largura, altura;
	int velocidade;
	int ativo;
	char tipo[20];
};

void inicializaPowerUp(struct PowerUp* powerUp);
void gerarPowerUp(struct PowerUp* powerUp, struct Lixeira *lixeira);
void moverPowerUp(struct PowerUp* powerUp);
void desenhaPowerUp(struct PowerUp powerUp);
int colidePowerUp(struct PowerUp PowerUp, struct Lixeira lixeira);
void ativaPowerUp(struct PowerUp PowerUp, struct Lixeira* lixeira, int *tempoLento, int *tempoIma);

#endif