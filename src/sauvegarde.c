#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/entite.h"
#include "../head/arbre.h"
#include "../head/mapStruct.h"
#include "../head/inventaire.h"

int one_next_cpt_unlock(t_competence * competence){
    int i;
    for(i=0; i<competence->nb_suiv; i++){
        if(competence->suivantes[i]->competence_acquise == acquis){
            return i;
        }
    }
    return -1;
}

int cpt_aquise(FILE * sauv, t_arbre * arbre){
    int ind=-1;
    t_competence * cpt_actuelle = arbre->competence[0];
    if(cpt_actuelle->competence_acquise != non_acquis){
        do{
            fprintf(sauv, "%s\n", cpt_actuelle->nom);
            if((ind = one_next_cpt_unlock(cpt_actuelle)) > -1){
                cpt_actuelle = cpt_actuelle->suivantes[ind];
            }
        }while(cpt_actuelle->competence_acquise != non_acquis && ind>-1);
    }
    fprintf(sauv, "END_OF_CPT\n");
    return 1;
}

int sauvegarde(entite_t * personnage, int num_etage){
    if(personnage != NULL){
        FILE * f_sauv = fopen("../sauv/sauvegarde.txt", "w");
        if(personnage->nom != NULL && strcmp(personnage->nom, "")){
            fprintf(f_sauv, "%s\n", personnage->nom);
        }
        else{
            fprintf(f_sauv, "None\n");
        }
        if(personnage->arbre == NULL){
            fprintf(f_sauv, "None\n");
        }
        else if(personnage->arbre->classe == ASSASSIN){
            fprintf(f_sauv, "0\n");
        }
        else if(personnage->arbre->classe == GUERRIER){
            fprintf(f_sauv, "1\n");
        }
        else if(personnage->arbre->classe == MAGE){
            fprintf(f_sauv, "2\n");
        }
        else if(personnage->arbre->classe == ARCHER){
            fprintf(f_sauv, "3\n");
        }
        cpt_aquise(f_sauv, personnage->arbre);
        fprintf(f_sauv, "%d\n", num_etage);
        for(int i=0; i<NB_OBJET; i++){
            fprintf(f_sauv, "%d\n", personnage->inventaire->nb[i]);
        }

        fclose(f_sauv);
    }
    else{
        printf("Le personnage n'a pas été initialisé : impossible de sauvegarder\n");
    }
    return 1;
}

int appliquer(entite_t * personnage, t_competence *  competence){
    personnage->degats *= competence->buff.buff_degat;
    personnage->vie *= competence->buff.buff_vie;
    personnage->vitesse_att *= competence->buff.buff_vit_att;
    personnage->vitesse_depl *= competence->buff.buff_vit_depl;
    personnage->perim_detect += competence->buff.perim_detect-1;
    return 1;
}


int chargement(entite_t ** personnage){
    FILE * f_sauv = fopen("../sauv/sauvegarde.txt", "r");
    if(f_sauv){
        *personnage = creer_personnage(*personnage);
        *personnage = init_inventaire_personnage(*personnage);
        fscanf(f_sauv, "%s", (*personnage)->nom);
        int classe;
        fscanf(f_sauv, "%d", &classe);
        switch(classe){
            case ARCHER : init_arbre(&(*personnage)->arbre, cpt_archer, classe); break;
            case ASSASSIN : init_arbre(&(*personnage)->arbre, cpt_assassin, classe); break;
            case GUERRIER : init_arbre(&(*personnage)->arbre, cpt_guerrier, classe); break;
            case MAGE : init_arbre(&(*personnage)->arbre, cpt_mage, classe); break;
            default : break;
        }
        char c;
        char *nom_cpt = malloc(sizeof(char)*50);
        fscanf(f_sauv, "%c", &c);
        fgets(nom_cpt, 50, f_sauv);
        nom_cpt[strlen(nom_cpt)-1]='\0';
        t_competence * racine = (*personnage)->arbre->competence[0];
        while(strcmp(nom_cpt, "NULL") && strcmp(nom_cpt, "END_OF_CPT")){
            if(!strcmp(nom_cpt, racine->nom)){
                racine->competence_acquise = acquis;
                appliquer(*personnage, racine);
                fgets(nom_cpt, 50, f_sauv);
                nom_cpt[strlen(nom_cpt)-1]='\0';
                for(int i=0; i<racine->nb_suiv; i++){
                    if(!strcmp(racine->suivantes[i]->nom, nom_cpt)){
                        racine = racine->suivantes[i];
                    }
                }
            }
        }
        free(nom_cpt);
        nom_cpt=NULL;

        int num_etage;
        fscanf(f_sauv, "%d", &num_etage);

        for(int i=0; i<NB_OBJET; i++){
            fscanf(f_sauv, "%d", &(*personnage)->inventaire->nb[i]);
        }

        return num_etage;
    }
    else{
        printf("Erreur : impossible d'ouvrir le fichier de sauvegarde\n");
        return -1;
    }
}

/*
int main(){
    t_arbre * mage;
    init_arbre(&mage, cpt_mage, MAGE);
    entite_t * personnage;
    personnage = creer_personnage(personnage);
    //personnage->nom = "médor";
    personnage = init_inventaire_personnage(personnage);
    //afficher_entite(personnage);
    
    int rang;
    rang=acces_obj("Grimoire");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 30;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Or");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 50;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Green Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Grey Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 30;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Griffe");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Red Goo");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        printf("ressource ajoutée!\n");
    }

    rang=acces_obj("Tetes");
    if(rang>-1){
        personnage->inventaire->nb[rang] = 20;
        printf("ressource ajoutée!\n");
    }

    afficher_inventaire(personnage);
    competence_debloquer(personnage, mage->competence[0], mage);
    competence_debloquer(personnage, mage->competence[1], mage);
    competence_debloquer(personnage, mage->competence[3], mage);
    competence_debloquer(personnage, mage->competence[5], mage);
    competence_debloquer(personnage, mage->competence[9], mage);
    sauvegarde(personnage, 2);
    detruire_arbre(&personnage->arbre);
    detruire_entitee(personnage);

    chargement(&personnage);
    afficher_entite(personnage);
    //aff_classe(personnage->arbre);
    //afficher_inventaire(personnage);
    detruire_arbre(&personnage->arbre);
    detruire_entitee(personnage);
}
*/