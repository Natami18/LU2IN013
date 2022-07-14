#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "entree_sortie.h"
#include "choix.h"
#include "comparaison.h"

#define NB_PROJETS 10
#define BUDGET 750
#define NB_VOTANTS 10000


int main(int argc, char const *argv[]){
	srand(time(NULL));
	int i, **tab, **choix, **graphe, ***tab_choix = (int***)malloc(sizeof(int**)*NB_VOTANTS);
	double temps_cpu; 
	float somme1 = 0, somme2 = 0, somme3 = 0, somme4 = 0, somme5 = 0;
	clock_t temps_initial, temps_final;
	FILE *fic, *fic1;

	if(tab_choix){
		fic1 = fopen("CV1B.txt", "w");
		if(fic1){
			for(int i = 1; i < 101 ; i++){ //projet
				for(int j = 0 ; j < 10 ; j++){
					printf("1\n");
					somme1 = 0; somme2 = 0; somme3 = 0; somme4 = 0; somme5 = 0;
					printf("2\n");
					tab = init_tab_random(i);
					printf("3\n");
					for (int k = 0 ; k < NB_VOTANTS ; k++){
						tab_choix[k] = choix_votant_1_a_random(i);
					}
					printf("4\n");
					graphe = graphe_choix(tab_choix, NB_VOTANTS, tab, i);
					
					printf("5\n");
					temps_initial = clock();
					choix = choix_final_1(tab_choix, NB_VOTANTS, tab, i, BUDGET);
					temps_final = clock();
					printf("6\n");
					temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
					printf("7\n");
					somme1 += temps_cpu;
					printf("8\n");
					liberer_matrice_int(choix, 2);
					
					printf("9\n");
					temps_initial = clock();
					choix = choix_final_2(tab_choix, NB_VOTANTS, tab, i, BUDGET);
					temps_final = clock();
					printf("10\n");
					temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
					printf("11\n");
					somme2 += temps_cpu;
					printf("12\n");
					liberer_matrice_int(choix, 2);
					
					printf("13\n");
					temps_initial = clock();
					choix = choix_final_3(tab_choix, NB_VOTANTS, tab, i, BUDGET);
					temps_final = clock();
					printf("14\n");
					temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
					printf("15\n");
					somme3 += temps_cpu;
					printf("16\n");
					liberer_matrice_int(choix, 2);
					
					printf("17\n");
					temps_initial = clock();
					choix = choix_final_4(tab, graphe, i, BUDGET);
					temps_final = clock();
					printf("18\n");
					temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
					printf("19\n");
					somme4 += temps_cpu;
					printf("20\n");
					liberer_matrice_int(choix, 2);
					
					printf("21\n");
					temps_initial = clock();
					choix = choix_final_5(tab, graphe, i, BUDGET);
					temps_final = clock();
					printf("22\n");
					temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
					printf("23\n");
					somme5 += temps_cpu;
					
					printf("24\n");
					for(int k = 0 ; k < NB_VOTANTS ; k++){
						liberer_matrice_int(tab_choix[k], 2);
					}
					printf("25\n");
					liberer_matrice_int(choix, 2);
					printf("26\n");
					liberer_matrice_int(tab, 3);
					printf("27\n");
					liberer_matrice_int(graphe, i);
				}
				fprintf(fic1, "%i %f %f %f %f %f\n", i, somme1/10, somme2/10, somme3/10, somme4/10, somme5/10);
				printf("i = %i\n", i);
			}
			fclose(fic1);
		}
		free(tab_choix);
	}
	return 0;
}