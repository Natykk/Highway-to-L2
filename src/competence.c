#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/competence.h"

int init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice){
    competence->obj_necessaires = malloc(sizeof(objet_inv_t));
    competence->obj_necessaires->nb = malloc(sizeof(int) * competence->taille_tab_obj_nec);
    competence->obj_necessaires->objet = malloc(sizeof(objet_t) * competence->taille_tab_obj_nec);
    switch(typeClasse){
        case ASSASSIN:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //griffe
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[2];     //Fourrure
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Griffe
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Griffe
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Fourrure
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Fourrure
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 4; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 10; 
                    competence->obj_necessaires->objet[0] = tab_objet[14];     //Coeur de diable
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[11];     //Corne de diablotin
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[13];     //Lance
                    break;
                default : break;
            }
            break;
        case MAGE:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 9; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[2] = 6; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[9];     //Massue
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 14; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 6; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Green Goo
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[9];     //Lance-pierre
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 18;                  
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[12];    //Queue de Diablotin
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[15];    //Tête
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 30; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[10];     //Red Goo
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[15];     //Tête
                    break;
                default : break;
            }
            break;
        case GUERRIER:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[2];     //Fourrure
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Green Goo
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[5];     //Grey Goo
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 17; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 20; 
                    competence->obj_necessaires->objet[0] = tab_objet[16];     //Croquettes
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[13];     //Lance
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[10];     //Red Goo
                    break;
                default : break;
            }
            break;
        case ARCHER:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Or
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[1];     //Fourrure
                    competence->obj_necessaires->nb[2] = 10; 
                    competence->obj_necessaires->objet[2] = tab_objet[8];     //Cailloux
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 19; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[2] = 9; 
                    competence->obj_necessaires->objet[2] = tab_objet[7];     //Lance-pierre
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[13];    //Lance
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Massue
                    competence->obj_necessaires->nb[2] = 9; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[2] = 8; 
                    competence->obj_necessaires->objet[2] = tab_objet[8];     //Cailloux
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 15; 
                    competence->obj_necessaires->objet[0] = tab_objet[10];     //Red Goo
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[12];     //Queue de diablotin
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[11];     //Corne de diablotin
                    break;
                default : break;
            }
            break;
        default: break;
    }
    return 1;
}

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

    printf("Buff :\n\t- Vie*%.2f\n\t- Att*%.2f\n\t- Vit_att*%.2f\n\t- Vit_depl*%.2f\n\t- bonus_perim_detect+%d\n", competence.buff.buff_vie, competence.buff.buff_degat, competence.buff.buff_vit_att, competence.buff.buff_vit_depl, competence.buff.perim_detect);

    printf("\n * Nécéssite :\n");
    for(int j=0; j<competence.taille_tab_obj_nec; j++){
        printf("\t- %s x %d\n", competence.obj_necessaires->objet[j].nom, competence.obj_necessaires->nb[j]);
    }
    
    printf("\n");
}
