#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "competence.h"

int init_assassin(t_competence assassin[NB_CPT]){
    int i, j, k=0;
    for(i=0; i<5; i++){
        if(assassin[i].nb_suiv>0){
            assassin[i].suivantes=malloc(sizeof(t_competence)*assassin[i].nb_suiv);
            for(j=0; j<assassin[i].nb_suiv; j++){
                printf("%d\n",k+1);
                assassin[i].suivantes[j]=assassin[++k];
                printf("suivant assassin[%d] : %s\n", i ,assassin[i].suivantes[j].nom);
            }
        }
    }
    return 0;
}

int init_arbres(){
    init_assassin(assassin);
    //printf("Init...OK\n");
    printf("%s,%s\n", assassin[0].suivantes[0].nom, assassin[0].desc);
    //init_mage(mage);
    //init_guerrier(guerrier);
    //init_archer(archer);
    return 0;
}

int main(){
    init_arbres();
}