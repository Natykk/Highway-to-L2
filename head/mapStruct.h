#ifndef __MAPSTRUCT__
#define __MAPSTRUCT__

#define SALLE_UNUSED -1
#include "entite.h"
#include "objet.h"

#define VIDE 0 //<! Case vide
#define MUR 1 //<! Case Mur
#define PORTE 2 //<! Case Porte
#define OBSTACLE 3 //<! Case Obstacle
#define PILIER 4 //<! Case Piliers
#define PERSO 5 //<! Case Personnage
// Mob entre 10 et 21
#define MARCHAND 31 //<! Case Marchand
#define BOSS 69  //<! Case Boss
#define PROJ_FLECHE_H 70 //<! Case Projectile fleche vers le haut
#define PROJ_FLECHE_D 71 //<! Case Projectile fleche vers la droite
#define PROJ_FLECHE_B 72 //<! Case Projectile fleche vers le bas
#define PROJ_FLECHE_G 73 //<! Case Projectile fleche vers la gauche
#define PROJ_BOULE_H 80 //<! Case Projectile boule vers le haut
#define PROJ_BOULE_D 81  //<! Case Projectile boule vers la droite
#define PROJ_BOULE_B 82 //<! Case Projectile boule vers le bas
#define PROJ_BOULE_G 83 //<! Case Projectile boule vers la gauche

#define DIM_ETAGE 5 //<! Dimension d'un étage
#define DIM_SALLE 25 //<! Dimension d'une salle
 
#define LARG_SALLE_BOSS 35 //<! Largeur d'une salle de boss
#define LONG_SALLE_BOSS 25 //<! Longueur d'une salle de boss

#define LONG_MARCHAND 8 //<! Longueur d'une salle de marchand
#define LARG_MARCHAND 12 //<! Largeur d'une salle de marchand

#define LARG_COULOIR 7 //<! Largeur d'un couloir
#define LONG_COULOIR 15 //<! Longueur d'un couloir

#define MOB_MAX 10 //<! Nombre de mob maximum dans une salle
extern int NumEtage;

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
/**
 * \fn void afficher_salle(t_salle salle)
 * \brief Affiche une salle
 * \param salle Salle à afficher
 * 
*/
void afficher_salle(t_salle salle);
/**
 * \fn int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE])
 * \brief Vérifie si une salle est disponible
 * \param x Coordonnée x de la salle
 * \param y Coordonnée y de la salle
 * \param etage Etage dans lequel se trouve la salle
 * \return 1 si la salle est disponible, 0 sinon
*/
int salle_disponible(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]);
/**
 * \fn t_pos trouverSalle(int num_salle, t_etage * etage)
 * \brief Trouve une salle dans un étage
 * \param num_salle Numéro de la salle à trouver
 * \param etage Etage dans lequel se trouve la salle
 * 
 * \return Position de la salle trouvée 
*/
t_pos trouverSalle(int num_salle, t_etage * etage);
/**
 * \fn int nb_lieu_libre(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE])
 * \brief Compte le nombre de salle libre autour des coordonnées x et y
 * 
 * \param x Coordonnée x
 * \param y Coordonnée y 
 * \param etage Etage dans lequel chercher
 * 
 * \return Nombre de salle libre autour des coordonnées x et y
*/
int nb_lieu_libre(int x, int y, t_salle etage[DIM_ETAGE][DIM_ETAGE]);
/**
 * \fn int nbVoisin(int x, int y, t_etage * etage)
 * \brief Compte le nombre de voisins d'une salle
 * \param x Coordonnée x
 * \param y Coordonnée y
 * \param etage Etage dans lequel chercher
 * 
 * \return Nombre de voisins de la salle
*/
int nbVoisin(int x, int y, t_etage * etage);

/**
 * \fn int genererSalle(int x_salle, int y_salle, t_etage * etage)
 * \brief Génère une salle
 * \param x_salle Coordonnée x de la salle
 * \param y_salle Coordonnée y de la salle
 * \param etage Etage dans lequel se trouve la salle
 * 
 * \return 1 si la génération s'est bien passée, 0 sinon
*/
int genererSalle(int x_salle, int y_salle, t_etage * etage);

/**
 * \fn int genererCouloir(int x_salle, int y_salle, t_etage * etage)
 * \brief Génère un couloir
 * \param x_salle Coordonnée x de la salle
 * \param y_salle Coordonnée y de la salle
 * \param etage Etage dans lequel se trouve la salle
 * 
 * \return 1 si la génération s'est bien passée, 0 sinon
*/
int etageConforme(t_etage * etage);

/**
 * \fn int genererEtage(t_etage * etage)
 * \brief Génère un étage
 * \param etage Etage à générer
 * \return 1 si la génération s'est bien passée, 0 sinon
*/
int genererEtage(t_etage * etage);

/**
 * \fn int genererNiv(t_niv * niveau)
 * \brief Génère un niveau
 * \param niveau Niveau à générer
 * \return 1 si la génération s'est bien passée, 0 sinon
*/
int genererNiv(t_niv * niveau);

/**
 * \fn int detruireNiv(t_niv ** niveau)
 * \brief Détruit un niveau
 * \param niveau Niveau à détruire
 * \return 1 si la destruction s'est bien passée, 0 sinon
*/
int detruireNiv(t_niv ** niveau);



#endif
