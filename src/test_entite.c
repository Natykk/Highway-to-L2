/**
 * @file test_entite.c
 * @author GEORGET Rémy
 * @brief Fichier de test pour les entitées de notre jeu
 * @version 0.1
 * @date 2023-03-31 
 */

#include <stdio.h>
#include <stdlib.h>

#include "../head/entite.h"

/**
 * @fn main
 * @brief Le but sera de creer differents mobs et entites afin de les tester. Le but sera de faire en sorte de prendre le maximum de cas particuliers
 * 
 * @return int 
 */

int main() {

    
    /* -------------------------------------------------------------------------- */
    /*                        Creation des entitees de test                       */
    /* -------------------------------------------------------------------------- */

    entite_t* personnage = NULL;
    entite_t* slime_vert = NULL;
    entite_t* satan = NULL;    

    int nb_entite_init = 0;

    printf("----------------------------------------------------- \n");
    printf("*         Test sur la création des entitees :       * \n");
    printf("----------------------------------------------------- \n");

    /* -------------------- Création des differentes entites -------------------- */
    personnage = creer_personnage(personnage); 
    slime_vert = creer_monstre(slime_vert, "Slime_Vert");
    satan = creer_boss(satan, "Satan");

    /* ----------- On regarde si les entites ont bien été initialisés ----------- */
    if(personnage != NULL) nb_entite_init++;
    if(slime_vert != NULL) nb_entite_init++;
    if(satan != NULL) nb_entite_init++;

    /* ---------------- Affichage du nombre d'entités initialisés --------------- */
    printf("\n Nombre d'entites crées : %d \n\n", nb_entite_init);

    printf("----------------------------------------------------- \n");
    printf("*         Test sur l'affichage des entitees :       * \n");
    printf("----------------------------------------------------- \n");

    printf("\n------------- Affichage du Personnage : -------------\n\n");

    afficher_entite(personnage);

    printf("\n-----------------------------------------------------\n");

    printf("\n---------------- Affichage du Mob : ----------------\n\n");

    afficher_entite(slime_vert);

    printf("\n-----------------------------------------------------\n");

    printf("\n---------------- Affichage du Boss : ----------------\n\n");

    afficher_entite(satan);

    printf("\n-----------------------------------------------------\n");

    printf("----------------------------------------------------- \n");
    printf("*         Test de destruction des entitees :        * \n");
    printf("----------------------------------------------------- \n");

    /* -------------------- Destruction des differentes entites -------------------- */
    detruire_entitee(&personnage);
    detruire_entitee(&slime_vert);
    detruire_entitee(&satan);

    /* ----------- On regarde si les entites ont bien été détruites ----------- */
    if(personnage == NULL) nb_entite_init--;
    if(slime_vert == NULL) nb_entite_init--;
    if(satan == NULL) nb_entite_init--;

    /* ---------------- Affichage du nombre d'entités detruites --------------- */
    printf("\n Nombre d'entites restantes : %d \n\n", nb_entite_init);









}
