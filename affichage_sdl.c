#define WIDTH 800
#define HEIGHT 600
#define CADRE 10
#define NB_PIECES 7

/** Dessine un pixel
 * screen : Surface cible
 * x, y : Coordonnées du point
 * color : Couleur du pixel à dessiner
**/
void setPixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
  *((Uint32*)(screen->pixels) + x + y * screen->w) = color;
}

/** Dessine un carré dans le repère de la surface de jeu
 * screen : Surface cible
 * coteBloc : Largeur d'un bloc
 * color : Couleur du bloc à dessiner
 * hBlocs : Position horizontale du bloc
 * vBlocs : Position verticale du bloc
 * cadre : Décalage du bord de la surface
**/
void drawSquare(SDL_Surface *screen, int coteBloc, Uint32 color, int hBlocs, int vBlocs, int cadre)
{
	SDL_Rect blitrect = {cadre + hBlocs*coteBloc, cadre + vBlocs*coteBloc,0,0};
	SDL_Surface *carre = NULL;
	// TODO Calculer width et length avant
	carre = SDL_CreateRGBSurface(0,coteBloc,coteBloc,32, 0, 0, 0,255);
	SDL_FillRect(carre, NULL, color);
	SDL_BlitSurface(carre,NULL, screen, &blitrect);
	
	SDL_FreeSurface(carre);
	
}

/** Dessine la grille de la surface de jeu
 * screen : Surface cible
 * coteBloc : Largeur d'un bloc
 * hBlocs : Dimension horizontale de la grille en blocs
 * hBlocs : Dimension verticale de la grille en blocs
 * cadre : Décalage du bord de la surface
**/
void drawGrid(SDL_Surface *screen, int coteBloc, int hBlocs, int vBlocs, int cadre)
{
	int x, y;
	for(y = cadre; y < cadre+vBlocs*coteBloc+1; y += coteBloc)
	{
		for(x = cadre; x < cadre+hBlocs*coteBloc; x++)
		{
			setPixel(screen, x,y, SDL_MapRGB(screen->format, 100,100,100));
		}
	}
	
	for(x = cadre; x < cadre+hBlocs*coteBloc+1; x += coteBloc)
	{
		for(y = cadre; y < cadre+vBlocs*coteBloc; y++)
		{
			setPixel(screen, x,y, SDL_MapRGB(screen->format, 100,100,100));
		}
	}
}

/** Dessine la surface de jeu
 * screen : Surface cible
 * surface : Surface de jeu à dessiner
 * cadre : Décalage du bord de la surface
**/
void drawGameMatrix(SDL_Surface *screen, GameMatrix *surface, int cadre)
{
	int x, y, val, colorIndex, i;
	// Dessine la surface de jeu
	for(y = 0; y < surface->height; y++)
	{
		for(x = 0; x < surface->width; x++)
		{
			val = surface->surf[y][x];
			if(val != 0)
			{
				colorIndex = val;
				drawSquare(screen, surface->coteBloc,surface->colors[colorIndex-1], x, y, cadre);
			}
		}
	}
	// Dessine la pièce mobile
	for(i = 0; i < 4; i++)
	{
		drawSquare(screen, surface->coteBloc, surface->colors[surface->pieceMobile[0].color], surface->pieceMobile[i].x, surface->pieceMobile[i].y, cadre);
	}
}
