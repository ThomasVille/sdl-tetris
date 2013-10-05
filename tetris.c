#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>
#include "piece.c"
#include "affichage_sdl.c"


void addPiece(GameMatrix*, int[NB_PIECES][5][5]);
void moveLeft(Piece *piece);
void moveDown(Piece *piece);
void moveRight(Piece *piece);
int testCollisions(Piece piece);
void drawPiece(SDL_Surface *screen, Piece piece);
int **createTable(int nbLin, int nbCol);

/* DEBUG */
void addRandElem(GameMatrix *);

int main(int argc, char** argv)
{
	int continuer = 1;
	int i = 0,j = 0;

	// Tableau qui représente toutes les pièces possibles
	int pieces[NB_PIECES][5][5] = {{{0,0,10,0,0},{0,0,10,0,0},{0,0,10,0,0},{0,0,10,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,20,20,0,0},{0,20,20,0,0},{0,0,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,0,0,0},{0,30,30,30,0},{0,0,30,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,40,0,0},{0,0,40,0,0},{0,0,40,40,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,50,0,0},{0,0,50,0,0},{0,50,50,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,60,0,0},{0,60,60,0,0},{0,60,0,0,0},{0,0,0,0,0}},
								   {{0,0,0,0,0},{0,0,70,0,0},{0,0,70,70,0},{0,0,0,70,0},{0,0,0,0,0}}};

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
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
 
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
	
	addPiece(surface, pieces);
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

void moveLeft(Piece *piece)
{
	piece->x--;
	if(testCollisions(*piece))
		piece->x++;

}

void moveDown(Piece *piece)
{
	piece->y++;
	if(testCollisions(*piece))
		piece->y--;
}
void moveRight(Piece *piece)
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

void drawPiece(SDL_Surface *screen, Piece piece)
{
	//drawSquare(screen, piece.cote, piece.x, piece.y);
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
