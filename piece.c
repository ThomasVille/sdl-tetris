struct Carre
{
	int x, y;
	int color;
};
typedef struct Carre Carre;

struct GameMatrix
{
	int height, width; /// Largeur et hauteur de la surface de jeu en blocs
	int coteBloc;
	int **surf;
	Carre pieceMobile[4];
	Uint32 colors[7];
};
typedef struct GameMatrix GameMatrix;

/** Couleurs des pièces
- 0		I		rouge
- 1 	O		bleu
- 2 	T		brun
- 3 	L		magenta
- 4 	J		blanc
- 5 	Z		cyan
- 6 	S		vert
**/
