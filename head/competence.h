#ifndef __COMPETENCE__
#define __COMPETENCE__
/**
 * \file competence.h
 * \brief Fichier contenant les structures et prototypes de fonctions pour la gestion des compétences
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum {non_acquis, acquis} t_acquis;
typedef enum {AUCUNE_CLASSE=-1, ASSASSIN, GUERRIER, MAGE, ARCHER} t_classe;

#include "objet.h"

#define T_NOM 100 //<! Taille du nom d'une compétence
#define T_DESC 300 //<! Taille de la description d'une compétence
#define NB_CPT 10  //<! Nombre de compétences par classe

#define NO_IMPROVE 1 //<! Pas d'amélioration
#define SMALL_IMPROVE 2  //<! Améliore légèrement 
#define MIDDLE_IMPROVE 3  //<! ameliore 
#define BIG_IMPROVE 4     //<!améliore grandement 
#define ULTRA_IMPROVE 5   //<! améliore énormémément 

/**
 * \struct buff_s
 * \brief Structure contenant les différents buffs d'une compétence
 * \details Cette structure est utilisée pour la création d'une compétences
 * 
*/
typedef struct buff_s{
    float buff_vie; //<! Buff de vie
    float buff_degat; //<! Buff de dégâts
    float buff_vit_att; //<! Buff de vitesse d'attaque
    float buff_vit_depl; //<! Buff de vitesse de déplacement
    int perim_detect; //<! Périmetre de détection
} t_buff;

/**
 * \struct competence
 * \brief Structure contenant les informations d'une compétence
 * \details Cette structure est utilisée pour la création des compétences
*/
typedef struct competence{
    t_acquis competence_acquise; //<! Indique si la compétence est acquise ou non
    char nom[T_NOM]; //<! Nom de la compétence
    char desc[T_DESC]; //<! Description de la compétence
    t_buff buff; //<! Buff de la compétence
    struct competence **precedentes; //<! Pointeur sur la compétence précédente
    int nb_prec; //<! Nombre de compétences précédentes
    struct competence **suivantes; //<! Pointeur sur la compétence suivante
    int nb_suiv; //<! Nombre de compétences suivantes
    char *name_img;      //<! chemin vers  l'image de la compétence (debloquée ou non).
    objet_inv_t *obj_necessaires; //<! Pointeur sur les objets nécessaires pour débloquer la compétence
    int taille_tab_obj_nec; //<! Taille du tableau d'objets nécessaires
    int etage; //<! Etage de la compétence
} t_competence;

extern t_competence cpt_assassin[]; //<! Tableau de Compétence d'assassin
extern t_competence cpt_guerrier[]; //<! Tableau de Compétence de guerrier
extern t_competence cpt_archer[]; //<! Tableau de Compétence d'archer
extern t_competence cpt_mage[]; //<! Tableau de Compétence de mage

/* Fonctions de competence.c */
/**
 * \fn int init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice)
 * \brief Fonction qui initialise les objets nécessaires pour débloquer une compétence
 * \param competence Pointeur sur la compétence à initialiser
 * \param typeClasse Type de la classe
 * \param indice Indice de la compétence dans le tableau de compétences
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice);

/**
 * \fn int changer_nomImgCpt(t_competence * competence)
 * \brief Fonction qui change le nom de l'image de la compétence
 * \param competence Pointeur sur la compétence à initialiser
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int changer_nomImgCpt(t_competence * competence);

/**
 * \fn int init_competences(t_competence **competences, t_classe typeClasse)
 * \brief Fonction qui initialise les compétences d'une classe
 * \param competences Pointeur sur le tableau de compétences à initialiser
 * \param typeClasse Type de la classe
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int init_competences(t_competence **competences, t_classe typeClasse);

/**
 * \fn void aff_competence(t_competence competence)
 * \brief Fonction qui affiche les informations d'une compétence
 * \param competence Compétence à afficher
 * 
*/
void aff_competence(t_competence competence);

#include "arbre.h"
/**
 * \fn int remplissage_nomImgCpt(t_competence **competences, t_classe typeClasse)
 * \brief Fonction qui remplit le nom de l'image de la compétence
 * \param competences Pointeur de pointeur sur le tableau de compétences à initialiser
 * \param typeClasse Type de la classe
 * \return 0 si tout s'est bien passé, -1 sinon
 * \details Cette fonction est utilisée pour remplir le nom de l'image de la compétence
*/
int remplissage_nomImgCpt(t_competence **competences, t_classe typeClasse);


#endif