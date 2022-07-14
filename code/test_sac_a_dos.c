#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"

int main(){
    srand(time(NULL));
    int i, **tab = (int**)malloc(sizeof(int*)*3), **objets = NULL;
    for(i = 0 ; i < 3 ; i++){
        tab[i] = (int*)malloc(sizeof(int)*4) ;
    }
    tab[0][0] = 1; tab[0][1] = 2; tab[0][2] = 3; tab[0][3] = 4;
    tab[1][0] = 2; tab[1][1] = 7; tab[1][2] = 1; tab[1][3] = 2;
    tab[2][0] = 1; tab[2][1] = 4; tab[2][2] = 2; tab[2][3] = 2;

    float **mat = remplir_matrice(tab,4);

    printf("Voici le tableau d'objets-poids-valeur : \n");
    afficher_matrice_int(tab, 3, 4); 
    
    i = nb_colonne_matrice(tab, 4);
    printf("Nombre de colonne = %i\n", i);
    
    printf("\nVoici sa matrice associee : \n");
    afficher_matrice_float(mat, 4, i);

    objets = objets_selectionnes(tab, mat, 6, 4, i);
    printf("\nVoici le choix : \n");
    afficher_matrice_int(objets, 2, 4);
    liberer_matrice_int(objets, 2);
   
    objets = objets_selectionnes(tab, mat, 9, 4, i);
    printf("\nVoici le choix : \n");
    afficher_matrice_int(objets, 2, 4);
    liberer_matrice_int(objets, 2);
   
    objets = objets_selectionnes(tab, mat, 4, 4, i);
    printf("\nVoici le choix : \n");
    afficher_matrice_int(objets, 2, 4);
    liberer_matrice_int(objets, 2);
   
    objets = objets_selectionnes(tab, mat, 1, 4, i);
    printf("\nVoici le choix : \n");
    afficher_matrice_int(objets, 2, 4);
    liberer_matrice_int(objets, 2);
   
    liberer_matrice_int(tab, 3);
    liberer_matrice_float(mat, 4);

    return 0;
}