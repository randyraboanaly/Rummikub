#include "objets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>

/*****************************************
 * Fonctions modèle
 ****************************************/

TABTUILES initialiser_pioche(TABTUILES pioche);
TABTUILES melanger_pioche(TABTUILES pioche);
void afficher_tab_tuiles(TABTUILES tuiles);
bool verif_combinaison(TABTUILES combinaison);
bool verifier_meme_tuile(TUILE tuileA, TUILE tuileB);
bool verifier_meme_tabTuiles (TABTUILES tab1, TABTUILES tab2);
TABTUILES retirer_tuile(TUILE tuileAretirer, TABTUILES tuiles);
TABTUILES retirer_tuiles(TABTUILES tuilesAretirer, TABTUILES tuiles);
TABTUILES piocher_tuile(int nbrTuiles, TABTUILES pioche);
int choisir_tourJoueur(int nbrJoueurs, TABTUILES pioche);
TUILE initialiser_tuile(void);
TABTUILES copier_tab(TABTUILES tab1, TABTUILES tab2);
TABTUILES ajouter_tuile (TUILE tuileAajouter, TABTUILES tab);
TABTUILES ajouter_tuiles (TABTUILES tuilesAajouter, TABTUILES tab);
int indMaxTuile(TABTUILES tab);
void sauvegarder_file (CHEVALET* chevaletsJoueurs, int nbrJoueurs);
int joueur_a_gagne(CHEVALET* chevaletsJoueurs, int nbrJoueurs);
int sommeTuiles(TABTUILES tab);
int minSommeTuiles(CHEVALET* chevaletsJoueurs, int nbrJoueurs);
TABTUILES affecte_val_joker(TABTUILES tab);
bool verif_debute_partie(int scoreJoueur);
int calcul_combinaison (TABTUILES tab);
bool verif_peut_debuter_partie(int scoreJoueur);
bool verifier_modification (TABTUILES tabTuiles, int colonne);
numCase transformer_point_en_case(SDL_Event pos, int surface);
SDL_Event transformer_case_en_point(numCase nc, int surface);
int verif_selection(SDL_Event event);
numCase verif_prendreTuileChev(SDL_Event event, TABTUILES tab);
TABTUILES verif_prendreTuileTable(SDL_Event event, TABLE table);
numCase verif_depose (SDL_Event event, TABLE table);
bool peut_remplacer_tuile(numCase ncTuileAretirer, TABTUILES combinaison, TUILE tuileAdeposer);
TUILE peut_decaler_combinaison (TABTUILES combinaison, TUILE tuileAjouter);
TABTUILES peut_diviser_combinaison (TABTUILES combinaison, numCase ncTuileDepart);
TABTUILES supp_tuiles_vides (TABTUILES tab);
TABLE vider_table (TABLE table);
TABLE peut_replacer_partie_diviser (TABTUILES tabTuiles, TABLE table, numCase ncTable);
TABLE creer_table (int c, int l);
numCaseTab combinaison_possible (CHEVALET chevaletJoueur);
numCaseTab supp_nc (numCaseTab ncTab);
TABTUILES vider_tabTuiles (TABTUILES tabTuiles);
numCaseTab copier_tabNumCase(numCaseTab tab1, numCaseTab tab2);
void afficher_tab_numCase(numCaseTab tabNumCase);
CHEVALET* scoreFinal(CHEVALET* chevaletsJoueurs, int nbrJoueurs, int numGagnant, bool piocheVide);

/*****************************************
 * Fonctions vue
 ****************************************/

/*
int choisir_DifficulteOrdi(POINT clic);
char* recupererContenuChamp(int ind);
*/
bool clic_bouton (SDL_Event event, SDL_Rect imageJouer);
void cleanup();
bool verif_clic (SDL_Event event);
SDL_Color get_color(enum COULT couleur);
int init(int imgFlags);
SDL_Surface* creer_fenetre();
SDL_Rect afficher_image_menu(SDL_Surface* pWindowSurface, const char* imagePath, int num);
SDL_Surface* ecrire_texte(TTF_Font* pFont,const char texte[], SDL_Color color, SDL_Surface *ecran, int y);
SDL_Rect creer_surface(SDL_Surface *ecran, int x, int y,int w,int h,int rouge, int vert, int bleu);
void afficher_tab_jeu(SDL_Surface* pWindowSurface,const char* fontPath);
void afficher_modeJeu(SDL_Surface* pWindowSurface, const char* fontPath, TTF_Font* pFont, SDL_Color color_black);
void afficher_NbrJoueurs (SDL_Surface* pWindowSurface, const char* fontPath, TTF_Font* pFont, SDL_Color color_black);
SDL_Rect afficher_bouton(TTF_Font* pFont,const char num_tuile[],SDL_Color fontColor, SDL_Surface *ecran, int x, int y,int w,int h,int rouge, int vert, int bleu, int x_num_tuile, int y_num_tuile);
void afficher_tuiles (TTF_Font* pFont, SDL_Surface *pWindowSurface, TABTUILES tab, int x, int y, int interface);
void tuile_active(SDL_Surface* ecran, int x, int y);
int retourne_pos (int numTuile);
char**  recuperer_pseudo_clavier(SDL_Surface* fenetre,int nbjoueurs,int modejeu);
void afficher_board (SDL_Surface* pWindowSurface);
void afficher_combinaisons (SDL_Surface* pWindowSurface);
void afficher_score (SDL_Surface* pWindowSurface, int nbJoueurs,const char* fontPath, CHEVALET* chevaletsJoueurs,char** les_pseudos,int tourJoueur);
void afficher_tour(SDL_Surface* pWindowSurface, const char* fontPath, char * nom_joueur);
void efface_tour(SDL_Surface* pWindowSurface);
bool afficher_finPartie(SDL_Surface* pWindowSurface, const char* fontPath, TTF_Font* pFont, SDL_Color color_blue,int nbjoueurs, char** les_pseudos, char* gagnant, CHEVALET* chevaletsJoueurs);