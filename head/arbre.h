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

/**
 * \fn int one_preced_cpt_debloq(t_competence * competence)
 * \brief Fonction permettant de savoir si une compétence a au moins une compétence précédente débloquée
 * \param competence Pointeur sur la compétence à tester
 * \return 0 si la compétence n'a pas de compétence précédente débloquée, 1 sinon
*/
int one_preced_cpt_debloq(t_competence * competence);

/**
 * \fn int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence)
 * \brief Fonction permettant de savoir si une compétence est dans l'arbre de compétences du joueur
 * \param personnage Pointeur sur l'entité du joueur
 * \param competence Pointeur sur la compétence à tester
 * \return 0 si la compétence n'est pas dans l'arbre de compétences du joueur, 1 sinon
*/
int cpt_in_arbre_joueur(entite_t * personnage, t_competence * competence);

/**
 * \fn int peut_deploquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt)
 * \brief Fonction permettant de savoir si une compétence peut être débloquée
 * \param personnage Pointeur sur l'entité du joueur
 * \param competence Pointeur sur la compétence à tester
 * \param arbre_cpt Pointeur sur l'arbre de compétences du joueur
 * \return 0 si la compétence ne peut pas être débloquée, 1 sinon
*/
int peut_deploquer_cpt(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);


/**
 * \fn int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt)
 * \brief Fonction permettant de débloquer une compétence
 * \param personnage Pointeur sur l'entité du joueur
 * \param competence Pointeur sur la compétence à débloquer
 * \param arbre_cpt Pointeur sur l'arbre de compétences du joueur
 * \return 0 si la compétence ne peut pas être débloquée, 1 sinon
*/
int competence_debloquer(entite_t * personnage, t_competence * competence, t_arbre * arbre_cpt);

#endif