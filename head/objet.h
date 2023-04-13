#ifndef __OBJET__
#define __OBJET__

#include "objet_inv.h"

#define NB_OBJET 17

/**
 * @file objet.h
 * @brief Fichier contenant toutes les structutes de données liées aux objets
 * @author GEORGET Rémy, GALLAIS Mathéo
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * @brief Tableau qui réference tous les objets du jeu
 */
extern 
objet_t tab_objet[NB_OBJET]; //<! Tableau qui réference tous les objets du jeu

/**
 * \fn void afficher_objet(objet_inv_t*)
 * \brief Fonction qui affiche les informations d'un objet
 * \param objet Pointeur sur l'objet à afficher
 * 
*/
void afficher_objet(objet_inv_t*);
/**
 * \fn int acces_obj(char*)
 * \brief Fonction qui donne la place d'un objet dans le tableau tab_objet selon sont nom
 * \param nom Nom de l'objet
 * \return La place de l'objet dans le tableau tab_objet
*/
int acces_obj(char*);

#endif
