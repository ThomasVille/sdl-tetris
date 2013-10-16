#ifndef _INTERFACE_
#define _INTERFACE_

#include "interface.c"

int mainMenu(SDL_Surface *screen);
int inGameInterface(SDL_Surface *screen, TTF_Font *police, int score);

#endif
