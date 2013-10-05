/** Catalogues des pièces du Tetris **/

struct SurfaceJeu
{
	int hauteur, largeur;
	int coteBloc;
	int **surf;
};
typedef struct SurfaceJeu SurfaceJeu;

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
