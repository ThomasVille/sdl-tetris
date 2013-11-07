#ifndef _INTERFACE_
#define _INTERFACE_

#include "interface.c"

void mainMenu(SDL_Surface *screen, TTF_Font *police);
int inGameInterface(SDL_Surface *screen, TTF_Font *police, int score);
void afficherProchainePiece (GameMatrix *pieceSuivante, int indicePiece,int pieces[NB_PIECES][5][5],TTF_Font *police, SDL_Surface *screen);

#endif
