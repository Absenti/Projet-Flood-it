#include<stdio.h>
#include "Exercice_5.h"

void agrandi_Zsg_graphe(Graphe_zone *graphe, Sommet *s)
{
	
/* Le but ici est d'ajouter les sommets adjacent de s en tant que bordure (s'ils ne sont pas deja dans la Lzsg ou la bordure)

Etape 1 : Initialisation de la liste de sommets adjacent
Etape 2 : On parcourt la liste, si le sommet est marqué comme '"non visité (2)", alors on l'ajoute à la bordure, on change le marquage, et tailleB qu'on augmente

*/
	// Etape 1 //
	Cellule_som * adj = (Cellule_som*) malloc(sizeof(Cellule_som));
	adj = s->sommet_adj;
	// Etape 2 //
	while(adj !=NULL){
		//printf("at least here\n");
		if(graphe->marque[adj->sommet->num]==2){
			ajoute_liste_sommet(adj->sommet,&graphe->B[adj->sommet->cl]);
			graphe->marque[adj->sommet->num] = 1;
			graphe->tailleB[adj->sommet->cl]++;
			
			
		}
		
		adj = adj->suiv;
	}
	free(adj);
	
}
int sequence_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff)
{
	/*
	Etape 1 : Instancier d'un graphe via cree_graphe_zone
	Etape 2 : agrandirrt_zone à partir de graphe->mat[0][0]
	Etape 3 : A que tour, determiner la couleur de la plus grosse bordure (via tailleB) 
	Etape 3 bis : Utiliser agrandi_zsg_graphe_zone pour chaque sommet de B[cl] 
	Etape 4 (optionnel) : Si aff, parcourir graphe->lzsg et attribuer aux cases correspondant de la grille la couleur
	Etape 5 : Condition d'arret => nb de sommet de zsg = nbsom du graphe
	Etape 6 : Retourner le nb de changement de couleur
*/
	int cpt = 0;
	//Etape 1
	Graphe_zone * graphe = cree_graphe_zone(M, dim, nbcl);

	//Etape 2 : Ajouter la case de reference
	
	ajoute_liste_sommet(graphe->mat[0][0], &graphe->Lzsg);
	agrandi_Zsg_graphe(graphe,graphe->mat[0][0]);
	graphe->marque[graphe->mat[0][0]->num] = 0;
	graphe->nb_som_zsg++;
	
		
	//Etape 3 
	int compteur_sommet = 1;//Car on a ajouter le sommet concernant la case (0,0);
	int couleur = 0;
	
	while(compteur_sommet != graphe->nbsom){
		//Trouver une nouvelle couleur
		couleur = graphe->mat[0][0]->cl;
		for (int i = 0; i< nbcl; i++){
			if(graphe->tailleB[i] > graphe->tailleB[couleur] && i!= couleur){
				couleur = i;
			}
		}		
		cpt++;
		
		
		//Pour la couleur donnée, je transfere les cases de la bordure dans la Lzsg
		Cellule_som * b_temp = graphe->B[couleur];
		while(b_temp!= NULL) {
			agrandi_Zsg_graphe(graphe, b_temp->sommet); // Les cases autour deviennent la nouvelle bordure
			compteur_sommet++; // augmente le nombre de sommet dans la lzsg
			ajoute_liste_sommet(b_temp->sommet, &graphe->Lzsg); // On ajoute le sommet à la lzsg
			graphe->marque[b_temp->sommet->num] = 0; // On marque ce sommet en tant que zsg
			b_temp = b_temp->suiv; // On passe au suivant
		}
		//Je remets à 0 la liste de sommet pour cette couleur dans **B
		detruit_liste_sommet(&b_temp);
		detruit_liste_sommet(&graphe->B[couleur]);
		graphe->B[couleur] = NULL;
		graphe->tailleB[couleur] = 0;
		
		if(aff) {
			for(Cellule_som*z_temp = graphe->Lzsg ; z_temp != NULL; z_temp = z_temp->suiv){
				for(ListeCase Lz_temp = z_temp->sommet->cases ; Lz_temp != NULL; Lz_temp = Lz_temp->suiv){
					Grille_attribue_couleur_case(G,Lz_temp->i,Lz_temp->j,couleur);
					
				}
			}
			Grille_redessine_Grille(G);
			Grille_attente_touche();
		}
		
	
	}
	liberer_graphe_zone(graphe);
	return cpt;
		
}
