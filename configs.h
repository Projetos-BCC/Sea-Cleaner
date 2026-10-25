#ifndef CONFIG_H
#define CONFIG_H

extern int largura_tela;
extern int altura_tela;

typedef enum {
	ESTADO_MENU,
	ESTADO_JOGANDO,
	ESTADO_GAMEOVER
} estadoJogo;

#endif