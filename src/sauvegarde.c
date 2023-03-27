#include <stdio.h>
#include <stdlib.h>

#include "../head/entite.h"
#include "../head/arbre.h"
#include "../head/mapStruct.h"
#include "../head/inventaire.h"

int one_next_cpt_unlock(t_competence * competence){
    int i;
    for(i=0; i<competence->nb_suiv; i++){
        if(competence->suivantes[i]->competence_acquise == acquis){
            printf("%d - ", i);
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
        if(personnage->nom != NULL){
            fprintf(f_sauv, "%s\n", personnage->nom);
        }
        if(personnage->arbre == NULL){
            fprintf(f_sauv, "\n");
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

        fclose(f_sauv);
    }
    else{
        printf("Le personnage n'a pas été initialisé : impossible de sauvegarder\n");
    }
    return 1;
}


int main(){
    entite_t * personnage;
    personnage = creer_personnage(personnage);
    personnage->nom = "médor";
    personnage = init_inventaire_personnage(personnage);
    init_arbre(&personnage->arbre, cpt_mage, MAGE);
    afficher_entite(personnage);
    
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
    competence_debloquer(personnage, personnage->arbre->competence[0]);
    competence_debloquer(personnage, personnage->arbre->competence[1]);
    competence_debloquer(personnage, personnage->arbre->competence[3]);
    competence_debloquer(personnage, personnage->arbre->competence[5]);
    competence_debloquer(personnage, personnage->arbre->competence[9]);
    sauvegarde(personnage, 2);


    afficher_inventaire(personnage);
    detruire_arbre(&personnage->arbre);
    detruire_entitee(personnage);
}