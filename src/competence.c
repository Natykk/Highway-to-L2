#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/competence.h"

//Met le nom de la compétence en question à "débloqué"
int changer_nomImgCpt(t_competence * competence){
    int i;
    for(i=0; i<strlen(competence->name_img); i++);
    i--;
    competence->name_img[i]='u';

    return 1;
}

//Met le nom des compétences à "bloqué" (l=lock);
int remplissage_nomImgCpt(t_competence * competence){  
    int j, k;
    if(competence->name_img==NULL){
        competence->name_img=malloc(sizeof(char)*T_NOM);
        for(j=0; j<strlen(competence->nom); j++){
            if((competence->nom[j]>='A' && competence->nom[j]<='Z') || (competence->nom[j]>'0' && competence->nom[j]<='9')){
                competence->name_img[k++] = competence->nom[j];
            }
        }
        competence->name_img[k]='\0';
        competence->name_img = realloc(competence->name_img, sizeof(char)*(strlen(competence->name_img)+1));
    }
    strcat(competence->name_img,"_l.png");

    return 1;
}

int init_competences(t_competence* competences[NB_CPT], t_classe typeClasse){
    int i, j, k;
    int branche_parcourus=0;
    int reculer=0;
    int avancer=0;

    /* Remplissage nom fichier sprite compétence */
    if(!remplissage_nomImgCpt(*competences)) return 0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        if(competences[i]->nb_suiv>0){
            competences[i]->suivantes=malloc(sizeof(t_competence)*competences[i]->nb_suiv);
            for(j=0; j<competences[i]->nb_suiv; j++){
                if(competences[k]->nb_prec>1+branche_parcourus){
                    competences[i]->suivantes[j]=*competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i]->suivantes[j]=*competences[k++];
                    branche_parcourus=0;
                }
                //printf("compétence %s[%d] : suivant  %s\n",competences[i].nom, i, competences[i].suivantes[j].nom);
                if(typeClasse==GUERRIER && i==5 && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
                else if(typeClasse==GUERRIER && i==6 && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
            }
            if(reculer) k--; reculer=0;
            if(avancer) k++; avancer=0;
        }
        else{
            competences[i]->suivantes=NULL;
        }
    }
    printf("\n");
    
    //Remplissage des tableaux de compétences précédentes pour chaque compétence
    branche_parcourus=0;
    for(i=NB_CPT-1, k=i-1; i>=0; i--){
        if(competences[i]->nb_prec>0){
            competences[i]->precedentes=malloc(sizeof(t_competence)*competences[i]->nb_prec);
            for(j=0; j<competences[i]->nb_prec ; j++){
                if(competences[k]->nb_suiv>1+branche_parcourus){
                    competences[i]->precedentes[j]=*competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i]->precedentes[j]=*competences[k--];
                    branche_parcourus=0;
                }
                //printf("compétence %s[%d] : précédent  %s\n",competences[i].nom, i, competences[i].precedentes[j].nom);
                if(typeClasse==GUERRIER && i==NB_CPT-2 && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
                else if(typeClasse==GUERRIER && i==NB_CPT-3 && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
            }
            if(reculer) k++; avancer=0;
            if(avancer) k--; reculer=0;
        }
        else{
            competences[i]->precedentes=NULL;
        }
    }

    return 1;
}

void aff_classe(t_competence* competences[NB_CPT]){
    int i, j;
    for(i=0; i<NB_CPT; i++){
        printf("\n");
        printf("%s : %s (%lu)\nDesc : %s\n", competences[i]->nom, competences[i]->name_img, strlen(competences[i]->name_img), competences[i]->desc);
        printf("Nombre comp preced : %d = {", competences[i]->nb_prec);
        for(j=0; j<competences[i]->nb_prec; j++){
            printf(" %s ", competences[i]->precedentes[j].nom);
        }
        printf("}\n");
        printf("Nombre comp suiv : %d = {", competences[i]->nb_suiv);
        for(j=0; j<competences[i]->nb_suiv; j++){
            printf(" %s ", competences[i]->suivantes[j].nom);
        }
        printf("}\n");

        printf("Buff :\n\t- Vie*%d\n\t- Att*%d\n\t- Vit_att*%d\n\t- Vit_depl*%d\n\t- diam*%d\n",competences[i]->buff_stat.buff_vie, competences[i]->buff_stat.buff_degat, competences[i]->buff_stat.buff_vit_att, competences[i]->buff_stat.buff_vit_depl, competences[i]->buff_stat.perim_detect);
        printf("\n");
    }
}

int detruire_competences(t_competence competences[NB_CPT]){
    int i;
    for(i=0; i<NB_CPT; i++){
        free(competences[i].name_img);
        competences[i].name_img=NULL;

        if(competences[i].nb_prec>0){
            free(competences[i].precedentes);
            competences[i].precedentes=NULL;
        }
        if(competences[i].nb_suiv>0){
            free(competences[i].suivantes);
            competences[i].suivantes=NULL;
        }
    }
    return 0;
}
