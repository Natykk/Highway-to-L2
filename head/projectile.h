#ifndef PROJ_H
#define PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../head/entite.h"

typedef struct projectile_s
{
    int vitesse_depl;
    int portee;
    float degats;
    bool touche;
    int xp;
    int yp;
    int x;
    int y;
    t_dir dir;
} projectile_t;

typedef struct element
{
    projectile_t *proj;
    struct element *pred;
    struct element *succ;
} t_element;

extern t_element * drapeau;
extern t_element * ec;

typedef enum proj_s
{
    AUCUN_PROJ = -1,
    FLECHE,
    BOULE
} proj_t;

typedef struct stat_proj_s
{
    int vitesse_depl;
    int porte;
} stat_proj_t;

void init_liste_proj(void);
int liste_vide_proj(void);
int hors_liste_proj(void);
void en_tete_proj(void);
void en_queue_proj(void);
void precedent_proj(void);
void suivant_proj(void);
void valeur_elt_proj(projectile_t **);
void modif_elt_proj(projectile_t *);
void oter_elt_proj(void);
void ajout_droit_proj(projectile_t *);
void ajout_gauche_proj(projectile_t *);

int valide(int x, int y);
projectile_t *creer_projectiles(proj_t type);
void detruire_projectiles(projectile_t **proj);
void calcul_position(projectile_t *proj);

#endif