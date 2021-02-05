#include "fonctions.h"
/*****************************************
 * Contrôleur (Main) 
 ****************************************/

// Exécuter à la racine du dossier du projet : 
// gcc -Wall src/controleur.c src/vue.c src/modele.c -o bin/prog src/fonctions.h -I include -L lib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image
// et ensuite bin\prog.exe
int main (int argc, char **argv) {
    CHEVALET* chevaletsJoueurs;
    char** les_pseudos;
    TABTUILES pioche, tuilesDivisees;
    numCaseTab ncTuilesOrdi;
    int i, j, modeJeu, nbrJoueurs, tourJoueur, niveau, score, gagnant;
    TABLE table;
    TUILE t, tBis, tuileVide, tuileAretirer;
    numCase nc, ncTable, ncTuileAjoutee, ncOrdi;
    bool continuer, piocher, finTour, destinationVide, tourOrdi, piocheVide;
    int* numJoueursDebutent;
    
    // Initialisation variables 
    numJoueursDebutent = (int*) malloc (sizeof(int));
    continuer = true;                    
    tuileVide = initialiser_tuile();
    gagnant = -1;
    ncTuileAjoutee.c = 0; ncTuileAjoutee.l = 0;
    ncOrdi.c = -1; ncOrdi.l = -1;
    ncTuilesOrdi.nbrNumCase = 0;
    piocheVide = false;

    // Initialisation variables interface
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
    init(imgFlags);

    // Creer la fenetre
    SDL_Surface* pWindowSurface = creer_fenetre(); // Ecran principal
    SDL_bool lancer_menu = SDL_TRUE;
    SDL_bool lancer_jeu = SDL_FALSE;
    SDL_bool lancer_debut = SDL_FALSE;
    SDL_bool lancer_difficult = SDL_TRUE;
    SDL_bool lancer_x = SDL_FALSE;
    SDL_Event event,eventdifficult, positionDepart, surfaceSelec;

    afficher_image_menu(pWindowSurface,"./data/rummikub.jpg",1);
    SDL_Rect imagejouer= afficher_image_menu(pWindowSurface,"./data/jouer.png",2);
    SDL_Rect boutonPiocher;
    SDL_Rect finir;

    const char* fontPath = "./data/meteoricbold.ttf";
    TTF_Font* pFont = TTF_OpenFont(fontPath,40);
    TTF_Font* pbouton = TTF_OpenFont(fontPath,15);
    TTF_Font* font_mode = TTF_OpenFont(fontPath,20);
    SDL_Color color_white = {255, 255, 255};
    SDL_Color color_black = {0, 0, 0};
    TTF_SetFontStyle(pbouton , TTF_STYLE_BOLD);
    SDL_Color color_marron = {64, 0, 0};

    SDL_Rect surface_hh, surface_ho, surface_j2, surface_j3, surface_j4,niveau_facile,niveau_difficile; 

    // Charge la police
    TTF_SetFontStyle(pFont, TTF_STYLE_BOLD);
    ecrire_texte(pFont,"Bienvenue sur Rummikub", color_white, pWindowSurface, WINDOW_HEIGHT/10);

    // Boucle affichage du menu
    while (lancer_menu) 
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    lancer_menu = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(clic_bouton(event, imagejouer))
                    {
                        event.type = SDL_MOUSEBUTTONUP;
                        afficher_modeJeu(pWindowSurface, fontPath, pFont, color_black); 
                    }
                    break;
            }
            
            switch(event.type)
            {
                case SDL_QUIT:
                    lancer_menu = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    surface_hh = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 175, 150, 350, 80,192, 192, 192);
                    surface_ho = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 175, 300, 350, 80,192, 192, 192);
                    if(clic_bouton(event, surface_hh)) 
                    {
                        modeJeu = 0;// Humain VS Humain
                        //Choisir le mode de jeu
                        SDL_WM_SetCaption("Rummikub nombre de joueurs", NULL);
                        SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));
                        
                        ecrire_texte(pFont,"Choisissez le nombre des joueurs", color_black, pWindowSurface, WINDOW_HEIGHT/10);
                        //Joueur 2
                        surface_j2 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150,150,300, 50,192, 192, 192);
                        ecrire_texte(font_mode,"2 Joueurs", color_black, pWindowSurface, 160);

                        //Joueur 3
                        surface_j3 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150, 250,300, 50,192, 192, 192);
                        ecrire_texte(font_mode,"3 Joueurs", color_black, pWindowSurface, 260);

                        //Joueur 4
                        surface_j4 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150, 350,300, 50,192, 192, 192);
                        ecrire_texte(font_mode,"4 Joueurs", color_black, pWindowSurface, 360);

                        SDL_Flip(pWindowSurface);
                    } 
                    else if (clic_bouton(event, surface_ho))
                    {
                        modeJeu = 1; // Humain VS Ordinateur
                        //Choisir le mode de jeu
                        SDL_WM_SetCaption("Rummikub difficulté du jeu", NULL);
                        SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));

                        ecrire_texte(pFont,"Choisissez la difficulté du jeu", color_black, pWindowSurface, WINDOW_HEIGHT/10);

                        //niveau facile
                        niveau_facile = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150,150,300, 50,192, 192, 192);
                        ecrire_texte(font_mode,"Niveau facile", color_black, pWindowSurface, 160);

                        //niveau difficile
                        niveau_difficile = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150, 250,300, 50,192, 192, 192);
                        ecrire_texte(font_mode,"Niveau difficile", color_black, pWindowSurface, 260);

                        SDL_Flip(pWindowSurface);
                        while (lancer_difficult) {
                            while(SDL_PollEvent(&eventdifficult))
                            {
                                switch(eventdifficult.type)
                                {
                                    case SDL_QUIT: 
                                        lancer_difficult = SDL_FALSE;
                                        break;
                                    case SDL_MOUSEBUTTONDOWN:
                                        if(clic_bouton(eventdifficult, niveau_facile)) niveau = 1;
                                        else if(clic_bouton(eventdifficult, niveau_difficile)) niveau = 2;
                                        //Choisir le mode de jeu
                                        SDL_WM_SetCaption("Rummikub nombre de joueurs", NULL);
                                        SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 160, 115));
                                        
                                        ecrire_texte(pFont,"Choisissez le nombre des joueurs", color_black, pWindowSurface, WINDOW_HEIGHT/10);
                                        //Joueur 2
                                        surface_j2 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150,150,300, 50,192, 192, 192);
                                        ecrire_texte(font_mode,"2 Joueurs", color_black, pWindowSurface, 160);

                                        //Joueur 3
                                        surface_j3 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150, 250,300, 50,192, 192, 192);
                                        ecrire_texte(font_mode,"3 Joueurs", color_black, pWindowSurface, 260);

                                        //Joueur 4
                                        surface_j4 = creer_surface(pWindowSurface, WINDOW_WIDTH/2 - 150, 350,300, 50,192, 192, 192);
                                        ecrire_texte(font_mode,"4 Joueurs", color_black, pWindowSurface, 360);

                                        SDL_Flip(pWindowSurface);
                                        lancer_difficult = SDL_FALSE;          
                                }
                            }
                        }
                    }
                    printf("modeJeu = %d\n", modeJeu);
                    event.type = SDL_MOUSEBUTTONUP;
                    lancer_jeu = SDL_TRUE;
                    lancer_menu = SDL_FALSE;
                    break;
            } 
        }
    }    

    // Boucle lancement du jeu
    while (lancer_jeu) {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: 
                    lancer_jeu = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(clic_bouton(event, surface_j2))
                    {
                        nbrJoueurs = 2;
                    }
                    else if(clic_bouton(event, surface_j3))
                    {
                        nbrJoueurs = 3;
                    }
                    else if(clic_bouton(event, surface_j4))
                    {
                        nbrJoueurs = 4;
                    }
                    les_pseudos = recuperer_pseudo_clavier(pWindowSurface,nbrJoueurs,modeJeu);
                    afficher_tab_jeu(pWindowSurface,fontPath);
                    boutonPiocher = afficher_bouton(pbouton,"Piocher tuile",color_marron, pWindowSurface, 10, 480,180,50,255,255,200, 50, 495);
                    finir = afficher_bouton(pbouton,"Finir tour",color_marron, pWindowSurface, 810, 480,180,50,255,255,200, 850, 495);
                    event.type = SDL_MOUSEBUTTONUP;
                    lancer_jeu = SDL_FALSE;
                    lancer_debut = SDL_TRUE;
                    break;                  
            }
        }
    }

    // On alloue le tableau de pointeurs
    chevaletsJoueurs = (CHEVALET*) malloc (sizeof(CHEVALET)*nbrJoueurs);

    // Initialisation de la table
    table = creer_table(11, 4);

    // Initialisation de la pioche
    pioche = initialiser_pioche(pioche);

    for (i=0; i<nbrJoueurs; i++) {
        // On affecte à chaque joueur un numéro
        chevaletsJoueurs[i].joueur.numJoueur = i;
        //On affecte à chaque joueur un pseudos
        chevaletsJoueurs[i].joueur.nomJoueur = les_pseudos[i];
        // On affecte à chaque joueur un score nul
        chevaletsJoueurs[i].joueur.scoreJoueur = 0;
        // Les joueurs piochent 14 tuiles
        chevaletsJoueurs[i].tabTuiles.tuiles =  (TUILE*) malloc (sizeof(TUILE));
        chevaletsJoueurs[i].tabTuiles = piocher_tuile(14, pioche);
        // On retire les tuiles piochées de la pioche
        pioche = retirer_tuiles(chevaletsJoueurs[i].tabTuiles, pioche);
        numJoueursDebutent[i] = i;
    }

    // Choix du joueur qui commencera
    tourJoueur = choisir_tourJoueur(nbrJoueurs, pioche);

    lancer_jeu = false;
    
    // Boucle jeu
    while (lancer_debut) 
    {    
        while(SDL_PollEvent(&event))
        {    
            lancer_menu = false;
            lancer_difficult = false;
            lancer_x = false;
            finTour = false; piocher = false;
            tourOrdi = false;
            
            // Afficher les tuiles du chevalet
            afficher_tuiles (pFont, pWindowSurface, chevaletsJoueurs[tourJoueur].tabTuiles, 180, 432, 1);
            
            // Afficher les tuiles de la table
            j = 40;
            for (i=0; i<table.nbrTabsTuiles; i++) 
            {
                afficher_tuiles (pFont, pWindowSurface, table.tabsTuiles[i], -25, j, 2);
                j += 80;
                if (i == ncTuileAjoutee.l) {
                    if (verifier_modification(table.tabsTuiles[i], ncTuileAjoutee.c)) {
                        score = 0;
                        score += calcul_combinaison(table.tabsTuiles[i]);
                        chevaletsJoueurs[tourJoueur].joueur.scoreJoueur += score;
                    }
                }
            }
            ncTuileAjoutee.c = -1; ncTuileAjoutee.l = -1;

            afficher_score(pWindowSurface, nbrJoueurs, fontPath, chevaletsJoueurs, les_pseudos,tourJoueur);

            if (continuer) 
            {
                t = initialiser_tuile();
            
                if (verif_debute_partie(chevaletsJoueurs[tourJoueur].joueur.scoreJoueur) && !lancer_jeu) {
                    numJoueursDebutent[tourJoueur] = -1;
                    finTour = true;
                    nc.c = -1; nc.l = -1;
                    tuilesDivisees.nbrTuiles = 0;
                }

                if (modeJeu && tourJoueur != 0) {
                    if (ncTuilesOrdi.nbrNumCase == 0) {
                        ncOrdi.c = -1; ncOrdi.l = -1;
                        ncTuilesOrdi = combinaison_possible (chevaletsJoueurs[tourJoueur]); 
                    }
                    if (ncTuilesOrdi.nbrNumCase > 0) {
                        nc = ncTuilesOrdi.tab[0];
                        ncTuilesOrdi = supp_nc(ncTuilesOrdi);
                        event.type = SDL_MOUSEBUTTONDOWN;
                        tourOrdi = true;
                    }
                    else {
                        ncOrdi.c = -1; ncOrdi.l = -1;
                        piocher = rand() % 2;
                        if (!piocher) finTour = true;
                        event.type = SDL_MOUSEBUTTONUP;
                    }
                }

                // Prendre une tuile ou piocher
                switch(event.type)
                {  
                    case SDL_QUIT: 
                        lancer_debut = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (tourOrdi && tourJoueur != 0) event = transformer_case_en_point(nc, 1);
                        // On vérifie si l'endroit où le joueur a cliqué correspond a une tuile
                        finTour = clic_bouton(event, finir);
                        piocher = clic_bouton(event, boutonPiocher);
                        j = verif_selection(event);
                        nc.c = -1; nc.l = -1;
                        tuilesDivisees.nbrTuiles = -1;
                        if (j == 1) nc = verif_prendreTuileChev (event, chevaletsJoueurs[tourJoueur].tabTuiles);
                        else if (j == 2) {
                            tuilesDivisees = verif_prendreTuileTable (event, table);
                            if (tuilesDivisees.nbrTuiles != 0) nc = transformer_point_en_case(event, 2);
                        }
                        if ((nc.c != -1 && nc.l != -1) || ((tuilesDivisees.nbrTuiles != 0) && (nc.c != -1 && nc.l != -1))) 
                        {
                            printf("prendre tuile\n");
                            positionDepart = transformer_case_en_point(nc, j);
                            tuile_active(pWindowSurface, positionDepart.button.x, positionDepart.button.y);
                            if (j == 1) {
                                if (nc.l > 0) nc.l = 9;
                                t = chevaletsJoueurs[tourJoueur].tabTuiles.tuiles[nc.c+nc.l];
                            } 
                            surfaceSelec.button.x = j;
                            continuer = false;
                        }
                        break;
                }

                // Sinon on vérifie si l'endroit où il a cliqué correspond au bouton piocher une tuile ou au bouton finir son tour
                if (piocher || finTour)
                {
                            for (i=0; i<table.nbrTabsTuiles; i++) {
                                TABTUILES copieTabTuiles = supp_tuiles_vides(table.tabsTuiles[i]);
                                if (copieTabTuiles.nbrTuiles < 3) {
                                    chevaletsJoueurs[tourJoueur].tabTuiles = ajouter_tuiles(copieTabTuiles, chevaletsJoueurs[tourJoueur].tabTuiles);
                                    table.tabsTuiles[i] = retirer_tuiles(copieTabTuiles, table.tabsTuiles[i]);
                                }
                            }
                            if (piocher) 
                            {
                                TABTUILES tuilesPiochees;
                                tuilesPiochees = piocher_tuile(1, pioche);
                                chevaletsJoueurs[tourJoueur].tabTuiles = ajouter_tuiles(tuilesPiochees, chevaletsJoueurs[tourJoueur].tabTuiles);
                                pioche = retirer_tuiles(tuilesPiochees, pioche);
                                printf("piocher\n");
                            }
                            // On vérifie si la partie peut débuter
                            int tourJoueurActuel;
                            if (!lancer_jeu) 
                            {
                                printf("avant debut de jeu\n");
                                lancer_jeu = true;
                                table = vider_table(table);
                                for (i=0; i<nbrJoueurs; i++) {
                                    if (!verif_debute_partie(chevaletsJoueurs[i].joueur.scoreJoueur)) {
                                        lancer_jeu = false;
                                    }
                                } 
                                // On boucle tant que le prochain joueur est égal au joueur actif ou s'il a déjà validé sa combinaison
                                tourJoueurActuel = tourJoueur;
                                for (i=0; i<nbrJoueurs; i++)
                                {
                                    if (numJoueursDebutent[i] != -1 && tourJoueurActuel!=i && !verif_debute_partie(chevaletsJoueurs[i].joueur.scoreJoueur)) 
                                    {
                                        tourJoueur = i;
                                    }
                                }
                            }
                            if (lancer_jeu) 
                            {
                                printf("debut jeu\n");
                                tourJoueurActuel = tourJoueur;
                                while (tourJoueurActuel==tourJoueur) {
                                    tourJoueur = rand() % nbrJoueurs;
                                }
                            }
                            printf("tour = %d\n", tourJoueur);  

                            // Vérifier si l'un des joueurs a gagné
                            gagnant = joueur_a_gagne(chevaletsJoueurs, nbrJoueurs);
                            if (pioche.nbrTuiles==0) {
                                gagnant = minSommeTuiles(chevaletsJoueurs, nbrJoueurs);
                                piocheVide = true;
                                afficher_finPartie( pWindowSurface, fontPath, pFont,color_marron,nbrJoueurs, les_pseudos,chevaletsJoueurs[gagnant].joueur.nomJoueur,chevaletsJoueurs);
                            }
                            if (gagnant!=-1) lancer_debut = SDL_FALSE;             
                            printf("gagnant = %d\n",gagnant);
                            afficher_combinaisons(pWindowSurface);
                            afficher_board (pWindowSurface);
                        }
                        event.type = SDL_MOUSEBUTTONUP;
            }
          
            else
            {
                if (modeJeu && tourJoueur != 0) {
                    event.type = SDL_MOUSEBUTTONDOWN;
                    tourOrdi = true;
                }
                // Poser une tuile
                switch(event.type)
                {  
                    case SDL_QUIT: 
                        lancer_debut = SDL_FALSE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if ((!verifier_meme_tuile(t, initialiser_tuile())) || tuilesDivisees.nbrTuiles != 0)
                        {
                            srand(time(NULL));
                            if (tourOrdi && tourJoueur != 0) {
                                if (ncOrdi.c == -1 && ncOrdi.l == -1) {
                                    ncOrdi.c = rand() % 2; ncOrdi.l = rand() % 4;
                                }
                                else {
                                    numCase ncOrdiAncien;
                                    ncOrdiAncien.c = ncOrdi.c; ncOrdiAncien.l = ncOrdi.l;
                                    while (ncOrdiAncien.c == ncOrdi.c) ncOrdi.c = rand() % 11;
                                }
                                event = transformer_case_en_point(ncOrdi, 2); 
                            }
                            // On vérifie si le joueur tente de poser une tuile sur la table
                            ncTable = verif_depose(event, table);
                            if (ncTable.l != -1 && ncTable.c != -1) {
                                tBis = table.tabsTuiles[ncTable.l].tuiles[ncTable.c];  
                                destinationVide = verifier_meme_tuile(tBis, tuileVide);
                                if (lancer_jeu && tuilesDivisees.nbrTuiles == 0 && !destinationVide) {
                                   if (peut_remplacer_tuile(ncTable, table.tabsTuiles[ncTable.l], t)) {
                                        if (tBis.typeTuile == 0) {
                                            lancer_menu = true;
                                        }
                                        else if (tBis.typeTuile == 1) {
                                            lancer_difficult = true;
                                        }
                                    }
                                    else {
                                        tuileAretirer = peut_decaler_combinaison(table.tabsTuiles[ncTable.l], t);
                                        if (!verifier_meme_tuile(tuileAretirer, tuileVide)) {
                                            TABTUILES tab;
                                            tab = copier_tab(table.tabsTuiles[ncTable.l], tab);
                                            tab = supp_tuiles_vides(tab);
                                            int taille = tab.nbrTuiles;
                                            if (verifier_meme_tuile(tBis, tab.tuiles[taille-1])) 
                                            {
                                                ncTable.c += 1;
                                                lancer_x = true;
                                                table.tabsTuiles[ncTable.l] = retirer_tuile(tuileAretirer, table.tabsTuiles[ncTable.l]);  
                                            }
                                            else if (verifier_meme_tuile(tBis, tab.tuiles[0])) 
                                            {
                                                ncTable.c -= 1;
                                                lancer_x = true;
                                                table.tabsTuiles[ncTable.l] = retirer_tuile(tuileAretirer, table.tabsTuiles[ncTable.l]);  
                                            }                                  
                                        }    
                                    }
                                }
                                if (destinationVide || lancer_difficult || lancer_x) 
                                {
                                    printf("\nposer tuile\n");
                                    if (surfaceSelec.button.x == 1) {
                                        table.tabsTuiles[ncTable.l].tuiles[ncTable.c] = t;
                                        if (!verif_combinaison(table.tabsTuiles[ncTable.l])) 
                                        {
                                            table.tabsTuiles[ncTable.l].tuiles[ncTable.c] = initialiser_tuile();
                                        }
                                        else {
                                            chevaletsJoueurs[tourJoueur].tabTuiles = retirer_tuile(t, chevaletsJoueurs[tourJoueur].tabTuiles);
                                            if (lancer_difficult) chevaletsJoueurs[tourJoueur].tabTuiles = ajouter_tuile(tBis, chevaletsJoueurs[tourJoueur].tabTuiles);
                                        }
                                    } 
                                    if (surfaceSelec.button.x == 2 && tuilesDivisees.nbrTuiles != 0)
                                    {
                                        j=0;
                                        int tailleTuilesDiv = tuilesDivisees.nbrTuiles;
                                        for (i=ncTable.c; i<table.tabsTuiles[ncTable.l].nbrTuiles; i++) {
                                            if (verifier_meme_tuile(table.tabsTuiles[ncTable.l].tuiles[i], tuileVide) && j<tailleTuilesDiv) {
                                                table.tabsTuiles[ncTable.l].tuiles[i] = tuilesDivisees.tuiles[j];
                                                j++;
                                                tuilesDivisees.nbrTuiles--;
                                            }
                                        }
                                        if (!verif_combinaison(table.tabsTuiles[ncTable.l]) || tuilesDivisees.nbrTuiles != 0) 
                                        {
                                            for (i=ncTable.c; i< table.tabsTuiles[ncTable.l].nbrTuiles; i++) {
                                                table.tabsTuiles[ncTable.l].tuiles[i] = initialiser_tuile();
                                            }      
                                        }
                                        else {
                                            for (i=nc.c; i<table.tabsTuiles[nc.l].nbrTuiles; i++) {
                                                table.tabsTuiles[nc.l].tuiles[i] = initialiser_tuile();
                                            } 
                                        }
                                    }
                                    if (!lancer_difficult) {
                                        ncTuileAjoutee.c = ncTable.c; ncTuileAjoutee.l = ncTable.l;
                                    }
                                }
                            }
                            afficher_combinaisons(pWindowSurface);
                            afficher_board (pWindowSurface);
                        }
                        event.type = SDL_MOUSEBUTTONUP;
                        if (lancer_menu) t = tBis;
                        else if (lancer_x) t = tuileAretirer;
                        else continuer = true;
                        break;
                }
            }
        }
    }

    // Sauvegarder les pseudos et scores des joueurs
    chevaletsJoueurs = scoreFinal(chevaletsJoueurs, nbrJoueurs, gagnant, piocheVide);
    sauvegarder_file(chevaletsJoueurs, nbrJoueurs);

    TTF_CloseFont(pFont);
    cleanup();
    SDL_Quit();

    return 0;

}