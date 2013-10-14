#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>

#include <time.h>
#include <math.h>
#include "piece.c"
#include "affichage_sdl.c"
#include "gameLogic.h"

int **createTable(int nbLin, int nbCol);
/// Initialise la SDL
void initSDL(SDL_Surface **ptr_screen);
/// Crée un GameMatrix
GameMatrix* newGameMatrix(SDL_Surface *screen);
/// Temporise (attend le temps nécessaire pour atteindre les FPS souhaités)
void tempoFps(int *nextTick, int ticksBetweenFrames);
/// Calcul les vrais FPS
void computeTrueFps(int *realFps, int *realFpsCpt, int *lastSecondTicks);


int main(int argc, char** argv)
{
	
	int continuer = 1, vitesse = 6, cadre = 10, score = 0, nbLignes = 0, nbLignesTotale = 0, scoring = 0;
	int i = 0,j = 0;
	clock_t depart, fin;
	GameMatrix *surface = NULL;
	
	/// Titre de la fenêtre
	char caption[64];
	
	/** Gérer les FPS **/
	/// Nombre de FPS qu'on veut atteindre
	int goalFps = 50;
	/// Temps qui se passe entre deux frames (en millisecondes)
	int ticksBetweenFrames = 1*(1000/goalFps);
	/// Tick à attendre avant la prochaine frame (en millisecondes)
	int nextTick = 0;
	/// Vrais FPS
	int realFps = goalFps, realFpsCpt = 0, lastSecondTicks = 0;
	/// Compteur pour descendre la pièce mobile
	int moveDownCpt = 0;

	/** Variables SDL **/
	SDL_Surface *screen = NULL, *texteScore = NULL;
	SDL_Event event;
	
	// Tableau qui représente toutes les pièces possibles
	int pieces[NB_PIECES][5][5] = {{{0,0,10,0,0},{0,0,10,0,0},{0,0,11,0,0},{0,0,10,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,20,20,0,0},{0,20,21,0,0},{0,0,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,0,0,0},{0,30,31,30,0},{0,0,30,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,40,0,0},{0,0,41,0,0},{0,0,40,40,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,50,0,0},{0,0,51,0,0},{0,50,50,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,60,0,0},{0,60,61,0,0},{0,60,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,70,0,0},{0,0,71,70,0},{0,0,0,70,0},{0,0,0,0,0}}};
		
	
	

	srand(time(NULL));


	// Envoie l'adresse du pointeur de sorte à le modifier
	initSDL(&screen);
	// Crée une nouvelle surface de jeu
	surface = newGameMatrix(screen);
	
		
	addPiece(surface, pieces);
		
		
	do
	{
		moveDownCpt++;
		realFpsCpt++;
		nbLignes = 0;		
		scoring = 0;
		/* Gère les évenements */
		while(SDL_PollEvent(&event))
		{
			
			switch(event.type)
			{
				case SDL_KEYDOWN: // Gère l'appui sur une touche
					switch(event.key.keysym.sym)
					{
						case SDLK_LEFT:
							moveLeft(surface);
							break;
						case SDLK_RIGHT:
							moveRight(surface);
							break;
						case SDLK_UP:
							rotate(surface);
							break;
						case SDLK_ESCAPE:
							continuer = 0;
						case SDLK_DOWN:
							vitesse*=5;						
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_DOWN: //pour descendre plus vite
							vitesse/=5;
							break;
						
						default:
							break;	
							
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
			}*/
		
		drawGrid(screen, surface->coteBloc, surface->width, surface->height, cadre);
		drawGameMatrix(screen, surface, cadre);
		SDL_Flip(screen);
		
		// Régule les FPS
		tempoFps(&nextTick, ticksBetweenFrames);
		// Calcul les vrais FPS
		computeTrueFps(&realFps, &realFpsCpt, &lastSecondTicks);
		
		// Met à jour le titre de la fenêtre
		sprintf(caption, "Tetris Powaaa ! %d fps !", realFps);
		SDL_WM_SetCaption(caption, NULL);

		if(moveDownCpt >= realFps/vitesse)
		{
			moveDownCpt = 0;
			if(moveDown(surface) == 1)
			{
				
				nbLignes = (fixPiece(surface));
				printf("nombre de lignes = %d\n",nbLignes);
				
				
				scoring = pow(2,nbLignes-1)*100;
				if (scoring < 100)
					score -= 50;
					
				score += scoring;	
				
				printf("score = %d\n", score);
				
				nbLignesTotale += nbLignes;
				if (nbLignesTotale >= 10)
				{
					nbLignesTotale -= 10;
					vitesse += 2; 
				}
					
				if (surface->surf[2][4] !=0)
					continuer = 0;
					
				else	
					addPiece(surface, pieces);
				
			}
		}
	}while (continuer);
	
	SDL_FreeSurface(screen);
	
	
	return EXIT_SUCCESS;
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

/* Initialise la SDL
 * ptr_screen : Pointeur sur le pointeur de la SDL_Surface
 * On récupère un pointeur sur un pointeur pour modifier le pointeur
 * original
*/
void initSDL(SDL_Surface **ptr_screen)
{
	/*************************** Initialisation SDL	***************************/ 
	atexit(SDL_Quit);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
 
	// Modifie la valeur du pointeur 'screen'
	*ptr_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE || SDL_DOUBLEBUF);
	
	if (*ptr_screen == NULL) {
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	printf("%p\n", *ptr_screen);
	SDL_WM_SetCaption("Tetris Powaaaa !", NULL);
	

	/*************************** Initialisation SDL	***************************/ 
}

GameMatrix* newGameMatrix(SDL_Surface *screen)
{
	int i = 0,j = 0;
	
	/** Crée la surface de jeu **/
	GameMatrix *surface = malloc(sizeof(GameMatrix));
	/// Dimensions de la grille de jeu
	surface->height = 22;
	surface->width = 10;
	surface->surf = createTable(surface->height, surface->width);
	
	// Calcul de la largeur d'un bloc en fonction des dimensions de la fenêtre
	surface->coteBloc = (HEIGHT-CADRE*2)/surface->height;
	
	// Initialisation de la surface à 0
	for(i = 0; i < surface->height; i++)
		for(j = 0; j < surface->width; j++)
			surface->surf[i][j] = 0;
				
	// Initialisation des couleurs		
	surface->colors[0] = SDL_MapRGB(screen->format, 255,0,0); // Rouge
	surface->colors[1] = SDL_MapRGB(screen->format, 0,0,255); // Bleu
	surface->colors[2] = SDL_MapRGB(screen->format, 189,141,70); // Brun
	surface->colors[3] = SDL_MapRGB(screen->format, 255,0,255); // Magenta
	surface->colors[4] = SDL_MapRGB(screen->format, 255,255,255); // Blanc
	surface->colors[5] = SDL_MapRGB(screen->format, 0,255,255); // Cyan
	surface->colors[6] = SDL_MapRGB(screen->format, 0,255,0); // Vert
	
	return surface;
}


void tempoFps(int *nextTick, int ticksBetweenFrames)
{
	// Si on doit attendre avant la prochaine frame
	if(*nextTick > SDL_GetTicks())
		SDL_Delay(*nextTick - SDL_GetTicks());
	// On calcule le tick où la prochaine frame va s'afficher
	*nextTick = SDL_GetTicks() + ticksBetweenFrames;
}

void computeTrueFps(int *realFps, int *realFpsCpt, int *lastSecondTicks)
{
	if(SDL_GetTicks() >= *lastSecondTicks+1000)
	{
		*realFps = *realFpsCpt;
		*realFpsCpt = 0;
		*lastSecondTicks = SDL_GetTicks();
	}
}

