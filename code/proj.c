#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int min(int a, int b){
    if(a<=b){
        return a;
    }
    return b;
}

int nb_colonne_matrice(int **tab, int n){
    int i, somme = 1;
    for(i = 0 ; i < n ; i++){
        somme += tab[2][i];
    }
    return somme;
}

int ** remplir_matrice(int **tab, int n){// n = nombre total d'objets
    int **mat = (int**)malloc(n*sizeof(int*)); //On creer les n lignes de la matrice
    int c = nb_colonne_matrice(tab,n), i, j;
    if(mat){
        for(i = 0 ; i < n ; i++){
            mat[i] = (int*)malloc(c*sizeof(int)); // On creer les c colonnes de la matrice
            
            //S'il y a un probleme d'allocation
            if(mat[i] == NULL){
                for(j = 0 ; j < i ; j++){
                    free(mat[j]); //On desalloue toutes les colonnes precedemment allouees
                }
                free(mat); //On desalloue la matrice
                return NULL;
            }
            
            //S'il n'y a pas de probleme d'allocation
            for(j = 0 ; j < c ; j++){
                if(i == 0){
                    if(j < tab[2][0]){
                        mat[i][j] = 0;
                    }
                    if(j == tab[2][0]){
                        mat[i][j] = tab[1][0];
                    }
                    else{
                        mat[i][j] = (int)INFINITY;
                    }
                }
                else{
                    if(j < tab[2][i]){
                        mat[i][j] = mat[i-1][j];
                    }
                    else{
                        mat[i][j]= min(mat[i-1][j], tab[1][i] + mat[i-1][j-i]);
                    }
                }
            }
        }
    }
    return mat;
}

void liberer_matrice(int **tab, int ligne){
    int i;
    for(i = 0 ; i < ligne ; i++){
        free(tab[i]);
    }
    free(tab);
}

void afficher_matrice(int **tab, int ligne, int colonne){
    int i, j;
    for(i = 0 ; i < ligne ; i++){
        for (j = 0; i < colonne; j++){
            printf("%i\t", tab[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int i, **tab = (int**)malloc(sizeof(int*)*3);
    for(i = 0 ; i < 3 ; i++){
        tab[i] = (int*)malloc(sizeof(int)*4) ;
    }
    tab[0][0] = 1; tab[0][1] = 2; tab[0][2] = 3; tab[0][3] = 4;
    tab[1][0] = 2; tab[1][1] = 2; tab[1][2] = 1; tab[1][3] = 2;
    tab[2][0] = 1; tab[2][1] = 7; tab[2][2] = 2; tab[2][3] = 2;
    int **mat = remplir_matrice(tab,4);

    printf("Voici le tableau d'objets-poids-valeur : \n");
    afficher_matrice(tab, 3, 4); //Il y a un probleme au niveau du tableau ! 
    //printf("\nVoici sa matrice associée : \n");
    //afficher_matrice(mat, 4, nb_colonne_matrice(tab, 4));
    liberer_matrice(tab, 3);
    liberer_matrice(mat, 4);
    
    return 0;
}