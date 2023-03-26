#ifndef __ARBRE__
#define __ARBRE__

#include "competence.h"

typedef struct arbre{
    t_classe classe;
    t_competence **competence;
} t_arbre;

int remplir_cpt_arbre(t_competence ** cpt_dest, t_competence * cpt_src);
int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse);
void aff_classe(t_arbre * arbre);
int detruire_arbre(t_arbre ** arbre);

#endif