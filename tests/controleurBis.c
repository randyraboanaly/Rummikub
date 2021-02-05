#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions.h"

/*****************************************
 * Contrôleur (Main) 
 ****************************************/

// Exécuter à la racine du dossier du projet : 
// gcc -Wall src/controleur.c src/vue.c src/modele.c -o bin/prog src/fonctions.h -I include -L lib -lmingw32 -lSDL2main -lSDL2
// et ensuite bin\prog.exe

int main (int argc, char **argv) {

	CHEVALET* chevaletsJoueurs;
    TUILE* combinaison; //(ensemble de TUILES pour les suites et les séries)
    TUILE** table; //(ensemble des combinaisons posées sur le plateau)
    TUILE* pioche;
    int tourJoueur, tourJoueurBis, gagnant, nbrJoueurs, modeJeu, difficulteJeu, i, scoreJoueur, nbrCombinaisons, nbrJoueursDebuter;
    BOOL piocheVide;
    piocheVide = false;

    // On alloue les tableaux de pointeurs
    chevaletsJoueurs = (CHEVALET*) malloc (sizeof(CHEVALET));
    combinaison = (TUILE*) malloc (sizeof(TUILE));
    table = (TUILE**) malloc (sizeof(TUILE*));
    pioche =  (TUILE*) malloc (sizeof(TUILE));
    debuterPartie =  (int*) malloc (sizeof(int));

    // Affichage du menu du jeu
    afficher_menuJeu();

    // Choix du nombre de joueurs
    nbrJoueurs = choisir_NbrJoueurs(POINT clic);

    // Choix du mode de jeu
    modeJeu = choisir_ModeJeu(POINT clic);

    // Choix de la difficulté de l’ordinateur (si le mode de jeu choisi est : humain contre ordinateur)
    if (modeJeu == 2) difficulteJeu = choisir_DifficulteOrdi(POINT clic);

    // Saisie des pseudos
    for (i=0; i<nbrJoueurs; i++) {
        chevaletsJoueurs[i].joueur.numJoueur = i;
        // On récupère le contenu inséré dans les champs de texte (dans l’affichage)
        chevaletsJoueurs[i].joueur.nomJoueur = recupérerContenuChamp(i);
        chevaletsJoueurs[i].joueur.scoreJoueur = 0;
    }

    // Initialisation de la pioche
    pioche = initialiser_pioche(pioche);

    // Affichage du plateau de jeu
    afficher_tabJeu();

    // Les joueurs piochent 14 tuiles
    for (i=0; i<nbrJoueurs; i++) {
        chevaletsJoueurs[i].tabTuiles.tuiles =  (TUILE*) malloc (sizeof(TUILE));
        chevaletsJoueurs[i].tabTuiles = piocher_tuile(14, pioche);
        // On retire les tuiles piochées de la pioche
        pioche = retirer_tuiles(chevaletsJoueurs[i].tabTuiles, pioche);
    }


    // Début de la partie
    tourJoueur = choisir_tourJoueur(nbrJoueurs, pioche);
    tourJoueurBis = tourJoueurBis;

    nbrJoueursDebuter = 0;
    
    // Le joueur choisi dépose ses combinaisons sur la table
    do {
        nbrCombinaisons = 0;
        clic = wait_clic();
        // On boucle tant que le joueur actif n’a pas cliqué sur le bouton finir le tour
        while (!finir_tour(POINT clic)) {
            clic = wait_clic();
            // On vérifie si le joueur a cliqué sur “valider une combinaison”
            if (valider_combinaison(POINT clic)) {
                // On vérifie si la combinaison validée est correcte
                if (verif_combinaison(combinaison)) {
                    // On ajoute la combinaison actuelle au tableau “table”
                    nbrCombinaisons++;
                    ajouterCombinaisonAtable(combinaison,table);
                }
            }
            // Si ce n’est pas le cas, cela veut dire qu’il a cliqué sur une tuile à déplacer
            else {
                position = verif_prendreTuile (tourJoueur, clic);
                if (position != -1) {
                    // On convertit un point du plateau en une numCase d'un chevalet
                    i = transformer_point_en_ind(position); 
                    t = chevaletsJoueurs[tourJoueur].tuiles[i];
                    clic = wait_clic();
                    position = verif_deposeTuile (tourJoueur, clic);
                    // On vérifie si l’endroit où le joueur souhaite déposer la tuile est correct
                    if (position != -1) {
                        afficher_tuile(position, t);
                    }
                }
            }
        }
        // On calcule la somme des combinaisons de la table
        for (i=0; i<nbrCombinaisons; i++) {
            chevaletsJoueurs[tourJoueur].joueur.scoreJoueur += calcul_combinaison(table[i]);
        }

        // On vérifie si le joueur actif peut débuter la partie (si son score >= 30)
        if (verif_peut_debuter_partie(chevaletsJoueurs[tourJoueur].joueur.scoreJoueur)) {
            // On supprime les tuiles posées par le joueur de son chevalet
            chevaletsJoueurs[tourJoueur].tuiles = retirerCombinaisonsJoueur(table, chevaletsJoueurs[tourJoueur].tuiles);
            nbrJoueursDebuter++;
        }
        // SINON cela veut dire que son score <30 alors le joueur actif pioche et passe son tour
        else {
            chevaletsJoueurs[tourJoueur].joueur.scoreJoueur = 0;
            chevaletsJoueurs[tourJoueur].tuiles = piocher_tuile(1, pioche, false);
        }

        // On boucle tant que le prochain joueur est égal au joueur actif ou s'il a déjà validé sa combinaison
        while (tourJoueurBis == tourJoueur || verif_a_debute_partie(tourJoueur)) tourJoueur = i = rand() % 3;
        tourJoueur = tourJoueurBis;

	} while (nbrJoueursDebuter!=nbrJoueurs);


    // Début partie
    do {
        /* Faire les opérations liées à un début de partie */

        // On vérifie si l'un des joueurs a gagné
        gagnant = joueur_a_gagne(chevaletsJoueurs, nbrJoueurs);
        // On vérifie si la pioche est nulle, dans ce cas on choisit un gagnant
        if (pioche->numTuile=0 && gagnant==-1) {
            gagnant = minSommeTuiles(chevaletsJoueurs);
            piocheVide = true;
        }

    } while(gagnant==-1)

    chevaletsJoueurs = scoreFinal(chevaletsJoueurs, nbrJoueurs, gagnant, piocheVide);

    // On enregistre les pseudos et les scores des joueurs
    for (i=0; i<nbrJoueurs; i++) 
    {
        sauvegarder_file(chevaletsJoueurs);
    }

    return 0;
}
