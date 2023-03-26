#ifndef __INVENTAIRE__
#define __INVENTAIRE__

#include "entite.h"


void looter(entite_t *, entite_t * );
entite_t* init_inventaire_monstre(entite_t * );
entite_t* init_inventaire_personnage(entite_t * );
void afficher_inventaire(entite_t *);

#endif