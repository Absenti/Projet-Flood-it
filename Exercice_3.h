#ifndef __Exercice_3__
#define __Exercice_3__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Structure.h"
#include "Exercice_2.h"

//Initialisation une S_Zsg
void init_Zsg(S_Zsg ** Z, int dim, int nbcl) ;

//Ajoute une case dans Lzsg
int ajoute_Zsg(S_Zsg * Z, int i , int j);

//Ajoute une case dans la bordure *B
int ajoute_Bordure(S_Zsg * Z, int i, int j, int couleur);

//Verifie si la case appartient à la Lzsg
int appartient_Zsg(S_Zsg * Z, int i, int j);

// Verifie si la case appartient à la bordure
int appartient_Bordure(S_Zsg*Z, int i, int j, int couleur);

//Renvoi le nombre de case ajoutées à Lzsg 
int agrandi_Zsg(int **M, S_Zsg * Z, int cl, int k, int l);

//Version rapide
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff) ;

#endif  /* __Exercice_3__ */
