#include <../head/projectile.h>
#include <../head/cac.h>
#include <../head/mapStruct.h>
#include <../head/entite.h>
#include <../head/liste_proj.h>

void maj_proj(entite_t * posPers, t_salle * map);
void attaque_proj(proj_t typeproj, entite_t * posPers, t_salle * map);
bool degats(int degats, int id_mob, t_salle * map);
void attaque_cac(proj_t typeproj, entite_t * posPers, t_salle * map);