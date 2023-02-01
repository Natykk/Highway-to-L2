#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <entite.h>
#include <objet.h>

/**
 * @file inventaire.c
 * @brief Fichier d'en-tete pour les primitives liées aux entites
 * @author GEORGET Rémy, GALLAIS Matéo.
 * @version 1.0
 * @date 31/01/2023
 */


void looter(objet_inv_t * inventaire){
    char obj[50];
    printf("Quel objet voulez vous looter ? : ");
    scanf("%s", obj);

    int rang = acces_obj(obj);

    

    (inventaire[rang]->nb)++;
}

/**
 * @brief Test de l'inventaire avec utilisation des primitives
 * et des structures de données liées aux objets.
 * @return int 
 */
int main(){
    return 0;
}