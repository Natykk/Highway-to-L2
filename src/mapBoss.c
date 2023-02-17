#include <stdio.h>
#include <stdlib.h>

#include "mapStruct.h"

#define BOSS 10 //Boss : à enlever quand boss créés
#define SPON 11 //Lieu de spon dans la salle du boss : à enlever ?

void afficher_salle(t_salle_boss * salle){
    int i, j;
    for(i=0; i<LARG_SALLE_BOSS; i++){
        for(j=0; j<LONG_SALLE_BOSS; j++){
            switch(salle->dim[i][j]){
                case VIDE : printf(" "); break;
                case MUR : printf("*"); break;
                case PILIER : printf("o"); break;
                case BOSS : printf("B"); break;
                case SPON : printf("S"); break;
                case PORTE : printf("P"); break;
            }
        }
        printf("\n");
    }
}

t_salle_boss * genererSalleBoss(t_salle_boss * salleBoss){
    salleBoss = malloc(sizeof(t_salle_boss));
    int i, j;
    for(i=0; i<LARG_SALLE_BOSS; i++){
        for(j=0; j<LONG_SALLE_BOSS; j++){
            if(j==0 || i==0 || i==LARG_SALLE_BOSS-1 || j==LONG_SALLE_BOSS-1){
                salleBoss->dim[i][j]=MUR;
            }
            else if((i==LARG_SALLE_BOSS/3 || i==2*LARG_SALLE_BOSS/3) && (j==LONG_SALLE_BOSS/5 || j==2*LONG_SALLE_BOSS/5 || j==3*LONG_SALLE_BOSS/5 || j==4*LONG_SALLE_BOSS/5)){
                salleBoss->dim[i][j]=PILIER;
            }
            else if(i==LARG_SALLE_BOSS/2 && j==LONG_SALLE_BOSS-5){
                salleBoss->dim[i][j]=BOSS;
            }
            else if(i==LARG_SALLE_BOSS/2 && j==4){  
                salleBoss->dim[i][j]=SPON;
            }
            else{
                salleBoss->dim[i][j]=VIDE;
            }

            if(i==LARG_SALLE_BOSS/2 && j==LONG_SALLE_BOSS-1){
                salleBoss->dim[i][j]=PORTE;
            }
        }
    }
    return salleBoss;
}

void detruireSalleBoss(t_salle_boss ** salleBoss){
    free(*salleBoss);
    *salleBoss=NULL;
}

int main(){
    t_salle_boss * salleBoss;
    salleBoss = genererSalleBoss(salleBoss);
    afficher_salle(salleBoss);
    detruireSalleBoss(&salleBoss);
}