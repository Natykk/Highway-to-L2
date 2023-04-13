#ifndef __INVENTAIRE__
#define __INVENTAIRE__

#include "entite.h"
/**
 * \file inventaire.h
 * \brief Fichier contenant les prototypes de fonctions pour la gestion des inventaires
*/
/**
 * \fn void looter(entite_t * monstre, entite_t * personnage)
 * \brief Fonction qui permet de looter un monstre
 * \param source Pointeur sur l'entité du monstre
 * \param cible Pointeur sur l'entité du joueur
 * 
*/
void looter(entite_t *, entite_t * );
/**
 * \fn entite_t* init_inventaire_monstre(entite_t * monstre)
 * \brief Fonction qui initialise l'inventaire d'un monstre
 * \param monstre Pointeur sur l'entité du monstre
 * \return Pointeur sur l'entité du monstre
*/
entite_t* init_inventaire_monstre(entite_t * );

/**
 * \fn entite_t* init_inventaire_personnage(entite_t * personnage)
 * \brief Fonction qui initialise l'inventaire du joueur
 * \param personnage Pointeur sur l'entité du joueur
 * \return Pointeur sur l'entité du joueur
*/
entite_t* init_inventaire_personnage(entite_t * );

/**
 * \fn void afficher_inventaire(entite_t * personnage)
 * \brief Fonction qui affiche l'inventaire du joueur
 * \param personnage Pointeur sur l'entité du joueur
*/
void afficher_inventaire(entite_t *);

#endif