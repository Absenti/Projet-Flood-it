#ifndef __Exercice_2__
#define __Exercice_2__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Exercice_1.h"
// Version itérative 
void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L);

// Meme fonction que sequence_aleatoire_rec mais qui utilise trouve_moi_imp
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __Exercice_2__ */
