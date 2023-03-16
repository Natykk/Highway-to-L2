#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

projectile_t ** proj_courant = NULL;
int nb_proj_cour = 0;

void maj_proj(projectile_t ** proj, int nb_proj){
    int i;
    for(i=0; i<nb_proj; i++){
        if(proj[i] == NULL){
            
        }
    }
}

void attaque_proj(proj_t typeproj, float degats, float vitesse_att, int x, int y, t_dir dir){
    /*On créer le projectile*/
    projectile_t * proj = creer_projectiles(typeproj, degats, dir);
    /*Le projectile pars des coordonnées et dans la direction du joeur*/
    proj->x = x;
    proj->y = y;
    proj->dir = dir;

    /*Nouveau projectile courant*/
    nb_proj_cour++;
    int rang = nb_proj_cour - 1;
    proj_courant = realloc(sizeof(projectile_t *)*nb_proj_cour); /*On agrandit le tableau des projectiles courants*/
    proj_courant[rang] = proj; /*On insert le noueau projectile*/
}

void attaque_cac(proj_t typeproj,float degats, float vitesse_att, int x, int y, t_dir dir);