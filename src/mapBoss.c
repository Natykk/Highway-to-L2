#include <stdio.h>
#include <stdlib.h>

#include "../head/mapBoss.h"

#define BOSS 10 //Boss : à enlever quand boss créés
#define SPAWN 10 //Lieu de SPAWN dans la salle du boss : à enlever ?

void afficher_salle_boss(t_salle * salle){
    int i, j;
    for(i=0; i<LARG_SALLE_BOSS; i++){
        for(j=0; j<LONG_SALLE_BOSS; j++){
            switch(salle->dim[i][j]){
                case VIDE : printf(" "); break;
                case MUR : printf("*"); break;
                case PILIER : printf("o"); break;
                case BOSS : printf("B"); break;
                case PORTE : printf("P"); break;
            }
        }
        printf("\n");
    }
}

t_salle * genererSalleBoss(t_salle * salleBoss){
    salleBoss = malloc(sizeof(t_salle));
    salleBoss->nb_mobs=0;
    for(int i=0; i<LARG_SALLE_BOSS; i++){
            for(int j=0; j<LONG_SALLE_BOSS; j++){
                salleBoss->dim[i][j]=0;
            }
        }
    int i, j;
    for(i=0; i<LARG_SALLE_BOSS; i++){
        for(j=0; j<LONG_SALLE_BOSS; j++){
            if(j==0 || i==0 || i==LARG_SALLE_BOSS-1 || j==LONG_SALLE_BOSS-1){
                salleBoss->dim[i][j]=MUR;
            }
            else if((i==LARG_SALLE_BOSS/3 || i==2*LARG_SALLE_BOSS/3) && (j==LONG_SALLE_BOSS/5 || j==2*LONG_SALLE_BOSS/5 || j==3*LONG_SALLE_BOSS/5 || j==4*LONG_SALLE_BOSS/5)){
                salleBoss->dim[i][j]=MUR; // Ancienne valeur : PILIER
            }
            if(i==LARG_SALLE_BOSS/2 && j==LONG_SALLE_BOSS-1){
                salleBoss->dim[i][j]=PORTE;
            }
        }
    }
    return salleBoss;
}

void detruireSalleBoss(t_salle ** salleBoss){
    free(*salleBoss);
    *salleBoss=NULL;
}

t_salle * genererSalleMarchand(t_salle * salleMarchand){
    salleMarchand = malloc(sizeof(t_salle));
    salleMarchand->nb_mobs=0;
    
    for(int i=0; i<LARG_MARCHAND; i++){
            for(int j=0; j<LONG_MARCHAND; j++){
                salleMarchand->dim[i][j]=0;
            }
        }
    int i, j;
    for(i=0; i<LARG_MARCHAND; i++){
        for(j=0; j<LONG_MARCHAND; j++){
            if(j==0 || i==0 || i==LARG_MARCHAND-1 || j==LONG_MARCHAND-1){
                salleMarchand->dim[i][j]=MUR;
            }else if(i==LARG_MARCHAND/2 && j==LONG_MARCHAND/2){
                salleMarchand->dim[i][j]=MARCHAND;
            }else{
                salleMarchand->dim[i][j]=VIDE;
            }
            // met une porte sur le coté droit
            if(i==LARG_MARCHAND-1 && j==LONG_MARCHAND/2){
                salleMarchand->dim[i][j]=PORTE;
            }
            
        }
    }
    return salleMarchand;
}