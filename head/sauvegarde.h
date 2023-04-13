#ifndef __SAUV__
#define __SAUV__

#include "entite.h"

int sauvegarde(entite_t *personnage, int num_etage, unsigned char *key);
int chargement(entite_t **personnage, unsigned char *key);
int sha256_file(const char *path, char *hash);

#endif