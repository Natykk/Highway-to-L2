#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

void maj_proj(){
    en_tete();
    while(ec != drapeau){
        /*Traitement element courant*/
        suivant();
    }
}

void attaque_proj(proj_t typeproj, float degats, float vitesse_att, int x, int y, t_dir dir){
    /*On créer le projectile*/
    projectile_t * proj = creer_projectiles(typeproj, degats, dir);
    /*Le projectile pars des coordonnées et dans la direction du joueur*/
    proj->x = x;
    proj->y = y;
    proj->dir = dir;

    /*Nouveau projectile courant*/
    en_tete();
    ajout_droit(proj);
}

void attaque_cac(proj_t typeproj,float degats, float vitesse_att, int x, int y, t_dir dir);