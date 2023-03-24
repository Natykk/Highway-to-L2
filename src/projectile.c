#include <stdio.h>
#include <stdlib.h>
#include <../head/projectile.h>



/*Statistiques des projectiles*/
#define NB_PROJ 2
stat_proj_t tab_stat_proj[NB_PROJ] = {
    {2.0, 4}, /*FLECHE*/
    {1.5, 6}  /*BOULE*/
};
/*------------------------*/



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