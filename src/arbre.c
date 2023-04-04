#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../head/arbre.h"
#include "../head/inventaire.h"

/**
 * \fn void aff_classe (t_arbre * arbre)
 * \brief Affiche la classe de l'arbre
 * \param arbre : arbre dont on veut afficher la classe
 * \return void
*/
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
/**
 * \fn int detruire_arbre(t_arbre ** arbre)
 * \brief Désalloue la mémoire de l'arbre
 * \param arbre : arbre dont on veut désallouer la mémoire
 * \return 0 si tout s'est bien passé, 1 sinon
*/
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

/**
 * \fn ini init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse)
 * \brief Initialise l'arbre de compétences
 * \param arbre : arbre à initialiser
 * \param competences : tableau de compétences
 * \param typeClasse : type de classe de l'arbre
 * \return 0 si tout s'est bien passé, 1 sinon
 */
int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse){
    (*arbre) = malloc(sizeof(t_arbre));
    (*arbre)->classe = typeClasse;
    (*arbre)->competence = malloc(sizeof(t_competence*)*NB_CPT);
    (*arbre)->etages[0] = non_acquis;
    (*arbre)->etages[1] = non_acquis;
    (*arbre)->etages[2] = non_acquis;
    (*arbre)->etages[3] = non_acquis;
    (*arbre)->etages[4] = non_acquis;
    for(int i=0; i<NB_CPT; i++){
        (*arbre)->competence[i] = &competences[i];
    }
    init_competences((*arbre)->competence, (*arbre)->classe);

    return 0;
}
/**
 * \fn int one_preced_cpt_debloq(t_competence * competence)
 * \brief Vérifie si une compétence a au moins une compétence précédente débloquée
 * \param competence : compétence dont on veut vérifier les précédentes
 * \return 1 si au moins une compétence précédente est débloquée, 0 sinon
*/
int one_preced_cpt_debloq(t_competence * competence){
    int i;
    if(competence->nb_prec == 0){
        return 1;
    }
    for(i=0; i<competence->nb_prec; i++){
        if(competence->precedentes[i]->competence_acquise == acquis){
            return 1;
        }
    }
    return 0;
   
}
/**
 * \fn int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence)
 * \brief Vérifie si une compétence est dans l'arbre du joueur
 * \param personnage : personnage dont on veut vérifier l'arbre
 * \param competence : compétence dont on veut vérifier l'appartenance à l'arbre
 * \return 1 si la compétence est dans l'arbre du joueur, 0 sinon
*/
int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence){
    if(personnage->arbre != NULL){
        for(int i=0; i<NB_CPT; i++){
            if(personnage->arbre->competence[i] == competence){
                return 1;
            }
        }
    }
    return 0;
}
/**
 * \fn int peut_debloquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt)
 * \brief Vérifie si une compétence peut être débloquée
 * \param personnage : personnage dont on veut vérifier l'arbre
 * \param competence : compétence dont on veut vérifier la possibilité de déblocage
 * \param arbre_cpt : arbre de compétences du joueur
 * \return 1 si la compétence peut être débloquée, 0 sinon
*/
int peut_deploquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt){
    int i, ind_obj;
    
    if(competence->competence_acquise == non_acquis && one_preced_cpt_debloq(competence) && cpt_in_arbre_joueur(personnage, competence) && arbre_cpt->etages[competence->etage-1] == non_acquis){
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
    else if(!cpt_in_arbre_joueur(personnage, competence)){
        return -3;  //compétence d'un autre arbre
    }
    else if(competence->competence_acquise != non_acquis){ //la compétence est déja acquise.
        return 0;
    }
    else if(!one_preced_cpt_debloq(competence)){   //Aucune des compétences précédentes n'est acquise.
        return -1;
    }
    else if(arbre_cpt->etages[competence->etage-1] != non_acquis){
        return -5;
    }
    else{
        return -4;
    }
}
/**
 * \fn int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt)
 * \brief Débloque une compétence
 * \param personnage : personnage dont on veut débloquer la compétence
 * \param competence : compétence à débloquer
 * \param arbre_cpt : arbre de compétences du joueur
 * \return 0 si la compétence a été débloquée, -1 si la compétence n'a pas pu être débloquée (aucune compétence précédente n'est acquise), -2 si la compétence n'a pas pu être débloquée (pas assez de ressources dans l'inventaire), -3 si la compétence n'a pas pu être débloquée (compétence d'un autre arbre), -4 si la compétence n'a pas pu être débloquée (autre raison), -5 si la compétence n'a pas pu être débloquée (étage déjà débloqué)
*/
int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt){
    int ind_obj, i;
    if(arbre_cpt->competence[0] == competence){
        if(personnage->arbre == NULL){
            personnage->arbre = arbre_cpt;
        }
        else{
            return -3;
        }
    }
    if(peut_deploquer_cpt(personnage, competence, arbre_cpt) == 1){
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
        arbre_cpt->etages[competence->etage-1] = acquis;
        return 1;
    }
    else if(!peut_deploquer_cpt(personnage, competence, arbre_cpt)){
        printf("Compétence non déblocable : déjà acquise !\n");
        return 0;
    }
    else if(peut_deploquer_cpt(personnage, competence, arbre_cpt) == -1){
        printf("Compétence non déblocable : Aucune compétence précédente n'est acquise !\n");
        return -1;
    }
    else if(peut_deploquer_cpt(personnage, competence, arbre_cpt) == -2){
        printf("Compétence non déblocable : nombre de ressources nécessaire insuffisant !\n");
        return -2;
    }
    else if(peut_deploquer_cpt(personnage, competence, arbre_cpt) == -3){
        printf("Compétence non déblocable : une compétence de départ d'un autre arbre de compétence a déjà été débloqué !\n");
        return -3;
    }
    else if(peut_deploquer_cpt(personnage, competence, arbre_cpt) == -5){
        printf("Compétence non déblocable : une compétence de même niveau a déjà été débloquée !\n");
        return -5;
    }
    else{
        printf("Compétence non déblocable : raison inconnue !\n");
    }
    return -4;
}

/*
int main(){
    t_arbre * mage;
    t_arbre * guerrier;
    t_arbre * archer;
    t_arbre * assassin;

    entite_t * personnage = creer_personnage(personnage);
    init_inventaire_personnage(personnage);

    for(int i=0; i<NB_OBJET; i++){
        personnage->inventaire->nb[i] = 100;
    }

    init_arbre(&mage, cpt_mage, MAGE);
    init_arbre(&archer, cpt_archer, ARCHER);
    init_arbre(&assassin, cpt_assassin, ASSASSIN);
    init_arbre(&guerrier, cpt_guerrier, GUERRIER);

    competence_debloquer(personnage, mage->competence[0], mage);
    competence_debloquer(personnage, mage->competence[1], mage);
    competence_debloquer(personnage, mage->competence[2], mage);
    competence_debloquer(personnage, mage->competence[3], mage);
    competence_debloquer(personnage, mage->competence[4], mage);
    competence_debloquer(personnage, mage->competence[5], mage);
    competence_debloquer(personnage, mage->competence[6], mage);
    competence_debloquer(personnage, mage->competence[7], mage);
    competence_debloquer(personnage, mage->competence[8], mage);
    competence_debloquer(personnage, mage->competence[9], mage);

    aff_classe(mage);
}
*/
