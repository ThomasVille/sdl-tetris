char* SaisieNom (SDL_Surface *screen, TTF_Font *police)
{
		int i=0;
		char *name = NULL, texteNom[26];
		SDL_Event event;
		SDL_Surface *titre, *saisie, *gameOver;
		SDL_Color couleurBlanche = {200, 200, 200}, couleurSaisie = {150,50,50}, couleurRouge = {255,50,50};
		SDL_Rect entete, nomEntre, perdu;
		SDL_EnableKeyRepeat(0,0);
		name = (char*)calloc(sizeof(char),20);
		
		perdu.x = 340;
		perdu.y = 70;
		
		entete.x = 260;
		entete.y = 200;
		
		nomEntre.x = 240;
		nomEntre.y = 300;
		
		sprintf(texteNom, "%s", name);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,40,30)); 
		gameOver = TTF_RenderText_Blended(police, "Perdu", couleurRouge);
		saisie = TTF_RenderText_Blended(police, texteNom, couleurSaisie);
		titre = TTF_RenderText_Blended(police, "Entrez votre nom", couleurBlanche);
		SDL_BlitSurface(gameOver, NULL, screen, &perdu);
		SDL_BlitSurface(titre, NULL, screen, &entete); 
		SDL_BlitSurface(saisie, NULL, screen, &nomEntre);
		SDL_Flip(screen);
		
					
			
			while (SDL_WaitEvent(&event))
			{
				switch(event.type)
				{
					case SDL_KEYDOWN: // Gère l'appui sur une touche
						switch(event.key.keysym.sym)
						{
								case SDLK_ESCAPE:
									exit(EXIT_SUCCESS);
								break;
								case SDLK_RETURN:
									for (;i<19;i++)
									{
										name[i] = ' ';	
									}
									return name;
								break;
								case SDLK_BACKSPACE://pour effacer, on reaffiche toutes les surfaces
									if (i>0)
									{
										name[i-1] = '\0';//on met a zero la case d avant
										i--;// on decremente i pour reecrire dans la case ensuite
										SDL_FreeSurface(saisie);
										sprintf(texteNom, "%s", name);
										SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,40,30)); 
										saisie = TTF_RenderText_Blended(police, texteNom, couleurSaisie);
										//printf("le nom est affiché\n");		
										SDL_BlitSurface(saisie, NULL, screen, &nomEntre);
										SDL_BlitSurface(titre, NULL, screen, &entete); 
										SDL_BlitSurface(gameOver, NULL, screen, &perdu); 
										SDL_Flip(screen);		
										printf("nom = %s\n", name);
									}
								

						}	
						
				
					if (SDLK_a <= event.key.keysym.sym && event.key.keysym.sym <= SDLK_z)//zones des caracteres minuscules
					{
						if (i<=19)
						{
							name[i] = event.key.keysym.sym;//on recupere la valeur entrée
							sprintf(texteNom, "%s", name);
							SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,40,30)); 
							SDL_FreeSurface(saisie);
							saisie = TTF_RenderText_Blended(police, texteNom, couleurSaisie);
							printf("le nom est affiché\n");		
							SDL_BlitSurface(saisie, NULL, screen, &nomEntre); 
							SDL_BlitSurface(titre, NULL, screen, &entete); 
							SDL_BlitSurface(gameOver, NULL, screen, &perdu);
							SDL_Flip(screen);
							
							i++;
							printf("nom = %s\n", name);
						}
						else return name;
					} 
					if (SDLK_KP0 <= event.key.keysym.sym && event.key.keysym.sym <= SDLK_KP9)//zones des caracteres minuscules
					{
						if (i<=19)
						{
							name[i] = event.key.keysym.sym + '0';//on recupere la valeur entrée
							sprintf(texteNom, "%s", name);
							SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,40,30)); 
							SDL_FreeSurface(saisie);
							saisie = TTF_RenderText_Blended(police, texteNom, couleurSaisie);
							printf("le nom est affiché\n");		
							SDL_BlitSurface(saisie, NULL, screen, &nomEntre); 
							SDL_BlitSurface(titre, NULL, screen, &entete); 
							SDL_BlitSurface(gameOver, NULL, screen, &perdu);
							SDL_Flip(screen);
							
							i++;
							printf("nom = %s\n", name);
						}
						else return name;
					} 
							SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,50,40,30)); 
							SDL_FreeSurface(saisie);
							saisie = TTF_RenderText_Blended(police, texteNom, couleurSaisie);
							printf("le nom est affiché\n");		
							SDL_BlitSurface(saisie, NULL, screen, &nomEntre); 
							SDL_BlitSurface(titre, NULL, screen, &entete); 
							SDL_BlitSurface(gameOver, NULL, screen, &perdu);
							SDL_Flip(screen);
						
				}
			
			}			
		
		
			
			
}	
	
		



void EnregistrerScore (int score, char *name)
{
	FILE* FichierScore = fopen("scores.txt", "a+"), *buffer = fopen("buffer.txt", "a+");//ouvre le fichier scores.txt en mode lecture ecriture en bout de fichier
	char chaineScore[9];
	int i = 0;
	sprintf(chaineScore,"%d",score);
	
	for (i = strlen(chaineScore); i<8;i++) //on complete la chaine du score pour pouvoir avoir un ecart constant
	{
			chaineScore[i] = ' ';
			//printf("chaine du score %s\n",chaineScore);
	}
	chaineScore[8]='\0';	
	
	
	if (FichierScore != NULL)
	{
		fprintf(FichierScore,"%s %s\n", name, chaineScore);//on ecrit le nom puis le score dasn le fichier
		
		
		
		fclose(FichierScore);
	}
	else printf("impossible de charger le fichier scores.txt (verfifiez les droits de lecture/ecriture)\n");	
		
}	



