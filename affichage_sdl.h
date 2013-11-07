#ifndef _AFFICHAGE_SDL_
#define _AFFICHAGE_SDL_

#include "affichage_sdl.c"

struct Fps
{
	/// Nombre de FPS qu'on veut atteindre
	int goal;
	/// Temps qui se passe entre deux frames (en millisecondes)
	int ticksBetweenFrames;
	/// Tick à attendre avant la prochaine frame (en millisecondes)
	int nextTick;
	/// Vrais FPS
	int real, realCpt, lastSecondTicks;
};
typedef struct Fps Fps;

void setPixel(SDL_Surface *screen, int x, int y, Uint32 color);
void drawSquare(SDL_Surface *screen, int coteBloc, Uint32 color, int hBlocs, int vBlocs, int cadre);
void drawGrid(SDL_Surface *screen, int coteBloc, int hBlocs, int vBlocs, int cadre);
void drawGameMatrix(SDL_Surface *screen, GameMatrix *surface, int cadre);
void initSDL(SDL_Surface **ptr_screen, TTF_Font **ptr_police);



#endif
