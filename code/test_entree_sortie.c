#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "entree_sortie.h"
#include "choix.h"


#define VALEUR_MIN 0
#define VALEUR_MAX 10
#define NB_PROJETS 6
#define BUDGET 3000
#define NB_VOTANTS 60000


int main(int argc, char const *argv[]){
	srand(time(NULL));
	int **tab = init_tab_random(NB_PROJETS), **valeur = clone_tab(tab, 3, NB_PROJETS);
	
	if((tab) && (valeur)){
		ecriture_tab_opv("test_tableau_opv.txt", tab, NB_PROJETS);

		int taille = 0, **test = lecture_tab_opv("test_tableau_opv.txt", &taille);
		if(test){
			afficher_matrice_int(test, 3, taille);
			liberer_matrice_int(test, 3);
			printf("taille = %i\n", taille);
		}


		for(int i = 0 ; i < 10 ; i++){
			int** choix = choix_votant_1_a_random(NB_PROJETS);
			ecriture_choix("test_choix.txt", choix, NB_PROJETS);
			liberer_matrice_int(choix, 2);
			
			for(int i = 0 ; i < NB_PROJETS ; i++){
				valeur[2][i] = VALEUR_MIN + rand()%(VALEUR_MAX - VALEUR_MIN + 1);
			}
			ecriture_valeur("test_valeur.txt", valeur, NB_PROJETS);
		}

		int ***lecture = lecture_choix("test_choix.txt", &taille);
		if(lecture){
			printf("taille = %i\n", taille);
			for(int i = 0 ; i < taille ; i++){
				afficher_matrice_int(lecture[i], 2, NB_PROJETS);
				printf("\n");
				liberer_matrice_int(lecture[i], 2);
			}
			free(lecture);
			lecture = NULL;
		}

		lecture = lecture_valeur("test_valeur.txt", &taille, tab, NB_PROJETS);
		if(lecture){
			printf("taille = %i\n", taille);
			for(int i = 0 ; i < taille ; i++){
				afficher_matrice_int(lecture[i], 3, NB_PROJETS);
				printf("\n");
				liberer_matrice_int(lecture[i], 3);
			}
			free(lecture);
			lecture = NULL;
		}

		liberer_matrice_int(valeur, 3);
		liberer_matrice_int(tab, 3);
	}
	
	else{
		if(tab){
			liberer_matrice_int(tab, 3);
		}
		if(valeur){
			liberer_matrice_int(valeur, 3);
		}		
	}

	return 0;
}