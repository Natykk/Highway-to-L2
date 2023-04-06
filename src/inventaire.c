#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../head/inventaire.h"
#include "../head/objet.h"

/**
 * @file inventaire.c
 * @brief Fichier d'en-tete pour les primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Matéo.
 * @version 1.0
 * @date 31/01/2023
 */
/**
 * \fn afficher_inventaire(entite_t * entite)
 * @brief Fonction qui permet d'afficher l'inventaire d'une entite
 * @param entite
 * 
*/
void afficher_inventaire(entite_t * entite) {
    for(int i = 0; i < entite->place_inv; i++) {
        printf("{%s,%d} \n", entite->inventaire->objet[i].nom, entite->inventaire->nb[i]);
    }
}

/**
 * @fn looter
 * @brief Fonction qui permet de looter l'objet mis en parametre 
 * 
 * @param inventaire 
 * @param nom_obj 
 */
extern
void looter(entite_t * entite_source, entite_t * entite_destination){
    /*
    Check inventaire source objet par objet
    Si objet trouve 
    Alors tu prends le nombre de l'objet et le rang
    et tu le place dans l'inventaire destination 
    */
    int i;
    int rang;
    //printf("LOOTAGE DU MOB %s\n",entite_source->nom);
    // Pour chaque objet que possede la source
    for(i = 0; i < entite_source->place_inv; i++) {
        rang = acces_obj(entite_source->inventaire->objet[i].nom);
        
        //printf("mob : %d\n", entite_source->inventaire->nb[i]);
        entite_destination->inventaire->nb[rang] += entite_source->inventaire->nb[i];
        //printf("perso : %s\n", entite_destination->inventaire->objet[rang].nom);
        /*
        // On regarde si l'objet est bien dans l'inventaire 
        for(j = 0; j < entite_destination->place_inv; j++) {
            if((entite_destination->inventaire->objet[j]) == temp->objet )  {
                entite_destination->inventaire->nb[j] += temp->nb;
            }
        }
        */
    }
    //afficher_inventaire(entite_destination);
}

/**
 * @fn init_inventaire_personnage
 * @brief Fonction qui peremt de d'initialiser l'inventaire du personnage 
 * 
 * @param personnage 
 */
extern
entite_t* init_inventaire_personnage(entite_t * personnage) {
    int i;
    //printf("INIT PERSO\n");
    for(i = 0; i < personnage->place_inv; i++) {
        personnage->inventaire->objet[i] = tab_objet[i];
        personnage->inventaire->nb[i] = 0;
    }
    return personnage;
}


/**
 * @fn init_inventaire_monstre
 * @brief Fonction qui permet d'initialiser l'iventaire d'un monstre en fonction de ce qu'il loot
 * 
 * @param monstre 
 */
extern
entite_t* init_inventaire_monstre(entite_t * monstre) {
    //printf("Init du mob %s \n",monstre->nom);
    int rang_mob = acces_mob(monstre->nom);
    //printf("%s \n", monstre->nom);
    switch(rang_mob) {
        case 0: // Slime Vert --> Green Goo
            monstre->inventaire->objet[0] = tab_objet[1];
            monstre->inventaire->nb[0] = rand()%4+1;
            return monstre;
       case 1: // Loup --> Fourrure et Griffe
            monstre->inventaire->objet[0] = tab_objet[2];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[3];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;
        case 2: // Brigant --> Or
            monstre->inventaire->objet[0] = tab_objet[0];
            monstre->inventaire->nb[0] = rand()%4+1;
            return monstre;
        case 3: // Chaman --> Or, Grimoire
            monstre->inventaire->objet[0] = tab_objet[4];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[0];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;
        case 4: // Slime Gris --> Grey Goo
            monstre->inventaire->objet[0] = tab_objet[5];
            monstre->inventaire->nb[0] = rand()%4+1;
            return monstre;
        case 5: // Nain --> Pioche, Or 
            monstre->inventaire->objet[0] = tab_objet[6];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[0];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;
        case 6: // Nain_Rider --> Or, Lance Pierre, Cailloux 
            monstre->inventaire->objet[0] = tab_objet[7];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[8];
            monstre->inventaire->nb[1] = rand()%4+1;

            monstre->inventaire->objet[2] = tab_objet[0];
            monstre->inventaire->nb[2] = rand()%4+1;
            return monstre;
        case 7: // Orc --> Or, Massue 
            monstre->inventaire->objet[0] = tab_objet[9];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[0];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;
        case 8: // Sime_Rouge --> Red Goo
            monstre->inventaire->objet[0] = tab_objet[10];
            monstre->inventaire->nb[0] = rand()%4+1;
            return monstre;
        case 9: // Diablotin --> Cornes de Diablotin, Queue de Diablotin, Or
            monstre->inventaire->objet[0] = tab_objet[11];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[12];
            monstre->inventaire->nb[1] = rand()%4+1;

            monstre->inventaire->objet[2] = tab_objet[0];
            monstre->inventaire->nb[2] = rand()%4+1;
            return monstre;
        case 10: // Diable --> Lance, Coeur de dibale.
            monstre->inventaire->objet[0] = tab_objet[13];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[14];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;
        case 11: // Cerbere --> Tete, Croquettes.
            monstre->inventaire->objet[0] = tab_objet[15];
            monstre->inventaire->nb[0] = rand()%4+1;

            monstre->inventaire->objet[1] = tab_objet[16];
            monstre->inventaire->nb[1] = rand()%4+1;
            return monstre;

        default: 
            printf("Erreur lors de l'initialisation de l'inventaire du mob ! \n"); 
            return monstre;       
    }
}


