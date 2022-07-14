#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "entree_sortie.h"

void ecriture_choix(char* fichier, int** choix, int n){
	FILE* fic = fopen(fichier, "a");
	if(fic){
		for(int i = 0 ; i < n ; i++){
			fprintf(fic, "%i\t", choix[1][i]);
		}
		fprintf(fic, "\n");
		fclose(fic);
	}
}

void ecriture_valeur(char* fichier, int** tab, int n){
	FILE* fic = fopen(fichier, "a");
	if(fic){
		for(int i = 0 ; i < n ; i++){
			fprintf(fic, "%i\t", tab[2][i]);
		}
		fprintf(fic, "\n");
		fclose(fic);
	}
}

void ecriture_tab_opv(char* fichier, int** tab, int n){
	FILE* fic = fopen(fichier, "w");
	if(fic){
		for(int i = 0 ; i < 3; i++){
			for(int j = 0 ; j < n ; j++){
				fprintf(fic, "%i\t", tab[i][j]);
			}
			fprintf(fic, "\n");
		}
		fclose(fic);
	}
}

int*** lecture_choix(char* fichier, int* taille){
	FILE* fic = fopen(fichier, "r");
	char ligne[1000000];
	int votants = 0;
	if(fic){
		while(fgets(ligne, 1000000, fic)){//On compte le nombre de votants
			votants++;
		}
		fclose(fic);
	}
	if(votants){
		printf("Votants = %i\n", votants);
		*taille = votants;
		int*** res = (int***)malloc(votants * sizeof(int**));
		if(res){
			for(int i = 0 ; i < votants ; i++){//On initialise les colonnes du tableau à NULL
				res[i] = NULL;
			}
			char temp[1000000];
			int i, j;
			fic = fopen(fichier, "r");
			if(fic){
				votants = 0;
				while(fgets(ligne, 1000000, fic)){//Pour chaque votant, ...
					i = 0;
					j = 0;
					while(ligne[i] != '\0'){//... on compte le nombre de projets total, ...
						if((ligne[i] == '0') || (ligne[i] == '1')){
							j++;
						}
						i++;
					}
					i = 0;
					int** tab_temp = (int**)malloc(2 * sizeof(int*)); //... on creer son tableau de choix correspondant
					if(tab_temp){
						for(int k = 0 ; k < 2 ; k++){
							tab_temp[k] = (int*)malloc(j * sizeof(int));
							if(tab_temp[k] == NULL){
								for(int l = 0 ; l < k ; l++){
									free(tab_temp[l]);
								}
								free(tab_temp);
								tab_temp = NULL;
								*taille = 0;
							}
						}
					}
					if(tab_temp){//si le tableau est alloué, on l'initialise...
						for(int k = 0 ; k < j ; k++){
							tab_temp[0][k] = k + 1;
						}
						j = 0;
						while(ligne[i] != '\0'){//... avec les valeurs contenues dans le fichier
							if((ligne[i] == '0') || (ligne[i] == '1')){
								temp[0] = ligne[i];
								temp[1] = '\0';
								tab_temp[1][j] = atoi(temp);
								j++;
							}
							i++;
						}
					}
					res[votants] = tab_temp;
					votants++;
				}
				fclose(fic);
			}
		}
		return res;//on retourne le tableau de tableau de choix
	}
	return NULL;
}

int*** lecture_valeur(char* fichier, int* taille, int** tab, int n){
	FILE* fic = fopen(fichier, "r");
	char ligne[1000000];
	int votants = 0;
	if(fic){
		while(fgets(ligne, 1000000, fic)){//On compte le nombre de votants
			votants++;
		}
		fclose(fic);
	}
	if(votants){
		printf("Votants = %i\n", votants);
		*taille = votants;
		int*** res = (int***)malloc(votants * sizeof(int**));
		if(res){
			for(int i = 0 ; i < votants ; i++){//On initialise les colonnes du tableau à NULL
				res[i] = NULL;
			}
			char temp[1000000];
			int i, j;
			fic = fopen(fichier, "r");
			if(fic){
				votants = 0;
				while(fgets(ligne, 1000000, fic)){//Pour chaque votant, ...
					i = 0;
					int **tab_temp = clone_tab(tab, 3, n), k; //... on crée son tableau de choix correspondant
					if(tab_temp){//si le tableau est alloué, on l'initialise...
						j = 0;
						k = 0;
						while(ligne[i] != '\0'){//... avec les valeurs contenues dans le fichier
							if((ligne[i] >= '0') && (ligne[i] <= '9')){
								temp[j] = ligne[i];
								j++;
							}
							if(ligne[i] == '\t'){
								temp[j] = '\0';
								tab_temp[2][k] = atoi(temp);
								temp[0] = '\0';
								j = 0;
								k++;
							}
							i++;
						}
					}
					res[votants] = tab_temp;
					votants++;
				}
				fclose(fic);
			}
		}
		return res;//on retourne le tableau de tableau de choix
	}
	return NULL;
}

int** lecture_tab_opv(char* fichier, int* taille){
	FILE* fic = fopen(fichier, "r");
	char ligne[1000000], temp[1000000];
	int projets = 0, i = 0, j = 0, k, l, **res = (int**)malloc(3 * sizeof(int**));
	if(res){
		fic = fopen(fichier, "r");
		if(fic){
			if(fgets(ligne, 1000000, fic)){
				while(ligne[i] != '\n'){
					if(ligne[i] == '\t'){
						projets++;
					}
					i++;
				}
				*taille = projets;
				for(i = 0 ; i < 3 ; i++){//On crée le tableau objet-poids-valeur
					res[i] = (int*)malloc(projets * sizeof(int));
					if(res[i] == NULL){
						for(j = 0 ; j < i ; j++){
							free(res[j]);
						}
						free(res);
						res = NULL;
						return NULL;
					}
				}
				for(j = 0 ; j < projets ; j++){
					res[0][j] = j + 1;
				}
				i = 1;
				while(fgets(ligne, 1000000, fic)){
					j = 0;
					k = 0;
					while(ligne[k] != '\0'){
						if((ligne[k] >= '0') && (ligne[k] <= '9')){
							temp[l] = ligne[k];
							l++;
						}
						if(ligne[k] == '\t'){
							temp[l] = '\0';
							res[i][j] = atoi(temp);
							j++;
							temp[0] = '\0';
							l = 0;
						}
						k++;
					}
					i++;
				}
			}
			fclose(fic);
		}
		else{
			free(res);
			res = NULL;
		}
		return res;//on retourne le tableau
	}
	return NULL;
}

int** valeur_to_choix_a(int** tab, int n, float B){
	float** mat = remplir_matrice(tab, n);
	if(mat){
		int** res = objets_selectionnes(tab, mat, B, n, nb_colonne_matrice(tab, n));
		liberer_matrice_float(mat, n);
		mat = NULL;
		return res;
	}
	return NULL;
}

int** valeur_to_choix_b(int** tab, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		tri_fusion_int(tab_temp, 3, 0, n - 1);
		int** res = (int**)malloc(2*sizeof(int*));
		if(res){
			for(int i = 0 ; i < 2 ; i++){
				res[i] = (int*)malloc(n*sizeof(int));
				if(res[i] == NULL){
					for(int j = 0 ; j < i ; j++){
						free(res[j]);
						res[j] = NULL;
					}
					free(res);
					res = NULL;
					return NULL;
				}
			}
			for(int i = 0 ; i < n ; i++){
				res[0][i] = i + 1;
				res[1][i] = 0;
			}
			int temp = 0;
			for(int i = 0 ; i < n ; i++){
				if((temp + tab_temp[1][i]) <= B){
					temp += tab_temp[1][i];
					res[1][tab_temp[0][i] - 1] = 1;
				}
			}
		}
		liberer_matrice_int(tab_temp, 3);
		tab_temp = NULL;
		return res;
	}
	return NULL;
}

int*** valeur_to_choix(int*** lecture, int taille, float B, int n){
	int*** res = (int***)malloc(sizeof(int**));
	if(res){
		for(int i = 0 ; i < taille ; i++){
			res[i] = valeur_to_choix_a(lecture[i], n, B);
			//res[i] = valeur_to_choix_b(lecture[i], n, B);
		}
	}
	return res;
}