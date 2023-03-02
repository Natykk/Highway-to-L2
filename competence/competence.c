#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "competence.h"
//Met le nom de la compétence en question à "débloqué"
int changer_nomImgCpt(t_competence competence){
    int i;
    for(i=0; i<strlen(competence.name_img); i++);
    i--;
    competence.name_img[i]='u';

    return 1;
}

//Met le nom des compétences à "bloqué" (l=lock);
int remplissage_nomImgCpt(t_competence arbre[NB_CPT]){  
    int i, j, k;

    for(i=0; i<NB_CPT; i++){
        k=0;
        if(arbre[i].name_img==NULL){
            arbre[i].name_img=malloc(sizeof(char)*T_NOM);
            for(j=0; j<strlen(arbre[i].nom); j++){
                if((arbre[i].nom[j]>='A' && arbre[i].nom[j]<='Z') || (arbre[i].nom[j]>'0' &&arbre[i].nom[j]<='9')){
                    arbre[i].name_img[k++] = arbre[i].nom[j];
                }
            }
            arbre[i].name_img[k]='\0';
            arbre[i].name_img = realloc(arbre[i].name_img, sizeof(char)*(strlen(arbre[i].name_img)+1));
        }
        strcat(arbre[i].name_img,"_l.png");
    }
    return 1;
}


int init_arbre(t_competence arbre[NB_CPT]){
    int i, j, k;
    int branche_parcourus=0;
    int reculer=0;
    int avancer=0;

    /* Remplissage nom fichier sprite compétence */
    if(!remplissage_nomImgCpt(arbre)) return 0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        if(i==0){
            changer_nomImgCpt(arbre[i]);
        }
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
                //printf("compétence %s[%d] : suivant  %s\n",arbre[i].nom, i, arbre[i].suivantes[j].nom);
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
            arbre[i].suivantes=NULL;
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
                //printf("compétence %s[%d] : précédent  %s\n",arbre[i].nom, i, arbre[i].precedentes[j].nom);
                if(!strcmp(arbre[i].nom,"Bottes de sept lieues") && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
                else if(!strcmp(arbre[i].nom,"Bottes des géants") && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
            }
            if(reculer) k++; avancer=0;
            if(avancer) k--; reculer=0;
        }
        else{
            arbre[i].precedentes=NULL;
        }
    }

    return 1;
}

void aff_classe(t_competence arbre[NB_CPT]){
    int i, j;
    for(i=0; i<NB_CPT; i++){
        printf("\n");
        printf("%s : %s (%lu)\nDesc : %s\n", arbre[i].nom, arbre[i].name_img, strlen(arbre[i].name_img), arbre[i].desc);
        printf("Nombre comp preced : %d = {", arbre[i].nb_prec);
        for(j=0; j<arbre[i].nb_prec; j++){
            printf(" %s ", arbre[i].precedentes[j].nom);
        }
        printf("}\n");
        printf("Nombre comp suiv : %d = {", arbre[i].nb_suiv);
        for(j=0; j<arbre[i].nb_suiv; j++){
            printf(" %s ", arbre[i].suivantes[j].nom);
        }
        printf("}\n");

        printf("Buff :\n\t- Vie*%d\n\t- Att*%d\n\t- Vit_att*%d\n\t- Vit_depl*%d\n\t- diam*%d\n",arbre[i].buff_stat.buff_vie, arbre[i].buff_stat.buff_degat, arbre[i].buff_stat.buff_vit_att, arbre[i].buff_stat.buff_vit_depl, arbre[i].buff_stat.perim_detect);
        printf("\n");
    }
}

int detruire_arbre(t_competence arbre[NB_CPT]){
    int i;
    for(i=0; i<NB_CPT; i++){
        free(arbre[i].name_img);
        arbre[i].name_img=NULL;

        if(arbre[i].nb_prec>0){
            free(arbre[i].precedentes);
            arbre[i].precedentes=NULL;
        }
        if(arbre[i].nb_suiv>0){
            free(arbre[i].suivantes);
            arbre[i].suivantes=NULL;
        }
    }
    return 0;
}

int main(){
    init_arbre(assassin);
    aff_classe(assassin);
    init_arbre(mage);
    aff_classe(mage);
    init_arbre(guerrier);
    aff_classe(guerrier);
    init_arbre(archer);
    aff_classe(archer);

    detruire_arbre(assassin);
    detruire_arbre(mage);
    detruire_arbre(guerrier);
    detruire_arbre(archer);
}