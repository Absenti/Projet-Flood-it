#ifndef __Exercice_6__
#define __Exercice_6__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Structure.h"
#include "Exercice_5.h"



/* initialise la File */
void initFile(File_Sommet **F);
/* realise l'operation enfiler */
void enfiler(File_Sommet *F, Sommet *s);
/* realise l'operation defiler */
Sommet *defiler(File_Sommet *F);


/* Realise un parcours en largeur dans le graphe g_z a partir du sommet racine : mise a jour des champs distance et pere de tous les sommets-zones de g_z */
void parcours_en_largeur(Graphe_zone *g_z, Sommet *racine);
/* Calcule  une sequence de couleurs en appliquant la strategie parcours en largeur puis max-bordure*/
int sequence_parcours_largeur_puis_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __Exercice_6__ */
