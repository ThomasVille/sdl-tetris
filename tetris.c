#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include "piece.c"
#include "affichage_sdl.c"


void nouvellePiece(Piece*, int);
void deplacerGauche(Piece *piece);
void deplacerBas(Piece *piece);
void deplacerDroite(Piece *piece);
int testCollisions(Piece piece);
void dessinerPiece(SDL_Surface *screen, Piece piece);

int main(int argc, char** argv)
{
	/** Variables SDL **/
	SDL_Surface *screen = NULL;
	SDL_Event event;
	
	/** Variables Jeu **/
	int surface_jeu[HAUTEUR][LARGEUR];
	Piece *piece_qui_descend = malloc(sizeof(Piece)); // Pièce qui descend, controlable par le joueur
	int continuer = 1;
	int i = 0,j = 0;
	
	// Initialisation du tableau à 0
	for(i = 0; i < HAUTEUR; i++)
		for(j = 0; j < LARGEUR; j++)
			surface_jeu[i][j] = 0;
	
	/** Graphique **/
	// Calcul de la largeur d'un bloc en fonction des dimensions de la fenêtre
	int coteBloc = (HEIGHT-CADRE*2)/HAUTEUR;
	
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

	
	nouvellePiece(piece_qui_descend, coteBloc);
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
							deplacerGauche(piece_qui_descend);
							break;
						case SDLK_RIGHT:
							deplacerDroite(piece_qui_descend);
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
		dessinerGrille(screen, coteBloc);
		deplacerBas(piece_qui_descend);
		dessinerPiece(screen, *piece_qui_descend);
		
		SDL_Flip(screen);
		
		usleep(500000);

	}while (continuer);
	
	SDL_FreeSurface(screen);
	
	return EXIT_SUCCESS;
}

void nouvellePiece(Piece *piece, int cote)
{
	piece->x = LARGEUR/2;
	piece->y = 0;
	piece->type = rand()%8;
	piece->cote = cote;
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

