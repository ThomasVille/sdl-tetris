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
int initSDL(SDL_Surface *screen);


int main(int argc, char** argv)
{
	
	int continuer = 1, vitesse = 6, cadre = 10, score = 0, nbLignes = 0, nbLignesTotale = 0, scoring = 0;
	int i = 0,j = 0;
	clock_t depart, fin;

	// Tableau qui représente toutes les pièces possibles
	int pieces[NB_PIECES][5][5] = {{{0,0,10,0,0},{0,0,10,0,0},{0,0,11,0,0},{0,0,10,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,20,20,0,0},{0,20,21,0,0},{0,0,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,0,0,0},{0,30,31,30,0},{0,0,30,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,40,0,0},{0,0,41,0,0},{0,0,40,40,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,50,0,0},{0,0,51,0,0},{0,50,50,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,60,0,0},{0,60,61,0,0},{0,60,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,70,0,0},{0,0,71,70,0},{0,0,0,70,0},{0,0,0,0,0}}};
		
	/** Variables SDL **/
	SDL_Surface *screen = NULL, *texteScore = NULL;
	SDL_Event event;
	
	/*************************** Initialisation SDL	***************************/ 
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
 
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
 
	if (screen == NULL) {
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
 
	SDL_WM_SetCaption("Tetris Powaaaa !", NULL);
	

	/*************************** Initialisation SDL	***************************/ 
/*	if(initSDL(screen) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printf("%p\n", screen);*/
	srand(time(NULL));


	/** Crée la surface de jeu **/
	GameMatrix *surface = malloc(sizeof(GameMatrix));
	surface->height = 22;
	surface->width = 10;
	surface->surf = createTable(surface->height, surface->width);
	// Calcul de la largeur d'un bloc en fonction des dimensions de la fenêtre
	surface->coteBloc = (HEIGHT-CADRE*2)/surface->height;
	
	// Initialisation de la surface à 0
	for(i = 0; i < surface->height; i++)
		for(j = 0; j < surface->width; j++)
			surface->surf[i][j] = 0;
				
			
	surface->colors[0] = SDL_MapRGB(screen->format, 255,0,0); // Rouge
	surface->colors[1] = SDL_MapRGB(screen->format, 0,0,255); // Bleu
	surface->colors[2] = SDL_MapRGB(screen->format, 189,141,70); // Brun
	surface->colors[3] = SDL_MapRGB(screen->format, 255,0,255); // Magenta
	surface->colors[4] = SDL_MapRGB(screen->format, 255,255,255); // Blanc
	surface->colors[5] = SDL_MapRGB(screen->format, 0,255,255); // Cyan
	surface->colors[6] = SDL_MapRGB(screen->format, 0,255,0); // Vert
	
		
	addPiece(surface, pieces);
	
	depart = clock();
		
		
	
	do
	{
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
		
		if(clock() > depart + (CLOCKS_PER_SEC)/vitesse)
		{
			
			depart = clock();
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

/*
int initSDL(SDL_Surface *screen)
{
		
	return 0;
}
*/
