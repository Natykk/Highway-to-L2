#include <stdio.h>
#include <stdlib.h>

#include <./head/projectile.h>
#include <./head/mapStruct.h>

void init_liste_proj(void){
//Cree la liste constitue du seul drapeau
    drapeau = malloc(sizeof(t_element));
    drapeau->pred = drapeau;
    drapeau->succ = drapeau;
    ec = drapeau;
}

int liste_vide_proj(void){
    return (drapeau->succ == drapeau);
}

int hors_liste_proj(void){
    return (ec == drapeau);
}

void en_tete_proj(void){
    if(!liste_vide_proj())
        ec = drapeau->succ;
}

void en_queue_proj(void){
    if(!liste_vide_proj())
        ec = drapeau->pred;
}

void precedent_proj(void){
    if(!liste_vide_proj())
        ec = ec->pred;
}

void suivant_proj(void){
    if(!liste_vide_proj())
        ec = ec->succ;
}

void valeur_elt_proj(projectile_t ** proj){
    if(!liste_vide_proj())
        (*proj) = ec->proj;
}

void modif_elt_proj(projectile_t * proj){
    if(!hors_liste_proj())
        ec->proj = proj;
}

void oter_elt_proj(void){
    t_element * old;

    if(!hors_liste_proj()){
        old = ec;
        ec->pred->succ = ec->succ;
        ec->succ->pred = ec->pred;
        ec=ec->pred;
        old->proj = NULL;
        free(old);
    }

}

void ajout_droit_proj(projectile_t * proj){
    t_element * nouv;

    if(!hors_liste_proj() || liste_vide_proj()){
        nouv = malloc(sizeof(t_element));
        nouv->proj=proj;
        //Chainage nouv
        nouv->pred=ec;
        nouv->succ=ec->succ;
        //Chainage autour
        ec->succ->pred = nouv;
        ec->succ = nouv;
        
        ec=nouv;
    } 
}

void ajout_gauche_proj(projectile_t * proj){
    t_element * nouv;

    if(!hors_liste_proj() || liste_vide_proj()){
        nouv = malloc(sizeof(t_element));
        nouv->proj=proj;
        //Chainage nouv
        nouv->succ=ec;
        nouv->pred=ec->pred;
        //Chainage autour
        ec->pred->succ = nouv;
        ec->pred = nouv;
        
        ec=nouv;
    }
}


/*Statistiques des projectiles*/
#define NB_PROJ 2
stat_proj_t tab_stat_proj[NB_PROJ] = {
    {2.0, 4}, /*FLECHE*/
    {1.5, 6}  /*BOULE*/
};
/*------------------------*/

int valide(int x, int y){
    return (x >= 0 && x<= LARG_SALLE_BOSS) && (y >= 0 && y <= LONG_SALLE_BOSS);
}

projectile_t * creer_projectiles(proj_t type){
    projectile_t * nouv = malloc(sizeof(projectile_t));
    switch(type){
        case FLECHE:
            nouv->vitesse_depl = tab_stat_proj[FLECHE].vitesse_depl;
            nouv->portee = tab_stat_proj[FLECHE].porte;
            break;
        case BOULE:
            nouv->vitesse_depl = tab_stat_proj[BOULE].vitesse_depl;
            nouv->portee = tab_stat_proj[BOULE].porte;
            break;
    }
    return nouv;
}

void detruire_projectiles(projectile_t ** proj){
    free((*proj));
    (*proj) = NULL;
}

void calcul_position(projectile_t * proj){
    /*On calcule les nouvelles coordonnées*/
    proj->xp = proj->x;
    proj->yp = proj->y;
    switch(proj->dir){
        case HAUT:
            proj->y -= proj->vitesse_depl;
            break;
        case DROITE:
            proj->x += proj->vitesse_depl;
            break;
        case BAS:
            proj->y += proj->vitesse_depl;
            break;
        case GAUCHE:
            proj->x -= proj->vitesse_depl;
            break;
    }
    proj->portee -= proj->vitesse_depl;
}