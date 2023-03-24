#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

void maj_proj(entite_t * posPers, t_salle * map){
    en_tete();
    projectile_t * tmp;
    while(!hors_liste()){
        /*Traitement element courant*/
        tmp = ec->proj;
        int id_tile;
        if((id_tile = map->dim[tmp->x][tmp->y]) >= 10 || id_tile == VIDE){
            ec->proj->touche = true;
            if(degats(ec->proj->degats, id_tile, map))
                looter(map->mob[id_tile - 10], posPers);
        }
        if(!(tmp->portee) || tmp->touche){
            detruire_projectiles(&tmp);
            oter_elt();
        }
        suivant();
    }
}

void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map){
    /*On créée le projectile*/
    projectile_t * proj = creer_projectiles(typeproj);
    /*Le projectile part des coordonnées et dans la direction du joueur*/
    proj->x = posPers->x;
    proj->y = posPers->y;
    proj->dir = posPers->dir;
    proj->degats = posPers->degats;
    /*Nouveau projectile courant*/
    en_tete();
    ajout_droit(proj);
}

bool degats(int degats, int id_mob, t_salle * map){
    (map->mob[id_mob - 10]->vie) -= degats;
    if((map->mob[id_mob - 10]->vie) <= 0)
        return true;
    return false;
}

void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map){
    int xe = posPers->x;
    int ye = posPers->y;
    int id_tile;

    switch(posPers->dir){
        case HAUT: ye--; break;
        case DROITE: xe++; break;
        case BAS: ye++; break;
        case GAUCHE: xe--; break;
        default: fprintf(stderr,"Erreur direction de personnage invalide\n");return; 
    }

    if((id_tile = map->dim[xe][ye]) >= 10){
        if(degats(posPers->degats, id_tile, map))
                    looter(map->mob[id_tile - 10], posPers);
    }
}