#include <stdio.h>
#include <stdlib.h>
#include "../head/attaques.h"

void maj_proj(entite_t * posPers, t_salle * map){
    projectile_t * tmp = NULL;
    int x_cour,y_cour;
    int PROJ_TIREUR;
    switch(posPers->arbre->classe){
        case ARCHER: PROJ_TIREUR = PROJ_FLECHE; break;
        case MAGE: PROJ_TIREUR = PROJ_BOULE; break;
    }
    en_tete_proj();
    while(!liste_vide_proj() && !hors_liste_proj()){
        /*Traitement element courant*/
        tmp = ec->proj;
        int id_tile;
        calcul_position(tmp); //On calcul la nouvelle position d'un projectile
        x_cour = tmp->xp;
        y_cour = tmp->yp;

        while(tmp != NULL && (x_cour != (tmp->x) || y_cour != (tmp->y)) && valide(x_cour, y_cour)){
            if((id_tile = map->dim[tmp->x][tmp->y]) >= 10){
                tmp->touche = true;
                if(degats(tmp->degats, id_tile, map)){
                    looter(map->mob[id_tile - 10], posPers);
                    detruire_mob(&(map->mob[id_tile-10]));
                    map->mob[(map->dim[tmp->x][tmp->y])] = NULL;
                    map->dim[tmp->x][tmp->y] = VIDE;

                }
            }else if(id_tile != VIDE){
                tmp->touche = true;
            }else{
                map->dim[tmp->x][tmp->y] = PROJ_TIREUR;
            }
            if(!(tmp->portee) || tmp->touche){
                detruire_projectiles(&tmp);
                oter_elt_proj();
            }
            if(tmp != NULL){
                switch(tmp->dir){
                    case HAUT: y_cour--; break;
                    case DROITE: x_cour++; break;
                    case BAS: y_cour++; break;
                    case GAUCHE: x_cour--; break;
                }
            }
        }
    suivant_proj();
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
    en_tete_proj();
    ajout_droit_proj(proj);
}

bool degats(int degats, int id_mob, t_salle * map){
    if(id_mob == MARCHAND){
        return false;
    }
    (map->mob[id_mob - 10]->vie) -= degats;
    if((map->mob[id_mob - 10]->vie) <= 0)
        return true;
    return false;
}

void attaque_cac(proj_t typeproj, entite_t * pers, t_salle * map){
    int xe = pers->x;
    int ye = pers->y;
    int id_tile;

    switch(pers->dir){
        case HAUT: ye--; break;
        case DROITE: xe++; break;
        case BAS: ye++; break;
        case GAUCHE: xe--; break;
        default: fprintf(stderr,"Erreur direction de personnage invalide\n");return; 
    }

    if((id_tile = map->dim[xe][ye]) >= 10){
        if(degats(pers->degats, id_tile, map)){
                    looter(map->mob[id_tile - 10], pers);
                    detruire_mob(&(map->mob[id_tile-10]));
                    map->mob[(map->dim[xe][ye])] = NULL;
                    map->dim[xe][ye] = VIDE;
        }
    }
}