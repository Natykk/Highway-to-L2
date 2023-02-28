#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "competence.h"

/*
int init_arbre(t_competence arbre[NB_CPT]){
    int i, j, k;
    int branche_parcourus=0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        if(arbre[i].nb_suiv>0){
            arbre[i].suivantes=malloc(sizeof(t_competence)*arbre[i].nb_suiv);
            for(j=0; j<arbre[i].nb_suiv; j++){
                if(arbre[k].nb_prec>1+branche_parcourus){
                    arbre[i].suivantes[j]=arbre[k];
                    branche_parcourus++;
                }
                else{
                    arbre[i].suivantes[j]=arbre[k++];
                    branche_parcourus=0;
                }
                printf("compétence %s[%d] : suivant  %s\n",arbre[i].nom, i, arbre[i].suivantes[j].nom);
            }
        }
        else{
            printf("compétence %s[%d] : pas de suisvant\n",arbre[i].nom, i);
        }
    }
    printf("\n");
    
    //Remplissage des tableaux de compétences précédentes pour chaque compétence
    branche_parcourus=0;
    for(i=NB_CPT-1, k=i-1; i>=0; i--){
        if(arbre[i].nb_prec>0){
            arbre[i].precedentes=malloc(sizeof(t_competence)*arbre[i].nb_prec);
            for(j=0; j<arbre[i].nb_prec ; j++){
                if(arbre[k].nb_suiv>1+branche_parcourus){
                    arbre[i].precedentes[j]=arbre[k];
                    branche_parcourus++;
                }
                else{
                    arbre[i].precedentes[j]=arbre[k--];
                    branche_parcourus=0;
                }
                printf("compétence %s[%d] : suivant  %s\n",arbre[i].nom, i, arbre[i].precedentes[j].nom);
            }
        }
        else{
            printf("compétence %s[%d] : pas de précédent\n",arbre[i].nom, i);
        }
    }
    return 0;
}
*/

int init_arbre(t_competence arbre[NB_CPT]){
    int i, j, k;
    int branche_parcourus=0;
    int reculer=0;
    int avancer=0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        if(arbre[i].nb_suiv>0){
            arbre[i].suivantes=malloc(sizeof(t_competence)*arbre[i].nb_suiv);
            for(j=0; j<arbre[i].nb_suiv; j++){
                if(arbre[k].nb_prec>1+branche_parcourus){
                    arbre[i].suivantes[j]=arbre[k];
                    branche_parcourus++;
                }
                else{
                    arbre[i].suivantes[j]=arbre[k++];
                    branche_parcourus=0;
                }
                printf("compétence %s[%d] : suivant  %s\n",arbre[i].nom, i, arbre[i].suivantes[j].nom);
                if(!strcmp(arbre[i].nom,"Bénédiction de Neptune") && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
                else if(!strcmp(arbre[i].nom,"Armure d'Hadès") && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
            }
            if(reculer) k--; reculer=0;
            if(avancer) k++; avancer=0;
        }
        else{
            printf("compétence %s[%d] : pas de suisvant\n",arbre[i].nom, i);
        }
    }
    printf("\n");
    
    //Remplissage des tableaux de compétences précédentes pour chaque compétence
    branche_parcourus=0;
    for(i=NB_CPT-1, k=i-1; i>=0; i--){
        if(arbre[i].nb_prec>0){
            arbre[i].precedentes=malloc(sizeof(t_competence)*arbre[i].nb_prec);
            for(j=0; j<arbre[i].nb_prec ; j++){
                if(arbre[k].nb_suiv>1+branche_parcourus){
                    arbre[i].precedentes[j]=arbre[k];
                    branche_parcourus++;
                }
                else{
                    arbre[i].precedentes[j]=arbre[k--];
                    branche_parcourus=0;
                }
                printf("compétence %s[%d] : précédent  %s\n",arbre[i].nom, i, arbre[i].precedentes[j].nom);
                if(!strcmp(arbre[i].nom,"Bottes de sept lieues") && branche_parcourus!=0){
                    k--;
                    reculer=1;
                }
                else if(!strcmp(arbre[i].nom,"Bottes des géants") && branche_parcourus!=0){
                    k++;
                    avancer=1;
                }
            }
            if(reculer) k++; reculer=0;
            if(avancer) k--; avancer=0;
        }
        else{
            printf("compétence %s[%d] : pas de précédent\n",arbre[i].nom, i);
        }
    }
    return 0;
}

int main(){
    init_arbre(assassin);
    printf("\n\n");
    init_arbre(mage);
    printf("\n\n");
    init_arbre(guerrier);
    printf("\n\n");
    init_arbre(archer);
}