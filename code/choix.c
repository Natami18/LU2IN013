#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "choix.h"

int** choix_votant_1_a_random(int n){
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
			if(rand()%101 <= 50){
				res[1][i] = 1;
			}
			else{
				res[1][i] = 0;
			}
		}
	}
	return res;
}

int** choix_votant_1_b_random(int** tab, int n){
	float temp;
	int compteur = 0;
	for(int i = 0 ; i < n ; i++){
		compteur += tab[1][i];
	}
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
			temp = rand()%101;
			res[0][i] = i + 1;

			//printf("temp1 = %.2f, proba = %.2f\n", (float)temp / 100, (float)tab[1][i] / compteur);

			if(((float)temp / 100) <= ((float)tab[1][i] / compteur)){
				res[1][i] = 1;
			}
			else{
				res[1][i] = 0;
			}
		}
	}
	return res;
}

int** choix_votant_1_manuel(int n){
	int nb_choix, cpt = 0, temp;
	printf("Combien de projet(s) voulez-vous choisir ?\n");
	scanf("%i", &nb_choix);
	while(nb_choix > n){
		printf("Il n'y a pas autant de projets proposés, veuillez selectionner un nombre entre 0 et %i\n", n);
		scanf("%i", &nb_choix);
	}
	if(nb_choix < 0){
		printf("Nous considérons que vous ne voulez pas choisir de projet. Merci et au revoir !\n");
		return NULL;
	}
	if(nb_choix == 0){
		printf("Nous considérons votre choix de ne pas choisir de projet. Merci et au revoir !\n");
		return NULL;
	}
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
		while(cpt < nb_choix){
			printf("Choississez un projet, il vous reste %i choix.\n", nb_choix - cpt);
			scanf("%i", &temp);
			while((temp < 1) || (temp > n) || (res[1][temp - 1] == 1)){
				if(res[1][temp - 1] == 1){
					printf("Vous avez déjà choisi ce projet. Choississez un projet, il vous reste %i choix.\n", nb_choix - cpt);
				}
				else{
					printf("Ce projet n'existe pas. Choississez un projet, il vous reste %i choix.\n", nb_choix - cpt);
				}
				scanf("%i", &temp);
			}
			res[1][temp - 1] = 1;
			cpt++;
		}
	}
	return res;
}

int** choix_votant_2_a_random(int** tab, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			tab_temp[2][i] = rand()%11;
		}
		float** mat = remplir_matrice(tab_temp, n);
		if(mat){
			int** res = objets_selectionnes(tab_temp, mat, B, n, nb_colonne_matrice(tab_temp, n));
			liberer_matrice_int(tab_temp, 3);
			tab_temp = NULL;
			liberer_matrice_float(mat, n);
			mat = NULL;
			return res;
		}
		liberer_matrice_int(tab_temp, 3);
		tab_temp = NULL;
	}
	return NULL;
}

int** choix_votant_2_a_manuel(int** tab, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			printf("Veuillez attribuer une valeur entre 0 et 10 au projet n°%i.\n", tab_temp[0][i]);
			scanf("%i", &(tab_temp[2][i]));
			if(tab_temp[2][i] < 0){
				printf("Nous considérons que la valeur que vous attribuez au projet n°%i est égale à 0.\n", tab_temp[0][i]);
				tab_temp[2][i] = 0;
			}
			if(tab_temp[2][i] > 10){
				printf("Nous considérons que la valeur que vous attribuez au projet n°%i est égale à 10.\n", tab_temp[0][i]);
				tab_temp[2][i] = 10;
			}
		}
		float** mat = remplir_matrice(tab_temp, n);
		if(mat){
			int** res = objets_selectionnes(tab_temp, mat, B, n, nb_colonne_matrice(tab_temp, n));
			liberer_matrice_int(tab_temp, 3);
			tab_temp = NULL;
			liberer_matrice_float(mat, n);
			mat = NULL;
			return res;
		}
		liberer_matrice_int(tab_temp, 3);
		tab_temp = NULL;
	}
	return NULL;
}

int** choix_votant_2_b_random(int** tab, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			tab_temp[2][i] = rand()%11;
		}
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
			int temp = 0;
			for(int i = 0 ; i < n ; i++){
				if((temp + tab_temp[1][i]) <= B){
					temp += tab_temp[1][i];
					res[1][tab_temp[0][i] - 1] = 1;
				}
				else{
					res[1][tab_temp[0][i] - 1] = 0;
				}
			}
		}
		liberer_matrice_int(tab_temp, 3);
		tab_temp = NULL;
		return res;
	}
	return NULL;
}

int** choix_votant_2_b_manuel(int** tab, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			printf("Veuillez attribuer une valeur entre 0 et 10 au projet n°%i.\n", tab_temp[0][i]);
			scanf("%i", &(tab_temp[2][i]));
			if(tab_temp[2][i] < 0){
				printf("Nous considérons que la valeur que vous attribuez au projet n°%i est égale à 0.\n", tab_temp[0][i]);
				tab_temp[2][i] = 0;
			}
			if(tab_temp[2][i] > 10){
				printf("Nous considérons que la valeur que vous attribuez au projet n°%i est égale à 10.\n", tab_temp[0][i]);
				tab_temp[2][i] = 10;
			}
		}
		tri_fusion_int(tab_temp, 3, 0, n - 1);
		printf("Voici le tableau après l'attribution des valeurs : \n");
		afficher_matrice_int(tab_temp, 3, n);
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
			int temp = 0;
			for(int i = 0 ; i < n ; i++){
				res[0][i] = i + 1;
				res[1][i] = 0;
				if(temp + tab_temp[1][i] <= B){
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

int** graphe_choix(int*** tab_choix, int v, int** tab, int n){
	int** res = (int**)malloc(n*sizeof(int*));
	if(res){
		for(int i = 0 ; i < n ; i++){
			res[i] = (int*)malloc(n*sizeof(int));
			if(res[i] == NULL){
				for(int j = 0 ; j < i ; j++){
					free(res[j]);
				}
				free(res);
				return NULL;
			}
		}
		for(int i = 0 ; i < n ; i++){
			for(int j = 0 ; j < n ; j++){
				res[i][j] = 0;
			}
		}
		for(int i = 0 ; i < v ; i++){
			for(int j = 0 ; j < n ; j++){
				if(tab_choix[i][1][j] == 1){
					res[j][j]++;
					for(int k = j + 1 ; k < n ; k++){
						if(tab_choix[i][1][k] == 1){
							res[k][j]++;
							res[j][k]++;
						}
					}
				}
			}
		}
	}
	return res;
}

int** choix_final_1(int*** tab_choix, int v, int** tab, int n, float B){
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
	}
	else{
		return NULL;
	}
	int** tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			tab_temp[2][i] = 0;
		}
		for(int i = 0 ; i < v ; i++){
			for(int j = 0 ; j < n ; j++){
				if(tab_choix[i][1][j] == 1){
					tab_temp[2][j]++;
				}
			}
		}
		tri_fusion_int(tab_temp, 3, 0, n - 1);
		float cpt = 0;
		for(int i = 0 ; i < n ; i++){
			if(cpt + tab_temp[1][i] <= B){
				cpt += tab_temp[1][i];
				res[1][tab_temp[0][i] - 1] = 1;
			}
		}
		liberer_matrice_int(tab_temp, 3);
		return res;
	}
	else{
		liberer_matrice_int(res, 2);
	}
	return NULL;
}

int** choix_final_2(int*** tab_choix, int v, int** tab, int n, float B){
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
	}
	else{
		return NULL;
	}
	float** tab_temp = (float**)malloc(3*sizeof(float*));
    if(tab_temp){
        for(int i = 0 ; i < 3 ; i++){
            tab_temp[i] = (float*)malloc(n*sizeof(float));
            if(tab_temp[i] == NULL){
                for(int j = 0 ; j < i ; j++){
                    free(tab_temp[j]);
                    tab_temp[j] = NULL;
                }
                free(tab_temp);
                tab_temp = NULL;
                return NULL;
            }
        }
        for(int i = 0 ; i < 3 ; i++){
        	for(int j = 0 ; j < n ; j++){
        		if(i == 2){
        			tab_temp[i][j] = 0;
        		}
        		else{
        			tab_temp[i][j] = (float)tab[i][j];
        		}
        	}
        }
        for(int i = 0 ; i < v ; i++){
			for(int j = 0 ; j < n ; j++){
				if(tab_choix[i][1][j] == 1){
					tab_temp[2][j]++;
				}
			}
		}
		for(int i = 0 ; i < n ; i++){
			tab_temp[2][i] /= tab_temp[1][i];
		}
		tri_fusion_float(tab_temp, 3, 0, n - 1);
		float cpt = 0;
		for(int i = 0 ; i < n ; i++){
			if(cpt + tab_temp[1][i] <= B){
				cpt += tab_temp[1][i];
				res[1][(int)tab_temp[0][i] - 1] = 1;
			}
		}
		liberer_matrice_float(tab_temp, 3);
		return res;
    }
	else{
		liberer_matrice_int(res, 2);
	}
	return NULL;
}

int** choix_final_3(int*** tab_choix, int v, int** tab, int n, float B){
	int **res = NULL, **tab_temp = clone_tab(tab, 3, n);
	if(tab_temp){
		for(int i = 0 ; i < n ; i++){
			tab_temp[2][i] = 0;
		}
		for(int i = 0 ; i < v ; i++){
			for(int j = 0 ; j < n ; j++){
				if(tab_choix[i][1][j] == 1){
					tab_temp[2][j]++;
				}
			}
		}
		float** mat = remplir_matrice(tab_temp, n);
		if(mat){
			res = objets_selectionnes(tab_temp, mat, B, n, nb_colonne_matrice(tab_temp, n));
			liberer_matrice_float(mat, n);
		}
		liberer_matrice_int(tab_temp, 3);
		return res;
	}
	return NULL;
}

int** choix_final_4(int** tab, int** graphe, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	int** res = (int**)malloc(2*sizeof(int*));
	if((res) && (tab_temp)){
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
	}
	else{
		if(res){
			liberer_matrice_int(res, 2);
		}
		if(tab_temp){
			liberer_matrice_int(tab_temp, 3);
		}
		return NULL;
	}
	int ligne = 0, i, cpt = 0, temp = 0;
	float somme = 0;
	for(i = 0 ; i < n ; i++){
		if((tab[1][i] <= B) && (graphe[i][i] > temp)){
			ligne = i;
			somme = tab[1][i];
			temp = graphe[i][i];
		}
	}
	cpt++;
	res[1][ligne] = 1;
	i = 0;
	while((somme <= B) && (i < n) && (cpt < n)){
		for(int j = 0 ; j < n ; j++){
			tab_temp[2][j] = graphe[ligne][j];
		}
		tri_fusion_int(tab_temp, 3, 0, n - 1);
		i = 1;
		while((i < n) && ((somme + tab_temp[1][i] >	B) || (res[1][tab_temp[0][i] - 1] == 1))){
			i++;
		}
		if(i < n){
			res[1][tab_temp[0][i] - 1] = 1;
			somme += tab_temp[1][i];
			ligne = tab_temp[0][i] - 1;
		}
		cpt++;
	}
	if(somme > B){
		res[1][tab_temp[0][i] - 1] = 0;
	}
	liberer_matrice_int(tab_temp, 3);
	return res;
}

int** choix_final_5(int** tab, int** graphe, int n, float B){
	int** tab_temp = clone_tab(tab, 3, n);
	int** res = (int**)malloc(2*sizeof(int*));
	if((res) && (tab_temp)){
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
	}
	else{
		if(res){
			liberer_matrice_int(res, 2);
		}
		if(tab_temp){
			liberer_matrice_int(tab_temp, 3);
		}
		return NULL;
	}
	int ligne = 0, i, cpt = 0, temp = 0;
	float somme = 0;
	for(i = 0 ; i < n ; i++){
		if((tab[1][i] <= B) && (graphe[i][i] > temp)){
			ligne = i;
			somme = tab[1][i];
			temp = graphe[i][i];
		}
	}
	cpt++;
	res[1][ligne] = 1;
	i = n - 1;
	while((somme <= B) && (i > 0) && (cpt < n)){
		for(int j = 0 ; j < n ; j++){
			tab_temp[2][j] = graphe[ligne][j];
		}
		tri_fusion_int(tab_temp, 3, 0, n - 1);
		i = n - 1;
		while((i > 0) && ((somme + tab_temp[1][i] > B) || (res[1][tab_temp[0][i] - 1] == 1))){
			i--;
		}
		if(i > 0){
			res[1][tab_temp[0][i] - 1] = 1;
			somme += tab_temp[1][i];
			ligne = tab_temp[0][i] - 1;
		}
		cpt++;
	}
	if(somme > B){
		res[1][tab_temp[0][i] - 1] = 0;
	}
	liberer_matrice_int(tab_temp, 3);
	return res;
}