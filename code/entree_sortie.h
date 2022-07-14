#ifndef ENTREE_SORTIE_H
#define ENTREE_SORTIE_H


void ecriture_choix(char* fichier, int** choix, int n);
void ecriture_valeur(char* fichier, int** tab, int n);
void ecriture_tab_opv(char* fichier, int** tab, int n);
int*** lecture_choix(char* fichier, int* taille);
int*** lecture_valeur(char* fichier, int* taille, int** tab, int n);
int** lecture_tab_opv(char* fichier, int* taille);
int** valeur_to_choix_a(int** tab, int n, float B);
int** valeur_to_choix_b(int** tab, int n, float B);
int*** valeur_to_choix(int*** lecture, int taille, float B, int n);


#endif