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
    char* nom; //<! Nom de l'entite
    int vie;   //<! Vie de l'entite
    int degats; //<! Degats de l'entite
    int vitesse_att; //<! Vitesse d'attaque de l'entite
    int vitesse_depl; //<! Vitesse de deplacement de l'entite
    int perim_detect; //<! Perimetre de detection de l'entite
    int x; //<! Coordonnée x de l'entite
    int y; //<! Coordonnée y de l'entite
    t_arbre * arbre; //<! Arbre de compétence de l'entite
    objet_inv_t * inventaire;  //<! Inventaire de l'entite
    int place_inv; //<! Nombre de Place dans l'inventaire de l'entite
    int persoOuMob;  //<! 0 si c'est un personnage, 1 si c'est un mob
    t_dir dir; //<! Direction de l'entite
}entite_t;


/**
 * @brief Tableau qui réference tout les mobs du jeu avec leurs stats de base
 */
extern 
entite_t tab_mob[NB_MOBS]; //<! Tableau qui réference tout les mobs du jeu avec leurs stats de base

extern  
entite_t tab_boss[NB_BOSS]; //<! Tableau qui réference tout les boss du jeu avec leurs stats de base

/**
 * \fn void afficher_entite(entite_t*)
 * \brief Fonction qui affiche les informations d'une entite
 * \param entite Pointeur sur l'entite à afficher
 * 
*/
extern void afficher_entite(entite_t *);

/**
 * \fn int acces_mob(char*)
 * \brief Fonction qui donne la place d'un mob dans le tableau tab_mob selon sont nom
 * \param nom Nom du mob
 * \return La place du mob dans le tableau tab_mob
*/
extern int acces_mob(char*);

/**
 * \fn int acces_boss(char*)
 * \brief Fonction qui donne la place d'un boss dans le tableau tab_boss selon sont nom
 * \param nom Nom du boss
 * \return La place du boss dans le tableau tab_boss
*/
extern int acces_boss(char*); 

/**
 * \fn void afficher_inventaire(entite_t*)
 * \brief Fonction qui affiche l'inventaire d'une entite
 * \param entite Pointeur sur l'entite dont on veut afficher l'inventaire
 * 
*/
extern entite_t * creer_personnage(entite_t *);

/**
 * \fn entite_t * creer_monstre(entite_t *, char *)
 * \brief Fonction qui crée un mob
 * \param entite Pointeur sur l'entite qui va devenir le mob
 * \param nom Nom du mob
 * \return Pointeur sur l'entite qui est devenue le mob
*/
extern entite_t * creer_monstre(entite_t *, char *);

/**
 * \fn entite_t * creer_boss(entite_t *, char *)
 * \brief Fonction qui crée un boss
 * \param entite Pointeur sur l'entite qui va devenir le boss
 * \param nom Nom du boss
 * \return Pointeur sur l'entite qui est devenue le boss
*/
extern entite_t * creer_boss(entite_t*, char *);


/**
 * \fn void detruire_entite(entite_t **)
 * \brief Fonction qui detruit une entite
 * \param entite Pointeur sur le pointeur sur l'entite à detruire
 * 
*/
extern void detruire_entitee(entite_t **);

/**
 * \fn void detruire_personnage(entite_t **)
 * \brief Fonction qui detruit un personnage
 * \param entite Pointeur sur le pointeur sur le personnage à detruire
 * 
*/
extern void detruire_personnage(entite_t **);
/**
 * \fn void detruire_mob(entite_t **)
 * \brief Fonction qui detruit un mob
 * \param entite Pointeur sur le pointeur sur le mob à detruire
*/
extern void detruire_mob(entite_t **);

/**
 * \fn void detruire_boss(entite_t **)
 * \brief Fonction qui detruit un boss
 * \param entite Pointeur sur le pointeur sur le boss à detruire
*/
extern void detruire_boss(entite_t**);

#endif