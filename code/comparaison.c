#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "entree_sortie.h"
#include "comparaison.h"

float poids_moyen(int** choix, int** tab, int n){
	float poids = 0;
	int compteur = 0;
	for(int i = 0 ; i < n ; i++){
		if(choix[1][i] == 1){
			compteur++;
			poids += tab[1][i];
		}
	}
	return poids/compteur;
}

float valeur_moyenne(int** choix, int** tab, int n){
	float valeur = 0;
	int compteur = 0;
	for(int i = 0 ; i < n ; i++){
		if(choix[1][i] == 1){
			compteur++;
			valeur += tab[2][i];
		}
	}
	return valeur/compteur;
}

int nombre_objets(int** choix, int n){
	int compteur = 0;
	for(int i = 0 ; i < n ; i++){
		if(choix[1][i] == 1){
			compteur++;
		}
	}
	return compteur;
}

int cout_total(int** choix, int** tab, int n){
	int cout = 0;
	for(int i = 0 ; i < n ; i++){
		if(choix[1][i] == 1){
			cout += tab[1][i];
		}
	}
	return cout;
}

float nombre_objets_par_personne_moyenne(int*** tab_choix, int v, int** choix, int n){
	int objet = 0;
	for(int i = 0 ; i < v ; i++){
		for(int j = 0 ; j < n ; j++){
			if((tab_choix[i][1][j] == 1) && (choix[1][j] == 1)){
				objet++;
			}
		}
	}
	return (float)(objet)/v;
}

int satisfaction_1(int*** tab_choix, int v, int** choix, int n, int* nul){
	int res = 0, cpt = 0;
	for(int i = 0 ; i < v ; i++){
		if(nombre_objets(tab_choix[i], n)){
			int j = 0;
			while((j < n) && ((choix[1][j] != 1) || (tab_choix[i][1][j] != choix[1][j]))){
				j++;
			}
			if(j < n){
				res++;
			}
		}
		else{
			cpt++;
		}
	}
	*nul = cpt;
	return res;
}

int* satisfaction_2(int*** tab_choix, int v, int** choix, int n, int nul){
	int* res = (int*)malloc(12*sizeof(int));
	if(res){
		for(int i = 0 ; i < 12 ; i++){
			res[i] = 0;
			//printf("res [%i] = %i\n", i, res[i]);
		}
	}
	else{
		return NULL;
	}
	for(int i = 0 ; i < v ; i++){
		int cpt = 0, nb, k = 0;
		float pourcent;
		nb = nombre_objets(tab_choix[i], n);
		if(nb){
			for(int j = 0 ; j < n ; j++){
				if((tab_choix[i][1][j] == 1) && (choix[1][j] == 1)){
					cpt++;
				}
			}
			pourcent = (float)cpt / nb * 100;			
			while(pourcent > 10*k){
				k++;
			}
			if(cpt == nb){
				res[11]++;
	//			printf("res [11] = %i\n", res[11]);
			}
			else{
				if(cpt == 0){
					res[0]++;
	//				printf("res [0] = %i\n", res[0]);
				}
				else{
					res[k + 1]++;
	//				printf("res [%i] = %i\n", k + 1, res[k + 1]);
				}
			}
		}	
	}
	return res;
}