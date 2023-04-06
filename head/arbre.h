#ifndef __ARBRE__
#define __ARBRE__

#include "competence.h"
#include "entite.h"
/**
 * \file arbre.h
 * \brief Fichier contenant les structure et prototype de fonction pour la gestion des arbres de compétences
*/

typedef struct arbre{
    t_classe classe;
    t_competence **competence;
    t_acquis etages[5];
} t_arbre;

#include "entite.h"

int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse);
void aff_classe(t_arbre * arbre);
int detruire_arbre(t_arbre ** arbre);
int one_preced_cpt_debloq(t_competence * competence);
int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence);
int peut_deploquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);
int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);

#endif