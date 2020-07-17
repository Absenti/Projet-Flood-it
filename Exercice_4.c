#include<stdio.h>
#include "Exercice_4.h"


void ajoute_liste_sommet(Sommet *s, Cellule_som ** L){
	Cellule_som * temp =(Cellule_som*) malloc(sizeof(Cellule_som));
	if(temp == NULL) printf("Erreur d'allocation de Cellule_som\n");
	temp->sommet = s;
	temp->suiv = *L;
	temp->prec = NULL;
	*L= temp;
}

void detruit_liste_sommet(Cellule_som **L){
	if (L == NULL) return;
	Cellule_som *temp =(Cellule_som*) malloc(sizeof(Cellule_som));
	if(temp == NULL) printf("Erreur d'allocation de Cellule_som\n");
	temp = *L;
	while((temp)){
		(*L) = (*L)->suiv;
		free(temp);
		(temp) = (*L);
	}
}

void ajoute_voisin(Sommet *s1, Sommet *s2){
	ajoute_liste_sommet(s1, &s2->sommet_adj);
	ajoute_liste_sommet(s2, &s1->sommet_adj);
}

int adjacent(Sommet *s1, Sommet *s2){
	if (s1 == s2) return 1;
	Cellule_som * temp1 = s1->sommet_adj;
	Cellule_som * temp2 = s2->sommet_adj;
	while (temp1 || temp2){
		if (temp1) {
			if (temp1->sommet == s2) return 1;
			temp1 = temp1 ->suiv;
		}
		if(temp2){
			if(temp2->sommet == s1) return 1;
			temp2 = temp2 ->suiv;
		}
	}
	return 0;
}
	
Graphe_zone * cree_graphe_zone(int**M, int dim, int nbcl){
	/* 
	Etape 1 : Initialiser la structure de graphe à 0 sommet, mettre mat à NULL pour chaque case
	Etape 2 : Pour chaque case de mat, crée un sommet vide case et utiliser trouve_zone pour determiner la zone => mettre à jour mat pour toutes les cases de la zone
	Etape 3 : Indiquer les sommets adjacents aux autres
	*/
	
	//Etape 1 (fait partiellement)

	
	int i=0, j=0;
	Graphe_zone * graphe = (Graphe_zone*) malloc(sizeof(Graphe_zone)); 
	graphe->nbsom = 0;
	graphe->nbcl = nbcl;
	graphe->nb_som_zsg = 0;
	graphe->dim = dim;
	graphe->som = NULL;
	
	graphe->B = (Cellule_som**)malloc(sizeof(Cellule_som*)*nbcl);
	graphe->tailleB = (int*) malloc(sizeof(int)*nbcl);
	for(i = 0; i<nbcl;i++) {
		graphe->B[i] = (Cellule_som*)malloc(sizeof(Cellule_som));; 
		graphe->B[i] = NULL;
		graphe->tailleB[i] = 0;
	}
	int ** matrice = (int**) malloc(sizeof(int*)*dim); // Matrice qui nous servira a compenser la modification de M
	graphe->mat =(Sommet ***) malloc(sizeof(Sommet**) * dim); // matrice de pointeur de sommet du graphe selon la case
	for(i = 0; i < dim; i++) {
		matrice[i] = (int*) malloc(sizeof(int)*dim);
		graphe->mat[i] = (Sommet**) malloc(sizeof(Sommet*)*dim);
		for(j=0; j<dim;j++){
			matrice[i][j] = -1;
			graphe->mat[i][j] = (Sommet*) malloc(sizeof(Sommet)*dim);
		}
	}
	
	for(i = 0; i<dim ; i++){
		for(int j = 0; j<dim; j++){
				if(M[i][j] != -1){
					//On crée donc les sommets
					Sommet *s =(Sommet *) malloc(sizeof(Sommet));
					s->num = graphe->nbsom++; //Attribue à num et ensuite incremente
					s->cl = M[i][j];
					s->cases = NULL;
					s->nbcase_som = 0;
					s->sommet_adj = NULL;
					s->distance = 0;
					s->pere = NULL;
					
					//Utilisation de trouve_zone (version itérative et recursive fonctionne
					trouve_zone_rec(M, dim , i, j, &s->nbcase_som, &s->cases) ; 
					// On ajoute le sommet crée dans le graphe 
					ajoute_liste_sommet(s, &graphe->som);
					//Si c'est la zsg, on l'ajoute en tant que telle
					if (i == 0 && j == 0){
						ajoute_liste_sommet(s, &graphe->Lzsg);
						graphe->nb_som_zsg++;
					}
						
					//Mise à jour de mat
					for(ListeCase temp = s->cases; temp !=NULL; temp = temp->suiv){
						//printf("i = %d et j = %d\n", temp->i, temp->j);
						graphe->mat[temp->i][temp->j] = s; 
						//printf("Error here\n");
						matrice[temp->i][temp->j] = s->cl;
					}
				}
		}
		
			
	}
	/*Etape 3 : Pour chaque sommet du graphe, je regarde chaque case, Pour les voisins de celle-ci, s'ils ont une couleur différente, alors je verifie que le sommet auquel elle appartient est adjacent à celui de référence, si non alors je l'ajoute en voisin */ 
	
	for(Cellule_som * tmp = graphe->som; (tmp) != NULL ; (tmp) = (tmp)->suiv){
		int couleur = (tmp)->sommet->cl;
		for(ListeCase L = (tmp)->sommet->cases ; L != NULL; L=L->suiv){

			// Autre possibilité if (M[L->i(+/- 1)][L->j(+/- 1)]->num > tmp->sommet->num)
				
			if(L->i != dim-1 && matrice[L->i+1][L->j] != couleur)
				if (! adjacent((tmp)->sommet, graphe->mat[L->i+1][L->j])){
					ajoute_voisin((tmp)->sommet, graphe->mat[L->i+1][L->j]);
					if(tmp->sommet->num == 0) {
						ajoute_liste_sommet(graphe->mat[L->i+1][L->j], &graphe->B[tmp->sommet->cl]);
						graphe->tailleB[tmp->sommet->cl]++;
					}
				}	

			if(L->i != 0 && matrice[L->i-1][L->j] != couleur)
				if (! adjacent((tmp)->sommet, graphe->mat[L->i-1][L->j])){
					ajoute_voisin((tmp)->sommet, graphe->mat[L->i-1][L->j]);
					if(tmp->sommet->num == 0) {
						ajoute_liste_sommet(graphe->mat[L->i-1][L->j], &graphe->B[tmp->sommet->cl]);
						graphe->tailleB[tmp->sommet->cl]++;
					}
				}	

					
			
			if(L->j != dim-1 && matrice[L->i][L->j+1] != couleur)
				if (! adjacent((tmp)->sommet, graphe->mat[L->i][L->j+1])) {
					ajoute_voisin((tmp)->sommet, graphe->mat[L->i][L->j+1]);
					if(tmp->sommet->num == 0) {
						ajoute_liste_sommet(graphe->mat[L->i-1][L->j], &graphe->B[tmp->sommet->cl]);
						graphe->tailleB[tmp->sommet->cl]++;
					}
				}	

				
			if(L->j != 0 && matrice[L->i][L->j-1] != couleur)
				if (! adjacent((tmp)->sommet, graphe->mat[L->i][L->j-1])) {
					ajoute_voisin((tmp)->sommet, graphe->mat[L->i][L->j-1]);
					if(tmp->sommet->num == 0) {
						ajoute_liste_sommet(graphe->mat[L->i+1][L->j], &graphe->B[tmp->sommet->cl]);
						graphe->tailleB[tmp->sommet->cl]++;
					}
				}	
		}
		
	}
	
	// On finit l'etape 1,  maintenant qu'on a tous les sommets
	graphe->marque = (int*)malloc(sizeof(int) * graphe->nbsom);
	for(i = 0; i< graphe->nbsom;i++) graphe->marque[i] = 2; 
	
	// Je rajoute le sommet de la case (0,0) dans la Lzsg et ses bordures dans 
	ajoute_liste_sommet(graphe->mat[0][0], &graphe->Lzsg);
	graphe->nb_som_zsg=1;
	graphe->marque[0]=0;
	// Je libere la matrice de booleen
	for(i=0;i<dim;i++)
		free(matrice[i]);
	return graphe;	
			
			
}
	

void afficher_sommet(Sommet * s){
	printf("Sommet n°%d, Couleur :%d, Nb de cases : %d\n", s->num, s->cl,s->nbcase_som);
	printf("Sommets adjacents: ");
	for(Cellule_som*temp = s->sommet_adj ; temp !=NULL; temp=temp->suiv)
		printf("n°%d ",temp->sommet->num);
	printf("\nListe des cases : ");
	for(ListeCase temp2 = s->cases ; temp2 != NULL; temp2 = temp2 -> suiv)
		printf("(%d, %d)", temp2->i, temp2->j);
	printf("\n*************\n");
}

void affiche_graphe(Graphe_zone * graphe){
	Cellule_som * zsg = NULL;
	Cellule_som * bordure =  NULL;
	Cellule_som * non_visite = NULL;
	printf(" ** Graphe Zone **\n");
	printf("Nombre de sommets-zone : %d\n",graphe->nbsom);
	
	for(Cellule_som * tmp = graphe->som; tmp != NULL ; tmp = tmp->suiv){
		switch(graphe->marque[tmp->sommet->num]){
			case 0 : 
				ajoute_liste_sommet(tmp->sommet, &zsg);
				break;
			case 1 : 
				ajoute_liste_sommet(tmp->sommet, &bordure);
				break;
			case 2 : 
				ajoute_liste_sommet(tmp->sommet, &non_visite);
				break;
		}
	}
	printf("===========================\nZsg :\n");
	while(zsg !=NULL){
		afficher_sommet(zsg->sommet);
		zsg = zsg->suiv;
	}
	printf("===========================\nBordure :\n");
	for(bordure; bordure !=NULL; bordure = bordure->suiv) afficher_sommet(bordure->sommet);
	printf("===========================\nNon Visité :\n");
	for(non_visite; non_visite !=NULL; non_visite = non_visite->suiv) afficher_sommet(non_visite->sommet);
	
	detruit_liste_sommet(&zsg);
	detruit_liste_sommet(&bordure);
	detruit_liste_sommet(&non_visite);
}

void liberer_graphe_zone(Graphe_zone * graphe){

/*
Etape 1 : Pour chaque sommet du graphe, liberer le contenu sur lequel il peut pointer (liste de case, sommet adjacent) puis le sommets en lui-meme
Etape 2 : Liberer le tableau tailleB et marque du graphe
Etape 3 : Liberer les tableau de pointeur vers des sommets (mat et B)
Etape 4 ; Liberer la liste de sommet de la zsg
Etape 5 : Liberer le graphe maintenant que les données vers lequel il pointe sont vide
*/
	
	// Etape 1 //
	Cellule_som * temp = graphe->som;
	while(graphe->som){ 
		detruit_liste(&temp->sommet->cases);
		detruit_liste_sommet(&temp->sommet->sommet_adj); 
		temp = graphe->som->suiv;
		free(graphe->som->sommet);
		graphe->som = temp;
		
	}
	// Etape 2 //
	free(graphe->marque);
	free(graphe->tailleB);
	// Etape 3 //
	for (int i = 0; i <graphe->nbcl ; i++) 
		free(graphe->B[i]);
	free(graphe->B);
	for(int i = 0; i < graphe->dim ; i ++)
		free(graphe->mat[i]);
	free(graphe->mat);
	
	// Etape 4 //
	detruit_liste_sommet(&graphe->Lzsg);
	// Etape 5 //
	free(graphe);

}

void mise_en_place(int ** M, int dim, int nbcl){
	
	Graphe_zone * graphe = cree_graphe_zone(M,dim,nbcl);
	
	affiche_graphe(graphe);
	
	liberer_graphe_zone(graphe);

}















