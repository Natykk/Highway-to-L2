#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

void maj_proj(t_salle * map){
    en_tete();
    projectile_t * tmp;
    while(!hors_liste()){
        /*Traitement element courant*/
        tmp = ec->proj;
        int id_tile;
        if((id_tile = map->dim[tmp->x][tmp->y]) >= 10 || id_tile == VIDE){
            touche = true;
            /*fonction de degats*/
        } /*A FAIRE*/ /*traitemment des degats en fonction de la case (mob, mur, porte, obstacle)*/
        if(!(tmp->porte) || tmp->touche){
            detruire_projectiles(&tmp);
            oter_elt();
        }
        suivant();
    }
}

void attaque_proj(proj_t typeproj, float degats, float vitesse_att, int x, int y, t_dir dir){
    /*On créée le projectile*/
    projectile_t * proj = creer_projectiles(typeproj, degats, dir);
    /*Le projectile part des coordonnées et dans la direction du joueur*/
    proj->x = x;
    proj->y = y;
    proj->dir = dir;
    proj->degats = degats;
    /*Nouveau projectile courant*/
    en_tete();
    ajout_droit(proj);
}

bool degats(float degats, int id_mob);

void attaque_cac(proj_t typeproj,float degats, float vitesse_att, int x, int y, t_dir dir);