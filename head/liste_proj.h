#include <./head/projectile.h>
typedef struct element {projectile_t * proj;
                        struct element * pred;
                        struct element * succ;
                        }t_element;

t_element * drapeau;
t_element * ec;

void init_liste_proj(void);
int liste_vide(void);
int hors_liste(void);
void en_tete(void);
void en_queue(void);
void precedent(void);
void suivant(void);
void valeur_elt(projectile_t **);
void modif_elt(projectile_t*);
void oter_elt(void);
void ajout_droit(projectile_t*);
void ajout_gauche(projectile_t*);