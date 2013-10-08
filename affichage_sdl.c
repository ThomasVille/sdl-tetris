#define HAUTEUR 22
#define LARGEUR 10
#define WIDTH 800
#define HEIGHT 600
#define CADRE 10
#define NB_PIECES 7

void setPixel(SDL_Surface *screen, int x, int y, Uint32 coul)
{
  *((Uint32*)(screen->pixels) + x + y * screen->w) = coul;
}

// Dessine un carré dans le repère de la surface de jeu
void drawSquare(SDL_Surface *screen, int coteBloc, Uint32 color, int x, int y)
{
	SDL_Rect blitrect = {CADRE + x*coteBloc,CADRE + y*coteBloc,0,0};
	SDL_Surface *carre = NULL;
	// TODO Calculer width et length avant
	carre = SDL_CreateRGBSurface(0,coteBloc,coteBloc,32, 0, 0, 0,255);
	SDL_FillRect(carre, NULL, color);
	SDL_BlitSurface(carre,NULL, screen, &blitrect);
	
	SDL_FreeSurface(carre);
	
}

// Dessine la grille de la surface de jeu
void drawGrid(SDL_Surface *screen, int coteBloc)
{
	int x, y;
	for(y = CADRE; y < CADRE+HAUTEUR*coteBloc+1; y += coteBloc)
	{
		for(x = CADRE; x < CADRE+LARGEUR*coteBloc; x++)
		{
			setPixel(screen, x,y, SDL_MapRGB(screen->format, 100,100,100));
		}
	}
	
	for(x = CADRE; x < CADRE+LARGEUR*coteBloc+1; x += coteBloc)
	{
		for(y = CADRE; y < CADRE+HAUTEUR*coteBloc; y++)
		{
			setPixel(screen, x,y, SDL_MapRGB(screen->format, 100,100,100));
		}
	}
}

void drawGameMatrix(SDL_Surface *screen, GameMatrix *surface)
{
	int x, y, val, colorIndex, i;
	// Dessine la surface de jeu
	for(y = 0; y < HAUTEUR; y++)
	{
		for(x = 0; x < LARGEUR; x++)
		{
			val = surface->surf[y][x];
			if(val != 0)
			{
				colorIndex = val/10;
				drawSquare(screen, surface->coteBloc,surface->colors[colorIndex-1], x, y);
			}
		}
	}
	// Dessine la pièce mobile
	for(i = 0; i < 4; i++)
	{
		drawSquare(screen, surface->coteBloc, surface->colors[0], surface->pieceMobile[i].x, surface->pieceMobile[i].y);
	}
}
