
#include "../head/entite.h"
#include "../head/arbre.h"
#include <string.h>

/**
 * @file entite.c
 * @brief Primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Mathéo , GAUTERON Nathan
 * @version 1.0
 * @date 31/01/2023
 */

/**
 * @brief tableau qui stocke tout les mobs présents dans le jeu
 */
entite_t tab_mob[NB_MOBS] = {
    {"Slime_Vert", 2, 1, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1},
    {"Loup", 10, 4, 1.0, 1.2, 8, 0, 0, NULL, NULL, 2},
    {"Brigant", 20, 6, 0.9, 1.1, 7, 0, 0, NULL, NULL, 1},
    {"Chaman", 12, 12, 0.8, 1, 9, 0, 0, NULL, NULL, 2},
    {"Slime_Gris", 10, 5, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1},
    {"Nain", 30, 8, 0.75, 0.40, 5, 0, 0, NULL, NULL, 2},
    {"Nain_Rider", 20, 5, 1.5, 1.2, 10, 0, 0, NULL, NULL, 3},
    {"Orc", 80, 20, 0.10, 0.20, 8, 0, 0, NULL, NULL, 2},
    {"Slime_Rouge", 50, 25, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1},
    {"Diablotin", 40, 40, 1.4, 1.0, 5, 0, 0, NULL, NULL, 3},
    {"Diable", 80, 80, 0.8, 1.2, 10, 0, 0, NULL, NULL, 2},
    {"Cerbere", 200, 100, 1.8, 0.7, 12, 0, 0, NULL, NULL, 2}
};

/**
 * @fn afficher_entite
 * @brief Fonction qui permet d'afficher une entitée 
 * 
 * @param entite 
 */
extern
void afficher_entite(entite_t* entite) {
    printf("Affichage de l'entité : \n");
    switch (entite->persoOuMob){
        case 0: printf("[PERSO] "); break;
        case 1: printf("[MOB] "); break;
        default: printf("[] "); break;
    }
    printf("Nom : %s [%d-%d]\n", entite->nom, entite->x, entite->y);
    printf("Classe : ");
    switch(entite->arbre->classe){
        case ARCHER : printf("ARCHER\n"); break;
        case ASSASSIN : printf("ASSASSIN\n"); break;
        case MAGE : printf("MAGE\n"); break;
        case GUERRIER : printf("GUERRIER\n"); break;
        default : printf("Aucune classe\n"); break;
    }
    printf(" - Vie : %.2f\n", entite->vie);
    printf(" - Dégats : %.2f\n", entite->degats);
    printf(" - Vitesse d'attaque : %.2f\n", entite->vitesse_att);
    printf(" - Vitesse de déplacement : %.2f\n", entite->vitesse_depl);
    switch (entite->persoOuMob){
        case 0: printf(" - Bonus de diminution du périmètre de detction des mobs : %d\n", entite->perim_detect); break;
        case 1: printf(" - Périmètre de détection : %d\n", entite->perim_detect); break;
        default: break;
    }
}

/**
 * @fn associer_entite
 * @brief Fonction qui permet de faire '=' mais pour une entitée
 * 
 * @param source 
 * @param destination 
 */
extern
void associer_entite(entite_t *source, entite_t *destination) {
    strcpy(source->nom,destination->nom);
    source->vie = destination->vie;
    source->degats = destination->degats;
    source->vitesse_att = destination->vitesse_att;
    source->vitesse_depl = destination->vitesse_depl;
    source->x = destination->x;
    source->y = destination->y;
    source->place_inv = destination->place_inv;
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
    for (int i = 0; i < NB_MOBS; i++){
        if(!strcmp(tab_mob[i].nom, chaine)) {
            return i;
        }
    }
    return -1;
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
    entite->perim_detect = 0;
    entite->x = 0;
    entite->y = 0;
    entite->arbre = NULL;
    entite->place_inv = NB_OBJET;
    entite->inventaire = malloc(sizeof(objet_inv_t));
    entite->inventaire->nb = malloc(sizeof(int)*entite->place_inv);
    entite->inventaire->objet = malloc(sizeof(objet_t)*entite->place_inv);
    entite->persoOuMob = 0;
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
    //printf("degats : %f \n", entite->degats);
    entite->vitesse_att = tab_mob[emplacement].vitesse_att;
    entite->vitesse_depl = tab_mob[emplacement].vitesse_depl;
    entite->perim_detect = tab_mob[emplacement].perim_detect;
    entite->x = tab_mob[emplacement].x;
    entite->y = tab_mob[emplacement].y;
    entite->place_inv = tab_mob[emplacement].place_inv;
    entite->inventaire = malloc(sizeof(objet_inv_t));
    entite->inventaire->objet = malloc(sizeof(objet_t)*entite->place_inv);
    entite->inventaire->nb = malloc(sizeof(int)*(entite->place_inv));

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
    // Destruction du nom de l'entite
    if(entite->nom != NULL){
        free(entite->nom);
        entite->nom = NULL;
    }
    

    // Destruction de l'inventaire
    free(entite->inventaire->objet);
    entite->inventaire->objet = NULL;

    free(entite->inventaire->nb);
    entite->inventaire->nb = NULL;

    free(entite->inventaire);
    entite->inventaire = NULL;

    // Destruction de l'entitee
    free(entite);
    entite=NULL;
}


