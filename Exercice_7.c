#include<stdio.h>
#include "Exercice_7.h"
/*
New strategie = parcours à partir du milieu 

int sequence_couleur_favorite(int ** M, Grille * G,int dim, int nbcl, int aff){
	int cpt=0;
	//Erreur de base
	if( M == NULL || G == NULL || dim < 0 || nbcl < 1){
		printf("Probleme d'argument\n");
		exit(0);
	}
	int milieu;
	if (dim %2) milieu = dim/2; // si dim est pair
	if(! dim%2) milieu = (dim+1)/2 // si dim est impair
	
}
 
// Parcours couleur favorite	
int sequence_couleur_favorite(int ** M, Grille * G,int dim, int nbcl, int aff){
	int cpt=0;
	//Erreur de base
	if( M == NULL || G == NULL || dim < 0 || nbcl < 1){
		printf("Probleme d'argument\n");
		exit(0);
	}
	//Taleau pour compter les couleur
	int *tab_couleur = (int*) malloc(sizeof(int)*nbcl);
	for(int i = 0; i < nbcl ; i++) tab_couleur[i] = 0;
	//Combien de case par couleur
	for(int i = 0; i < dim ; i++)
		for(int j = 0; j < dim ; j ++)
			tab_couleur[M[i][j]]++;
	int couleur_max = 0;
	// recherche du max dans le tableau
	for (int i =0; i < nbcl ; i++) if(tab_couleur[i] > couleur_max) couleur_max = tab_couleur[i];
	
	int taille_init = 0;
	int taille_final = dim*dim;
		
	while (taille_init != taille_final){
		ListeCase L = malloc(sizeof(ListeCase));
		init_liste(&L);
		

// Parcours max bordure avec listeCase

*/

void trouve_zone_case_maxbordure(int **M, int nbcase, int i, int j, int *taille, int nbcl, int * tab_couleur, ListeCase * L){
	
	//Erreur de base	
	if (M == NULL || nbcase < 0 || i < 0 || j < 0) {
		printf("Erreur d'argument\n");
		exit(0);
	}
	
	//Debut comme la version recursive
	int couleur = M[i][j]; //On defini la couleur de la case choisi comme référence
	ListeCase pile; //On alloue la pile 
	init_liste(&pile);
	ajoute_en_tete(&pile, i, j);
	int boole = 1 ;
	//On defini une nouvelle liste qui va nous servir à empiler la case autour, avant de les analyser 
	while (test_liste_vide(&pile) == 0) { // tant que la liste est non vide
		int i2, j2;
		enleve_en_tete(&pile, &i2, &j2); // dépile en affectant les valeurs de i et j et la tete de liste à i2 et j2 
		
		if(M[i2][j2] != -1){
			ajoute_en_tete(L,i2,j2);
			* taille = *taille +1;
			M[i2][j2] = -1;
			
			// On s'occupe maintenance de ce qu'il y a autour en reprenant les conditions de la version récursif 
			
			if (i2 != nbcase-1 && M[i2+1][j2] == couleur) ajoute_en_tete(&pile, i2+1, j2); // on empile la case du dessus dans la zsg
			if (i2 != nbcase-1 && M[i2+1][j2] != couleur) tab_couleur[M[i2+1][j2]]++; // on empile la case du dessus dans la bordure
		
			if (i2 != 0 && M[i2-1][j2] == couleur) ajoute_en_tete(&pile, i2-1, j2); // on empile la case du dessous
			if (i2 != 0 && M[i2-1][j2] != couleur) tab_couleur[M[i2-1][j2]]++; // on empile la case du dessous

			if (j2 != nbcase-1 && M[i2][j2+1] == couleur) ajoute_en_tete(&pile, i2, j2+1); // on empile la case à droite
			if (j2 != nbcase-1 && M[i2][j2+1] != couleur) tab_couleur[M[i2][j2+1]]++; // on empile la case à droite

			if (j2 != 0 && M[i2][j2-1] == couleur) ajoute_en_tete(&pile, i2, j2-1); //On empile la case à gauche
			if (j2 != 0 && M[i2][j2-1] != couleur) tab_couleur[M[i2][j2-1]]++; //On empile la case à gauche
		}
	}
}
int sequence_aleatoire_case_maxbordure(int **M, Grille *G, int dim, int nbcl, int aff){
	int cpt=0;
	//Erreur de base
	if( M == NULL || G == NULL || dim < 0 || nbcl < 1){
		printf("Probleme d'argument\n");
		exit(0);
	}
	// On initialise tout ce dont on aura besoin 
	int taille_init = 0;
	int taille_final = dim*dim;
	int couleur;
	int a = 0;
	int max = 0;
	int tab_couleur[nbcl] ; 
	while (taille_init != taille_final){ // Si l'utilisateur gagne
		
		//Etape 1 : trouver une couleur différente de la Zsg
		// On sait que les couleurs sont régis par un nombre compris entre 1 et nbcl (besoin du modulo)		

		couleur = M[0][0];
		if (! a) 
			while (couleur == M[0][0]) 
				couleur = rand() % nbcl ;
		
		if (a){
			for (int i = 0; i < nbcl ; i++) if(max < tab_couleur[i]) max = tab_couleur[i] ; 
		}
		

		//Etape 2 : On va définir la Zsg via la fonction trouve_zone_rec
		ListeCase L = malloc(sizeof(ListeCase));
		init_liste(&L);
		taille_init = 0;
		trouve_zone_case_maxbordure(M, dim, 0,0, &taille_init, nbcl, tab_couleur, &L); 
		if (taille_init >1) a = 1;
		
		//Etape 3 : Changement de couleur de la zsg et affichage si necessaire
		ListeCase temp = malloc(sizeof(ListeCase));
		temp = L;
		while(temp){
			M[(temp)->i][(temp)->j] = couleur;
			if(aff) 
				Grille_attribue_couleur_case(G,(temp)->i, (temp)->j, couleur);
			temp=(temp)->suiv;
		}
		if (aff) {
			Grille_redessine_Grille(G);
			Grille_attente_touche();
		}
		
		//Libération de la mémoire
		for(int i = 0; i < nbcl ; i++) tab_couleur[i] = 0;
		detruit_liste(&temp);
		detruit_liste(&L);
		//printf("%d != %d \n", taille_init, taille_final);
		
		//Incrémentation du compteur
		cpt++;

	}
	free(tab_couleur);
	return cpt;
}

