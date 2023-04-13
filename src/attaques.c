#include <stdio.h>
#include <stdlib.h>
#include "../head/attaques.h"
/**
 * \fn void maj_proj(entite_t * posPers, t_salle * map)
 * \brief Fonction permettant de mettre à jour les projectiles
 * \param posPers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
*/
void maj_proj(entite_t *posPers, t_salle *map)
{
    projectile_t *tmp = NULL;
    int x_cour, y_cour;
    int PROJ_TIREUR;
    bool depassement;
    en_tete_proj();
    while (!liste_vide_proj() && !hors_liste_proj())
    {
        /*Traitement element courant*/
        int id_tile;
        tmp = ec->proj;
        calcul_position(tmp); // On calcule la nouvelle position d'un projectile
        x_cour = tmp->xp;
        y_cour = tmp->yp;
        switch (posPers->arbre->classe)
        {
        case ARCHER:
            PROJ_TIREUR = tmp->dir + PROJ_FLECHE_H;
            break;
        case MAGE:
            PROJ_TIREUR = tmp->dir + PROJ_BOULE_B;
            break;
        }

        while (tmp != NULL && !depassement && valide(x_cour, y_cour))
        {
            id_tile = map->dim[x_cour][y_cour];
            if (id_tile > 9 && id_tile < 22)
            {
                tmp->touche = true;
                if (degats(tmp->degats, id_tile, map))
                {
                    looter(map->mob[id_tile - 10], posPers);
                    detruire_mob(&(map->mob[id_tile - 10]));
                    map->mob[(map->dim[x_cour][y_cour])] = NULL;
                    map->dim[x_cour][y_cour] = VIDE;
                }
            }
            else if (id_tile > VIDE && id_tile < PERSO)
            {
                tmp->touche = true;
            }
            if ((tmp->portee) <= 0 || tmp->touche)
            {
                if (map->dim[tmp->xp][tmp->yp] != PERSO)
                    map->dim[tmp->xp][tmp->yp] = VIDE;
                detruire_projectiles(&tmp);
                oter_elt_proj();
            }
            if (tmp != NULL)
            {
                switch (tmp->dir)
                {
                case HAUT:
                    y_cour--;
                    depassement = (y_cour < tmp->y);
                    break;
                case DROITE:
                    x_cour++;
                    depassement = (x_cour > tmp->x);
                    break;
                case BAS:
                    y_cour++;
                    depassement = (y_cour > tmp->y);
                    break;
                case GAUCHE:
                    x_cour--;
                    depassement = (x_cour < tmp->x);
                    break;
                }
            }
        }
        if (tmp != NULL && map->dim[tmp->x][tmp->y] == VIDE)
        {
            map->dim[tmp->x][tmp->y] = PROJ_TIREUR;
        }
        if (tmp != NULL && map->dim[tmp->xp][tmp->yp] != PERSO)
            map->dim[tmp->xp][tmp->yp] = VIDE;
        suivant_proj();
    }
}
/**
 * \fn void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map)
 * \brief Fonction permettant de qui gère un projectile
 * \param typeproj Type de projectile
 * \param posPers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
 * 
*/
void attaque_proj(proj_t typeproj, entite_t *posPers, t_salle *map)
{
    /*On créée le projectile*/
    projectile_t *proj = creer_projectiles(typeproj);
    /*Le projectile part des coordonnées et dans la direction du joueur*/
    proj->x = posPers->x;
    proj->y = posPers->y;
    proj->dir = posPers->dir;
    proj->degats = posPers->degats;
    /*Nouveau projectile courant*/
    en_tete_proj();
    ajout_droit_proj(proj);
}
/**
 * \fn bool degats(int degats, int id_mob, t_salle * map)
 * \brief Fonction permettant de gérer les dégats infligés à un mob
 * \param degats Dégats infligés
 * \param id_mob Identifiant du mob
 * \param map Pointeur sur la salle
 * \return true si le mob est mort, false sinon
*/
bool degats(int degats, int id_mob, t_salle *map)
{
    if (id_mob == MARCHAND)
    {
        return false;
    }
    if (id_mob == BOSS)
    {
        (map->mob[0]->vie) -= degats;
        if ((map->mob[0]->vie) <= 0)
        {
            return true;
        }
    }
    else
    {
        (map->mob[id_mob - 10]->vie) -= degats;
        printf("vie restante : %d", map->mob[id_mob - 10]->vie);
        if ((map->mob[id_mob - 10]->vie) <= 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * \fn void attaque_cac(proj_t typeproj, entite_t *pers, t_salle *map)
 * \brief Fonction permettant de gérer une attaque au corps à corps
 * \param typeproj Type de projectile
 * \param pers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
 * 
*/
void attaque_cac(proj_t typeproj, entite_t *pers, t_salle *map)
{
    int xe = pers->x;
    int ye = pers->y;
    int id_tile;

    switch (pers->dir)
    {
    case HAUT:
        ye--;
        break;
    case DROITE:
        xe++;
        break;
    case BAS:
        ye++;
        break;
    case GAUCHE:
        xe--;
        break;
    default:
        fprintf(stderr, "Erreur direction de personnage invalide\n");
        return;
    }

    if ((id_tile = map->dim[xe][ye]) >= 10)
    {
        if (degats(pers->degats, id_tile, map))
        {
            if (id_tile == BOSS)
            {
                looter(map->mob[0], pers);
                detruire_mob(&(map->mob[0]));
                map->mob[(map->dim[xe][ye])] = NULL;
                map->dim[xe][ye] = VIDE;
            }
            else
            {
                looter(map->mob[id_tile - 10], pers);
                detruire_mob(&(map->mob[id_tile - 10]));
                map->mob[(map->dim[xe][ye])] = NULL;
                map->dim[xe][ye] = VIDE;
            }
        }
    }
}