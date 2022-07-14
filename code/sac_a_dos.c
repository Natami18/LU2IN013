#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrice.h"
#include "sac_a_dos.h"

int nb_colonne_matrice(int **tab, int n){
    int i, somme = 1;
    for(i = 0 ; i < n ; i++){
        somme += tab[2][i];
    }
    return somme;
}

float** remplir_matrice(int **tab, int n){// n = nombre total d'objets
    float** mat = (float**)malloc(n*sizeof(float*)); //On creer les n lignes de la matrice
    int c = nb_colonne_matrice(tab,n), i, j;
    if(mat){
        for(i = 0 ; i < n ; i++){
            mat[i] = (float*)malloc(c*sizeof(float)); // On creer les c colonnes de la matrice
            
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
                    if(j == 0){
                        mat[i][j] = 0;
                    }
                    else{
                        if(j == tab[2][0]){
                            mat[i][j] = tab[1][0];
                        }
                        else{
                            mat[i][j] = INFINITY;
                        }
                    }
                }
                else{
                    if(j < tab[2][i]){
                        mat[i][j] = mat[i-1][j];
                    }
                    else{
                        mat[i][j]= fmin(mat[i-1][j], tab[1][i] + mat[i-1][j-tab[2][i]]);
                    }
                }
            }
        }
    }
    return mat;
}

int** objets_selectionnes(int** tab, float** mat, float B, int n, int c){
    int** res = (int**)malloc(2*sizeof(int*));
    if(res){
        for(int i = 0 ; i < 2 ; i++){
            res[i] = (int*)malloc(n*sizeof(int));
            if(res[i] == NULL){
                for(int j = 0 ; j < i ; j++){
                    free(res[j]);
                    res[j] = NULL;
                }
                free(res);
                res = NULL;
                return NULL;
            }
        }
        for(int i = 0 ; i < n ; i++){
            res[0][i] = i + 1;
            res[1][i] = 0;
        }
        int ligne = n - 1, colonne = 0, B_temp = B;
        float temp = 0, somme = 0;
        while(B_temp){
            for(int i = c - 1 ; i >= 0 ; i--){
                if(mat[n-1][i] == B_temp){
                    colonne = i;
                    B_temp = 1;
                    break;
                }
            }
            B_temp --;
        }
        temp = mat[ligne][colonne];
        while((ligne) && (colonne)){
            //printf("ligne = %i, colonne = %i, temp = %.2f\n", ligne, colonne, temp);
            if(temp == mat[ligne - 1][colonne]){
                ligne--;
                //printf("ligne = %i, colonne = %i, temp = %.2f\n", ligne, colonne, temp);
            }
            else{
                if(somme + tab[1][ligne] <= B){
                    res[1][ligne] = 1;
                    somme += tab[1][ligne];
                }
                ligne--;
                colonne--;
                //printf("ligne = %i, colonne = %i, temp = %.2f\n", ligne, colonne, temp);
                while((ligne) && (colonne) && (mat[ligne][colonne] >= temp)){
                    colonne--;
                    //printf("ligne = %i, colonne = %i, temp = %.2f\n", ligne, colonne, temp);
                }
            }
            temp = mat[ligne][colonne];
            //printf("ligne = %i, colonne = %i, temp = %.2f\n", ligne, colonne, temp);
        }
        if((colonne) && (temp) && (temp != INFINITY) && somme + tab[1][0] <= B){
            res[1][0] = 1;
            somme += tab[1][0];
        }
        //printf("somme = %.2f\n", somme);
        return res;
    }
    return NULL;
}