#include "fonctions.h"

/*****************************************
 * Modèle
 ****************************************/

TABTUILES melanger_pioche(TABTUILES pioche) 
{
    int i, j;
    TUILE t;
    for (i = 0; i < pioche.nbrTuiles; i++) 
    {
        //srand(time(NULL));
        j = i + rand() % (pioche.nbrTuiles-i);
        t = pioche.tuiles[j];
        pioche.tuiles[j] = pioche.tuiles[i];
        pioche.tuiles[i] = t;
    }
    return pioche;
}

TABTUILES initialiser_pioche(TABTUILES pioche) 
{
    int i, j, num, couleur;
    num = 1;
    couleur = 0;
    pioche.nbrTuiles = 106;
    pioche.tuiles =  (TUILE*) malloc (sizeof(TUILE)*pioche.nbrTuiles);
    for (i=0; i<104; i++) 
    {
        pioche.tuiles[i].numTuile = num;
        pioche.tuiles[i].coulTuile = couleur;
        pioche.tuiles[i].typeTuile = Simple;
        num++;
        if (num > 13) {
            num = 1;
            couleur++;
        }
       if (couleur > 3) couleur = 0;
    }    
    for (j=i; j<=(i+1); j++) 
    {
        pioche.tuiles[j].typeTuile = Joker;
        pioche.tuiles[j].numTuile = -1;
        pioche.tuiles[j].coulTuile = -1;
    }
    pioche = melanger_pioche(pioche);
    return pioche;
}

void afficher_tab_tuiles(TABTUILES tabTuiles) 
{   
    int i;
    for (i=0; i<tabTuiles.nbrTuiles; i++) 
    {
        printf("tuiles n%d coul = %d\n", i, tabTuiles.tuiles[i].coulTuile);
        printf("tuiles n%d num = %d\n", i, tabTuiles.tuiles[i].numTuile);
        printf("tuiles n%d type = %d\n", i, tabTuiles.tuiles[i].typeTuile);
        printf("\n");
    }
}

void afficher_tab_numCase(numCaseTab tabNumCase) 
{   
    int i;
    for (i=0; i<tabNumCase.nbrNumCase; i++) 
    {
        printf("numCase n%d l = %d\n", i, tabNumCase.tab[i].l);
        printf("numCase n%d c = %d\n", i, tabNumCase.tab[i].c);
        printf("\n");
    }
}

TABTUILES piocher_tuile(int nbrTuiles, TABTUILES pioche) 
{
    int i;
    TABTUILES tabTuiles;
    tabTuiles.tuiles = (TUILE*) malloc (sizeof(TUILE)*nbrTuiles);

    tabTuiles.nbrTuiles = 0;
    if (nbrTuiles<=pioche.nbrTuiles) {
        for (i=0; i<nbrTuiles; i++) 
        {
            tabTuiles.tuiles[i].coulTuile=pioche.tuiles[i].coulTuile;
            tabTuiles.tuiles[i].typeTuile=pioche.tuiles[i].typeTuile;
            tabTuiles.tuiles[i].numTuile=pioche.tuiles[i].numTuile;
        }
        tabTuiles.nbrTuiles += nbrTuiles;
    }
    return tabTuiles;
}

bool verifier_meme_tuile(TUILE tuileA, TUILE tuileB) 
{
    if (tuileA.coulTuile==tuileB.coulTuile
        && tuileA.numTuile==tuileB.numTuile
        && tuileA.typeTuile==tuileB.typeTuile) return true;
    else return false;
}

bool verifier_meme_tabTuiles (TABTUILES tab1, TABTUILES tab2)
{
    int i;
    for (i=0; i<tab1.nbrTuiles; i++) {
        if (!verifier_meme_tuile(tab1.tuiles[i],tab2.tuiles[i])) return false;
    }
    return true;
}

TUILE initialiser_tuile()
{
    TUILE t;
    t.typeTuile = -1;
    t.coulTuile = -1;
    t.numTuile = -1;
    return t;
}

TABTUILES copier_tab(TABTUILES tab1, TABTUILES tab2) {
    int i;
    tab2.tuiles = (TUILE*) malloc (sizeof(TUILE)*tab1.nbrTuiles);
    for (i=0; i<tab1.nbrTuiles; i++) {
        tab2.tuiles[i] = tab1.tuiles[i];
    }
    tab2.nbrTuiles = tab1.nbrTuiles;
    return tab2;
}

numCaseTab copier_tabNumCase(numCaseTab tab1, numCaseTab tab2) {
    int i;
    tab2.tab = (numCase*) malloc (sizeof(numCase)*tab1.nbrNumCase);
    for (i=0; i<tab1.nbrNumCase; i++) {
        tab2.tab[i] = tab1.tab[i];
    }
    tab2.nbrNumCase = tab1.nbrNumCase;
    return tab2;
}

TABTUILES retirer_tuile (TUILE tuileAretirer, TABTUILES tabTuiles) 
{
    int i, y;
    for (i=0; i<tabTuiles.nbrTuiles; i++) 
    {
        if (verifier_meme_tuile(tuileAretirer, tabTuiles.tuiles[i])) 
        {
            tuileAretirer = initialiser_tuile();
            for (y=i; y<tabTuiles.nbrTuiles-1; y++) 
            {
                tabTuiles.tuiles[y]=tabTuiles.tuiles[y+1];
                tabTuiles.tuiles[y+1] = initialiser_tuile();
            }
            tabTuiles.nbrTuiles--;
        }
    }
    return tabTuiles;
}

TABTUILES retirer_tuiles(TABTUILES tabTuilesRetirer, TABTUILES tabTuiles) 
{
    int i;
    TABTUILES tabTuilesRetirerBis;
    tabTuilesRetirerBis = copier_tab(tabTuilesRetirer, tabTuilesRetirerBis);
    for (i=0; i<tabTuilesRetirerBis.nbrTuiles; i++) 
    {
        tabTuiles = retirer_tuile(tabTuilesRetirerBis.tuiles[i], tabTuiles);
    }
    return tabTuiles;
}

TABTUILES ajouter_tuile (TUILE tuileAajouter, TABTUILES tab)
{
    if (tab.nbrTuiles<18) {
        tab.tuiles[tab.nbrTuiles] = tuileAajouter;
        tab.nbrTuiles++;
    }
    return tab;
}

TABTUILES ajouter_tuiles (TABTUILES tuilesAajouter, TABTUILES tab) 
{
    int i;
    for (i=0; i<tuilesAajouter.nbrTuiles; i++)
    {
        tab = ajouter_tuile(tuilesAajouter.tuiles[i], tab);
    }
    return tab;
}

int indMaxTuile(TABTUILES tab)
{
    int i, max, ind;
    max = -1;
    ind = 0;
    for (i=0; i<tab.nbrTuiles; i++) 
    {
        if (tab.tuiles[i].numTuile > max) 
        {
            max = tab.tuiles[i].numTuile;
            ind = i;
        }
    }
    return ind;
}

int choisir_tourJoueur(int nbrJoueurs, TABTUILES pioche) 
{
    TABTUILES debutPartie;
    int tour;
    debutPartie.tuiles = (TUILE*) malloc (sizeof(TUILE)*4);
    // On pioche un nombre de tuiles précis
    debutPartie = piocher_tuile(nbrJoueurs, pioche); 
    tour = indMaxTuile(debutPartie);
    return tour;
}

void sauvegarder_file (CHEVALET* chevaletsJoueurs, int nbrJoueurs)
{
    int i, c, nbLignes;
    c=0;
    nbLignes=0;
	FILE* fichier = NULL;
 	fichier = fopen("parties.txt","r");     
    if (fichier!=NULL) 
    {
        while ((c = fgetc(fichier)) != EOF)
        {
            if (c=='P')  nbLignes++;
        }
    }
    else {
        fichier = fopen("parties.txt", "w");
        fseek(fichier, 10, SEEK_CUR);
        for (i=0; i<4; i++) 
        {
            fseek(fichier, 10, SEEK_CUR);
            fputs("Joueur ",fichier);
            fprintf(fichier, "%d", i+1);
        }
    }
    fclose(fichier);

    fichier = fopen("parties.txt","r+");    
    fseek(fichier, 0, SEEK_END);
    if(fichier!=NULL)
    {
        if (nbLignes != 0) 
        {
            fputs("\n",fichier);
        }
        nbLignes++;
        fprintf(fichier, "\nPartie %d :", nbLignes);
        for (i=0; i<nbrJoueurs; i++) 
        {
            fseek(fichier, 10, SEEK_CUR);
            fprintf(fichier, "%s : ", chevaletsJoueurs[i].joueur.nomJoueur);
            fprintf(fichier, "%d", chevaletsJoueurs[i].joueur.scoreJoueur);
        }
        fclose(fichier);
    }
}

int sommeTuiles(TABTUILES tab) 
{
    int i, somme;
    somme = 0;
    for (i=0; i<tab.nbrTuiles; i++)
    {
        somme += tab.tuiles[i].numTuile;
    }
    return somme;
}

int minSommeTuiles(CHEVALET* chevaletsJoueurs, int nbrJoueurs)
{
    int i, gagnant, sommeMin, somme;
    sommeMin = sommeTuiles(chevaletsJoueurs[0].tabTuiles);
    gagnant = chevaletsJoueurs[0].joueur.numJoueur;
    for (i=0; i<nbrJoueurs; i++) 
    {
        somme = sommeTuiles(chevaletsJoueurs[i].tabTuiles);
        if (sommeMin>somme) {
            sommeMin = somme;
            gagnant = chevaletsJoueurs[i].joueur.numJoueur;
        }
    }
    return gagnant;
}

int joueur_a_gagne(CHEVALET* chevaletsJoueurs, int nbrJoueurs)
{
    int i;
    for (i=0; i<nbrJoueurs; i++)
    {
        if (chevaletsJoueurs[i].tabTuiles.nbrTuiles==0) {
            return chevaletsJoueurs[i].joueur.numJoueur;
        }
    }
    return -1;
}

TABTUILES supp_tuiles_vides (TABTUILES tab) 
{
    TABTUILES tabBis;
    TUILE t;
    int i, y;
    y=0;
    tabBis.tuiles = (TUILE*) malloc (sizeof(TUILE)*tab.nbrTuiles);
    tabBis.nbrTuiles = 0;
    t = initialiser_tuile();
    for (i=0; i<tab.nbrTuiles; i++) 
    {
        if (!verifier_meme_tuile(tab.tuiles[i], t))
        {
            tabBis.tuiles[y] = tab.tuiles[i];
            tabBis.nbrTuiles++;
            y++;
        }
    }
    return tabBis;
} 

bool verif_combinaison(TABTUILES combinaison) 
{
    int i;
    TABTUILES combinaisonBis;
    bool suites, series;
    int couleur, numeroTuile, nombre;
    combinaisonBis = supp_tuiles_vides(combinaison);
    suites = false; series = false;
    if (combinaisonBis.nbrTuiles > 0)
    {
        couleur = combinaisonBis.tuiles[0].coulTuile;
        numeroTuile = combinaisonBis.tuiles[0].numTuile;
        nombre = combinaisonBis.tuiles[0].numTuile;
        for (i=1; i<combinaisonBis.nbrTuiles; i++)
        {
            nombre++;
            if (combinaisonBis.tuiles[i].coulTuile == couleur)
            {
                if (combinaisonBis.tuiles[i].numTuile != nombre || series) return false;
                else suites = true;
            }
            else if (combinaisonBis.tuiles[i].coulTuile != couleur)
            {
                if (combinaisonBis.tuiles[i].numTuile != numeroTuile || suites) return false;
                else series = true;
            }
        }
    }
    return true;
}

TABTUILES affecte_val_joker(TABTUILES tab)
{
    int i;
    for (i=0; i<tab.nbrTuiles; i++)
    {
       if (tab.tuiles[i].typeTuile == Joker) tab.tuiles[i].numTuile = 30;
    }
    return tab;
}

bool verif_debute_partie(int scoreJoueur) 
{
    if (scoreJoueur >= 30) return true;
    else return false;
}

TABLE vider_table (TABLE table) 
{
    int i, j;
    for (i=0; i<table.nbrTabsTuiles; i++)
    {
        for (j=0; j<table.tabsTuiles[i].nbrTuiles; j++) 
        {
            table.tabsTuiles[i].tuiles[j] = initialiser_tuile();
        }
    }
    return table;
}

TABTUILES vider_tabTuiles (TABTUILES tabTuiles) 
{
    int i;
    for (i=0; i<tabTuiles.nbrTuiles; i++)
    {
        tabTuiles.tuiles[i] = initialiser_tuile();
    }
    tabTuiles.nbrTuiles = 0;
    return tabTuiles;
}

CHEVALET* scoreFinal(CHEVALET* chevaletsJoueurs, int nbrJoueurs, int numGagnant, bool piocheVide)
{
    int i, somme, scoreGagnant;
    somme = 0;
    scoreGagnant = sommeTuiles(chevaletsJoueurs[numGagnant].tabTuiles);

    for (i=0; i<nbrJoueurs; i++) 
    {
        affecte_val_joker(chevaletsJoueurs[i].tabTuiles);
        somme = sommeTuiles(chevaletsJoueurs[i].tabTuiles);
        if (chevaletsJoueurs[i].joueur.numJoueur != numGagnant)
        {
            if (piocheVide)
            {
                chevaletsJoueurs[i].joueur.scoreJoueur = 0 -(somme - scoreGagnant);
                chevaletsJoueurs[numGagnant].joueur.scoreJoueur += chevaletsJoueurs[i].joueur.scoreJoueur;
            }
            else 
            {   
                chevaletsJoueurs[i].joueur.scoreJoueur = 0 - somme;
                chevaletsJoueurs[numGagnant].joueur.scoreJoueur += somme;
            }
        }
    }
    return chevaletsJoueurs;
}

numCase transformer_point_en_case(SDL_Event pos, int surface)
{
    numCase nc;
    if (surface == 1)
    {
        nc.l = (pos.button.y / 500);
        nc.c = (pos.button.x / 60) - 4;
    }
    else
    {
        nc.l = (pos.button.y / 100);
        nc.c = (pos.button.x / 62);
    }
    return nc;
}

SDL_Event transformer_case_en_point(numCase nc, int surface)
{
    SDL_Event centre;
    if (surface == 1)
    {
        centre.button.x = ((nc.c + 4) * 60);
        centre.button.y = ((nc.l + 1) * 80) + 350;
    }
    else
    {
        centre.button.x = ((nc.c) * 60) + 30;
        centre.button.y = ((nc.l + 1) * 65);
    }
    return centre;
}

bool peut_remplacer_tuile(numCase ncTuileAretirer, TABTUILES combinaison, TUILE tuileAdeposer)
{
    TABTUILES copieCombinaison;
    copieCombinaison = copier_tab(combinaison, copieCombinaison);
    if (ncTuileAretirer.l != -1 && ncTuileAretirer.c != -1) {
        copieCombinaison.tuiles[ncTuileAretirer.c] = tuileAdeposer;
        if (verif_combinaison(copieCombinaison))
        {
            return true;
        }
    }
    return false;
}

TABLE creer_table (int c, int l) 
{
    int i, j;
    TABLE tab;
    TUILE t;
    t = initialiser_tuile();
    tab.nbrTabsTuiles = l;
    for (i=0; i<tab.nbrTabsTuiles; i++) 
    {
        tab.tabsTuiles[i].tuiles = (TUILE*) malloc (sizeof(TUILE)*c);                          
        tab.tabsTuiles[i].nbrTuiles = c;
        for (j=0; j<tab.tabsTuiles[i].nbrTuiles; j++) 
        {
            tab.tabsTuiles[i].tuiles[j] = t;
        }
    } 
    return tab;
}

bool verifier_modification (TABTUILES tabTuiles, int colonne)
{
    TUILE t, t2;
    t = initialiser_tuile();
    if (colonne != -1) {
        t2 = tabTuiles.tuiles[colonne];
        if (!verifier_meme_tuile(t, t2)) 
        {
            return true;
        }
    }
    return false;
}

int calcul_combinaison (TABTUILES tab)
{
    int i, total;
    TABTUILES tabBis;
    tabBis = supp_tuiles_vides(tab);
    total = 0;
    if (tabBis.nbrTuiles >= 3) {
        for (i=0; i<tabBis.nbrTuiles; i++) 
        {
            total += tabBis.tuiles[i].numTuile;
        }
    }
    return total;
}

TUILE peut_decaler_combinaison (TABTUILES combinaison, TUILE tuileAjouter)
{
    TABTUILES combinaisonComplete, combinaisonAjoutFin, combinaisonAjoutDebut, combinaisonTuileDebut;
    TUILE tuileARetirer;
    tuileARetirer = initialiser_tuile();

    combinaisonComplete = copier_tab(combinaison, combinaisonComplete);
    combinaisonComplete = supp_tuiles_vides(combinaisonComplete);
    combinaisonAjoutFin = copier_tab(combinaisonComplete, combinaisonAjoutFin);
    combinaisonAjoutDebut = copier_tab(combinaisonComplete, combinaisonAjoutDebut);

    // Ajouter la tuile à la fin
    combinaisonAjoutFin = retirer_tuile(combinaisonComplete.tuiles[0], combinaisonAjoutFin);
    combinaisonAjoutFin = ajouter_tuile(tuileAjouter, combinaisonAjoutFin);

    // Ajouter la tuile au début
    combinaisonTuileDebut.nbrTuiles = 1;
    combinaisonTuileDebut.tuiles = (TUILE*) malloc (sizeof(TUILE)*1);
    combinaisonTuileDebut.tuiles[0] = tuileAjouter;
    combinaisonAjoutDebut = retirer_tuile(combinaisonComplete.tuiles[combinaisonComplete.nbrTuiles-1], combinaisonAjoutDebut);
    combinaisonTuileDebut = ajouter_tuiles(combinaisonAjoutDebut, combinaisonTuileDebut);

    if (verif_combinaison(combinaisonAjoutFin)) 
    {
        afficher_tab_tuiles(combinaisonAjoutFin);
        tuileARetirer = combinaisonComplete.tuiles[0];
    }
    else if (verif_combinaison(combinaisonTuileDebut))
    {
        afficher_tab_tuiles(combinaisonTuileDebut);
        tuileARetirer = combinaisonComplete.tuiles[combinaisonComplete.nbrTuiles-1];
    }
    return tuileARetirer;
}

TABTUILES peut_diviser_combinaison (TABTUILES combinaison, numCase ncTuileDepart)
{
    int i, y;
    y=0;
    TABTUILES combinaisonBis;
    combinaisonBis.tuiles = (TUILE*) malloc (sizeof(TUILE)*combinaison.nbrTuiles);
    combinaisonBis.nbrTuiles = y;
    for (i=ncTuileDepart.c; i<combinaison.nbrTuiles+1; i++)
    {
        if (!verifier_meme_tuile(combinaison.tuiles[i], initialiser_tuile())) {
            combinaisonBis.nbrTuiles = y;
            combinaisonBis.tuiles[y] = combinaison.tuiles[i];
            y++;
        }
    }
    if (verif_combinaison(combinaisonBis) && combinaisonBis.nbrTuiles != 0) return combinaisonBis;
    return combinaison;
}

int verif_selection(SDL_Event event)
{
    int retour;
    retour = 0;
    if ((event.button.x > 203 && event.button.x < 795) && (event.button.y > 410 && event.button.y < 595)) retour = 1;
    else if (event.button.x >= 13 && event.button.x <= 700 && event.button.y >= 35 && event.button.y <= 400) retour = 2;
    return retour;
}

numCaseTab combinaison_possible (CHEVALET chevaletJoueur) 
{
    int i, j;
    TABTUILES tabTuiles;
    numCaseTab combinaison;
    numCaseTab combinaisonMax;
    combinaisonMax.tab = (numCase*) malloc (sizeof(numCase)*11);
    combinaison.tab = (numCase*) malloc (sizeof(numCase)*11);
    tabTuiles.tuiles = (TUILE*) malloc (sizeof(TUILE)*11);
    tabTuiles.nbrTuiles = 0;
    combinaisonMax.nbrNumCase = 0;
    for (i=0; i<chevaletJoueur.tabTuiles.nbrTuiles; i++) 
    {
        if (i >= 9) {
            combinaison.tab[0].c = i-9;
            combinaison.tab[0].l = 1;
        }
        else {
            combinaison.tab[0].c = i;
            combinaison.tab[0].l = 0;
        }
        combinaison.nbrNumCase = 1;
        tabTuiles = ajouter_tuile(chevaletJoueur.tabTuiles.tuiles[i], tabTuiles);
        tabTuiles.nbrTuiles = 1;
        for (j=0; j<chevaletJoueur.tabTuiles.nbrTuiles; j++) 
        {
            if (j!=i) 
            {
                tabTuiles = ajouter_tuile(chevaletJoueur.tabTuiles.tuiles[j], tabTuiles);
                if (verif_combinaison(tabTuiles)) 
                {
                    if (j >= 9) {
                        combinaison.tab[combinaison.nbrNumCase].c = j-9;
                        combinaison.tab[combinaison.nbrNumCase].l = 1;
                    }
                    else {
                        combinaison.tab[combinaison.nbrNumCase].c = j;
                        combinaison.tab[combinaison.nbrNumCase].l = 0;
                    }
                    combinaison.nbrNumCase++;
                }
                else tabTuiles = retirer_tuile(chevaletJoueur.tabTuiles.tuiles[j], tabTuiles);
                if (combinaison.nbrNumCase > combinaisonMax.nbrNumCase) {
                    combinaisonMax = copier_tabNumCase(combinaison, combinaisonMax);
                }
            }
        }
        tabTuiles = vider_tabTuiles(tabTuiles);
    }
    if (combinaisonMax.nbrNumCase < 3) combinaisonMax.nbrNumCase = 0;
    return combinaisonMax;
}

numCaseTab supp_nc (numCaseTab ncTab)
{
    int i;
    for (i=0; i<ncTab.nbrNumCase-1; i++)
    {  
        if (ncTab.tab[i+1].c != 0)
        {
            ncTab.tab[i].c = (ncTab.tab[i+1].c)-1;
            ncTab.tab[i].l = ncTab.tab[i+1].l;
        }
    }
    ncTab.nbrNumCase--;
    return ncTab;
}

numCase verif_prendreTuileChev(SDL_Event event, TABTUILES tab)
{
    numCase nc;
    int ajout;
    nc = transformer_point_en_case(event, 1);
    ajout = 0;
    if (nc.l > 0) ajout = 9;
    if ((nc.c+ajout)<tab.nbrTuiles)
    {
        if ((tab.tuiles[nc.c+ajout].typeTuile == 0) || (tab.tuiles[nc.c+ajout].typeTuile == 1)) return nc;
    }   
    nc.c = -1;
    nc.l = -1;
    return nc;
}

TABTUILES verif_prendreTuileTable(SDL_Event event, TABLE table)
{
    numCase ncTable;
    TABTUILES tabTuiles;
    ncTable = transformer_point_en_case(event, 2);
    if ((table.tabsTuiles[ncTable.l].tuiles[ncTable.c].typeTuile == 0 || table.tabsTuiles[ncTable.l].tuiles[ncTable.c].typeTuile == 1))
    {
        tabTuiles = peut_diviser_combinaison(table.tabsTuiles[ncTable.l], ncTable);
        if (!verifier_meme_tabTuiles(tabTuiles, table.tabsTuiles[ncTable.l])) {
            return tabTuiles;
        }
    }
    tabTuiles.nbrTuiles = 0;
    return tabTuiles;
}

numCase verif_depose(SDL_Event event, TABLE table)
{
    numCase nc;

    if ((event.button.x >= 13 && event.button.x <= 700) && (event.button.y >= 35 && event.button.y <= 400))
    {
        nc = transformer_point_en_case(event, 2);
        if (nc.c < table.tabsTuiles[0].nbrTuiles && nc.l < table.nbrTabsTuiles) {
            TUILE t1 = initialiser_tuile();
            TUILE t2 = table.tabsTuiles[nc.l].tuiles[nc.c];
            if (verifier_meme_tuile(t1, t2) || t2.typeTuile == 0 || t2.typeTuile == 1) {
                return nc;
            }
        }
    }
    nc.c = -1;
    nc.l = -1;
    return nc;
}