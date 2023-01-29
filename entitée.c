#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_MOBS 12 

/**
 * @file test_entitées.c
 * @brief Programme de début pour gerer les entitées
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 27/01/2023
 */

/**
 * @struct entite_t
 * @brief Structure qui genere les entitées 
 * Caracteristiques : 
 * - Nom 
 * - Vie
 * - Dégats
 * - Vitesse d'attaque
 * - Vitesse de déplacement 
 * - Les coordonnées x et y 
 */
typedef struct entite_s {
    char* nom;
    int vie;    
    float degats;
    float vitesse_att;
    float vitesse_depl;
    int x;
    int y;
}entite_t;

/**
 * @brief Tableau qui réference tout les mobs du jeu avec leurs stats de base
 */
entite_t tab_mob[NB_MOBS] = {
    {"Slime_Vert", 2, 1, 0.75, 0.40, 0, 0},
    {"Loup", 10, 4, 1.0, 1.2, 0, 0},
    {"Brigant", 20, 6, 0.9, 1.1, 0, 0},
    {"Chaman", 12, 12, 0.8, 1, 0, 0},
    {"Slime_Gris", 10, 5, 0.75, 0.40, 0, 0},
    {"Nain", 30, 8, 0.75, 0.40, 0, 0},
    {"Nain_Rider", 20, 5, 1.5, 1.2, 0, 0},
    {"Orc", 80, 20, 0.10, 0.20, 0, 0},
    {"Slime_Rouge", 50, 25, 0.75, 0.40, 0, 0},
    {"Diablotin", 40, 40, 1.4, 1.0, 0, 0},
    {"Diable", 80, 80, 0.8, 1.2, 0, 0},
    {"Cerbere", 200, 100, 1.8, 0.7, 0, 0}
};


/**
 * @fn afficher_entite
 * @brief Fonction qui permet d'afficher une entitée 
 * 
 * @param entite 
 */
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
void detruire_entitee(entite_t* entite){

    free(entite->nom);
    entite->nom = NULL;
    free(entite);
    entite=NULL;
}

int main() {
    entite_t *mob;
    entite_t *perso;
    mob = creer_monstre(mob, "Chaman");
    perso = creer_personnage(perso);
    printf("\n\n");
    afficher_entite(mob);
    afficher_entite(perso);
    detruire_entitee(mob);
    detruire_entitee(perso);
}

