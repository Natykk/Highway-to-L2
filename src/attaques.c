#include <stdio.h>
#include <stdlib.h>
#include <../head/attaques.h>

void attaque_proj(proj_t typeproj, float degats, float vitesse_att, int x, int y){
    projectile_t * proj = creer_projectiles(typeproj, degats, dir);
}