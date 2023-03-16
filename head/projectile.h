#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum{AUCUN=-1, //!< Aucune direction
                HAUT, //!< Haut
                DROITE, //!< Droite
                BAS, //!< Bas
                GAUCHE} t_dir; //!< Gauche

typedef enum proj_s{FLECHE, BOULE, AUCUN}proj_t;

typedef struct stat_proj_s{
    float vitesse_depl;
    int porte;
}stat_proj_t;

typedef struct projectile_s{
    float vitesse_depl;
    int porte;
    float degats;
    bool touche = false;
    int x = 0;
    int y = 0;
    t_dir dir = AUCUN;
}projectile_t;

projectile_t * creer_projectiles(projectile,proj_t type);
void detruire_projectiles(projectile_t ** proj);
bool calcul_position(projectile_t * proj);