#ifndef __MAPSTRUCT__
#define __MAPSTRUCT__

#define SALLE_UNUSED -1
#include "entite.h"
#include "objet.h"

#define VIDE 0
#define MUR 1
#define PORTE 2
#define OBSTACLE 3
#define PILIER 4
// Mob entre 10 et 21
#define DIM_ETAGE 5
#define DIM_SALLE 25

#define LARG_SALLE_BOSS 35
#define LONG_SALLE_BOSS 25

#define LONG_MARCHAND 8
#define LARG_MARCHAND 12

#define LARG_COULOIR 7
#define LONG_COULOIR 15

#define MOB_MAX 10


/**
 * @file mapStruct.h
 * @brief Définition des structures de données pour la map
 * 
*/

/**
 * \enum t_statut
 * \brief Définition des différents statuts d'une salle
 * 
*/
typedef enum {COMMON, //!< Salle commune
                START, //!< Salle de départ
                EXIT //!< Salle de sortie
                } t_statut; 

/**
 * \struct position
 * \brief Définition d'une position
 * 
*/
typedef struct position{
    int x, y; //!< Coordonnées de la position
} t_pos;

/**
 * \struct salle
 * \brief Définition d'une salle avec ses dimensions, son numéro, son nombre de portes et de mobs et son statut
 * 
*/
typedef struct salle {
    int nb_mobs; //!< Nombre de mobs dans la salle
    int num_salle; //!< Numéro de la salle
    int nb_porte; //!< Nombre de portes dans la salle
    int dim[LARG_SALLE_BOSS][LONG_SALLE_BOSS]; //!< Tableau de la salle
    t_statut statut; //!< Statut de la salle
    entite_t* mob[20]; //!< Tableau de mobs dans la salle
} t_salle;

typedef struct salle_boss {
    int dim[LARG_SALLE_BOSS][LONG_SALLE_BOSS]; //!< Tableau de la salle
} t_salle_boss;

/**
 * \struct etage
 * \brief Définition d'un étage avec son nombre de salles et ses salles
 * 
*/
typedef struct etage {
    int nb_salle; //!< Nombre de salles dans l'étage
    t_salle etage[DIM_ETAGE][DIM_ETAGE];//!< Tableau de salles
    t_salle* Boss;
    t_salle* Marchand;
    int boss; //!< Salle du boss déverouillée ou pas (1 ou 0)
    int marchand;
} t_etage;

/**
 * \struct niveau
 * \brief Définition d'un niveau avec ses étages
 * 
*/
typedef struct niveau {
    t_etage etages[3];  //!< 3 etages par niveau
} t_niv;

/* Erreurs */
#define OK 0 //!< Pas d'erreur
#define ERR_CREA_MAP 100 //!< Erreur de création de la map


// Structure de données pour les boutons


/* Fonctions  */

void afficher_salle(t_salle salle);

int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]);

t_pos trouverSalle(int num_salle, t_etage * etage);

int nb_lieu_libre(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]);

int nbVoisin(int x, int y, t_etage * etage);

int genererSalle(int x_salle, int y_salle, t_etage * etage);

int etageConforme(t_etage * etage);

int genererEtage(t_etage * etage);

int genererNiv(t_niv * niveau);

int detruireNiv(t_niv ** niveau);



#endif
