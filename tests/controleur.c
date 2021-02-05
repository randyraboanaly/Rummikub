#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"

/*****************************************
 * Contrôleur (Main) 
 ****************************************/

// Exécuter à la racine du dossier du projet : 
// gcc -Wall src/controleur.c src/vue.c src/modele.c -o bin/prog src/fonctions.h -I include -L lib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image
// et ensuite bin\prog.exe

int main (int argc, char **argv) {

	CHEVALET* chevaletsJoueurs;
    TABTUILES pioche;
    int i, nbrJoueurs, tourJoueur, tourJoueurBis, gagnant;

    // On alloue les tableaux de pointeurs
    chevaletsJoueurs = (CHEVALET*) malloc (sizeof(CHEVALET));
     
    // Initialisation de la pioche
    pioche = initialiser_pioche(pioche);
    
    nbrJoueurs = 2;

    for (i=0; i<nbrJoueurs; i++) {
        // On affecte à chaque joueur un numéro
        chevaletsJoueurs[i].joueur.numJoueur = i;
        // On affecte à chaque joueur un score nul
        chevaletsJoueurs[i].joueur.scoreJoueur = 0;
        // Les joueurs piochent 14 tuiles
        chevaletsJoueurs[i].tabTuiles.tuiles =  (TUILE*) malloc (sizeof(TUILE));
        chevaletsJoueurs[i].tabTuiles = piocher_tuile(14, pioche);
        // On retire les tuiles piochées de la pioche
        pioche = retirer_tuiles(chevaletsJoueurs[i].tabTuiles, pioche);
    }

    // Début de la partie
    tourJoueur = choisir_tourJoueur(nbrJoueurs, pioche);
    tourJoueurBis = tourJoueur;
    printf("tour = %d\n", tourJoueurBis);

    // Vérifier si l'un des joueurs a gagné
    gagnant = joueur_a_gagne(chevaletsJoueurs, nbrJoueurs);
    if (pioche.nbrTuiles==0) gagnant = minSommeTuiles(chevaletsJoueurs, nbrJoueurs);
    printf("gagnant = %d\n",gagnant);

    // Sauvegarder les pseudos et scores des joueurs
    //sauvegarder_file(chevaletsJoueurs, nbrJoueurs);

    return 0;
}
