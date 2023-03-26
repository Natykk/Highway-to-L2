#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/competence.h"

//Met le nom de la compétence en question à "débloqué"
int changer_nomImgCpt(t_competence * competence){
    int i;
    for(i=0; i<strlen(competence->name_img); i++);
    i--;
    while(competence->name_img[i] != 'l'){
        i--;
    }
    competence->name_img[i]='u';

    return 1;
}

//Met le nom des compétences à "bloqué" (l=lock);
int remplissage_nomImgCpt(t_competence *competences){  
    int i, j, k;
    for(i=0; i<NB_CPT; i++){
        if(competences[i].name_img==NULL){
            competences[i].name_img=malloc(sizeof(char)*T_NOM);
            for(j=0, k=0; j<strlen(competences[i].nom); j++){
                if((competences[i].nom[j]>='A' && competences[i].nom[j]<='Z') || (competences[i].nom[j]>'0' && competences[i].nom[j]<='9')){
                    competences[i].name_img[k++] = competences[i].nom[j];
                }
            }
            competences[i].name_img[k]='\0';
        }
        strcat(competences[i].name_img,"_l.png");
    }

    return 1;
}

int init_competences(t_competence * competences, t_classe typeClasse){
    int i, j, k;
    int branche_parcourus=0;
    int reculer=0;
    int avancer=0;

    /* Remplissage nom fichier sprite compétence */
    if(!remplissage_nomImgCpt(competences)) return 0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        init_obj_necessaires(&(competences[i]), typeClasse, i);

        if(competences[i].nb_suiv>0){
            competences[i].suivantes=malloc(sizeof(t_competence)*competences[i].nb_suiv);
            for(j=0; j<competences[i].nb_suiv; j++){
                if(competences[k].nb_prec>1+branche_parcourus){
                    competences[i].suivantes[j]=&competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i].suivantes[j]=&competences[k++];
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
            competences[i].suivantes=NULL;
        }
    }
    
    //Remplissage des tableaux de compétences précédentes pour chaque compétence
    branche_parcourus=0;
    for(i=NB_CPT-1, k=i-1; i>=0; i--){
        if(competences[i].nb_prec>0){
            competences[i].precedentes=malloc(sizeof(t_competence)*competences[i].nb_prec);
            for(j=0; j<competences[i].nb_prec ; j++){
                if(competences[k].nb_suiv>1+branche_parcourus){
                    competences[i].precedentes[j]=&competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i].precedentes[j]=&competences[k--];
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
            if(reculer) k--; reculer=0;
            if(avancer) k++; avancer=0;
        }
        else{
            competences[i].precedentes=NULL;
        }
    }

    return 1;
}

void aff_competence(t_competence competence){
    printf("\n");
    if(competence.competence_acquise == non_acquis){
        printf("(NON ACQUISE) ");
    }
    else{
        printf("(ACQUISE) ");
    }
    printf("%s : %s (%lu)\nDesc : %s\n", competence.nom, competence.name_img, strlen(competence.name_img), competence.desc);
    
    printf("Nombre comp preced : %d = {", competence.nb_prec);
    for(int j=0; j<competence.nb_prec; j++){
        printf(" %s ", competence.precedentes[j]->nom);
    }
    printf("}\n");
    printf("Nombre comp suiv : %d = {", competence.nb_suiv);
    for(int j=0; j<competence.nb_suiv; j++){
        printf(" %s ", competence.suivantes[j]->nom);
    }
    printf("}\n");

    printf("Buff :\n\t- Vie*%.2f\n\t- Att*%.2f\n\t- Vit_att*%.2f\n\t- Vit_depl*%.2f\n\t- diam-%d\n", competence.buff.buff_vie, competence.buff.buff_degat, competence.buff.buff_vit_att, competence.buff.buff_vit_depl, competence.buff.perim_detect);

    printf("\n * Nécéssite :\n");
    for(int j=0; j<competence.taille_tab_obj_nec; j++){
        printf("\t- %s x %d\n", competence.obj_necessaires->objet[j].nom, competence.obj_necessaires->nb[j]);
    }
    
    printf("\n");
}
