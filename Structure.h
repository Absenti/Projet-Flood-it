#ifndef __STRUCTURE__
#define __STRUCTURE__

#include "API_Grille.h"
#include "Liste_case.h"


/*Exercice 3*/

typedef struct {
	int dim;
	int nbcl;
	
	ListeCase Lzsg;
	ListeCase *B;
	int **App;
} S_Zsg;


/*Exercice 4*/ 

typedef struct sommet Sommet;

typedef struct cellule_som{
	Sommet *sommet ; 
	struct cellule_som *suiv;
	struct cellule_som * prec; //Exercice 5 pour parcours en largeur
} Cellule_som; 

struct sommet{
	int num;	/* Numero du sommet (sert uniquement a l'affichage) */
	int cl;		/* Couleur d'origine du sommet-zone */
	ListeCase cases;	/* Listes des cases du sommet-zone */
	int nbcase_som; /* Nombre de cases de cette liste */
	Cellule_som *sommet_adj;	/* Liste des aretes pointeurs sur les sommets adjacent */
	
	// Exercice 5 // 
	int distance;			/* distance au noeud racine : sert uniquement dans l'exo 5 */
	Sommet * pere;			 /* Pere du sommet dans l'arborescence du parcours en largeur : exo5 uniquement */

};

typedef struct graphe_zone 
{
    int nbsom;         /* Nombre de sommets dans le graphe */
    int nbcl;          /* nombre de couleurs */
    int *marque;        /* Tableau de marquage des sommets-zones : 0(Lzsg), 1(Bordure) ou 2(non-visite) */

    Cellule_som * Lzsg; /* Liste des sommets-zones appartenant a la  ;zone superieure gauche*/
    int nb_som_zsg;     /* Nombre sommets-zones dans la Zsg : a mettre a jour*/

    Cellule_som ** B;  /* Tableau de listes de sommets-zones composant la bordure de la Zonz superieure gauche indicé sur les couleurs*/
    int *tailleB;      /* Taille de chacune des listes des sommets-zones composant la bordure : a maintenir a jour */
	int dim;
    Cellule_som * som;  /* Liste chainee des sommets-zones du graphe */

    Sommet *** mat;    /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient ue case (i, j) de la grille */
}Graphe_zone;



//Exercice 6//

/* Struct de File (liste doublement chainee) destine a stocker des sommets (Exo 5) */

typedef struct _fileSommet {
    Cellule_som * tete;
    Cellule_som * queue;
    int nb;
} File_Sommet;


#endif  /* __STRUCTURE__ */
