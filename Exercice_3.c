#include<stdio.h>
#include "Exercice_3.h"


void init_Zsg(S_Zsg ** Z, int dim, int nbcl){
	// Initialise la structure S_zsg selon la dimension et le nombre de couleur
	/* J'ai décidé de passer par un double pointeur au lieu d'un simple comme indiqué, car sinon je n'arrive pas à acceder à App après avoir initialisé une nouvelle structure avec une erreur de segmentation */
	int i =0, j=0;
	
	S_Zsg *temp = (S_Zsg *)malloc(sizeof(S_Zsg));

	temp->dim = dim;
	temp->nbcl = nbcl;
	temp->Lzsg = NULL; //Car il n'y a rien dedans au départ

	// une liste pour chaque couleur
	temp->B = (ListeCase *)malloc(sizeof(ListeCase) * nbcl);
	for(i=0; i<nbcl;i++) temp->B[i] = NULL;

	temp->App = (int **)malloc(sizeof(int *) * dim);
	for (i = 0; i < dim; i++){
		temp->App[i] = (int *)malloc(sizeof(int) * dim);
		for(j = 0; j< dim; j++) 
			temp->App[i][j] = -2;
	}

	*Z = temp;
	
}


int ajoute_Zsg(S_Zsg * Z, int i , int j){
	// Ajoute une case dans la liste Lzsg (contient toutes les cases de la zsg)
	if (ajoute_en_tete(&Z->Lzsg, i, j) == 0) return 0;
	// Ne pas oublier de mettre à jour la matrice App
	Z->App[i][j] = -1; 
	return (Z->Lzsg->i == i && Z->Lzsg->j == j);
}

int ajoute_Bordure(S_Zsg * Z, int i, int j, int couleur){
	//Ajoute une case dans la liste de case *B de Z 
	if (ajoute_en_tete(&Z->B[couleur], i, j) == 0) return 0;
	// Ne pas oublier de mettre à jour la matrice App
	Z->App[i][j] = couleur; 
	return (Z->B[couleur]->i == i && Z->B[couleur]->j == j);
}

int appartient_Zsg(S_Zsg * Z, int i, int j){
	// Renvoi 1 si (i,j) est une case de Lzsg de Z, sinon 0
	return (Z->App[i][j] == -1);
}

int appartient_Bordure(S_Zsg*Z, int i, int j, int couleur){
	// Renvoie 1 si une case est de la couleur donnée, sinon 0
	return (Z->App[i][j] == couleur);
}

int agrandi_Zsg(int **M, S_Zsg * Z, int cl, int k, int l){
	/* k = i, l = j
	Retourne le nombre de case ajouté à Lzsg 
	Parcourt de la zone (k,l) via algo itérative 
	S'inspirer de la question 2.1
	*/
	//Cas 1 : si la case est de couleur cl => ajout à Lzsg s elle n'y est pas deja
	//Cas 2 : d'une case avec une couleur hors *B => on l'ajoute à *B 

	
	
	ListeCase temp; //On alloue une liste temporaire 
	init_liste(&temp);
	ajoute_en_tete(&temp, k, l);
	int compteur = 0 ; // Initialisation du compteur
	while (test_liste_vide(&temp) == 0) { // tant que la liste est non vide
		int k2, j2;
		enleve_en_tete(&temp, &k2, &j2); // dépile et affecte les valeurs de k et l et la tete de liste à k2 et j2 
		if (M[k2][j2] == cl){ // Cas 1
			if (!appartient_Zsg(Z, k2, j2)){
				ajoute_Zsg(Z, k2, j2); // Si ca n'appartient à Lzsg, on l'ajoute
				compteur++;
				//On va maintenant empiler les cases voisines en verifiant qu'elles ne sont pas deja dans Lzsg
				
				if (k2 != Z->dim-1 && !(appartient_Zsg(Z, k2+1, j2))) 
					ajoute_en_tete(&temp, k2+1, j2); 
				if (k2 > 0 && !(appartient_Zsg(Z, k2-1, j2)))
					ajoute_en_tete(&temp, k2-1, j2); 
				if (j2 != Z->dim-1 && !(appartient_Zsg(Z, k2, j2+1)))
					ajoute_en_tete(&temp, k2, j2+1);
				if (j2 > 0 && !(appartient_Zsg(Z, k2, j2-1)))
					ajoute_en_tete(&temp, k2, j2-1); 
			}
		}
		else{ // Cas 2
			if (! appartient_Bordure(Z, k2, j2, M[k2][j2])) ajoute_Bordure(Z, k2, j2, M[k2][j2]);
		}
	}
	return compteur;
}

int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff) {
	/* 
	Etape 1 : Initialiser les listes à vide
	Etape 2 : Utiliser la fonction agrandi_Zsg à partir de M[0][0] 
	Etape 3 : Choix de couleur aleatoire => colorier toutes les cases de zsg (si aff = 1, mettre à jour la grille
	Etape 4 : Pour chaque case (i,j) de *B utiliser agrandi_zsg et detruire *B 
	Etape 5 (Optionnel) : S'occuper de l'affichage 
	*/
	
	int compteur = 0; // Ce n'est pas indiqué mais je suppose que comme les autre fonction "sequence_aleatoire", il faut renseigner le nombre de changement de couleur
	
	//Etape 1
	S_Zsg * Z = NULL;
	init_Zsg(&Z, dim, nbcl);

	// On doit connaitre le nombre de case contenu dans la zsg afin de savoir à quel moment l'user gagne
	int taille_final = dim*dim;
	
	//Etape 2
	int taille_init = agrandi_Zsg(M, Z, M[0][0], 0, 0); 
	while (taille_final != taille_init){
		//Etape 3 
		int couleur = M[0][0];
		while(couleur == M[0][0]) couleur = rand() % nbcl ;
		compteur++;
		for(ListeCase temp = Z->Lzsg ; temp != NULL; temp = temp->suiv) {
			M[temp->i][temp->j] = couleur;
			if(aff) Grille_attribue_couleur_case(G,temp->i,temp->j,M[temp->i][temp->j]);
		}

		// Etape 4 
		for(ListeCase temp2 = Z->B[couleur] ; temp2 != NULL; temp2 = temp2->suiv)
			 taille_init = taille_init + agrandi_Zsg(M,Z,couleur,temp2->i,temp2->j);
		detruit_liste(&Z->B[couleur]);
	
		//Etape 5 
		if(aff){
			Grille_redessine_Grille(G);
			Grille_attente_touche();
		}
	}
	return compteur;
}			
		
		
		 
		
		
	
	
