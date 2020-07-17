#ifndef __Exercice_7__
#define __Exercice_7__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Structure.h"
#include "Exercice_6.h"

//int sequence_diagonale(int ** M, Grille * G,int dim, int nbcl, int aff);

void trouve_zone_case_maxbordure(int **M, int nbcase, int i, int j, int *taille, int nbcl, int * tab_couleur, ListeCase * L);
int sequence_aleatoire_case_maxbordure(int **M, Grille *G, int dim, int nbcl, int aff);


#endif  /* __Exercice_7__ */
