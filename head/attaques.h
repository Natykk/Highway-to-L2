#include <../head/projectile.h>
#include <../head/cac.h>

void maj_proj(t_salle * map, entite_t * posPers);
void attaque_proj(proj_t typeproj, int degats, entite_t * posPers, t_dir dir);
bool degats(int degats, int id_mob, t_salle * map);
void attaque_cac(proj_t typeproj, int degats, entite_t * posPers, t_dir dir);