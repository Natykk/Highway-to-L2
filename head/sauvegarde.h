#include <./head/entite.h>
#include <./head/arbre.h>
#include <./head/mapStruct.h>
#include <./head/inventaire.h>

int one_next_cpt_unlock(t_competence * competence);
int cpt_aquise(FILE * sauv, t_arbre * arbre);
int sauvegarde(entite_t * personnage, int num_etage);
int appliquer(entite_t * personnage, t_competence *  competence);
int chargement(entite_t ** personnage);