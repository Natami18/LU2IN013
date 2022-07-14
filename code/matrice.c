#include <stdio.h>
#include <stdlib.h>

#define POIDS_MIN 1
#define POIDS_MAX 2000
#define VALEUR_MIN 0
#define VALEUR_MAX 10


int** init_tab_random(int n){
    int** res = (int**)malloc(3*sizeof(int*));
    if(res){
        for(int i = 0 ; i < 3 ; i++){
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
            res[0][i] = i + 1; //numero du projet
            res[1][i] = POIDS_MIN + rand()%(POIDS_MAX - POIDS_MIN + 1); //poids du projet
            res[2][i] = VALEUR_MIN + rand()%(VALEUR_MAX - VALEUR_MIN + 1); //valeur du projet
        }
    }
    return res;
}

void set_valeur_projet(int** tab, int projet, int valeur){
    tab[2][projet - 1] = valeur;
}

void set_cout_projet(int** tab, int projet, int cout){
    tab[1][projet - 1] = cout;
}

int min_prix(int** tab, int n){
    int res = tab[1][0];
    for(int i = 1 ; i < n ; i++){
        if(tab[1][i] < res){
            res = tab[1][i];
        }
    }
    return res;
}

int max_prix(int** tab, int n){
    int res = tab[1][0];
    for(int i = 1 ; i < n ; i++){
        if(tab[1][i] > res){
            res = tab[1][i];
        }
    }
    return res;
}

int min_valeur(int** tab, int n){
    int res = tab[2][0];
    for(int i = 1 ; i < n ; i++){
        if(tab[2][i] < res){
            res = tab[2][i];
        }
    }
    return res;
}

int max_valeur(int** tab, int n){
    int res = tab[2][0];
    for(int i = 1 ; i < n ; i++){
        if(tab[2][i] > res){
            res = tab[2][i];
        }
    }
    return res;
}


int** clone_tab(int** tab, int ligne, int colonne){
    if(tab){
        int** res = (int**)malloc(ligne*sizeof(int*));
        if(res){
            for(int i = 0 ; i < ligne ; i++){
                res[i] = (int*)malloc(colonne*sizeof(int));
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
            for(int i = 0 ; i < ligne ; i++){
                for(int j = 0 ; j < colonne ; j++){
                    res[i][j] = tab[i][j];
                }
            }
        }
        return res;
    }
    return NULL;
}

void liberer_matrice_int(int** tab, int ligne){
    int i;
    if(tab){
        for(i = 0 ; i < ligne ; i++){
            free(tab[i]);
        }
        free(tab);    
    }
}

void liberer_matrice_float(float** tab, int ligne){
    int i;
    if(tab){
        for(i = 0 ; i < ligne ; i++){
            free(tab[i]);
        }
        free(tab);
    }
}

void afficher_matrice_int(int** tab, int ligne, int colonne){
    int i, j;
    if(tab){
        for(i = 0 ; i < ligne ; i++){
            for (j = 0; j < colonne; j++){
                printf("%i\t", tab[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("Le tableau est vide.\n");
    }
}

void afficher_matrice_float(float** tab, int ligne, int colonne){
    int i, j;
    if(tab){
        for(i = 0 ; i < ligne ; i++){
            for (j = 0; j < colonne; j++){
                printf("%.2f\t", tab[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("Le tableau est vide.\n");
    }
}

void interclasser_int(int** tab, int ligne, int p, int m, int g){
    int temp[ligne][100000], i, j, k, l;
    for(i = 0 ; i < ligne ; i++){
        for(j = p ; j <= g ; j++){
            temp[i][j] = tab[i][j];
        }
    }
    i = p;
    j = m + 1;
    for(k = p ; k <= g ; k++){
        if(i == m + 1){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][j];
            }
            j++;
        }
        else if(j == g + 1){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][i];
            }
            i++;
        }
        else if(temp[ligne - 1][i] >= temp[ligne - 1][j]){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][i];
            }
            i++;
        }
        else{
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][j];
            }
            j++;
        }
    }
}

void interclasser_float(float** tab, int ligne, int p, int m, int g){
    float temp[ligne][100000];
    int i, j, k, l;
    for(i = 0 ; i < ligne ; i++){
        for(j = p ; j <= g ; j++){
            temp[i][j] = tab[i][j];
        }
    }
    i = p;
    j = m + 1;
    for(k = p ; k <= g ; k++){
        if(i == m + 1){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][j];
            }
            j++;
        }
        else if(j == g + 1){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][i];
            }
            i++;
        }
        else if(temp[ligne - 1][i] >= temp[ligne - 1][j]){
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][i];
            }
            i++;
        }
        else{
            for(l = 0 ; l < ligne ; l++){
                tab[l][k] = temp[l][j];
            }
            j++;
        }
    }
}

void tri_fusion_int(int** tab, int ligne, int debut, int fin){
    if(debut < fin){
        int milieu = (debut + fin)/2;
        tri_fusion_int(tab, ligne, debut, milieu);
        tri_fusion_int(tab, ligne, milieu + 1, fin);
        interclasser_int(tab, ligne, debut, milieu, fin);
    }
}

void tri_fusion_float(float** tab, int ligne, int debut, int fin){
    if(debut < fin){
        int milieu = (debut + fin)/2;
        tri_fusion_float(tab, ligne, debut, milieu);
        tri_fusion_float(tab, ligne, milieu + 1, fin);
        interclasser_float(tab, ligne, debut, milieu, fin);
    }
}