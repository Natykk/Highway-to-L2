#ifndef __ENTITE__
#define __ENTITE__

#define NB_MOBS 12
#define NB_BOSS 3

#include "objet.h"
typedef struct arbre t_arbre;

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
    int vie;    
    int degats;
    int vitesse_att;
    int vitesse_depl;
    int perim_detect;
    int x;
    int y;
    t_arbre * arbre;
    objet_inv_t * inventaire;
    int place_inv;
    int persoOuMob; // O pour personnage, 1 pour mob, 2 pour boss
    t_dir dir;
}entite_t;


/**
 * @brief Tableau qui réference tout les mobs du jeu avec leurs stats de base
 */
extern 
entite_t tab_mob[NB_MOBS];

extern 
entite_t tab_boss[NB_BOSS];

extern void afficher_entite(entite_t *);
extern int acces_mob(char*);
extern int acces_boss(char*); 

extern entite_t * creer_personnage(entite_t *);
extern entite_t * creer_monstre(entite_t *, char *);
extern entite_t * creer_boss(entite_t*, char *);

extern void detruire_entitee(entite_t **);
extern void detruire_personnage(entite_t **);
extern void detruire_mob(entite_t **);
extern void detruire_boss(entite_t**);

#endif