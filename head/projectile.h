#ifndef PROJ_H
#define PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../head/entite.h"

/**
 * \file proj.h
 * \brief Fichier contenant les prototypes des fonctions de gestion des projectiles
 */


/**
 * \struct projectile_s
 * \brief Structure contenant les informations d'un projectile
*/
typedef struct projectile_s
{
    int vitesse_depl; //<! Vitesse de déplacement du projectile
    int portee; //<! Portée du projectile
    float degats; //<! Dégâts du projectile
    bool touche; //<! Indique si le projectile a touché une cible
    int xp; //<! Position x du projectile
    int yp; //<! Position y du projectile
    int x; //<! Position x du tireur
    int y; //<! Position y du tireur
    t_dir dir; //<! Direction du projectile
} projectile_t;
/**
 * \struct element
 * \brief Structure contenant un pointeur sur un projectile et deux pointeurs sur des éléments de la liste
 * \details Cette structure est utilisée pour la liste chaînée des projectiles
 * 
*/
typedef struct element
{
    projectile_t *proj; //<! Pointeur sur le projectile
    struct element *pred; //<! Pointeur sur l'élément précédent
    struct element *succ; //<! Pointeur sur l'élément suivant
} t_element;

extern t_element * drapeau; //<! Pointeur sur le drapeau de la liste
extern t_element * ec;     //<! Pointeur sur l'élément courant de la liste

/**
 * \enum proj_s
 * \brief Enumération contenant les différents types de projectiles
 * \details Cette énumération est utilisée pour la création des projectiles
*/
typedef enum proj_s
{
    AUCUN_PROJ = -1, //<! Aucun projectile
    FLECHE, //<! Projectile de type flèche
    BOULE //<! Projectile de type boule 
} proj_t;

/**
 * \struct stat_proj_s
 * \brief Structure contenant les statistiques des projectiles
 * \details Cette structure est utilisée pour la création des projectiles
 * 
*/
typedef struct stat_proj_s
{
    int vitesse_depl; //<! Vitesse de déplacement du projectile
    int porte; //<! Portée du projectile
} stat_proj_t;

/**
 * \fn void init_liste_proj(void)
 * \brief Fonction d'initialisation de la liste chaînée des projectiles
 * \details Cette fonction initialise la liste chaînée des projectiles
*/
void init_liste_proj(void);
/**
 * \fn int liste_vide_proj(void)
 * \brief Fonction de vérification de la liste chaînée des projectiles
 * \details Cette fonction vérifie si la liste chaînée des projectiles est vide
 * \return 1 si la liste est vide, 0 sinon
*/
int liste_vide_proj(void);
/**
 * \fn int hors_liste_proj(void)
 * \brief Fonction de vérification de la liste chaînée des projectiles
 * \details Cette fonction vérifie si l'élément courant de la liste chaînée des projectiles est hors de la liste
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
int hors_liste_proj(void);
/**
 * \fn void en_tete_proj(void)
 * \brief Fonction de déplacement de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction déplace l'élément courant de la liste chaînée des projectiles sur le premier élément de la liste
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
void en_tete_proj(void);
/**
 * \fn void en_queue_proj(void)
 * \brief Fonction de déplacement de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction déplace l'élément courant de la liste chaînée des projectiles sur le dernier élément de la liste
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
void en_queue_proj(void);
/**
 * \fn void precedent_proj(void)
 * \brief Fonction de déplacement de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction déplace l'élément courant de la liste chaînée des projectiles sur l'élément précédent
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
void precedent_proj(void);
/**
 * \fn void suivant_proj(void)
 * \brief Fonction de déplacement de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction déplace l'élément courant de la liste chaînée des projectiles sur l'élément suivant
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
void suivant_proj(void);
/**
 * \fn void valeur_elt_proj(projectile_t **)
 * \brief Fonction de récupération de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction récupère l'élément courant de la liste chaînée des projectiles
 * \param proj Pointeur de pointeur sur le projectile
 * \return 1 si l'élément courant est hors de la liste, 0 sinon
*/
void valeur_elt_proj(projectile_t **);
/**
 * \fn void modif_elt_proj(projectile_t *)
 * \brief Fonction de modification de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction modifie l'élément courant de la liste chaînée des projectiles
 * \param proj Pointeur sur le projectile
 * 
*/
void modif_elt_proj(projectile_t *);
/**
 * \fn void oter_elt_proj(void)
 * \brief Fonction de suppression de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction supprime l'élément courant de la liste chaînée des projectiles
 * 
*/
void oter_elt_proj(void);
/**
 * \fn void ajout_droit_proj(projectile_t *)
 * \brief Fonction d'ajout d'un élément à droite de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction ajoute un élément à droite de l'élément courant de la liste chaînée des projectiles
 * \param proj Pointeur sur le projectile
*/
void ajout_droit_proj(projectile_t *);
/**
 * \fn void ajout_gauche_proj(projectile_t *)
 * \brief Fonction d'ajout d'un élément à gauche de l'élément courant de la liste chaînée des projectiles
 * \details Cette fonction ajoute un élément à gauche de l'élément courant de la liste chaînée des projectiles
 * \param proj Pointeur sur le projectile
 * 
*/
void ajout_gauche_proj(projectile_t *);
/**
 * \fn int taille_liste_proj(int x,int y);
 * \brief verifie si les coordonées pointe vers un endroit valide
 * \param x coordonée x
 * \param y coordonée y
 * \return 1 si les coordonées sont valide, 0 sinon
 * 
*/
int valide(int x, int y);
/**
 * \fn projectile_t *creer_projectiles(proj_t type);
 * \brief Fonction de création d'un projectile
 * \details Cette fonction crée un projectile selon le type passé en paramètre
 * \param type Type de projectile à créer
 * \return Pointeur sur le projectile créé
*/
projectile_t *creer_projectiles(proj_t type);
/**
 * \fn void detruire_projectiles(projectile_t **proj);
 * \brief Fonction de destruction d'un projectile
 * \details Cette fonction détruit un projectile
 * \param proj Pointeur de pointeur sur le projectile à détruire
 * 
*/
void detruire_projectiles(projectile_t **proj);
/**
 * \fn void calcul_position(projectile_t *proj);
 * \brief Fonction de calcul de la position d'un projectile
 * \details Cette fonction calcule la position d'un projectile
 * \param proj Pointeur sur le projectile
 * 
*/
void calcul_position(projectile_t *proj);

#endif