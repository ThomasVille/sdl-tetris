#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include "piece.c"
#include "affichage_sdl.c"


void nouvellePiece(SurfaceJeu*);
void deplacerGauche(Piece *piece);
void deplacerBas(Piece *piece);
void deplacerDroite(Piece *piece);
int testCollisions(Piece piece);
void dessinerPiece(SDL_Surface *screen, Piece piece);
int **createTable(int nbLin, int nbCol);

/* DEBUG */
void addRandElem(SurfaceJeu *);

int main(int argc, char** argv)
{
	int continuer = 1;
	int i = 0,j = 0;
	
	/** Variables SDL **/
	SDL_Surface *screen = NULL;
	SDL_Event event;
	
	/** Variables Jeu **/

	/** Crée la surface de jeu **/
	SurfaceJeu *surface = malloc(sizeof(SurfaceJeu));
	surface->hauteur = 20;
	surface->largeur = 10;
	surface->surf = createTable(surface->hauteur, surface->largeur);
	
	// Calcul de la largeur d'un bloc en fonction des dimensions de la fenêtre
	surface->coteBloc = (HEIGHT-CADRE*2)/surface->hauteur;
	
	// Initialisation de la surface à 0
	for(i = 0; i < surface->hauteur; i++)
		for(j = 0; j < surface->largeur; j++)
			surface->surf[i][j] = 0;	
	
	/*************************** Initialisation SDL	***************************/ 
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
 
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
 
	if (screen == NULL) {
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
 
	SDL_WM_SetCaption("Tetris Powaaaa !", NULL);
	
	/*************************** Initialisation SDL	***************************/ 

	
	nouvellePiece(surface);
	/** S'arrêtera quand le tableau est plein **/
	do
	{
		/* Gère les évenements */
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN: // Gère l'appui sur une touche
					switch(event.key.keysym.sym)
					{
						case SDLK_LEFT:
							//deplacerGauche(piece_qui_descend);
							break;
						case SDLK_RIGHT:
							//deplacerDroite(piece_qui_descend);
							
							/* DEBUG */
							addRandElem(surface);
							break;
						case SDLK_ESCAPE:
							continuer = 0;
					}
					break;
							
				case SDL_QUIT:
					continuer = 0;
			}
		}
		
		/* Rempli l'écran de noir */
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 50,50,50));
		/*for(i=0;i<=((WIDTH*2)/3);i++){
			for(j=0;j<=CADRE;j++){
				setPixel(screen, i,j,SDL_MapRGB(screen->format, 100,100,100));
			}
		}*/
		//dessinerGrille(screen, coteBloc);
		//deplacerBas(piece_qui_descend);
		//dessinerPiece(screen, *piece_qui_descend);
		dessinerSurfaceJeu(screen, surface);
		
		SDL_Flip(screen);
		
		usleep(500000);

	}while (continuer);
	
	SDL_FreeSurface(screen);
	
	return EXIT_SUCCESS;
}

void nouvellePiece(SurfaceJeu *surface)
{
	surface->surf[0][surface->largeur/2] = 10;
}

void deplacerGauche(Piece *piece)
{
	piece->x--;
	if(testCollisions(*piece))
		piece->x++;

}

void deplacerBas(Piece *piece)
{
	piece->y++;
	if(testCollisions(*piece))
		piece->y--;
}
void deplacerDroite(Piece *piece)
{
	piece->x++;
	if(testCollisions(*piece))
		piece->x--;

}
int testCollisions(Piece piece)
{
	if(piece.x < 0 || piece.x >= LARGEUR || piece.y < 0 || piece.y >= HAUTEUR)
		return 1;
	return 0;
		
}

void dessinerPiece(SDL_Surface *screen, Piece piece)
{
	dessinerCarre(screen, piece.cote, piece.x, piece.y);
}

// Crée un tableau à 2 dimensions
int **createTable(int nbLin, int nbCol){
	int i = 0;
	int **tableau = (int **)malloc(sizeof(int*)*nbLin);
	int *tableau2 = (int *)malloc(sizeof(int)*nbCol*nbLin);
	for(i = 0 ; i < nbLin ; i++){
		tableau[i] = &tableau2[i*nbCol];
	}
	return tableau;
}
/* DEBUG */
void addRandElem(SurfaceJeu *surface)
{
	int x = rand()%surface->largeur;
	int y = rand()%surface->hauteur;
	surface->surf[y][x] = 10;
}
