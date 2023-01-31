#include <stdio.h>
#include <entite.h>
#include <objet.c>

#define NB_OBJET 30

/**
 * @file objet.h
 * @brief Fichier contenant toutes les structutes de données lié aux objets
 * @author GEORGET Rémy, GALLAIS Mathéo
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * @struct objet_t
 * @brief Structure Objet 
 * Caracteristiques : 
 * - Nom 
 * - Description
 */
typedef struct objet_s{
    char nom[20];
    char description[50];
}objet_t;

/**
 * @struct objet_inv_t
 * 
 *
 * @brief Type union objet contenu dans l'inventaire:
 * - l'objet peut etre unique nb=1
 * - l'objet peut etre empilé avec d'autre de memes types nb > 1
 */
typedef struct objet_inv_s
{
    objet_t * objet;
    int nb;
    void (*detruire_un)(objet_t*);
    void (*detruire_tout)(objet_t*);
}objet_inv_t;

/**
 * @brief Tableau qui réference tous les objets du jeu avec leurs stats de bases
 */
objet_t tab_objet[NB_OBJET] = {
    {
        "Feuille",
        "Bah c'est une feuille quoi...",
        1
    }
    /**
     * @brief a remplir
     * 
     */
}

void afficher_objet(objet_inv_t *);
int acces_obj(char*);
objet_t * creer_objet(objet_t*, char*);
void detruire_objet(objet *);
