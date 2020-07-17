#include<stdio.h>
#include "Exercice_1.h"

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	/*Le but est de d'ajouter les cases autour de la case de référence ayant la meme couleur, dans la liste L
	Il faut donc faire attention aux cases sur le périmètre de la grille, et donc faire des cas selon si l'on est dans la premiere/derniere ligne/colonne de la grille */


	//Erreur de base
	if (M == NULL || nbcase < 0 || i < -1 || j < -1 ) {
		printf("Erreur d'argument\n");
		exit(0);
	}
	if( M[i][j] == -1) return;
	
	// On prend deja en compte la case de référence
	int couleur = M[i][j];
	ajoute_en_tete(L,i,j); // A chaque appel récursif d'une case avec la meme couleur, on l'ajoute à la liste
	*taille = *taille + 1;
	M[i][j] = -1;
	// On va vérifie chaque case autour de la case de référence (haut, bas, gauche et droite)
	//Pour la case du Haut
	if (j !=0 && M[i][j-1] == couleur){ // on verifie qu'il y a une ligne au dessus (qu'on ne soit pas à la 1ere ligne)
		trouve_zone_rec(M, nbcase, i,j-1, taille,L); // sinon appel recursif
	}
	
	if (j !=nbcase -1 && M[i][j+1] == couleur){ // on verifie qu'il y a une ligne au dessus (qu'on ne soit pas à la 1ere ligne)
			
		trouve_zone_rec(M, nbcase, i,j+1, taille,L); // sinon appel recursif
	}
	
	
	if (i !=0 && M[i-1][j] == couleur){ // on verifie qu'il y a une ligne au dessus (qu'on ne soit pas à la 1ere ligne)
			
		trouve_zone_rec(M, nbcase, i-1,j, taille,L); // sinon appel recursif
	}
	


	if (i !=nbcase -1 && M[i+1][j] == couleur){ // on verifie qu'il y a une ligne au dessus (qu'on ne soit pas à la 1ere ligne)
			
		trouve_zone_rec(M, nbcase, i+1,j, taille,L); // sinon appel recursif
	}
	
	
 
			
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
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
		trouve_zone_rec(M, dim, 0,0, &taille_init, &L); 
		
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


