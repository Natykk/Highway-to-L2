#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapStruct.h"

void afficher_etage(t_etage * etage){
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            if(etage->etage[i][j].num_salle==SALLE_UNUSED){
                printf("*");
            }
            else if(etage->etage[i][j].statut==COMMON){
                printf("O");
            }
            else if(etage->etage[i][j].statut==START){
                printf("D");
            }
            else if(etage->etage[i][j].statut==EXIT){
                printf("A");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}



int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]){
    if(x>0 && x<DIM_ETAGE && y>0 && y<DIM_ETAGE){
        if(etage[x][y].num_salle==SALLE_UNUSED){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

//fonction de création d'un etage, retourne 0 si la map a bien été créée sinon renvoie 100
int genererEtage(t_etage * etage){
    srand(time(NULL));
    int i, j;
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            etage->etage[i][j].num_salle=SALLE_UNUSED;
        }
    }

    int x=rand()%10;
    int y=rand()%10;
    int i_salle = 1;
    etage->etage[x][y].num_salle=i_salle++;
    etage->etage[x][y].statut=START;
    while (i_salle++<=etage->nb_salle){
        int prev_x = x;
        int prev_y = y;
        do{
            int choix_direction_salle = rand()%4;
            switch(choix_direction_salle){
                case 0 : 
                    if(salle_disponible(x+1,y,etage->etage)){
                        etage->etage[++x][y].num_salle=i_salle;
                    }
                    break;
                case 1 : 
                    if(salle_disponible(x-1,y,etage->etage)){
                        etage->etage[--x][y].num_salle=i_salle;
                    }
                    break;
                case 2 : 
                    if(salle_disponible(x,y+1,etage->etage)){
                        etage->etage[x][++y].num_salle=i_salle;
                    }
                    break;
                case 3 : 
                    if(salle_disponible(x,y-1,etage->etage)){
                        etage->etage[x][--y].num_salle=i_salle;
                    }
                    break;
            }
            if(i_salle<etage->nb_salle){
                etage->etage[x][y].statut=COMMON;
            }
            else if(i_salle==etage->nb_salle){
                etage->etage[x][y].statut=EXIT;
            }
        }while(x == prev_x && y == prev_y);
    }
    return OK;
}

//fonction de création d'un niveau, retourne 0 si la map a bien été créée sinon renvoie 100
int genererNiv(t_niv * niveau){
    srand(time(NULL));
    niveau = malloc(sizeof(t_niv));
    niveau->etages[0].nb_salle = rand()%7+3;
    genererEtage(&niveau->etages[0]);
    afficher_etage(&niveau->etages[0]);

    return OK;
}


int main(){
    t_niv * niveau;
    genererNiv(niveau);
}
