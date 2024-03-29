#ifndef __OBJET_INV__
#define __OBJET_INV__
/**
 * @struct objet_t
 * @brief Structure Objet 
 * Caracteristiques : 
 * - Nom 
 * - Description
 */
typedef struct objet_s{
    char nom[20]; //<! Nom de l'objet
    char description[400]; //<! Description de l'objet
} objet_t;

/**
 * @struct objet_inv_t
 * 
 *
 * @brief Type union objet contenu dans l'inventaire:
 * - l'objet peut etre unique nb=1
 * - l'objet peut etre empilé avec d'autre de memes types nb > 1
 */
typedef struct objet_inv_s{
    objet_t *objet; //<! Pointeur sur l'objet
    int *nb; //<! Nombre d'objet
} objet_inv_t;

#endif