void mainMenu(SDL_Surface *screen, TTF_Font *police)
{
	int compteur = 0, choix = 0, i = 1;
	SDL_Event event;
	SDL_Surface *esiea, *menu[4];
	SDL_Color couleurBlanche = {255, 255, 255};
	SDL_Color couleurJaune = {255, 255, 0};
	SDL_Rect *positions = (SDL_Rect*)malloc(4*sizeof(SDL_Rect));
	char **titres = (char**)malloc(4*11*sizeof(char));
	
	titres[0] = "Jouer";
	titres[1] = "Options";
	titres[2] = "Highscores";
	titres[3] = "Quit";
	
	/************positionnement des titres *************/
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,50,50)); 
	
	/// Initialise le menu
	for(i = 0; i < 4; i++)
	{
		positions[i].x = 300;
		positions[i].y = i*150 + 50;
		
		if(compteur == i)
			menu[i] = TTF_RenderText_Blended(police, titres[i], couleurJaune);
		else
			menu[i] = TTF_RenderText_Blended(police, titres[i], couleurBlanche);
	}
	/************positionnement des titres *************/
	
	do
	{
		SDL_Flip(screen);
		
		// Affichage du menu
		for(i = 0; i < 4; i++)
		{
			SDL_FreeSurface(menu[i]);
			if(compteur == i)
				menu[i] = TTF_RenderText_Blended(police, titres[i], couleurJaune);
			else
				menu[i] = TTF_RenderText_Blended(police, titres[i], couleurBlanche);
				
			SDL_BlitSurface(menu[i], NULL, screen, &positions[i]); 
		}
		
		// Evenements
		while(SDL_PollEvent(&event))
		{
				
			switch(event.type)
			{
				case SDL_KEYDOWN: // Gère l'appui sur une touche
					switch(event.key.keysym.sym)
					{
						case SDLK_DOWN: //incremente compteur (modulo 4 pour rester entre 0 et 3)
							compteur = ((compteur+1)+4)%4 ;
							break;
						case SDLK_UP: //décrémente compteur
							compteur = ((compteur-1)+4)%4;
							break;
						case SDLK_RETURN: //gere "ENTER" en fonction du titre selectionné
							switch(compteur)
							{
								case 0:
									SDL_FreeSurface(screen);
									return;
									break;
								case 1:
									//TODO Fonction Option	
									break;
								case 2:
									//TODO Fonction Highscore
									break;
								case 3:
									free(titres);
										
									TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
									TTF_Quit();
		
									SDL_FreeSurface(screen);
									SDL_Quit();
									exit(EXIT_SUCCESS);
									break;
							}
					}	
						
			}	
		}		
	}while (i = 1);
	
}


/* A finir !! */
int inGameInterface(SDL_Surface *screen, TTF_Font *police, int score)
{
	// Texte du score
	char texteScore[10];
	SDL_Surface *surfaceScore = NULL;
	SDL_Color couleurBlanche = {255, 255, 255};
	
	//texte du bloc suivant
	SDL_Surface *prochainBloc;
	SDL_Color Gris = {150,150,150};
	SDL_Rect positionTexte;
	positionTexte.x = 280;
	positionTexte.y = 250;
	prochainBloc = TTF_RenderText_Blended(police, "Bloc suivant:", Gris);
	SDL_BlitSurface(prochainBloc, NULL, screen, &positionTexte);
	
	// Position du score
	SDL_Rect positionScore;
	positionScore.x = WIDTH/2;
	positionScore.y = 450;
	
	// Met à jour l'affichage du score
	SDL_FreeSurface(surfaceScore);
	sprintf(texteScore, "Score : %d", score);
	surfaceScore = TTF_RenderText_Blended(police, texteScore, couleurBlanche);
	SDL_BlitSurface(surfaceScore, NULL, screen, &positionScore);
	
	return 0;
}

void afficherProchainePiece (GameMatrix *pieceSuivante, int indicePiece,int pieces[NB_PIECES][5][5], TTF_Font *police, SDL_Surface *screen)
{
	

	int x, y, i = 1;	
	int posX = 4, posY = 5;
	
	
	// Récupère les coordonnées du centre la pièce
	pieceSuivante->pieceMobile[0].x = posX-1;
	pieceSuivante->pieceMobile[0].y = posY-1;
	pieceSuivante->pieceMobile[0].color = indicePiece;
	
	// Parcours le tableau de la pièce tirée au hasard
	for(x = 0; x < 5; x++)
		for(y = 0; y < 5; y++)
		{
			// Si la case représente un carré et que ce carré n'est pas le centre de la pièce
			if(pieces[indicePiece][y][x] != 0 && pieces[indicePiece][y][x]%10 == 0)
			{
				// Calcul les coordonnées du carré dans la surface de jeu
				pieceSuivante->pieceMobile[i].x = posX+x-3;
				pieceSuivante->pieceMobile[i].y = posY+y-3;
				pieceSuivante->pieceMobile[i].color = indicePiece;
				
				i++;
			}
		}
		
	
}	
