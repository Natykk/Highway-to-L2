#ifndef __COMPETENCE__
#define __COMPETENCE__

#include <stdio.h>
#include <stdlib.h>

typedef enum {non_acquis, acquis} t_acquis;
typedef enum {ASSASSIN=0, GUERRIER, MAGE, ARCHER} t_classe;

#include "objet.h"

#define T_NOM 100
#define T_DESC 300
#define NB_CPT 10 

#define NO_IMPROVE 1
#define SMALL_IMPROVE 2         //améliore légèrement ...
#define MIDDLE_IMPROVE 3        //ameliore ...
#define BIG_IMPROVE 4           //améliore grandement ...
#define ULTRA_IMPROVE 5         //améliore énormémément ...

typedef struct buff_s{
    float buff_vie;
    float buff_degat;
    float buff_vit_att;
    float buff_vit_depl;
    int perim_detect;
} t_buff;

typedef struct competence{
    t_acquis competence_acquise;
    char nom[T_NOM];
    char desc[T_DESC];
    t_buff buff;
    struct competence **precedentes;
    int nb_prec;
    struct competence **suivantes;
    int nb_suiv;
    char *name_img;      //image unique qui prendra le nom de l'image de la compétence (debloquée ou non).
    objet_inv_t *obj_necessaires;
    int taille_tab_obj_nec;
} t_competence;

t_competence cpt_assassin[NB_CPT];
t_competence cpt_guerrier[NB_CPT];
t_competence cpt_archer[NB_CPT];
t_competence cpt_mage[NB_CPT];

/* Fonctions de competence.c */
int init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice);
int changer_nomImgCpt(t_competence * competence);
int init_competences(t_competence **competences, t_classe typeClasse);
void aff_competence(t_competence competence);

#include "arbre.h"

int remplissage_nomImgCpt(t_competence **competences, t_classe typeClasse);


#endif