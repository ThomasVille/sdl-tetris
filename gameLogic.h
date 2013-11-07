#ifndef _GAME_LOGIC_
#define _GAME_LOGIC_

#include "gameLogic.c"

void addPiece(GameMatrix *surface, int pieces[NB_PIECES][5][5], int index);
int fixPiece(GameMatrix *surface);

int moveLeft(GameMatrix *surface);
int moveRight(GameMatrix *surface);
/// Retourne 1 si la pièce atteint le bas, 0 sinon
int moveDown(GameMatrix *surface);
int rotate(GameMatrix *surface);
int testerLignes(GameMatrix *surface);



#endif
