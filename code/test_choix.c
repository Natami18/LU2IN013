#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "choix.h"
#include "entree_sortie.h"

#define NB_PROJETS 6
#define BUDGET 3000
#define NB_VOTANTS 60000

int main(int argc, char const *argv[]){
	srand(time(NULL));
	int i, **tab = init_tab_random(NB_PROJETS), **choix, **graphe;
	ecriture_tab_opv("test_tableau_opv.txt", tab, NB_PROJETS);
	printf("Le budget est de %i€\n", BUDGET);
	printf("\n");
	
	printf("Voici le tableau objet-poids-valeur :\n");
	afficher_matrice_int(tab, 3, NB_PROJETS);
	printf("\n");

/*	choix = choix_votant_1_a_random(NB_PROJETS);
	printf("Voici le choix propose par la fonction choix_votant_1_a_random :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

	choix = choix_votant_1_b_random(tab, NB_PROJETS);
	printf("Voici le choix propose par la fonction choix_votant_1_b_random :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

	choix = choix_votant_1_manuel(NB_PROJETS);
	printf("Voici le choix propose par la fonction choix_votant_1_manuel :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

	choix = choix_votant_2_a_random(tab, NB_PROJETS, BUDGET);
	printf("Voici le choix propose par la fonction choix_votant_2_a_random :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

	choix = choix_votant_2_a_manuel(tab, NB_PROJETS, BUDGET);
	printf("Voici le choix propose par la fonction choix_votant_2_a_manuel :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

*/	choix = choix_votant_2_b_random(tab, NB_PROJETS, BUDGET);
	printf("Voici le choix propose par la fonction choix_votant_2_b_random :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");

/*	choix = choix_votant_2_b_manuel(tab, NB_PROJETS, BUDGET);
	printf("Voici le choix propose par la fonction choix_votant_2_b_manuel :\n");
	afficher_matrice_int(choix, 2, NB_PROJETS);
	liberer_matrice_int(choix, 2);
	printf("\n");
*/

	int*** tab_choix = (int***)malloc(sizeof(int**)*NB_VOTANTS);
	if(tab_choix){
		for(int i = 0 ; i < NB_VOTANTS ; i++){
			tab_choix[i] = choix_votant_1_b_random(tab, NB_PROJETS);
		}

		graphe = graphe_choix(tab_choix, NB_VOTANTS, tab, NB_PROJETS);
		printf("Voici le graphe associé aux choix des votants :\n");
		afficher_matrice_int(graphe, NB_PROJETS, NB_PROJETS);
		printf("\n");

		choix = choix_final_1(tab_choix, NB_VOTANTS, tab, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_1 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		liberer_matrice_int(choix, 2);
		printf("\n");

		choix = choix_final_2(tab_choix, NB_VOTANTS, tab, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_2 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		liberer_matrice_int(choix, 2);
		printf("\n");

		choix = choix_final_3(tab_choix, NB_VOTANTS, tab, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_3 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		liberer_matrice_int(choix, 2);
		printf("\n");

		choix = choix_final_4(tab, graphe, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_4 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		liberer_matrice_int(choix, 2);
		printf("\n");

		choix = choix_final_5(tab, graphe, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_5 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		liberer_matrice_int(choix, 2);
		printf("\n");

		liberer_matrice_int(graphe, NB_PROJETS);
		for(int i = 0 ; i < NB_VOTANTS ; i++){
			liberer_matrice_int(tab_choix[i], 2);
		}
		free(tab_choix);
	}

	liberer_matrice_int(tab, 3);
	return 0;
}