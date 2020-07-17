#ifndef __Exercice_4__
#define __Exercice_4__

#include "API_Grille.h"
#include "Liste_case.h"
#include "Structure.h"
#include "Exercice_3.h"

void ajoute_liste_sommet(Sommet *s, Cellule_som **L);


void detruit_liste_sommet(Cellule_som **L);

void ajoute_voisin(Sommet *s1, Sommet *s2);

int adjacent(Sommet *s1, Sommet *s2);

Graphe_zone * cree_graphe_zone(int**M, int dim, int nbcl);

void afficher_sommet(Sommet *s);

void mise_en_place(int ** M, int dim, int nbcl); 

void affiche_graphe(Graphe_zone * graphe);

void liberer_graphe_zone(Graphe_zone *graphe);

#endif  /* __Exercice_4__ */
