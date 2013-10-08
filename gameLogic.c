void addPiece(GameMatrix *surface, int pieces[NB_PIECES][5][5])
{
	int index = rand()%NB_PIECES;
	int x, y, i = 0;
	int posX = surface->width/2, posY = 3;
	for(x = 0; x < 5; x++)
		for(y = 0; y < 5; y++)
		{
			if(pieces[index][y][x] != 0)
			{
				surface->pieceMobile[i].x = posX+x-3;
				surface->pieceMobile[i].y = posY+y-3;
				
				printf("%d %d\n", surface->pieceMobile[i].x, surface->pieceMobile[i].y);
				i++;
			}
		}
		
}

int moveLeft(GameMatrix *surface)
{
	int i = 0, x, y;
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		if( (x == 0) )
			return 1;
		if(surface->surf[y][x-1] > 0 && surface->surf[y][x-1] < 10)
			return 1;
	}
	for(i = 0; i < 4; i++)
		surface->pieceMobile[i].x--;
	return 0;
}

int moveRight(GameMatrix *surface)
{
	int i = 0, x, y;
	for(i = 0; i < 4; i++)
	{
		x = surface->pieceMobile[i].x;
		y = surface->pieceMobile[i].y;
		if( (x == surface->width-1) )
			return 1;
		if(surface->surf[y][x+1] > 0 && surface->surf[y][x+1] < 10)
			return 1;
	}
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
		printf("Salope ! x = %d y = %d\n", x, y);
		if( (y == surface->height-1) )
			return 1;
		if(surface->surf[y+1][x] > 0 && surface->surf[y+1][x] < 10)
			return 1;
	}
	for(i = 0; i < 4; i++)
		surface->pieceMobile[i].y++;
	
	return 0;
}

