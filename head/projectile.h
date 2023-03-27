#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <./head/entite.h>

typedef enum proj_s{FLECHE, BOULE, UNK}proj_t;

typedef struct stat_proj_s{
    float vitesse_depl;
    int porte;
}stat_proj_t;

typedef struct projectile_s{
    float vitesse_depl;
    int portee;
    float degats;
    bool touche;
    int x;
    int y;
    t_dir dir;
}projectile_t;

projectile_t * creer_projectiles(proj_t type);
void detruire_projectiles(projectile_t ** proj);
void calcul_position(projectile_t * proj);