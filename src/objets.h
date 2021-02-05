#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

/*****************************************
 * Enum
 ****************************************/

enum COULT { Jaune, Rouge, Noir, Bleu };

enum TYPET { Joker, Simple };

/*****************************************
 * Structures
 ****************************************/

typedef struct TUILE 
{ 
    int numTuile; 
    enum COULT coulTuile;
    enum TYPET typeTuile;

} TUILE;

typedef struct TABTUILES 
{ 
    TUILE * tuiles;
    int nbrTuiles;
} TABTUILES;

typedef struct JOUEUR
{
	int numJoueur;
	char* nomJoueur;
    int scoreJoueur;
} JOUEUR;

typedef struct CHEVALET 
{	
    TABTUILES tabTuiles;
	JOUEUR joueur;
} CHEVALET;

typedef struct numCase
{
    int l;
    int c;
} numCase;

typedef struct TABLE
{
	TABTUILES* tabsTuiles;
    int nbrTabsTuiles;
} TABLE;

typedef struct numCaseTab
{
    numCase* tab;
    int nbrNumCase;
} numCaseTab;

