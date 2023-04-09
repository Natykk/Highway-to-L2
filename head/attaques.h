#ifndef ATTAQUE_H
#define ATTAQUE_H

#include "../head/mapStruct.h"
#include "../head/inventaire.h"
#include "../head/projectile.h"

extern void maj_proj(entite_t * posPers, t_salle * map);
extern void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map);
extern bool degats(int degats, int id_mob, t_salle * map);
extern void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map);

#endif