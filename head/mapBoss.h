#ifndef __MAPBOSS__
#define __MAPBOSS__

#include "mapStruct.h"
/**
 * \file mapBoss.h
 * \brief Fichier contenant les prototypes de fonctions pour la gestion des salles boss
*/

/* Prototype des fonctions */
/**
 * \fn t_salle * genererSalleBoss(t_salle * salleBoss)
 * \brief Fonction qui génère une salle boss
 * \param salleBoss Pointeur sur la salle boss
 * \return Pointeur sur la salle boss
*/
t_salle * genererSalleBoss(t_salle * salleBoss);
/**
 * \fn void afficher_salle_boss(t_salle * salle)
 * \brief Fonction qui affiche la salle boss
 * \param salle Pointeur sur la salle boss
*/
void afficher_salle_boss(t_salle * salle);
/**
 * \fn void detruireSalleBoss(t_salle ** salleBoss)
 * \brief Fonction qui détruit la salle boss
 * \param salleBoss Pointeur sur le pointeur de la salle boss
*/
void detruireSalleBoss(t_salle ** salleBoss);
/**
 * \fn t_salle * genererSalleMarchand(t_salle * salleMarchand)
 * \brief Fonction qui génère une salle marchand
 * \param salleMarchand Pointeur sur la salle marchand
 * \return Pointeur sur la salle marchand
*/
t_salle * genererSalleMarchand(t_salle * salleMarchand);

#endif