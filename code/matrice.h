#ifndef MATRICE_H
#define MATRICE_H


int** init_tab_random(int n);
void set_valeur_projet(int** tab, int projet, int valeur);
void set_cout_projet(int** tab, int projet, int cout);
int min_prix(int** tab, int n);
int max_prix(int** tab, int n);
int min_valeur(int** tab, int n);
int max_valeur(int** tab, int n);
int** clone_tab(int** tab, int ligne, int colonne);
void liberer_matrice_int(int** tab, int ligne);
void liberer_matrice_float(float** tab, int ligne);
void afficher_matrice_int(int** tab, int ligne, int colonne);
void afficher_matrice_float(float** tab, int ligne, int colonne);
void interclasser_int(int** tab, int ligne, int p, int m, int g);
void interclasser_float(float** tab, int ligne, int p, int m, int g);
void tri_fusion_int(int** tab, int ligne, int debut, int fin);
void tri_fusion_float(float** tab, int ligne, int debut, int fin);

#endif