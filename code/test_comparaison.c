#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"
#include "entree_sortie.h"
#include "choix.h"
#include "comparaison.h"

#define NB_PROJETS 6
#define BUDGET 3000
#define NB_VOTANTS 60000

int main(int argc, char const *argv[]){
	srand(time(NULL));
	int nb_objet, c_tot, satisfaits, nul, *satisfaction, taille = 6, **tab, **choix, **graphe;
	float p_moy, v_moy, nb_objet_par_pers, pourcentage;
	FILE* fic;

	printf("Le budget est de %i€\n", BUDGET);
	printf("\n");

	tab = init_tab_random(NB_PROJETS);
	ecriture_tab_opv("test_tableau_opv", tab, NB_PROJETS);
//	tab = lecture_tab_opv("test_tableau_opv", &taille);
	
	printf("Voici le tableau objet-poids-valeur :\n");
	afficher_matrice_int(tab, 3, taille);
	printf("\n");

	int*** tab_choix = (int***)malloc(sizeof(int**)*NB_VOTANTS);
	if(tab_choix){
		for(int i = 0 ; i < NB_VOTANTS ; i++){
//			tab_choix[i] = choix_votant_1_a_random(taille);
//			tab_choix[i] = choix_votant_1_b_random(tab, taille);
			tab_choix[i] = choix_votant_2_a_random(tab, taille, BUDGET);
//			tab_choix[i] = choix_votant_2_b_random(tab, taille, BUDGET);
		}

		
		graphe = graphe_choix(tab_choix, NB_VOTANTS, tab, taille);
		printf("Voici le graphe associé aux choix des votants :\n");
		afficher_matrice_int(graphe, taille, taille);
		printf("\n");
	
		
		choix = choix_final_1(tab_choix, NB_VOTANTS, tab, taille, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_1 :\n");
		afficher_matrice_int(choix, 2, taille);

		p_moy = poids_moyen(choix, tab, taille);
		v_moy = valeur_moyenne(choix, tab, taille);
		nb_objet = nombre_objets(choix, taille);
		c_tot = cout_total(choix, tab, taille);
		nb_objet_par_pers = nombre_objets_par_personne_moyenne(tab_choix, NB_VOTANTS, choix, taille);
		satisfaits = satisfaction_1(tab_choix, NB_VOTANTS, choix, taille, &nul);
		satisfaction = satisfaction_2(tab_choix, NB_VOTANTS, choix, taille, nul);
		
		fic = fopen("4-2a-choix_final_1.txt", "w");
		if(fic){
			fprintf(fic, "Description de la fonction choix_final_1 :\n\n");
			fprintf(fic, "Le budget est de %.2i€.\nLe nombre de votants est %i.\n\n", BUDGET, NB_VOTANTS);
			
			fprintf(fic, "Voici le tableau objet-poids-valeur :\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[1][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[2][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Voici le graphe associé aux choix des votants :\n");
			for(int i = 0 ; i < taille ; i++){
				for(int j = 0 ; j < taille ; j++){
					fprintf(fic, "%i\t", graphe[i][j]);
				}
				fprintf(fic, "\n");
			}
			fprintf(fic, "\n");

			fprintf(fic, "Voici le tableau de choix : \n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[1][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Le cout moyen d'un objet est %.2f€.\n", p_moy);
			fprintf(fic, "La valeur moyenne d'un objet est %.2f.\n", v_moy);
			fprintf(fic, "Le nombre d'objets selectionnes est %i.\n", nb_objet);
			fprintf(fic, "Le cout total des objets selectionnes est %i€.\n", c_tot);
			fprintf(fic, "Le nombre d'objets choisis par un votant finalement selectionnes est %.2f.\n", nb_objet_par_pers);
			pourcentage = ((float)(NB_VOTANTS - nul) / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont voté pour au moins un objet est %i, soit %.2f pourcent des votants.\n", NB_VOTANTS - nul, pourcentage);
			pourcentage = ((float)nul / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui n'ont voté pour aucun projet est %i, soit %.2f pourcent des votants.\n", nul, pourcentage);
			pourcentage = ((float)satisfaits / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont au moins un objet selectionne est %i, soit %.2f pourcent des votants.\n", satisfaits, pourcentage);
			pourcentage = ((float)satisfaction[0] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement insatisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[0], pourcentage);
			for(int i = 1 ; i < 11 ; i++){
				pourcentage = ((float)satisfaction[i] / NB_VOTANTS) * 100;
				fprintf(fic, "Le nombre de personnes dont le taux de satisfaction est entre %i pourcent et %i pourcent est %i, soit %.2f pourcent des votants.\n", 10 * (i - 1), 10 * i, satisfaction[i], pourcentage);
			}
			pourcentage = ((float)satisfaction[11] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement satisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[11], pourcentage);
			fclose(fic);
		}
		
		liberer_matrice_int(choix, 2);
		printf("\n");
	
		
		choix = choix_final_2(tab_choix, NB_VOTANTS, tab, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_2 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		
		p_moy = poids_moyen(choix, tab, NB_PROJETS);
		v_moy = valeur_moyenne(choix, tab, NB_PROJETS);
		nb_objet = nombre_objets(choix, NB_PROJETS);
		c_tot = cout_total(choix, tab, NB_PROJETS);
		nb_objet_par_pers = nombre_objets_par_personne_moyenne(tab_choix, NB_VOTANTS, choix, NB_PROJETS);
		satisfaits = satisfaction_1(tab_choix, NB_VOTANTS, choix, taille, &nul);
		satisfaction = satisfaction_2(tab_choix, NB_VOTANTS, choix, NB_PROJETS, nul);
		
		fic = fopen("4-2a-choix_final_2.txt", "w");
		if(fic){
			fprintf(fic, "Description de la fonction choix_final_2 :\n\n");
			fprintf(fic, "Le budget est de %.2i€.\nLe nombre de votants est %i.\n\n", BUDGET, NB_VOTANTS);
			
			fprintf(fic, "Voici le tableau objet-poids-valeur :\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[1][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[2][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Voici le graphe associé aux choix des votants :\n");
			for(int i = 0 ; i < taille ; i++){
				for(int j = 0 ; j < taille ; j++){
					fprintf(fic, "%i\t", graphe[i][j]);
				}
				fprintf(fic, "\n");
			}
			fprintf(fic, "\n");

			fprintf(fic, "Voici le tableau de choix : \n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[1][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Le cout moyen d'un objet est %.2f€.\n", p_moy);
			fprintf(fic, "La valeur moyenne d'un objet est %.2f.\n", v_moy);
			fprintf(fic, "Le nombre d'objets selectionnes est %i.\n", nb_objet);
			fprintf(fic, "Le cout total des objets selectionnes est %i€.\n", c_tot);
			fprintf(fic, "Le nombre d'objets choisis par un votant finalement selectionnes est %.2f.\n", nb_objet_par_pers);
			pourcentage = ((float)(NB_VOTANTS - nul) / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont voté pour au moins un objet est %i, soit %.2f pourcent des votants.\n", NB_VOTANTS - nul, pourcentage);
			pourcentage = ((float)nul / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui n'ont voté pour aucun projet est %i, soit %.2f pourcent des votants.\n", nul, pourcentage);
			pourcentage = ((float)satisfaits / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont au moins un objet selectionne est %i, soit %.2f pourcent des votants.\n", satisfaits, pourcentage);
			pourcentage = ((float)satisfaction[0] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement insatisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[0], pourcentage);
			for(int i = 1 ; i < 11 ; i++){
				pourcentage = ((float)satisfaction[i] / NB_VOTANTS) * 100;
				fprintf(fic, "Le nombre de personnes dont le taux de satisfaction est entre %i pourcent et %i pourcent est %i, soit %.2f pourcent des votants.\n", 10 * (i - 1), 10 * i, satisfaction[i], pourcentage);
			}
			pourcentage = ((float)satisfaction[11] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement satisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[11], pourcentage);
			fclose(fic);
		}
		
		liberer_matrice_int(choix, 2);
		printf("\n");
	
		
		choix = choix_final_3(tab_choix, NB_VOTANTS, tab, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_3 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		
		p_moy = poids_moyen(choix, tab, NB_PROJETS);
		v_moy = valeur_moyenne(choix, tab, NB_PROJETS);
		nb_objet = nombre_objets(choix, NB_PROJETS);
		c_tot = cout_total(choix, tab, NB_PROJETS);
		nb_objet_par_pers = nombre_objets_par_personne_moyenne(tab_choix, NB_VOTANTS, choix, NB_PROJETS);
		satisfaits = satisfaction_1(tab_choix, NB_VOTANTS, choix, taille, &nul);
		satisfaction = satisfaction_2(tab_choix, NB_VOTANTS, choix, NB_PROJETS, nul);
		
		fic = fopen("4-2a-choix_final_3.txt", "w");
		if(fic){
			fprintf(fic, "Description de la fonction choix_final_3 :\n\n");
			fprintf(fic, "Le budget est de %.2i€.\nLe nombre de votants est %i.\n\n", BUDGET, NB_VOTANTS);
			
			fprintf(fic, "Voici le tableau objet-poids-valeur :\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[1][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[2][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Voici le graphe associé aux choix des votants :\n");
			for(int i = 0 ; i < taille ; i++){
				for(int j = 0 ; j < taille ; j++){
					fprintf(fic, "%i\t", graphe[i][j]);
				}
				fprintf(fic, "\n");
			}
			fprintf(fic, "\n");

			fprintf(fic, "Voici le tableau de choix : \n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[1][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Le cout moyen d'un objet est %.2f€.\n", p_moy);
			fprintf(fic, "La valeur moyenne d'un objet est %.2f.\n", v_moy);
			fprintf(fic, "Le nombre d'objets selectionnes est %i.\n", nb_objet);
			fprintf(fic, "Le cout total des objets selectionnes est %i€.\n", c_tot);
			fprintf(fic, "Le nombre d'objets choisis par un votant finalement selectionnes est %.2f.\n", nb_objet_par_pers);
			pourcentage = ((float)(NB_VOTANTS - nul) / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont voté pour au moins un objet est %i, soit %.2f pourcent des votants.\n", NB_VOTANTS - nul, pourcentage);
			pourcentage = ((float)nul / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui n'ont voté pour aucun projet est %i, soit %.2f pourcent des votants.\n", nul, pourcentage);
			pourcentage = ((float)satisfaits / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont au moins un objet selectionne est %i, soit %.2f pourcent des votants.\n", satisfaits, pourcentage);
			pourcentage = ((float)satisfaction[0] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement insatisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[0], pourcentage);
			for(int i = 1 ; i < 11 ; i++){
				pourcentage = ((float)satisfaction[i] / NB_VOTANTS) * 100;
				fprintf(fic, "Le nombre de personnes dont le taux de satisfaction est entre %i pourcent et %i pourcent est %i, soit %.2f pourcent des votants.\n", 10 * (i - 1), 10 * i, satisfaction[i], pourcentage);
			}
			pourcentage = ((float)satisfaction[11] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement satisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[11], pourcentage);
			fclose(fic);
		}
		
		liberer_matrice_int(choix, 2);
		printf("\n");
	

		choix = choix_final_4(tab, graphe, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_4 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		
		p_moy = poids_moyen(choix, tab, NB_PROJETS);
		v_moy = valeur_moyenne(choix, tab, NB_PROJETS);
		nb_objet = nombre_objets(choix, NB_PROJETS);
		c_tot = cout_total(choix, tab, NB_PROJETS);
		nb_objet_par_pers = nombre_objets_par_personne_moyenne(tab_choix, NB_VOTANTS, choix, NB_PROJETS);
		satisfaits = satisfaction_1(tab_choix, NB_VOTANTS, choix, taille, &nul);
		satisfaction = satisfaction_2(tab_choix, NB_VOTANTS, choix, NB_PROJETS, nul);
		
		fic = fopen("4-2a-choix_final_4.txt", "w");
		if(fic){
			fprintf(fic, "Description de la fonction choix_final_4 :\n\n");
			fprintf(fic, "Le budget est de %.2i€.\nLe nombre de votants est %i.\n\n", BUDGET, NB_VOTANTS);
			
			fprintf(fic, "Voici le tableau objet-poids-valeur :\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[1][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[2][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Voici le graphe associé aux choix des votants :\n");
			for(int i = 0 ; i < taille ; i++){
				for(int j = 0 ; j < taille ; j++){
					fprintf(fic, "%i\t", graphe[i][j]);
				}
				fprintf(fic, "\n");
			}
			fprintf(fic, "\n");

			fprintf(fic, "Voici le tableau de choix : \n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[1][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Le cout moyen d'un objet est %.2f€.\n", p_moy);
			fprintf(fic, "La valeur moyenne d'un objet est %.2f.\n", v_moy);
			fprintf(fic, "Le nombre d'objets selectionnes est %i.\n", nb_objet);
			fprintf(fic, "Le cout total des objets selectionnes est %i€.\n", c_tot);
			fprintf(fic, "Le nombre d'objets choisis par un votant finalement selectionnes est %.2f.\n", nb_objet_par_pers);
			pourcentage = ((float)(NB_VOTANTS - nul) / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont voté pour au moins un objet est %i, soit %.2f pourcent des votants.\n", NB_VOTANTS - nul, pourcentage);
			pourcentage = ((float)nul / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui n'ont voté pour aucun projet est %i, soit %.2f pourcent des votants.\n", nul, pourcentage);
			pourcentage = ((float)satisfaits / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont au moins un objet selectionne est %i, soit %.2f pourcent des votants.\n", satisfaits, pourcentage);
			pourcentage = ((float)satisfaction[0] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement insatisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[0], pourcentage);
			for(int i = 1 ; i < 11 ; i++){
				pourcentage = ((float)satisfaction[i] / NB_VOTANTS) * 100;
				fprintf(fic, "Le nombre de personnes dont le taux de satisfaction est entre %i pourcent et %i pourcent est %i, soit %.2f pourcent des votants.\n", 10 * (i - 1), 10 * i, satisfaction[i], pourcentage);
			}
			pourcentage = ((float)satisfaction[11] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement satisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[11], pourcentage);
			fclose(fic);
		}
		
		liberer_matrice_int(choix, 2);
		printf("\n");


		choix = choix_final_5(tab, graphe, NB_PROJETS, BUDGET);
		printf("Voici le choix propose par la fonction choix_final_5 :\n");
		afficher_matrice_int(choix, 2, NB_PROJETS);
		
		p_moy = poids_moyen(choix, tab, NB_PROJETS);
		v_moy = valeur_moyenne(choix, tab, NB_PROJETS);
		nb_objet = nombre_objets(choix, NB_PROJETS);
		c_tot = cout_total(choix, tab, NB_PROJETS);
		nb_objet_par_pers = nombre_objets_par_personne_moyenne(tab_choix, NB_VOTANTS, choix, NB_PROJETS);
		satisfaits = satisfaction_1(tab_choix, NB_VOTANTS, choix, taille, &nul);
		satisfaction = satisfaction_2(tab_choix, NB_VOTANTS, choix, NB_PROJETS, nul);
		
		fic = fopen("4-2a-choix_final_5.txt", "w");
		if(fic){
			fprintf(fic, "Description de la fonction choix_final_5 :\n\n");
			fprintf(fic, "Le budget est de %.2i€.\nLe nombre de votants est %i.\n\n", BUDGET, NB_VOTANTS);
			
			fprintf(fic, "Voici le tableau objet-poids-valeur :\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[1][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", tab[2][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Voici le graphe associé aux choix des votants :\n");
			for(int i = 0 ; i < taille ; i++){
				for(int j = 0 ; j < taille ; j++){
					fprintf(fic, "%i\t", graphe[i][j]);
				}
				fprintf(fic, "\n");
			}
			fprintf(fic, "\n");

			fprintf(fic, "Voici le tableau de choix : \n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[0][i]);
			}
			fprintf(fic, "\n");
			for(int i = 0 ; i < taille ; i++){
				fprintf(fic, "%i\t", choix[1][i]);
			}
			fprintf(fic, "\n\n");
			
			fprintf(fic, "Le cout moyen d'un objet est %.2f€.\n", p_moy);
			fprintf(fic, "La valeur moyenne d'un objet est %.2f.\n", v_moy);
			fprintf(fic, "Le nombre d'objets selectionnes est %i.\n", nb_objet);
			fprintf(fic, "Le cout total des objets selectionnes est %i€.\n", c_tot);
			fprintf(fic, "Le nombre d'objets choisis par un votant finalement selectionnes est %.2f.\n", nb_objet_par_pers);
			pourcentage = ((float)(NB_VOTANTS - nul) / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont voté pour au moins un objet est %i, soit %.2f pourcent des votants.\n", NB_VOTANTS - nul, pourcentage);
			pourcentage = ((float)nul / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui n'ont voté pour aucun projet est %i, soit %.2f pourcent des votants.\n", nul, pourcentage);
			pourcentage = ((float)satisfaits / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes qui ont au moins un objet selectionne est %i, soit %.2f pourcent des votants.\n", satisfaits, pourcentage);
			pourcentage = ((float)satisfaction[0] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement insatisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[0], pourcentage);
			for(int i = 1 ; i < 11 ; i++){
				pourcentage = ((float)satisfaction[i] / NB_VOTANTS) * 100;
				fprintf(fic, "Le nombre de personnes dont le taux de satisfaction est entre %i pourcent et %i pourcent est %i, soit %.2f pourcent des votants.\n", 10 * (i - 1), 10 * i, satisfaction[i], pourcentage);
			}
			pourcentage = ((float)satisfaction[11] / NB_VOTANTS) * 100;
			fprintf(fic, "Le nombre de personnes totalement satisfaites est %i, soit %.2f pourcent des votants.\n", satisfaction[11], pourcentage);
			fclose(fic);
		}
		
		liberer_matrice_int(choix, 2);
		printf("\n");

		
		for(int i = 0 ; i < NB_VOTANTS ; i++){
			liberer_matrice_int(tab_choix[i], 2);
		}
		free(tab_choix);
	}

	liberer_matrice_int(graphe, NB_PROJETS);
	liberer_matrice_int(tab, 3);
	return 0;
}