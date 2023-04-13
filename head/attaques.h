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

/**
 * \fn void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map)
 * \brief Fonction permettant d'attaquer avec un projectile
 * \param typeproj Type de projectile
 * \param posPers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
*/
extern void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map);


/**
 * \fn bool degats(int degats, int id_mob, t_salle * map)
 * \brief Fonction permettant de faire des dégats à un mob
 * \param degats Dégats à faire
 * \param id_mob ID du mob
 * \param map Pointeur sur la salle
 * \return Booléen
*/
extern bool degats(int degats, int id_mob, t_salle * map);


/**
 * \fn void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map)
 * \brief Fonction permettant d'attaquer au corps à corps
 * \param typeproj Type de projectile
 * \param posPers Pointeur sur la position du personnage
 * \param map Pointeur sur la salle
*/
extern void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map);

#endif