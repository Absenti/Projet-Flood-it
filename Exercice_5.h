#ifndef __Exercice_5__
#define __Exercice_5__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Structure.h"
#include "Exercice_4.h"

/* Met a jour les champs du graphe_zone g_z en ajoutant s a la Zsg : suivant le meme principe que la fonction 3.2 (mais adapte pour un sommet-zone)*/
void agrandi_Zsg_graphe(Graphe_zone *g_z, Sommet *s);
/* Calcule une sequence de couleurs en appliquant la strategie max-bordure : similaire a la fonction 3.3*/
int sequence_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __Exercice_5__ */
