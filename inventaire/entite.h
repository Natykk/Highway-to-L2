#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <objet.h>

#define NB_MOBS 12

/**
 * @file entite.h
 * @brief Fichier d'en-tete pour les primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */

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
    float degats;
    float vitesse_att;
    float vitesse_depl;
    int x;
    int y;
    objet_inv_t * inventaire;
    int place_inv;
}entite_t;

/**
 * @brief Tableau qui réference tout les mobs du jeu avec leurs stats de base
 */
entite_t tab_mob[NB_MOBS] = {
    {"Slime_Vert", 2, 1, 0.75, 0.40, 0, 0, 1},
    {"Loup", 10, 4, 1.0, 1.2, 0, 0, 2},
    {"Brigant", 20, 6, 0.9, 1.1, 0, 0, 1},
    {"Chaman", 12, 12, 0.8, 1, 0, 0, 2},
    {"Slime_Gris", 10, 5, 0.75, 0.40, 0, 0, 1},
    {"Nain", 30, 8, 0.75, 0.40, 0, 0, 2},
    {"Nain_Rider", 20, 5, 1.5, 1.2, 0, 0, 3},
    {"Orc", 80, 20, 0.10, 0.20, 0, 0, 2},
    {"Slime_Rouge", 50, 25, 0.75, 0.40, 0, 0, 1},
    {"Diablotin", 40, 40, 1.4, 1.0, 0, 0, 3},
    {"Diable", 80, 80, 0.8, 1.2, 0, 0, 2},
    {"Cerbere", 200, 100, 1.8, 0.7, 0, 0, 2}
};

void afficher_entite(entite_t *);
int acces_mob(char*);
entite_t * creer_personnage(entite_t *);
entite_t * creer_monstre(entite_t *, char *);
void detruire_entitee(entite_t *);