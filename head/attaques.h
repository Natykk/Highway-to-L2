#include <../head/projectile.h>
#include <../head/cac.h>

void maj_proj(t_salle * map);
void attaque_proj(proj_t typeproj, int degats, float vitesse_att, int x, int y, t_dir dir);
bool degats(int degats, int id_mob, t_salle * map);
void attaque_cac(proj_t typeproj, int degats, float vitesse_att, int x, int y, t_dir dir);