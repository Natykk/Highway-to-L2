#include <stdio.h>
#include <stdlib.h>

typedef enum{AUCUN=-1, //!< Aucune direction
                HAUT, //!< Haut
                DROITE, //!< Droite
                BAS, //!< Bas
                GAUCHE} t_dir; //!< Gauche

typedef enum type_proj_s{FLECHE, RAYON}type_proj_t;

typedef struct projectile_s{
    float vitesse_depl;
    int x;
    int y;
    int porte;
    int degat;
}projectile_t;

projectile_t * creer_projectiles(type_proj_t type);
void detruire_projectiles(projectile_t proj);

