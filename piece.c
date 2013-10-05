struct GameMatrix
{
	int height, width;
	int coteBloc;
	int **surf;
	Uint32 colors[7];
};
typedef struct GameMatrix GameMatrix;

struct Piece
{
	int x, y;
	int type;
	int tab;
	int cote;
};
typedef struct Piece Piece;

/** Couleurs des pièces
- 0		I		rouge
- 1 	O		bleu
- 2 	T		brun
- 3 	L		magenta
- 4 	J		blanc
- 5 	Z		cyan
- 6 	S		vert
**/
