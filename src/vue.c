#include "fonctions.h"
 
/*****************************************
 * Vue
 ****************************************/

void cleanup()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int init(int imgFlags)
{
     // Demarre SDL
    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
        return -1;
    }
    // Demarre IMG
    if ( IMG_Init(imgFlags) != imgFlags )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_image : '%s'\n",IMG_GetError());
        cleanup();
        return -1;
    }
    //Demarre TTF
    if ( TTF_Init() == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_TTF : '%s'\n",TTF_GetError());
        cleanup();
        return -1;
    }
    return 0;
}

SDL_Surface* creer_fenetre()
{
    SDL_Surface* pWindowSurface = SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Rummikub", NULL);
    SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));
    return pWindowSurface;
}

SDL_Rect afficher_image_menu(SDL_Surface* pWindowSurface, const char* imagePath, int num)
{
    SDL_Rect blitDestination;
    SDL_Surface* pImage = IMG_Load(imagePath);
    blitDestination.x = WINDOW_WIDTH/2 - pImage->w/2;
    if(num==1)
    {
        blitDestination.y = WINDOW_HEIGHT/2 - pImage->h/2;
    }
    else
    {
        blitDestination.y = 475;
    }
    blitDestination.w = pImage->w;
    blitDestination.h = pImage->h;
    SDL_BlitSurface(pImage,NULL,pWindowSurface,&blitDestination);
    SDL_Flip(pWindowSurface);
    SDL_FreeSurface(pImage);
    return blitDestination;
}

SDL_Surface* ecrire_texte(TTF_Font* pFont,const char texte[], SDL_Color color, SDL_Surface *ecran, int y)
{
    SDL_Rect position;
    SDL_Surface* texte_choisir_mode = TTF_RenderText_Solid(pFont,texte,color);
    position.x = WINDOW_WIDTH/2 - texte_choisir_mode->w/2;; 
    position.y = y;
    position.w = texte_choisir_mode->w;
    position.h = texte_choisir_mode->h;
    SDL_BlitSurface(texte_choisir_mode,NULL,ecran,&position);
    SDL_Flip(ecran);
    SDL_FreeSurface(texte_choisir_mode);
    return texte_choisir_mode;
}

SDL_Rect creer_surface(SDL_Surface *ecran, int x, int y,int w,int h,int rouge, int vert, int bleu)
{
    SDL_Rect position;
    SDL_Surface* mode_jeu1 = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
    position.x = x; 
    position.y = y;
    position.w = w;
    position.h = h;
    SDL_FillRect(mode_jeu1, NULL, SDL_MapRGB(ecran->format, rouge,vert,bleu)); 
    SDL_BlitSurface(mode_jeu1, NULL, ecran, &position); 
    return position;
}

SDL_Rect afficher_bouton(TTF_Font* pFont,const char num_tuile[],SDL_Color fontColor, SDL_Surface *ecran, int x, int y,int w,int h,int rouge, int vert, int bleu, int x_num_tuile, int y_num_tuile)
{
    SDL_Rect position;
    SDL_Surface* mode_jeu1 = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
    position.x = x; 
    position.y = y;
    position.w = w;
    position.h = h;
    SDL_FillRect(mode_jeu1, NULL, SDL_MapRGB(ecran->format, rouge,vert,bleu)); 
    SDL_BlitSurface(mode_jeu1, NULL, ecran, &position); 

    SDL_Rect position_num_tuile;
    SDL_Surface* affiche_tuile= TTF_RenderText_Solid(pFont,num_tuile,fontColor);
    position_num_tuile.x = x_num_tuile;
    position_num_tuile.y = y_num_tuile;
    position_num_tuile.w = affiche_tuile->w;
    position_num_tuile.h = affiche_tuile->h;
    SDL_BlitSurface(affiche_tuile,NULL,ecran,&position_num_tuile);

    return position;
}

void afficher_board (SDL_Surface* pWindowSurface) 
{
    SDL_Rect imagechev;
    SDL_Surface* imageChevalet = IMG_Load("./data/board.PNG");
    imagechev.x = WINDOW_WIDTH/2 - imageChevalet->w/2;
    imagechev.y = 420;
    imagechev.w = imageChevalet->w;
    imagechev.h = imageChevalet->h;
    SDL_BlitSurface(imageChevalet,NULL,pWindowSurface,&imagechev);
}

void afficher_combinaisons (SDL_Surface* pWindowSurface)
{
    SDL_Rect position;
    SDL_Surface* combinaison_jeu = SDL_CreateRGBSurface(SDL_HWSURFACE, 687, 365, 32, 0, 0, 0, 0);
    position.x = 13;
    position.y = 35;
    position.w = combinaison_jeu->w;
    position.h = combinaison_jeu->h;
    SDL_FillRect(combinaison_jeu, NULL, SDL_MapRGB(pWindowSurface->format, 64,0,0));
    SDL_BlitSurface(combinaison_jeu, NULL, pWindowSurface, &position);
}

void afficher_tab_jeu(SDL_Surface* pWindowSurface,const char* fontPath)
{
    SDL_WM_SetCaption("Jouer Partie", NULL);
    SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));
    
    SDL_Color fontColor = {90, 30, 41};
    
    TTF_Font* pFont = TTF_OpenFont(fontPath,40);
    TTF_SetFontStyle(pFont, TTF_STYLE_BOLD);
    TTF_Font* pScore = TTF_OpenFont(fontPath,15);
    TTF_SetFontStyle(pScore , TTF_STYLE_BOLD);
    TTF_Font* pFont1 = TTF_OpenFont(fontPath,20);
    TTF_SetFontStyle(pFont1, TTF_STYLE_BOLD);

    SDL_Rect position;
    
    SDL_Surface* combinaisons_tuiles = TTF_RenderText_Solid(pFont1,"Vos Combinaisons",fontColor);
    position.x = WINDOW_WIDTH/3 - combinaisons_tuiles->w/2;
    position.y = WINDOW_HEIGHT/50;
    position.w = combinaisons_tuiles->w;
    position.h = combinaisons_tuiles->h;
    SDL_BlitSurface(combinaisons_tuiles,NULL,pWindowSurface,&position);

    afficher_board(pWindowSurface);

    afficher_combinaisons(pWindowSurface);

    SDL_Flip(pWindowSurface);
}



void afficher_score (SDL_Surface* pWindowSurface, int nbJoueurs,const char* fontPath, CHEVALET* chevaletsJoueurs,char** les_pseudos, int tourJoueur)
{
    int i;
    SDL_Color fontColor = {90, 30, 41};
    TTF_Font* pScore = TTF_OpenFont(fontPath,15);
    TTF_SetFontStyle(pScore , TTF_STYLE_BOLD);
    SDL_Rect position;
    char score[10] = "";
    TTF_Font* pFont1 = TTF_OpenFont(fontPath,20);
    TTF_SetFontStyle(pFont1, TTF_STYLE_BOLD);

    //tableau de points

    SDL_Surface* board_points = SDL_CreateRGBSurface(SDL_HWSURFACE, 255, 300, 32, 0, 0, 0, 0);
    position.x = WINDOW_WIDTH/2 + board_points->w/1.1;
    position.y = 50;
    position.w = board_points->w;
    position.h = board_points->h;
    SDL_FillRect(board_points, NULL, SDL_MapRGB(pWindowSurface->format, 255,255,200));
    SDL_BlitSurface(board_points, NULL, pWindowSurface, &position); // Collage de la surface sur l'Ã©cran

    SDL_Surface* board_point = SDL_CreateRGBSurface(SDL_HWSURFACE, 120, 300, 32, 0, 0, 0, 0);
    position.x = 725;
    position.y = 50;
    position.w = board_point->w;
    position.h = board_point->h;
    SDL_FillRect(board_point, NULL, SDL_MapRGB(pWindowSurface->format, 255,255,255));
    SDL_BlitSurface(board_point, NULL, pWindowSurface, &position); // Collage de la surface sur l'Ã©cran
    
    //progression du jeu
    SDL_Surface* affiche_tour = TTF_RenderText_Solid(pScore,"A qui le tour?",fontColor);
    position.x = 730;
    position.y = 80;
    position.w = affiche_tour->w;
    position.h = affiche_tour->h;
    SDL_BlitSurface(affiche_tour,NULL,pWindowSurface,&position);

    /*SDL_Surface* affiche_joueur = TTF_RenderText_Solid(pScore,"Joueur:",fontColor);
    position.x = 730;
    position.y = 120;
    position.w = affiche_joueur->w;
    position.h = affiche_joueur->h;
    SDL_BlitSurface(affiche_joueur,NULL,pWindowSurface,&position);*/

    // On affiche les scores quand le jeu progresse
    SDL_Surface* combinaisons = TTF_RenderText_Solid(pFont1,"SCORES\n",fontColor);
    position.x = 865;
    position.y = 80;
    position.w = combinaisons->w;
    position.h = combinaisons->h;
    SDL_BlitSurface(combinaisons,NULL,pWindowSurface,&position);

    position.x = 955;
    position.y = 90;
    for (i=0; i<nbJoueurs; i++) {
        sprintf(score, "%d", chevaletsJoueurs[i].joueur.scoreJoueur);
        SDL_Surface* score_final = TTF_RenderText_Solid(pScore,score,fontColor);
        position.y += 50;
        position.w = score_final->w;
        position.h = score_final->h;
        SDL_BlitSurface(score_final,NULL,pWindowSurface,&position);
    }

    position.x = 847;
    position.y = 90;
    for (i=0; i<nbJoueurs; i++) {
        SDL_Surface* affiche_score2 = TTF_RenderText_Solid(pScore,les_pseudos[i],fontColor);
        position.y += 50;
        position.w = affiche_score2->w;
        position.h = affiche_score2->h;
        SDL_BlitSurface(affiche_score2,NULL,pWindowSurface,&position);
    }

    efface_tour(pWindowSurface);
    afficher_tour(pWindowSurface,fontPath,les_pseudos[tourJoueur]);
    
    SDL_Flip(pWindowSurface);
}

bool clic_bouton (SDL_Event event, SDL_Rect imagejouer)
{
    if((((event.button.x > imagejouer.x) || (event.button.x == imagejouer.x)) && 
        ((event.button.x < imagejouer.w+imagejouer.x) || (event.button.x == imagejouer.w+imagejouer.x)))
        &&
        (((event.button.y > imagejouer.y) || (event.button.y == imagejouer.y)) && 
        ((event.button.y < imagejouer.h+imagejouer.y) || (event.button.y == imagejouer.h+imagejouer.y))))
    return true;
    else return false;
}

void afficher_modeJeu(SDL_Surface* pWindowSurface, const char* fontPath, TTF_Font* pFont, SDL_Color color_black)
{
    //Choisir le mode de jeu
    SDL_WM_SetCaption("Rummikub Mode de jeu", NULL);
    SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));

    TTF_Font* font_mode = TTF_OpenFont(fontPath,20); 
    ecrire_texte(pFont,"Choisir votre mode de jeu", color_black, pWindowSurface, WINDOW_HEIGHT/10);

    //Humain VS Humain
    creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 175, 150, 350, 80,192, 192, 192); 
    ecrire_texte(font_mode,"Humain VS Humain", color_black, pWindowSurface, 170);

    //Humain VS Ordinateur
    creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 175, 300, 350, 80,192, 192, 192);
    ecrire_texte(font_mode,"Humain VS Ordinateur", color_black, pWindowSurface, 320);
    SDL_Flip(pWindowSurface);  
}

bool verif_clic (SDL_Event event) 
{
    bool boolean;
    switch(event.type)
    {
        case SDL_QUIT:
            boolean = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            boolean = true;
            break;
    }
    return boolean;
}

SDL_Color get_color(enum COULT couleur) 
{
    SDL_Color color_black = {0, 0, 0};
    SDL_Color color_jaune = {255, 255, 0}; 
    SDL_Color color_rouge = {255,0,0};
    SDL_Color color_blue = {30,144,255};
    if (couleur == Jaune) return color_jaune;
    else if (couleur == Bleu) return color_blue;
    else if (couleur == Rouge) return color_rouge;
    return color_black;
}

void tuile_active(SDL_Surface* ecran, int x, int y)
{
    SDL_Rect position;
    SDL_Surface* active_tuile = SDL_CreateRGBSurface(SDL_HWSURFACE, 53, 83, 32, 0, 0, 0, 0);
    position.x = x;
    position.y = y;
    SDL_FillRect(active_tuile, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
    SDL_BlitSurface(active_tuile, NULL, ecran, &position);
}

int retourne_pos (int numTuile)
{
    if (numTuile>=10) return 5;
    else return 10;
}

void afficher_tuiles (TTF_Font* pFont, SDL_Surface *pWindowSurface, TABTUILES tab, int x, int y, int interface)
{
    SDL_Rect position;
    int ajout;
    char numeroTuile[10];
    int i;
    SDL_Color color;
    position.x = x;
    position.y = y;
    for (i=0; i<tab.nbrTuiles; i++) {
        if (i == 9 && interface == 1) {
            position.y += 80;
            position.x = 240;
        }
        else position.x += 60;
        if (tab.tuiles[i].typeTuile != -1) 
        {
            if (tab.tuiles[i].typeTuile != Joker)
            {
                sprintf(numeroTuile, "%d", tab.tuiles[i].numTuile);
            }
            else numeroTuile[10] = 'J';
            color = get_color(tab.tuiles[i].coulTuile);
            ajout = retourne_pos(tab.tuiles[i].numTuile);
            afficher_bouton(pFont,numeroTuile,color, pWindowSurface, position.x, position.y,50,79,255, 255, 255, position.x+ajout, position.y+22);
            SDL_Flip(pWindowSurface);
        }
    }
}


bool afficher_finPartie(SDL_Surface* pWindowSurface, const char* fontPath, TTF_Font* pFont, SDL_Color color_blue,int nbjoueurs, char** les_pseudos,char* gagnant, CHEVALET* chevaletsJoueurs)
{
    int i;
    bool choix;
    SDL_Event event;
    char score[10] = "";
    SDL_WM_SetCaption("Fin de Partie", NULL);
    SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));
    
    TTF_Font* pFont1 = TTF_OpenFont(fontPath,20);
    SDL_Color fontColor = {90, 30, 41};

    SDL_Rect position, fin, prochaine_partie;
    
    SDL_Surface* fin_partie = TTF_RenderText_Solid(pFont,"Fin de la Partie",fontColor);
    position.x = 250;
    position.y = WINDOW_HEIGHT/50;
    position.w = fin_partie->w;
    position.h = fin_partie->h;
    SDL_BlitSurface(fin_partie,NULL,pWindowSurface,&position);

    //tableau de points
    prochaine_partie = creer_surface(pWindowSurface, 150,450,300,100,255,255,200);
    fin = creer_surface(pWindowSurface, 520,450,300,100,255,255,200);
    if(clic_bouton(event, prochaine_partie)) choix = true;
    else if(clic_bouton(event, fin))  choix = false;
    
                          
    position.x = 150;
    position.y = 90;
    for (i=0; i<nbjoueurs; i++) {
        SDL_Surface* affiche_score = TTF_RenderText_Solid(pFont,les_pseudos[i],fontColor);
        position.y += 50;
        position.w = affiche_score->w;
        position.h = affiche_score->h;
        SDL_BlitSurface(affiche_score,NULL,pWindowSurface,&position);
    }
    
    position.x = 600;
    position.y = 92;
    for (i=0; i<nbjoueurs; i++) {
        sprintf(score, "%d", chevaletsJoueurs[i].joueur.scoreJoueur);
        SDL_Surface* score_final = TTF_RenderText_Solid(pFont1,score,fontColor);
        position.y += 50;
        position.w = score_final->w;
        position.h = score_final->h;
        SDL_BlitSurface(score_final,NULL,pWindowSurface,&position);
    }

    ecrire_texte(pFont,"Gagnant: ", fontColor, pWindowSurface, 360);

    SDL_Surface* winner = TTF_RenderText_Solid(pFont,gagnant,fontColor);
        position.x = 600;
        position.y = 360;
        position.w = winner->w;
        position.h = winner->h;
        SDL_BlitSurface(winner ,NULL,pWindowSurface,&position);
    
    SDL_Surface* nouvel_partie = TTF_RenderText_Solid(pFont1,"Prochaine partie",fontColor);
        position.x = 200;
        position.y = 495;
        position.w = nouvel_partie->w;
        position.h = nouvel_partie->h;
        SDL_BlitSurface(nouvel_partie,NULL,pWindowSurface,&position);

         
    SDL_Surface* termine_jeu = TTF_RenderText_Solid(pFont1,"Arreter",fontColor);
        position.x = 630;
        position.y = 495;
        position.w = termine_jeu->w;
        position.h = termine_jeu->h;
        SDL_BlitSurface(termine_jeu ,NULL,pWindowSurface,&position);

    return choix;

    SDL_Flip(pWindowSurface);  
}

void afficher_tour(SDL_Surface* pWindowSurface, const char* fontPath, char * nom_joueur)
{
    SDL_Rect position;
    SDL_Color fontColor = {90, 30, 41};
    TTF_Font* pScore = TTF_OpenFont(fontPath,15);
    TTF_SetFontStyle(pScore , TTF_STYLE_BOLD);
    char tour[10] = "";

    sprintf(tour, nom_joueur);
    SDL_Surface* affiche_joueur = TTF_RenderText_Solid(pScore,tour,fontColor);
    position.x = 765;
    position.y = 120;
    position.w = affiche_joueur->w;
    position.h = affiche_joueur->h;
    SDL_BlitSurface(affiche_joueur,NULL,pWindowSurface,&position);   
    
}

void efface_tour(SDL_Surface* pWindowSurface)
{
    SDL_Rect position;
    SDL_Surface* tour_table = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
    position.x = 765;
    position.y = 120;
    position.w = tour_table->w;
    position.h = tour_table->h;
    SDL_FillRect(tour_table, NULL, SDL_MapRGB(pWindowSurface->format, 255,255,255));
    SDL_BlitSurface(tour_table, NULL, pWindowSurface, &position); 
}

char**  recuperer_pseudo_clavier(SDL_Surface* fenetre, int nbjoueurs, int modejeu)
{
    char**les_pseudos = malloc(nbjoueurs*sizeof(char));
	int curseur=0;
	char texteDemandePseudo[70];
	
    SDL_Color noir={0,0,0};
    TTF_Font *police_titre=TTF_OpenFont("./data/meteoricbold.ttf",20);
    TTF_Font *police_pseudos=TTF_OpenFont("./data/meteoricbold.ttf",15);
	SDL_Event event,event1,event2,event3;
	SDL_Rect posPseudo;

    SDL_bool taper_clavier = SDL_TRUE;
    SDL_bool taper_clavier1 = SDL_TRUE;
    SDL_bool taper_clavier2 = SDL_TRUE;
    SDL_bool taper_clavier3 = SDL_TRUE;
    int i=0,j=0,k=0,l=0;
    
	posPseudo.x=400; posPseudo.y=130; posPseudo.w=180; posPseudo.h=50;
	
	SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255, 160, 115));
	
	sprintf(texteDemandePseudo,"Veuillez entrez le pseudos du joueur numero 1 (%d caracteres max)",10);
	
	ecrire_texte(police_titre,texteDemandePseudo, noir, fenetre, WINDOW_HEIGHT/10);
	SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
	SDL_Flip(fenetre);
	
	SDL_EnableKeyRepeat(0,0);
    char*pseudoDemande=malloc(10*sizeof(char));
    char*pseudoDemande1=malloc(10*sizeof(char));
    char*pseudoDemande2=malloc(10*sizeof(char));
    char*pseudoDemande3=malloc(10*sizeof(char));
        
    for(i=0;i<10;i++)
    {
        pseudoDemande[i]=' ';
    }
    SDL_EnableUNICODE(SDL_ENABLE);
    while(taper_clavier)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                taper_clavier = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                if( (event.key.keysym.unicode == SDLK_BACKSPACE) && (curseur>0) )
                {
                    pseudoDemande[curseur-1]=' ';
                    curseur-=1;
                }
                
                if( (event.key.keysym.unicode!=SDLK_BACKSPACE) && (event.key.keysym.unicode!=SDLK_RETURN) && (curseur<(10)) )
                {
                    if(event.key.keysym.unicode >= 'a' && event.key.keysym.unicode <= 'z') {
                        pseudoDemande[curseur] = event.key.keysym.unicode;
                        curseur+=1;
                    }
                    else if(event.key.keysym.unicode >= 'A' && event.key.keysym.unicode <= 'Z') {
                        pseudoDemande[curseur] = event.key.keysym.unicode;
                        curseur+=1;
                    }
                }
                if( (event.key.keysym.unicode==SDLK_RETURN))
                {
                    taper_clavier = SDL_FALSE;
                    break;
                }
                SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
                ecrire_texte(police_pseudos,pseudoDemande, noir, fenetre, 150);
                SDL_Flip(fenetre);
        }
    }
    SDL_EnableUNICODE(SDL_DISABLE);
	les_pseudos[0] = pseudoDemande;
    if(nbjoueurs == 2 || nbjoueurs == 3 || nbjoueurs == 4)
    {
        if(modejeu == 0)
        {
            curseur = 0;
            SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255, 160, 115));

            sprintf(texteDemandePseudo,"Veuillez entrez le pseudos du joueur numero 2 (%d caracteres max)",10);
            
            ecrire_texte(police_titre,texteDemandePseudo, noir, fenetre, WINDOW_HEIGHT/10);
            SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
            SDL_Flip(fenetre);

            SDL_EnableKeyRepeat(0,0);
            for(j=0;j<10;j++)
            {
                pseudoDemande1[j]=' ';
            }
            SDL_EnableUNICODE(SDL_ENABLE);
            while(taper_clavier1)
            {
                SDL_WaitEvent(&event1);
                switch(event1.type)
                {
                    case SDL_QUIT:
                        taper_clavier1 = SDL_FALSE;
                        break;
                    case SDL_KEYDOWN:
                        if( (event1.key.keysym.unicode == SDLK_BACKSPACE) && (curseur>0) )
                        {
                            pseudoDemande1[curseur-1]=' ';
                            curseur-=1;
                        }
                        
                        if( (event1.key.keysym.unicode!=SDLK_BACKSPACE) && (event1.key.keysym.unicode!=SDLK_RETURN) && (curseur<(10)) )
                        {
                            if(event1.key.keysym.unicode >= 'a' && event1.key.keysym.unicode <= 'z') {
                                pseudoDemande1[curseur] = event1.key.keysym.unicode;
                                curseur+=1;
                            }
                            else if(event1.key.keysym.unicode >= 'A' && event1.key.keysym.unicode <= 'Z') {
                                pseudoDemande1[curseur] = event1.key.keysym.unicode;
                                curseur+=1;
                            }
                        }
                        if( (event1.key.keysym.unicode==SDLK_RETURN))
                        {
                            taper_clavier1 = SDL_FALSE;
                            break;
                        }
                        SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
                        ecrire_texte(police_pseudos,pseudoDemande1, noir, fenetre, 150);
                        SDL_Flip(fenetre);
                }
            }
            les_pseudos[1] = pseudoDemande1;
        }
        else
        {
            les_pseudos[1] = "Joueur 2";
        }
        
    }
    SDL_EnableUNICODE(SDL_DISABLE);
    if(nbjoueurs == 3 || nbjoueurs == 4)
    {
        if(modejeu == 0)
        {
            curseur = 0;
            SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255, 160, 115));

            sprintf(texteDemandePseudo,"Veuillez entrez le pseudos du joueur numero 3 (%d caracteres max)",10);
            
            ecrire_texte(police_titre,texteDemandePseudo, noir, fenetre, WINDOW_HEIGHT/10);
            SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
            SDL_Flip(fenetre);

            SDL_EnableKeyRepeat(0,0);
            for(k=0;k<10;k++)
            {
                pseudoDemande2[k]=' ';
            }
            while(taper_clavier2)
            {
                SDL_WaitEvent(&event2);
                switch(event2.type)
                {
                    case SDL_QUIT:
                        taper_clavier2 = SDL_FALSE;
                        break;
                    case SDL_KEYDOWN:
                        if( (event2.key.keysym.sym == SDLK_BACKSPACE) && (curseur>0) )
                        {
                            pseudoDemande2[curseur-1]=' ';
                            curseur-=1;
                        }
                        
                        if( (event2.key.keysym.sym!=SDLK_BACKSPACE) && (event2.key.keysym.sym!=SDLK_RETURN) && (curseur<(10)) )
                        {
                            if(event2.key.keysym.unicode >= 'a' && event2.key.keysym.unicode <= 'z') {
                                pseudoDemande2[curseur] = event2.key.keysym.unicode;
                                curseur+=1;
                            }
                            else if(event2.key.keysym.unicode >= 'A' && event2.key.keysym.unicode <= 'Z') {
                                pseudoDemande2[curseur] = event2.key.keysym.unicode;
                                curseur+=1;
                            }
                        }
                        if( (event2.key.keysym.sym==SDLK_RETURN))
                        {
                            taper_clavier2 = SDL_FALSE;
                            break;
                        }
                        SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
                        ecrire_texte(police_pseudos,pseudoDemande2, noir, fenetre, 150);
                        SDL_Flip(fenetre);
                }
            }
            les_pseudos[2] = pseudoDemande2;
        }
        else
        {
            les_pseudos[2] = "Joueur 3";
        }
        
    }
    if(nbjoueurs == 4)
    {
        if(modejeu == 0)
        {
            curseur = 0;
            SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,255, 160, 115));

            sprintf(texteDemandePseudo,"Veuillez entrez le pseudos du joueur numero 4 (%d caracteres max)",10);
            
            ecrire_texte(police_titre,texteDemandePseudo, noir, fenetre, WINDOW_HEIGHT/10);
            SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
            SDL_Flip(fenetre);

            SDL_EnableKeyRepeat(0,0);
            for(l=0;l<10;l++)
            {
                pseudoDemande3[l]=' ';
            }
            while(taper_clavier3)
            {
                SDL_WaitEvent(&event3);
                switch(event3.type)
                {
                    case SDL_QUIT:
                        taper_clavier3 = SDL_FALSE;
                        break;
                    case SDL_KEYDOWN:
                        if( (event3.key.keysym.sym == SDLK_BACKSPACE) && (curseur>0) )
                        {
                            pseudoDemande3[curseur-1]=' ';
                            curseur-=1;
                        }
                        
                        if( (event3.key.keysym.sym!=SDLK_BACKSPACE) && (event3.key.keysym.sym!=SDLK_RETURN) && (curseur<(10)) )
                        {
                            if(event3.key.keysym.unicode >= 'a' && event3.key.keysym.unicode <= 'z') {
                                pseudoDemande3[curseur] = event3.key.keysym.unicode;
                                curseur+=1;
                            }
                            else if(event3.key.keysym.unicode >= 'A' && event3.key.keysym.unicode <= 'Z') {
                                pseudoDemande3[curseur] = event3.key.keysym.unicode;
                                curseur+=1;
                            }
                        }
                        if( (event3.key.keysym.sym==SDLK_RETURN))
                        {
                            taper_clavier3 = SDL_FALSE;
                            break;
                        }
                        SDL_FillRect(fenetre,&posPseudo,SDL_MapRGB(fenetre->format,255, 255, 255));
                        ecrire_texte(police_pseudos,pseudoDemande3, noir, fenetre, 150);
                        SDL_Flip(fenetre);
                }
            }
            les_pseudos[3] = pseudoDemande3;
        }
        else
        {
            les_pseudos[3] = "Joueur 4";
        }
        
    }
    return les_pseudos;
}


