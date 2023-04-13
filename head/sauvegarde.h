#ifndef __SAUV__
#define __SAUV__
/**
 * \file sauvegarde.h
 * \brief Fichier contenant les prototypes des fonctions de sauvegarde et de chargement
*/
#include "entite.h"
/**
 * \fn int sauvegarde(entite_t *personnage, int num_etage, unsigned char *key)
 * \brief Fonction de sauvegarde
 * \param personnage Pointeur sur l'entité du joueur
 * \param num_etage Numéro de l'étage actuel
 * \param key Clé de chiffrement
 * \return 0 si la sauvegarde s'est bien passée, -1 sinon
*/
int sauvegarde(entite_t *personnage, int num_etage, unsigned char *key);
/**
 * \fn int chargement(entite_t **personnage, unsigned char *key)
 * \brief Fonction de chargement
 * \param personnage Pointeur sur le pointeur de l'entité du joueur
 * \param key Clé de chiffrement
 * \return 0 si le chargement s'est bien passé, -1 sinon
*/
int chargement(entite_t **personnage, unsigned char *key);
/**
 * \fn int sha256_file(const char *path, char *hash)
 * \brief Fonction de hashage
 * \param path Chemin du fichier à hasher
 * \param hash Pointeur sur le tableau de caractères contenant le hash
 * 
*/
int sha256_file(const char *path, char *hash);

#endif