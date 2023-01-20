#include <stdio.h>
#include <stdlib.h>

#define TAILLE_X_MAP 100
#define TAILLE_Y_MAP 50

void affichage(int map[TAILLE_X_MAP][TAILLE_Y_MAP]){
    int i, j;
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            if(map[i][j]==-1){      //-1 = MUR
                printf("\u2610");
            }
            else if(map[i][j]==0){
                printf("\u2B1C");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void remplissageMap(int map[TAILLE_X_MAP][TAILLE_Y_MAP]){
    int i, j;
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            if(i==0 || i==TAILLE_X_MAP-1 || j==0 || j==TAILLE_Y_MAP-1){
                map[i][j]=-1;
            }
            else{
                map[i][j]=0;
            }
        }
    }

}

int main(){
    int map[TAILLE_X_MAP][TAILLE_Y_MAP];
    remplissageMap(map);
    affichage(map);
}