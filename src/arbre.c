#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../head/arbre.h"
#include "../head/inventaire.h"


void aff_classe(t_arbre * arbre){
    int i;
    switch(arbre->classe){
        case ARCHER : printf("\n\t - ARCHER - \n"); break;
        case MAGE : printf("\n\t - MAGE - \n"); break;
        case GUERRIER : printf("\n\t - GUERRIER - \n"); break;
        case ASSASSIN : printf("\n\t - ASSASSIN - \n"); break;
        default : break;
    }
    for(i=0; i<NB_CPT; i++){
        aff_competence(*arbre->competence[i]);
    }
}

int detruire_arbre(t_arbre ** arbre){
    int i, j;
    switch((*arbre)->classe){
        case ARCHER : printf("\n\t - ARCHER - \n"); break;
        case MAGE : printf("\n\t - MAGE - \n"); break;
        case GUERRIER : printf("\n\t - GUERRIER - \n"); break;
        case ASSASSIN : printf("\n\t - ASSASSIN - \n"); break;
        default : break;
    }
    for(i=0; i<NB_CPT; i++){
        printf("cpt n°%d : destruction...", i);
        if((*arbre)->competence[i]->obj_necessaires->objet != NULL){
            free((*arbre)->competence[i]->obj_necessaires->objet);
            (*arbre)->competence[i]->obj_necessaires->objet = NULL;
        }
        else{
            printf("Erreur de free : objet déjà désalloué ou non alloué.\n");
            return 0;
        }
        if((*arbre)->competence[i]->obj_necessaires->nb != NULL){
            free((*arbre)->competence[i]->obj_necessaires->nb);
            (*arbre)->competence[i]->obj_necessaires->nb = NULL;
        }
        else{
            printf("Erreur de free : nb_objet déjà désalloué ou non alloué.\n");
            return 0;
        }
        if((*arbre)->competence[i]->obj_necessaires != NULL){
            free((*arbre)->competence[i]->obj_necessaires);
            (*arbre)->competence[i]->obj_necessaires = NULL;
        }
        else{
            printf("Erreur de free : objet_necessaires déjà désalloué ou non alloué.\n");
            return 0;
        }

        if((*arbre)->competence[i]->name_img != NULL){
            free((*arbre)->competence[i]->name_img);
            (*arbre)->competence[i]->name_img=NULL;
        }
        if((*arbre)->competence[i]->nb_prec>0){
            free((*arbre)->competence[i]->precedentes);
            (*arbre)->competence[i]->precedentes=NULL;
        }

        if((*arbre)->competence[i]->nb_suiv>0){
            free((*arbre)->competence[i]->suivantes);
            (*arbre)->competence[i]->suivantes=NULL;
        }
        printf("...OK\n");
    }

    free((*arbre)->competence);
    (*arbre)->competence = NULL;
    free(*arbre);
    *arbre = NULL;

    return 0;
}


int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse){
    (*arbre) = malloc(sizeof(t_arbre));
    (*arbre)->classe = typeClasse;
    (*arbre)->competence = malloc(sizeof(t_competence*)*NB_CPT);
    printf("initialisation des pointeurs sur compétences\n");
    for(int i=0; i<NB_CPT; i++){
        (*arbre)->competence[i] = &competences[i];
    }
    printf("initialisation des compétences\n");
    init_competences((*arbre)->competence, (*arbre)->classe);

    return 0;
}

int one_preced_cpt_debloq(t_competence * competence){
    int i;
    if(competence->nb_prec == 0){
        return 1;
    }
    for(i=0; i<competence->nb_prec; i++){
        if(competence->precedentes[i]->competence_acquise == acquis){
            return 1;
        }
        i++;
    }
    return 0;
   
}

int peut_deploquer_cpt(entite_t * personnage, t_competence * competence){
    int i, ind_obj;
    if(competence->competence_acquise == non_acquis && one_preced_cpt_debloq(competence)){
        for(i=0; i<competence->taille_tab_obj_nec; i++){
            ind_obj = acces_obj(competence->obj_necessaires->objet[i].nom);
            printf("Nb %s inventaire : %d\n", personnage->inventaire->objet[ind_obj].nom, personnage->inventaire->nb[ind_obj]);
            printf("Nb %s necessaires : %d\n", competence->obj_necessaires->objet[i].nom, competence->obj_necessaires->nb[i]);
            if(competence->obj_necessaires->nb[i] > personnage->inventaire->nb[ind_obj]){
                return -2;      //pas assez de ressource dans l'inventaire
            }
        }
        return 1;   //compétence déblocable
    }
    else if(competence->competence_acquise != non_acquis){ //la compétence est déja acquise.
        return 0;
    }
    else{   //Aucune des compétences précédentes n'est acquise.
        return -1;
    }
}

int competence_debloquer(entite_t * personnage, t_competence * competence){
    int ind_obj, i;

    if(peut_deploquer_cpt(personnage, competence) == 1){
        printf("Compétence déblocable !\n");
        changer_nomImgCpt(competence);
        personnage->degats *= competence->buff.buff_degat;
        personnage->vie *= competence->buff.buff_vie;
        personnage->vitesse_att *= competence->buff.buff_vit_att;
        personnage->vitesse_depl *= competence->buff.buff_vit_depl;
        personnage->perim_detect += competence->buff.perim_detect-1;
        for(i=0; i<competence->taille_tab_obj_nec; i++){
            ind_obj = acces_obj(competence->obj_necessaires->objet[i].nom);
            personnage->inventaire->nb[ind_obj] -= competence->obj_necessaires->nb[i];
        }
        competence->competence_acquise = acquis;
        return 1;
    }
    else if(!peut_deploquer_cpt(personnage, competence)){
        printf("Compétence non déblocable : déjà acquise !\n");
    }
    else if(peut_deploquer_cpt(personnage, competence) == -1){
        printf("Compétence non déblocable : Aucune compétence précédente n'est acquise !\n");
    }
    else if(peut_deploquer_cpt(personnage, competence) == -2){
        printf("Compétence non déblocable : nombre de ressources nécessaire insuffisant !\n");
    }
    else{
        printf("Compétence non déblocable : raison inconnue !\n");
    }
    return 0;
}

int main(){
    t_arbre * mage;
    
    entite_t * personnage;
    personnage = creer_personnage(personnage);
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
        personnage->inventaire->nb[rang] = 10;
        printf("ressource ajoutée!\n");
    }

    afficher_inventaire(personnage);
    printf("Après affichage inv\n");
    competence_debloquer(personnage, personnage->arbre->competence[0]);
    competence_debloquer(personnage, personnage->arbre->competence[1]);

    aff_classe(personnage->arbre);

    afficher_entite(personnage);

    afficher_inventaire(personnage);
    detruire_arbre(&personnage->arbre);
    detruire_entitee(personnage);
}