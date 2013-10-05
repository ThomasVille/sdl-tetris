#define HAUTEUR 20
#define LARGEUR 10
#define WIDTH 800
#define HEIGHT 600
#define CADRE 10

void setPixel(SDL_Surface *screen, int x, int y, Uint32 coul)
{
  *((Uint32*)(screen->pixels) + x + y * screen->w) = coul;
}

// Dessine un carré dans le repère de la surface de jeu
void dessinerCarre(SDL_Surface *screen, int coteBloc, int x, int y)
{
	SDL_Rect blitrect = {CADRE + x*coteBloc,CADRE + y*coteBloc,0,0};
	SDL_Surface *carre = NULL;
	// TODO Calculer width et length avant
	carre = SDL_CreateRGBSurface(0,coteBloc,coteBloc,32, 255,255,255,255);
	SDL_FillRect(carre, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_BlitSurface(carre,NULL, screen, &blitrect);
	
	SDL_FreeSurface(carre);
	
}

void dessinerGrille(SDL_Surface *screen, int coteBloc)
{
	int x, y;
	for(y = CADRE; y < CADRE+HAUTEUR*coteBloc+1; y += coteBloc)
	{
		for(x = CADRE; x < CADRE+LARGEUR*coteBloc; x++)
		{
			setPixel(screen, x,y, SDL_MapRGB(screen->format, 100,100,100));
		}
	}
}
