void addPiece(GameMatrix *surface, int pieces[NB_PIECES][5][5])
{
	int index = rand()%NB_PIECES;
	int x, y, i = 1;
	int posX = surface->width/2, posY = 2;
	
	
	
	
	// Récupère les coordonnées du centre la pièce
	surface->pieceMobile[0].x = posX-1;
	surface->pieceMobile[0].y = posY-1;
	surface->pieceMobile[0].color = index;
	
	// Parcours le tableau de la pièce tirée au hasard
	for(x = 0; x < 5; x++)
		for(y = 0; y < 5; y++)
		{
			// Si la case représente un carré et que ce carré n'est pas le centre de la pièce
			if(pieces[index][y][x] != 0 && pieces[index][y][x]%10 == 0)
			{
				// Calcul les coordonnées du carré dans la surface de jeu
				surface->pieceMobile[i].x = posX+x-3;
				surface->pieceMobile[i].y = posY+y-3;
				surface->pieceMobile[i].color = index;
				
				i++;
			}
		}
		
}

void fixPiece(GameMatrix *surface)
{
	int i, x, y, resLigne = 0;
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		
		surface->surf[y][x] = surface->pieceMobile[i].color+1;
	}
	
	
		
		
}
int moveLeft(GameMatrix *surface)
{
	int i = 0, x, y;
	// Parcours la liste des carrés
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		// Collision avec le bord gauche ou une pièce fixe à gauche
		if( (x == 0) )
			return 1;
		if(surface->surf[y][x-1] > 0 && surface->surf[y][x-1] < 10)
			return 1;
	}
	// Déplacement
	for(i = 0; i < 4; i++)
		surface->pieceMobile[i].x--;
	return 0;
}

int moveRight(GameMatrix *surface)
{
	int i = 0, x, y;
	// Collisions
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		if( (x == surface->width-1) )
			return 1;
		if(surface->surf[y][x+1] > 0 && surface->surf[y][x+1] < 10)
			return 1;
	}
	// Déplacement
	for(i = 0; i < 4; i++)
		surface->pieceMobile[i].x++;
	
	return 0;
}

int moveDown(GameMatrix *surface)
{
	
	int i = 0, x, y;
		
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		
		if( (y == surface->height-1) )
			return 1;
		if(surface->surf[y+1][x] > 0 && surface->surf[y+1][x] < 10)
			return 1;
	}
	for(i = 0; i < 4; i++)
		surface->pieceMobile[i].y++;
	
	return 0;
}

int rotate(GameMatrix *surface)
{
	int i;
	// Coordonnées d'un carré et du centre du carré
	int x, y, xC, yC;
	
	xC = surface->pieceMobile[0].x;
	yC = surface->pieceMobile[0].y;
	
		
	
	// Cherche pas à comprendre, sinon démontre ces deux formules :P
	for(i = 1; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		surface->pieceMobile[i].x = xC - y + yC;
		surface->pieceMobile[i].y = yC + x - xC;
		
		
	}
	return 0;
}

int testerLignes (GameMatrix *surface) // fonction qui test si les lignes sont pleines
{
	
	int i, j, produitLigne = 1, x, y, nbLigne, scoring;
	
	for (j = 0; j < 21;j++);
	{
		produitLigne = 1;
		
		for (i = 0; i < 10; i++) 
		{	
			produitLigne *= surface->surf[21][i]; //on fait le produit de toutes les cases de la ligne (si = 0 au moins une case n'est pas pleine)
		}
		
		if (produitLigne !=0)
		{
			nbLigne++;
			for (y = j; y>=1; y--)
			{
				for (x = 0; x < 10; x++)
				{
					surface->surf[y][x] = surface->surf[y-1][x]; //si il y a une ligne pleine, chaque ligne prend la valeur de celle qui est au dessus
				}					
					
			}	
			
		}	
	}
	scoring = (pow(2,nbLigne-1))*100; //on renvoi le score calculé en fonction du nombre de lignes complètes
	
	return scoring;
}




