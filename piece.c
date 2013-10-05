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

/** Types :
- 0 : T
- 1 : L
- 2 : L inversé
- 3 : I
- 4 : Z
- 5 : Z inversé
- 6 : carré
- 7 : carré simple
**/
