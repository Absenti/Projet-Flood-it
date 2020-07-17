#include<stdio.h>
#include "Exercice_6.h"



/* initialise la File */
void initFile(File_Sommet **F){
	File_Sommet * T = (File_Sommet*)malloc(sizeof(File_Sommet));
	if(T == NULL) 
		printf("Erreur d'allocation du File_Sommet\n");
	T->tete = NULL;
	T->queue = NULL;
	(T) ->nb = 0; 
	*F = T;

}
/* realise l'operation enfiler */
void enfiler(File_Sommet *F, Sommet *s){
	Cellule_som * temp = NULL;
	ajoute_liste_sommet(s, &temp);
	switch(F->nb){
		case 0:
			F->tete = temp;
			break;
		case 1 : // S'il y a que la tete alors on cree la queue et la relie à la tete
			F->queue= temp;
			F->queue->suiv = F->tete; 
			F->tete->prec = F->queue;
			
			break;
		default: //S'il y a une tete et une queue deja existante
			temp->suiv = F->queue;
			F->queue->prec = temp;
			F->queue = temp;
			break;
	}
	F->nb++;

}

/* realise l'operation defiler =>enlever la tete */
Sommet *defiler(File_Sommet *F){
	if (F == NULL || F->nb == 0)
		return NULL;
	Cellule_som * temp = F->tete;
	Sommet * s = (Sommet*)malloc(sizeof(Sommet));
	if(F->nb==1){ // S'il n'y a que la tete, on le prend
		s = temp->sommet;
		F->tete=NULL;
	}
	else{
		F->tete = F->tete->prec;
		F->tete->suiv = NULL;
		s = temp->sommet;
		
	}
	detruit_liste_sommet(&temp);
	F->nb--;
	return s;
}


/* Realise un parcours en largeur dans le graphe g_z a partir du sommet racine : mise a jour des champs distance et pere de tous les sommets-zones de g_z */
void parcours_en_largeur(Graphe_zone *graphe, Sommet *racine){
	
/* Distance = nombre d'arete par rapport à la racine
Pere = sommet pere
Les deux dans la structure de sommet
*/	
	
	//Matrice booleenne de verification
	int *visit = (int*) malloc(sizeof(int)*graphe->nbsom);
	for (int i = 0; i < graphe->nbsom ; i++) visit[i] = 0; 

	File_Sommet *F = NULL;
	initFile(&F);

	Sommet * s1_temp = NULL;
	Sommet * s2_temp = NULL;
	Cellule_som * c_temp = NULL;	

	//On ajoute deja la racine
	visit[racine->num] = 1;
	enfiler(F, racine);
	int distance = 0;
	
	while(F->nb > 0){
		s1_temp = defiler(F);
		distance++;
		for(Cellule_som * c_temp = s1_temp->sommet_adj ; c_temp !=NULL; c_temp=c_temp->suiv){
			s2_temp = c_temp->sommet;
			//Si le sommet n'a pas encore été visité
			if (! visit[s2_temp->num]){
				visit[s2_temp->num] = 1;
				enfiler(F,s2_temp);
				s2_temp->pere = s1_temp;
				s2_temp->distance = distance;
			}
		}
	}
	free(visit);
	free(c_temp);	
} 
/* Calcule  une sequence de couleurs en appliquant la strategie parcours en largeur puis max-bordure*/
int sequence_parcours_largeur_puis_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff){

/* 
Etape 1 : Initialisé les structure et variable dont on a besoin
Etape 2 : Effectuer le parcours en largeur
Etape 3 : Ajouter la racine à la zsg
Etape 4 : Determiner le chemin le plus rapide de la racine à la case (dim-1, dim-1) supposéé derniere, et ainsi les couleurs du chemin, et effectuer le trajet
Etape 5 : Re-definir la bordure de la Zsg pour faire la sequence max bordure
Etape 6 : Parcours max-bordure (voir exercice 5 pour plus d'explication)
Etape 7 : Liberer la mémoire
*/
	
	
	// Etape 1 // 
	int cpt = 0; // compteur à renvoyer pour le changement de couleur
	int compteur_sommet = 1; // compteur de sommet pour la boucle
	int couleur=0; // defini la couleur
	int cpt_couleur=0; // compteur de changement de couleur dans boucle

	Graphe_zone * graphe = cree_graphe_zone(M,dim,nbcl);
	Sommet * racine = graphe->mat[0][0];

	Cellule_som * temp = (Cellule_som*) malloc(sizeof(Cellule_som));
	temp = NULL;

	// Etape 2 //
	parcours_en_largeur(graphe,racine); 

	// Etape 3 //
	ajoute_liste_sommet(racine, &graphe->Lzsg);
	graphe->marque[racine->num] = 0;
	graphe->nb_som_zsg++;

	
	
	// Etape 4 //
	for(Sommet * bas_droite = graphe->mat[dim-1][dim-1]; bas_droite != graphe->mat[0][0] ; bas_droite = bas_droite->pere){
		ajoute_liste_sommet(bas_droite, &temp);
		cpt_couleur++;
		
	}
	for(Cellule_som * temp2 = temp; temp2 != NULL; temp2 = temp2->suiv){
		ajoute_liste_sommet(temp2->sommet, &graphe->Lzsg);
		graphe->marque[temp2->sommet->num] = 0;
		graphe->nb_som_zsg++;
		cpt_couleur--;
		cpt++;
		compteur_sommet++;
		
		if(aff) {
			for(Cellule_som*z_temp = graphe->Lzsg ; z_temp != NULL; z_temp = z_temp->suiv){
				
				for(ListeCase Lz_temp = z_temp->sommet->cases ; Lz_temp != NULL; Lz_temp = Lz_temp->suiv){
					Grille_attribue_couleur_case(G,Lz_temp->i,Lz_temp->j,couleur);
					M[Lz_temp->i][Lz_temp->j] = couleur;
					
				}
			}
			Grille_redessine_Grille(G);
			Grille_attente_touche();
		}
	}

	// Etape 5 // 
	for(Cellule_som*bordure_temp = graphe->Lzsg ; bordure_temp !=NULL; bordure_temp = bordure_temp->suiv)
		agrandi_Zsg_graphe(graphe, bordure_temp->sommet);
	
	detruit_liste_sommet(&temp);
	
	//sequence_max_bordure(M,G,dim,nbcl,aff); ne fonctionne pas

	
	
	// Etape 6 //
	while(compteur_sommet != graphe->nbsom ){
		//Trouver une nouvelle couleur
		
		couleur = graphe->mat[0][0]->cl;
		for (int i = 0; i< nbcl; i++){
			if(graphe->tailleB[i] > graphe->tailleB[couleur] && i!= graphe->mat[0][0]->cl){
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
				for(ListeCase Lz_temp = z_temp->sommet->cases ; Lz_temp != NULL; Lz_temp = Lz_temp->suiv)
					Grille_attribue_couleur_case(G,Lz_temp->i,Lz_temp->j,couleur);	
			}
			Grille_redessine_Grille(G);
			Grille_attente_touche();
		}
	}
	// Etape 7 //
	liberer_graphe_zone(graphe);
	return cpt;
}
