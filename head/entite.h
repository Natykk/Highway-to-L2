#ifndef __ENTITE__
#define __ENTITE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objet.h"
#include "competence.h"
#include "arbre.h"

#define NB_MOBS 12

/**
 * @file entite.h
 * @brief Fichier d'en-tete pour les primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * \enum t_dir
 * \brief Définition des directions
 *
 * 
*/
typedef enum{AUCUN=-1, //!< Aucune direction
                HAUT, //!< Haut
                DROITE, //!< Droite
                BAS, //!< Bas
                GAUCHE} t_dir; //!< Gauche
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
    float vie;    
    float degats;
    float vitesse_att;
    float vitesse_depl;
    int perim_detect;
    int x;
    int y;
    t_arbre * arbre;
    objet_inv_t * inventaire;
    int place_inv;
    int persoOuMob;
    t_dir dir;
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
void looter(entite_t *, entite_t * );
entite_t* init_inventaire_monstre(entite_t * );
entite_t* init_inventaire_personnage(entite_t * );
void afficher_inventaire(entite_t *);
#endif 