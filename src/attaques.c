#include <stdio.h>
#include <stdlib.h>
#include <./head/attaques.h>

void maj_proj(entite_t * posPers, t_salle * map){
    projectile_t * tmp = NULL;
    int x_cour,y_cour;
    en_tete_proj();
    while(!hors_liste_proj()){
        /*Traitement element courant*/
        tmp = ec->proj;
        int id_tile;
        calcul_position(tmp); //On calcul la nouvelle position d'un projectile
        x_cour = tmp->xp;
        y_cour = tmp->yp;
        while(x_cour != (tmp->x) && y_cour != (tmp->y) && valide(x_cour, y_cour)){
            if((id_tile = map->dim[tmp->x][tmp->y]) >= 10){
                tmp->touche = true;
                if(degats(tmp->degats, id_tile, map))
                    looter(map->mob[id_tile - 10], posPers);
            }else if(id_tile != VIDE){
                tmp->touche = true;
            }
            if(!(tmp->portee) || tmp->touche){
                detruire_projectiles(&tmp);
                oter_elt_proj();
            }
            switch(tmp->dir){
                case HAUT: y_cour--; break;
                case DROITE: x_cour++; break;
                case BAS: y_cour++; break;
                case GAUCHE: x_cour--; break;
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