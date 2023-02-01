#include <stdio.h>
#include <entite.h>
#include <objet.c>

#define NB_OBJET 17

/**
 * @file objet.h
 * @brief Fichier contenant toutes les structutes de données liées aux objets
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
    char description[400];
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
 * @brief Tableau qui réference tous les objets du jeu
 */
objet_t tab_objet[NB_OBJET] = {
    {
        "Or",
        "Echange le avec un marchant tu vas voir c'est pratique",
    }
    {
        "Green Goo",
        "Goute c'est bon",
    }
    {
        "Fourrure",
        "Ca en ferait un tres bon tapis"
    }
    {
        "Griffe",
        "A grou grou"
    }
    {
        "Grimoire",
        "Trop chiant a lire va voir le marchant"
    }
    {
        "Grey Goo",
        "Avale c'est pas mauvais"
    }
    {
        "Pioche",
        "I AM A DWARF AND I'M DIGGING A HOLE"
    }
    {
        "Lance-Pierre",
        "Rah ce nain"
    }
    {
        "Cailloux",
        "Bah ouais..."
    }
    {
        "Massue",
        "Ne pose pas ca sur n'importe quelle tete"
    }
    {
        "Red Goo",
        "Delecte toi c'est appreciable"
    }
    {
        "Cornes de Diablotin",
        "C'est deux longs objets, souvent associés en paire, sont maintenu sur le haut du crane d'un petit diablotin. Vous remarquerez sans doutes des similarités avec celle d'une chevre."
    }
    {
        "Queue de Diablotin",
        "Un diablotin est, dans la mythologie, le folklore et plusieurs traditions, une créature démoniaque de petite taille. Ils sont décrits comme de petites êtres espiègles agités et de taille réduite plutôt que de sérieuses menaces, et occupent une position inférieure dans la hiérarchie de la démonologie. Les assistants du Diable sont parfois nommés des « diablotins »."
    }
    {
        "Lance",
        "Compliqué a ranger dans un sac"
    }
    {
        "Coeur de Diable",
        "Mais pourquoi... Mais c'est immonde..."
    }
    {
        "Tetes",
        "Ah nan là c'est trop pour moi"
    }
    {
        "Croquettes",
        "Vraiment ?!"
    }
    /**
     * @brief a remplir
     * 
     */
}

void afficher_objet(objet_inv_t *);
int acces_obj(char*);
objet_t * creer_objet(objet_t* , char*);
void detruire_objet(objet *);
