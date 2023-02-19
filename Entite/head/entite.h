#ifndef __OBJET_H__
#define __OBJET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objet.h"

#define NB_MOBS 12

/**
 * @file entite.h
 * @brief Fichier d'en-tete pour les primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * @struct entite_t
 * @brief Structure qui genere les entitées 
 * Caracteristiques : 
 * - Nom 
 * - Vie
 * - Dégats
 * - Vitesse d'attaque
 * - Vitesse de déplacement 
 * - Les coordonnées x et y 
 */
typedef struct entite_s {
    char* nom;
    int vie;    
    float degats;
    float vitesse_att;
    float vitesse_depl;
    int x;
    int y;
    objet_inv_t * inventaire;
    int place_inv;
}entite_t;


/**
 * @brief Tableau qui réference tout les mobs du jeu avec leurs stats de base
 */
extern 
entite_t tab_mob[NB_MOBS];

void afficher_entite(entite_t *);
int acces_mob(char*);
entite_t * creer_personnage(entite_t *);
entite_t * creer_monstre(entite_t *, char *);
void detruire_entitee(entite_t *);

#endif 