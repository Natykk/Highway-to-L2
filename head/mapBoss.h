#ifndef __MAPBOSS__
#define __MAPBOSS__

#include "mapStruct.h"


/* Prototype des fonctions */
t_salle * genererSalleBoss(t_salle * salleBoss);
void afficher_salle_boss(t_salle * salle);
void detruireSalleBoss(t_salle ** salleBoss);
t_salle * genererSalleMarchand(t_salle * salleMarchand);

#endif