#include <stdio.h>
#include <stdlib.h>

typedef enum{AUCUN=-1, //!< Aucune direction
                HAUT, //!< Haut
                DROITE, //!< Droite
                BAS, //!< Bas
                GAUCHE} t_dir; //!< Gauche

typedef enum proj_s{FLECHE, BOULE}proj_t;

typedef struct projectile_s{
    float vitesse_depl;
    int porte;
    t_dir dir;
}projectile_t;

projectile_t * creer_projectiles(proj_t type, int degats, t_dir dir);
void detruire_projectiles(projectile_t ** proj);
void attaque_proj(proj_t typeproj, float degats, float vitesse_att, int x, int y);