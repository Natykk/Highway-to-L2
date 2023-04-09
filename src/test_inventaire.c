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
#include "../head/inventaire.h"

/**
 * @fn main
 * @brief Le but sera de creer differents mobs et entites afin de les tester. Le but sera de faire en sorte de prendre le maximum de cas particuliers
 * 
 * @return int 
 */

int main() {
    entite_t* personnage = NULL;
    entite_t* slime_vert = NULL;
    entite_t* satan = NULL; 

    int nb_entite_init = 0;

    printf("----------------------------------------------------- \n");
    printf("*         Test sur la création des entitees :       * \n");
    printf("----------------------------------------------------- \n");

    /* -------------------- Création des differentes entites -------------------- */

    /* Les inventaires des entites sont alloués dans la fonction de creation des mobs */
    personnage = creer_personnage(personnage); 
    slime_vert = creer_monstre(slime_vert, "Slime_Vert");
    satan = creer_boss(satan, "Satan");

    /* ----------- On regarde si les entites ont bien été initialisés ----------- */
    if(personnage != NULL) nb_entite_init++;
    if(slime_vert != NULL) nb_entite_init++;
    if(satan != NULL) nb_entite_init++;

    printf("Nombres d'entites crees : %d", nb_entite_init);

    printf("----------------------------------------------------- \n");
    printf("*       Test sur la création des inventaires :      * \n");
    printf("----------------------------------------------------- \n");

    /* - Creation des inventaires des entites qui en ont un (donc pas les boss) - */
    personnage = init_inventaire_personnage(personnage);
    slime_vert = init_inventaire_monstre(slime_vert);

    /* ------------------------ Affichage de l'inventaire ----------------------- */  
    printf("Affichage des inventaires avant le loot : \n");
    afficher_inventaire(personnage);
    afficher_inventaire(slime_vert);
    afficher_inventaire(satan);

    /* ----- On remarque que rien n'est affiche pour satan ce qui est normal ---- */

    printf("----------------------------------------------------- \n");
    printf("*             Test sur le loot des mobs             * \n");
    printf("----------------------------------------------------- \n");

    looter(slime_vert, personnage);

    printf("Affichage des inventaires apres le loot : \n");
    afficher_inventaire(personnage);
    afficher_inventaire(slime_vert);
    afficher_inventaire(satan);

    
    printf("\n----------------------------------------------------- \n");
    printf("*         Test de destruction des entitees :        * \n");
    printf("----------------------------------------------------- \n");

    /* -------------------- Destruction des differentes entites -------------------- */
   
    detruire_personnage(&personnage);
    detruire_mob(&slime_vert);
    detruire_boss(&satan);

    /* ----------- On regarde si les entites ont bien été détruites ----------- */

    if(personnage == NULL) nb_entite_init--;
    if(slime_vert == NULL) nb_entite_init--;
    if(satan == NULL) nb_entite_init--;

    /* ---------------- Affichage du nombre d'entités detruites --------------- */

    printf("\n Nombre d'entites restantes : %d \n\n", nb_entite_init);


}