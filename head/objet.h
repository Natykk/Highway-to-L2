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
objet_t tab_objet[NB_OBJET];

void afficher_objet(objet_inv_t*);
int acces_obj(char*);

#endif
