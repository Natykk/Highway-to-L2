#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

void maj_proj(t_salle * map, entite_t * posPers){
    en_tete();
    projectile_t * tmp;
    while(!hors_liste()){
        /*Traitement element courant*/
        tmp = ec->proj;
        int id_tile;
        if((id_tile = map->dim[tmp->x][tmp->y]) >= 10 || id_tile == VIDE){
            touche = true;
            if(degats(ec->proj->degats, id_tile, map))
                looter(map->mob[id_tile - 10], posPers);
        }
        if(!(tmp->porte) || tmp->touche){
            detruire_projectiles(&tmp);
            oter_elt();
        }
        suivant();
    }
}

void attaque_proj(proj_t typeproj, int degats, int x, int y, t_dir dir){
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

bool degats(int degats, int id_mob, t_salle * map){
    (map->mob[id_mob - 10]->vie) -= degats;
    if((map->mob[id_mob - 10]->vie) <= 0)
        return true;
    return false;
}

void attaque_cac(proj_t typeproj, int degats, int x, int y, t_dir dir){
    int xe = x, ye = y;
    switch(dir){
        case HAUT: ye--; break;
        case DROITE: xe++; break;
        case BAS: ye++; break;
        case GAUCHE: xe--; break;
        default: printf("Erreur\n");return; 
    }

    if((id_tile = map->dim[tmp->xe][tmp->ye]) >= 10){
        if(degats(degats, id_tile, map))
                    looter(map->mob[id_tile - 10], posPers);
    }
}