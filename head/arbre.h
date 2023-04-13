#ifndef __ARBRE__
#define __ARBRE__

#include "competence.h"
#include "entite.h"
/**
 * \file arbre.h
 * \brief Fichier contenant les structure et prototype de fonction pour la gestion des arbres de compétences
*/
/**
 * \struct t_arbre
 * \brief Structure contenant les informations sur un arbre de compétences et les compétences qu'il contient et les niveaux d'acquis
 * 
*/
typedef struct arbre{
    t_classe classe; //!< Type de classe
    t_competence **competence; //!< Tableau de pointeur sur les compétences
    t_acquis etages[5]; //!< Tableau contenant les niveaux d'acquis des compétences
} t_arbre;

#include "entite.h"

/**
 * \fn int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse)
 * \brief Fonction permettant d'initialiser un arbre de compétences
 * \param arbre Pointeur sur l'arbre de compétences à initialiser
 * \param competences Tableau de compétences
 * \param typeClasse Type de classe
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int init_arbre(t_arbre ** arbre, t_competence *competences, t_classe typeClasse);

/**
 * \fn void aff_classe(t_arbre * arbre)
 * \brief Fonction permettant d'afficher les compétences d'un arbre de compétences
 * \param arbre Pointeur sur l'arbre de compétences à afficher
*/
void aff_classe(t_arbre * arbre);

/**
 * \fn int detruire_arbre(t_arbre ** arbre)
 * \brief Fonction permettant de détruire un arbre de compétences
 * \param arbre Pointeur de Pointeur sur l'arbre de compétences à détruire
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int detruire_arbre(t_arbre ** arbre);


int one_preced_cpt_debloq(t_competence * competence);


int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence);


int peut_deploquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);


int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);

#endif