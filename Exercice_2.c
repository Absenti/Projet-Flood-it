#include<stdio.h>
#include "Exercice_2.h"

void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	/* Version avec empilé (ajoute_en_tete) et dépiler (enleve_en_tete) */
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
		
			if (i2 != nbcase-1 && M[i2+1][j2] == couleur) ajoute_en_tete(&pile, i2+1, j2); // on empile la case du dessus
			if (i2 != 0 && M[i2-1][j2] == couleur) ajoute_en_tete(&pile, i2-1, j2); // on empile la case du dessous
			if (j2 != nbcase-1 && M[i2][j2+1] == couleur) ajoute_en_tete(&pile, i2, j2+1); // on empile la case à droite
			if (j2 != 0 && M[i2][j2-1] == couleur) ajoute_en_tete(&pile, i2, j2-1); //On empile la case à gauche
		}
	}
}

/* Autre solution : tout en empiler dans pile et avancer dedans au fur et mesure, mais l'exercice demandant de dépiler, il faut donc enlever des cases tout en en ajoutant 	*/




// Ici il s'agit de réecrire la fonction sequence_aleatoire_rec, en remplacant juste trouve_zone_rec par trouve_zone_imp

int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
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
	while (taille_init != taille_final){ // Si l'utilisateur gagne
		
		//Etape 1 : trouver une couleur différente de la Zsg
		// On sait que les couleurs sont régis par un nombre compris entre 1 et nbcl (besoin du modulo)		

		couleur = M[0][0];
		while (couleur == M[0][0]) 
			couleur = rand() % nbcl ;

		//Etape 2 : On va définir la Zsg via la fonction trouve_zone_rec
		ListeCase L = malloc(sizeof(ListeCase));
		init_liste(&L);
		taille_init = 0;
		trouve_zone_imp(M, dim, 0,0, &taille_init, &L); 
		//Note : On irait plus vite si on pouvait connaitre la colonne et ligne d'une des cases sortante, au lieu de recommencer à la case 0,0 à la chaque passage dans la boucle
		
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
		detruit_liste(&temp);
		detruit_liste(&L);
		//printf("%d != %d \n", taille_init, taille_final);
		
		//Incrémentation du compteur
		cpt++;

	}
	
	return cpt;
}
