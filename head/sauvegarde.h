#ifndef __SAUV__
#define __SAUV__

#include "entite.h"

int sauvegarde(entite_t *personnage, int num_etage);
int chargement(entite_t **personnage);

#endif