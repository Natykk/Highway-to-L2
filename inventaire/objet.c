#include "objet.h"

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
extern
void afficher_obj(objet_inv_t * obj){
    if(obj->objet == NULL){
        printf("Espace vide \n");
        printf("J'ai connu des sacs d'aventuriers plus lourds que ca...");
    }else{
        printf("%s : \n%s\nQuantité : %i\n",obj->objet->nom, obj->objet->description,obj->nb);
    }
}


/**
 * @fn acces_obj
 * @brief Fonction qui prends en parametre le nom de l'objet et renvoie sa place correspondante
 * 
 * @param chaine une chaine de caractere correspondant au nom de l'objet
 * @return Un entier correspondant a la place de l'objet dans tab_objet
 */
extern
int acces_obj(char* chaine) {
    objet_t temp;
    for (int i = 0; i < NB_OBJET; i++){
        temp = tab_objet[i];
        if(!strcmp(temp.nom, chaine)) {
            return i;
        }
    }
}