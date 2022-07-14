#ifndef COMPARAISON_H
#define COMPARAISON_H


float poids_moyen(int** choix, int** tab, int n);
float valeur_moyenne(int** choix, int** tab, int n);
int nombre_objets(int** choix, int n);
int cout_total(int** choix, int** tab, int n);
float nombre_objets_par_personne_moyenne(int*** tab_choix, int v, int** choix, int n);
int satisfaction_1(int*** tab_choix, int v, int** choix, int n, int* nul);
int* satisfaction_2(int*** tab_choix, int v, int** choix, int n, int nul);


#endif