#include <stdio.h>
#include <string.h>
#include "../head/objet.h"

/**
 * @file objet.c
 * @brief Primitives liées aux objets
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * @fn afficher_obj
 * @brief Fonction qui affiche le contenu d'un case d'inventaire
 * 
 * @param obj case d'inventaire de type objet_inv_t
 */
/*
extern
void afficher_obj(objet_t * obj){
    if(obj->objet == NULL){
        printf("Espace vide \n");
        printf("J'ai connu des sacs d'aventuriers plus lourds que ca...");
    }else{
        printf("%s : \n%s\nQuantité : %i\n",obj->objet->nom, obj->objet->description,obj->nb);
    }
}
*/

/**
 * @brief Tableau qui stocke tout les objets du jeu 
 */
objet_t tab_objet[NB_OBJET] = {
    {"Or","Echange le avec un marchant tu vas voir c'est pratique",},
    {"Green Goo", "Goute c'est bon",},
    {"Fourrure", "Ca en ferait un tres bon tapis"},
    {"Griffe", "A grou grou"},
    {"Grimoire", "Trop chiant a lire va voir le marchant"},
    {"Grey Goo", "Avale c'est pas mauvais"},
    {"Pioche", "I AM A DWARF AND I'M DIGGING A HOLE"},
    {"Lance-Pierre", "Rah ce nain"},
    {"Cailloux", "Bah ouais..."},
    {"Massue", "Ne pose pas ca sur n'importe quelle tete"},
    {"Red Goo", "Delecte toi c'est appreciable"},
    {"Cornes de Diablotin", "C'est deux longs objets, souvent associés en paire, sont maintenu sur le haut du crane d'un petit diablotin. Vous remarquerez sans doutes des similarités avec celle d'une chevre."},
    {"Queue de Diablotin", "Un diablotin est, dans la mythologie, le folklore et plusieurs traditions, une créature démoniaque de petite taille. Ils sont décrits comme de petites êtres espiègles agités et de taille réduite plutôt que de sérieuses menaces, et occupent une position inférieure dans la hiérarchie de la démonologie. Les assistants du Diable sont parfois nommés des « diablotins »."},
    {"Lance", "Compliqué a ranger dans un sac"},
    {"Coeur de Diable", "Mais pourquoi... Mais c'est immonde..."},
    {"Tetes", "Ah nan là c'est trop pour moi"},
    {"Croquettes", "Vraiment ?!"}
};

/**
 * @fn acces_obj
 * @brief Fonction qui prends en parametre le nom de l'objet et renvoie sa place correspondante
 * 
 * @param chaine une chaine de caractere correspondant au nom de l'objet
 * @return Un entier correspondant a la place de l'objet dans tab_objet
 */
extern
int acces_obj(char* chaine) {
    for (int i = 0; i < NB_OBJET; i++){
        if(!strcmp(tab_objet[i].nom, chaine)) {
            return i;
        }
    }
    return -1;
}
