#include "entite.h"

/**
 * @file entite.c
 * @brief Primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */


/**
 * @fn afficher_entite
 * @brief Fonction qui permet d'afficher une entitée 
 * 
 * @param entite 
 */
extern
void afficher_entite(entite_t* entite) {
    printf("Affichage de l'entité : \n");
    printf("{%s, %d, %f, %f, %f, %d, %d} \n", entite->nom, entite->vie, entite->degats, entite->vitesse_att, entite->vitesse_depl, entite->x, entite->y);
}


/**
 * @fn acces_mob
 * @brief Fonction qui prends en parametre le nom du mob et renvoie le chiffre correspondant a la case dans le tableau
 * 
 * @param chaine 
 * @return int 
 */
extern
int acces_mob(char* chaine) {
    entite_t temp;
    for (int i = 0; i < NB_MOBS; i++){
        temp = tab_mob[i];
        if(!strcmp(temp.nom, chaine)) {
            return i;
        }
    }
}

/**
 * @fn creer_personnage
 * @brief Fonction qui permet de creer les personnages jouables
 * @param entite 
 * @return entite_t 
 */
extern
entite_t* creer_personnage (entite_t * entite){
    entite = malloc(sizeof(entite_t));
    entite->nom = malloc(sizeof(char)*30);

    entite->vie = 20;
    entite->degats = 5.0;
    entite->vitesse_att = 1.0;
    entite->vitesse_depl = 1.0;
    entite->x = 0;
    entite->y = 0;
    return entite;
}

/**
 * @fn creer_monstre
 * @brief Fonction qui permet de creer un mob a partir de son nom.
 * 
 * @param entite 
 * @param nom Ici le nom permet de retrouver quel mob on veut avoir. 
 * @return entite_t 
 */
extern
entite_t* creer_monstre (entite_t * entite, char * nom) {
    int emplacement = acces_mob(nom);
    int taille_nom = strlen(tab_mob[emplacement].nom);

    entite = malloc(sizeof(entite_t));
    entite->nom = malloc(sizeof(char)*taille_nom);
    
    strcpy(entite->nom,tab_mob[emplacement].nom);
    entite->vie = tab_mob[emplacement].vie;
    entite->degats = tab_mob[emplacement].degats;
    entite->vitesse_att = tab_mob[emplacement].vitesse_att;
    entite->vitesse_depl = tab_mob[emplacement].vitesse_depl;
    entite->x = tab_mob[emplacement].x;
    entite->y = tab_mob[emplacement].y;

    return entite;
}
/**
 * @fn detruire_entitee
 * @brief Fonction pour libérer la memoire utilisé pour les entités
 * @param entite  
 * @return rien 
 */
extern
void detruire_entitee(entite_t* entite){

    free(entite->nom);
    entite->nom = NULL;
    free(entite);
    entite=NULL;
}


