#include <stdio.h>
#include <stdlib.h>
#include <projectiles.h>

#define NB_PROJ 2

projectile_t * creer_projectiles(type_proj_t type, int degat, int dir){
    switch(type){
        case FLECHE:
            break;
        case RAYON:
            break;
    }
}

projectile_t tab_proj[NB_PROJ] = {
    {"fleche", 2.0, 15, 0},
    {"rayon", 1.5, 12, 0}
};

void detruire_projectiles(projectile_t proj)

int main(){
    
}