#ifndef CHOIX_H
#define CHOIX_H


int** choix_votant_1_a_random(int n);//sans corrélation
int** choix_votant_1_b_random(int** tab, int n);//avec corrélation
int** choix_votant_1_manuel(int n);
int** choix_votant_2_a_random(int** tab, int n, float B);//sac à dos
int** choix_votant_2_a_manuel(int** tab, int n, float B);
int** choix_votant_2_b_random(int** tab, int n, float B);//tri
int** choix_votant_2_b_manuel(int** tab, int n, float B);

int** graphe_choix(int*** tab_choix, int v, int** tab, int n);

int** choix_final_1(int*** tab_choix, int v, int** tab, int n, float B); /*Les projets sont triés du plus voulu au moins voulu puis ils sont sélectionnés tant que la somme de leur cout ne dépasse pas le budget*/
int** choix_final_2(int*** tab_choix, int v, int** tab, int n, float B); /*Les projets sont triés du plus (voulu/cout) au moins (voulu/cout) puis ils sont sélectionnés tant que la somme de leur cout ne dépasse pas le budget*/
int** choix_final_3(int*** tab_choix, int v, int** tab, int n, float B); /*On utilise l'algorithme du sac à dos*/
int** choix_final_4(int** tab, int** graphe, int n, float B); //avec le graphe
int** choix_final_5(int** tab, int** graphe, int n, float B); //avec le graphe


#endif