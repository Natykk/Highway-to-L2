#include <stdio.h>
#include <stdlib.h>
#include <../head/projectiles.h>

#define NB_PROJ 2

projectile_t tab_proj[NB_PROJ] = {
    {2.0, 15, AUCUN}, /*FLECHE*/
    {1.5, 12, AUCUN}  /*BOULE*/
};

projectile_t * creer_projectiles(proj_t type, int degats, t_dir dir){
    projectile_t * nouv = malloc(sizeof(projectile_t));
    switch(type){
        case FLECHE:
            nouv->vitesse_depl = tab_proj[FLECHE].vitesse_depl;
            nouv->porte = tab_proj[FLECHE].porte;
            break;
        case BOULE:
            nouv->vitesse_depl = tab_proj[BOULE].vitesse_depl;
            nouv->porte = tab_proj[BOULE].porte;
            break;
    }
    nouv->dir = dir;
    return nouv;
}

void detruire_projectiles(projectile_t ** proj){
    free((*proj));
    (*proj) = NULL;
}