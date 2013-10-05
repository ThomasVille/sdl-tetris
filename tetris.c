#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>
#include "piece.c"
#include "affichage_sdl.c"


void addPiece(GameMatrix*, int[NB_PIECES][5][5]);
int moveLeft(GameMatrix*);
int moveRight(GameMatrix*);
int moveDown(GameMatrix*);
int testCollisions(Piece piece);
int **createTable(int nbLin, int nbCol);

/* DEBUG */
void addRandElem(GameMatrix *);

int main(int argc, char** argv)
{
	int continuer = 1;
	int i = 0,j = 0;

	// Tableau qui représente toutes les pièces possibles
	int pieces[NB_PIECES][5][5] = {{{0,0,10,0,0},{0,0,10,0,0},{0,0,11,0,0},{0,0,10,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,20,20,0,0},{0,20,21,0,0},{0,0,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,0,0,0},{0,30,31,30,0},{0,0,30,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,40,0,0},{0,0,41,0,0},{0,0,40,40,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,50,0,0},{0,0,51,0,0},{0,50,50,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,60,0,0},{0,60,61,0,0},{0,60,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,70,0,0},{0,0,71,70,0},{0,0,0,70,0},{0,0,0,0,0}}};

	/** Variables SDL **/
	SDL_Surface *screen = NULL;
	SDL_Event event;
	
	srand(time(NULL));
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
	
	/* DEBUG */
	surface->surf[21][5] = 1;
	
	addPiece(surface, pieces);
	/** TODO S'arrêtera quand le tableau sera plein **/
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
							moveLeft(surface);
							break;
						case SDLK_RIGHT:
							moveRight(surface);
							
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
		drawGrid(screen, surface->coteBloc);
		moveDown(surface);
		
		drawGameMatrix(screen, surface);
		
		SDL_Flip(screen);
		
		usleep(500000);

	}while (continuer);
	
	SDL_FreeSurface(screen);
	
	return EXIT_SUCCESS;
}

void addPiece(GameMatrix *surface, int pieces[NB_PIECES][5][5])
{
	int index = rand()%NB_PIECES;
	int x, y;
	int posX = surface->width/2, posY = 3;
	for(x = 0; x < 5; x++)
		for(y = 0; y < 5; y++)
		{
			if(pieces[index][y][x] != 0)
				surface->surf[posY+y-3][posX+x-3] = pieces[index][y][x];
		}
		
}

int moveLeft(GameMatrix *surface)
{
	int x, y;
	/* Vérifie que la pièce n'est pas au bord */
	for(y = 0; y < surface->height; y++)
		if(surface->surf[y][0] >= 10)
			return 1;
	
	
	
	/* Parcours chaque lignes du tableau de droite à gauche et vérifie que
	 * l'on a pas une case mobile suivie d'une case fixe */
	 for(y = 0; y < surface->height; y++)
		for(x = surface->width-2; x >= 0; x--)
			if(surface->surf[y][x+1] >= 10 && surface->surf[y][x] < 10 && surface->surf[y][x] != 0)
			{
				printf("Bloqué par un bloc fixe\n");
				return 1;
			}
			
			
	/* Parcours le tableau depuis la gauche pour déplacer les cases une par une */
	for(y = 0; y < surface->height; y++)
		for(x = 1; x < surface->width; x++)
			if(surface->surf[y][x-1] == 0 && surface->surf[y][x] >= 10) // Si on est sur une case mobile à droite d'une case vide
			{
				// Copie l'ancienne case dans la nouvelle
				surface->surf[y][x-1] = surface->surf[y][x];
				// Supprime l'ancienne
				surface->surf[y][x] = 0;
			}
	return 0;
}
int moveRight(GameMatrix *surface)
{
	int x, y;
	/* Vérifie que la pièce n'est pas au bord */
	for(y = 0; y < surface->height; y++)
		if(surface->surf[y][surface->width-1] >= 10)
			return 1;
	
	
	/* Parcours chaque lignes du tableau de gauche à droite et vérifie que
	 * l'on a pas une case mobile suivie d'une case fixe */
	 for(y = 0; y < surface->height; y++)
		for(x = 1; x < surface->width; x++)
			if(surface->surf[y][x-1] >= 10 && surface->surf[y][x] < 10 && surface->surf[y][x] != 0)
			{
				printf("Bloqué par un bloc fixe\n");
				return 1;
			}
	
	
	/* Parcours le tableau depuis la droite pour déplacer les cases une par une */
	for(y = 0; y < surface->height; y++)
		for(x = surface->width-2; x >= 0; x--) // -1 pour être à la fin du tableau et -1 pour ne pas parcourir la dernière case
			if(surface->surf[y][x+1] == 0 && surface->surf[y][x] >= 10) // Si on est sur une case mobile à gauche d'une case vide
			{
				// Copie l'ancienne case dans la nouvelle
				surface->surf[y][x+1] = surface->surf[y][x];
				// Supprime l'ancienne
				surface->surf[y][x] = 0;
			}
	return 0;
}

int moveDown(GameMatrix *surface)
{
	int x, y;
	/* Vérifie qu'on peut descendre */
	
	// Vérifie qu'on est pas arrivé au sol
	for(x = 0; x < surface->width; x++)
	{
		printf(" %d ", surface->surf[surface->height-1][x]);
		if(surface->surf[surface->height-1][x] >= 10)
		{
			printf("Fin de la ligne\n");
			return 2;
		}
	}
	printf("\n");
	
	
	/* Parcours chaque colonne du tableau de haut en bas et vérifie que
	 * l'on a pas une case mobile suivie d'une case fixe */
	 for(x = 0; x < surface->width; x++)
		for(y = 1; y < surface->height; y++)
			if(surface->surf[y-1][x] >= 10 && surface->surf[y][x] < 10 && surface->surf[y][x] != 0)
			{
				printf("Bloqué par un bloc fixe\n");
				return 1;
			}
	
	
	/* Parcours le tableau depuis le bas pour déplacer les cases une par une */
	for(x = 0; x < surface->width; x++)
		for(y = surface->height-2; y >= 0; y--) // -1 pour être à la fin du tableau et -1 pour ne pas parcourir la dernière case
			if(surface->surf[y+1][x] == 0 && surface->surf[y][x] >= 10) // Si on est sur une case mobile au dessus d'une case vide
			{
				// Copie l'ancienne case dans la nouvelle
				surface->surf[y+1][x] = surface->surf[y][x];
				// Supprime l'ancienne
				surface->surf[y][x] = 0;
			}
	return 0;
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
void addRandElem(GameMatrix *surface)
{
	int x = rand()%surface->width;
	int y = rand()%surface->height;
	surface->surf[y][x] = 10;
}
