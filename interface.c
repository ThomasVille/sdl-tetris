int mainMenu(SDL_Surface *screen)
{
	SDL_Surface *background, *curseur, *esiea, *menu[4];
	
	return 0;
}


/* A finir !! */
int inGameInterface(SDL_Surface *screen, TTF_Font *police, int score)
{
	// Texte du score
	char texteScore[10];
	SDL_Surface *surfaceScore = NULL;
	SDL_Color couleurBlanche = {255, 255, 255};
	
	// Position du score
	SDL_Rect positionScore;
	positionScore.x = WIDTH/2;
	positionScore.y = HEIGHT/2;
	
	// Met à jour l'affichage du score
	sprintf(texteScore, "Score : %d", score);
	surfaceScore = TTF_RenderText_Blended(police, texteScore, couleurBlanche);
	SDL_BlitSurface(surfaceScore, NULL, screen, &positionScore);
	
	return 0;
}
