#ifndef ATTAQUE_H
#define ATTAQUE_H
/**
 * \file attaque.h
 * \brief Fichier contenant les prototypes de fonctions pour la gestion des attaques
 * 
*/
#include "../head/mapStruct.h"
#include "../head/inventaire.h"
#include "../head/projectile.h"
#include "../head/arbre.h"

/**
 * \fn void maj_proj(entite_t * posPers, t_salle * map)
 * \brief Fonction permettant de mettre à jour les projectiles
 * \param posPers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
*/
extern void maj_proj(entite_t * posPers, t_salle * map);

extern void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map);

extern bool degats(int degats, int id_mob, t_salle * map);

extern void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map);

#endif