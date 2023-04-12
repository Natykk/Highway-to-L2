
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
    {"Slime_Vert", 2, 1, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1, 1, HAUT},
    {"Loup", 10, 4, 1.0, 1.2, 8, 0, 0, NULL, NULL, 2, 1, HAUT},
    {"Brigant", 20, 6, 0.9, 1.1, 7, 0, 0, NULL, NULL, 1, 1, HAUT},
    {"Chaman", 12, 12, 0.8, 1, 9, 0, 0, NULL, NULL, 2, 1, HAUT},
    {"Slime_Gris", 10, 5, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1, 1, HAUT},
    {"Nain", 30, 8, 0.75, 0.40, 5, 0, 0, NULL, NULL, 2, 1, HAUT},
    {"Nain_Rider", 20, 5, 1.5, 1.2, 10, 0, 0, NULL, NULL, 3, 1, HAUT},
    {"Orc", 80, 20, 0.10, 0.20, 8, 0, 0, NULL, NULL, 2, 1, HAUT},
    {"Slime_Rouge", 50, 25, 0.75, 0.40, 6, 0, 0, NULL, NULL, 1, 1, HAUT},
    {"Diablotin", 40, 40, 1.4, 1.0, 5, 0, 0, NULL, NULL, 3, 1, HAUT},
    {"Diable", 80, 80, 0.8, 1.2, 10, 0, 0, NULL, NULL, 2, 1, HAUT},
    {"Cerbere", 200, 100, 1.8, 0.7, 12, 0, 0, NULL, NULL, 2, 1, HAUT}};

entite_t tab_boss[NB_BOSS] = {
    {"Volibeer", 400, 25, 0.5, 1, 10, 0, 0, NULL, NULL, 0, 1, HAUT},
    {"Darick", 800, 40, 1, 0.25, 15, 0, 0, NULL, NULL, 0, 1, HAUT},
    {"Satan", 1500, 150, 2, 2, 15, 0, 0, NULL, NULL, 0, 1, HAUT}};

/**
 * @fn afficher_entite
 * @brief Fonction qui permet d'afficher une entitée
 *
 * @param entite
 */
extern void afficher_entite(entite_t *entite)
{
    switch (entite->persoOuMob)
    {
    case 0:
        printf("[PERSO] ");
        break;

    case 1:
        printf("[MOB] ");
        break;
        
    case 2:
        printf("[BO] ");
        break;


    default:
        printf("[] ");
        break;
    }

    printf("Nom : %s [%d-%d]\n", entite->nom, entite->x, entite->y);

    printf("Classe : ");
    if (entite->arbre != NULL)
    {
        switch (entite->arbre->classe)
        {
        case ARCHER:
            printf("ARCHER\n");
            break;
        case ASSASSIN:
            printf("ASSASSIN\n");
            break;
        case MAGE:
            printf("MAGE\n");
            break;
        case GUERRIER:
            printf("GUERRIER\n");
            break;
        default:
            break;
        }
    }
    else
    {
        printf("Aucune classe\n");
    }
    printf(" - Vie : %.2f\n", entite->vie);
    printf(" - Dégats : %.2f\n", entite->degats);
    printf(" - Vitesse d'attaque : %.2f\n", entite->vitesse_att);
    printf(" - Vitesse de déplacement : %.2f\n", entite->vitesse_depl);
    switch (entite->persoOuMob)
    {
    case 0:
        printf(" - Bonus de diminution du périmètre de detction des mobs : %d\n", entite->perim_detect);
        break;
    case 1:
        printf(" - Périmètre de détection : %d\n", entite->perim_detect);
        break;
    default:
        break;
    }
}

/**
 * @fn associer_entite
 * @brief Fonction qui permet de faire '=' mais pour une entitée
 *
 * @param source
 * @param destination
 */
extern void associer_entite(entite_t *source, entite_t *destination)
{
    strcpy(source->nom, destination->nom);
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
extern int acces_mob(char *chaine)
{
    for (int i = 0; i < NB_MOBS; i++)
    {
        if (!strcmp(tab_mob[i].nom, chaine))
        {
            return i;
        }
    }
    return -1;
}

extern int acces_boss(char *chaine)
{
    for (int i = 0; i < NB_BOSS; i++)
    {
        if (!strcmp(tab_boss[i].nom, chaine))
        {
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
extern entite_t *creer_personnage(entite_t *entite)
{
    entite = malloc(sizeof(entite_t));
    entite->nom = malloc(sizeof(char) * 35);
    //strcpy(entite->nom, "Bon Scott");

    entite->vie = 999;
    entite->degats = 999;
    entite->vitesse_att = 1.0;
    entite->vitesse_depl = 1.0;
    entite->perim_detect = 0;
    entite->x = 0;
    entite->y = 0;
    entite->place_inv = NB_OBJET;
    entite->inventaire = malloc(sizeof(objet_inv_t));
    entite->inventaire->nb = malloc(sizeof(int) * entite->place_inv);
    entite->inventaire->objet = malloc(sizeof(objet_t) * entite->place_inv);
    entite->persoOuMob = 0;
    entite->arbre = NULL;

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
extern entite_t *creer_monstre(entite_t *entite, char *nom)
{
    int emplacement = acces_mob(nom);
    int taille_nom = strlen(tab_mob[emplacement].nom);

    entite = malloc(sizeof(entite_t));
    entite->nom = malloc(sizeof(char) * (taille_nom + 1));

    strcpy(entite->nom, tab_mob[emplacement].nom);

    entite->vie = tab_mob[emplacement].vie;
    entite->degats = tab_mob[emplacement].degats;
    entite->vitesse_att = tab_mob[emplacement].vitesse_att;
    entite->vitesse_depl = tab_mob[emplacement].vitesse_depl;
    entite->perim_detect = tab_mob[emplacement].perim_detect;

    entite->x = tab_mob[emplacement].x;
    entite->y = tab_mob[emplacement].y;

    entite->place_inv = tab_mob[emplacement].place_inv;
    entite->inventaire = malloc(sizeof(objet_inv_t));
    entite->inventaire->objet = malloc(sizeof(objet_t) * entite->place_inv);
    entite->inventaire->nb = malloc(sizeof(int) * (entite->place_inv));

    entite->persoOuMob = tab_mob[emplacement].persoOuMob;
    entite->dir = tab_mob[emplacement].dir;

    entite->arbre = NULL;

    return entite;
}

extern entite_t *creer_boss(entite_t *entite, char *nom)
{
    int emplacement = acces_boss(nom);
    int taille_nom = strlen(tab_boss[emplacement].nom);

    entite = malloc(sizeof(entite_t));
    entite->nom = malloc(sizeof(char)*(taille_nom+1));

    strcpy(entite->nom, tab_boss[emplacement].nom);

    entite->vie = tab_boss[emplacement].vie;
    entite->degats = tab_boss[emplacement].degats;
    // printf("degats : %f \n", entite->degats);
    entite->vitesse_att = tab_boss[emplacement].vitesse_att;
    entite->vitesse_depl = tab_boss[emplacement].vitesse_depl;
    entite->perim_detect = tab_boss[emplacement].perim_detect;
    entite->x = tab_boss[emplacement].x;
    entite->y = tab_boss[emplacement].y;

    entite->persoOuMob = tab_mob[emplacement].persoOuMob;
    entite->dir = tab_boss[emplacement].dir;

    entite->inventaire = NULL;

    entite->arbre = NULL;

    return entite;
}

/**
 * @fn detruire_entitee
 * @brief Fonction pour libérer la memoire utilisé pour les entités
 * @param entite
 * @return rien
 */
extern void detruire_entitee(entite_t **entite)
{
    // Destruction du nom de l'entite
    if ((*entite)->nom != NULL)
    {
        free((*entite)->nom);
        (*entite)->nom = NULL;
    }

    // Destruction de l'inventaire
    if ((*entite)->inventaire != NULL)
    {
        if ((*entite)->inventaire->objet != NULL)
        {
            free((*entite)->inventaire->objet);
            (*entite)->inventaire->objet = NULL;
        }

        if ((*entite)->inventaire->nb != NULL)
        {
            free((*entite)->inventaire->nb);
            (*entite)->inventaire->nb = NULL;
        }

        free((*entite)->inventaire);
        (*entite)->inventaire = NULL;
    }

    // Destruction de l'entitee
    if((*entite) != NULL) {
        free((*entite));
        (*entite) = NULL;
    }
}

/**
 * @fn detruire_personnage
 * @brief Fonction qui detruit le personnage
 * 
 * @param personnage 
 */
extern void detruire_personnage(entite_t **personnage) {

    // Destruction de l'inventaire
    free((*personnage)->inventaire->objet);
    (*personnage)->inventaire->objet = NULL;

    free((*personnage)->inventaire->nb);
    (*personnage)->inventaire->nb = NULL;

    free((*personnage)->inventaire);
    (*personnage)->inventaire = NULL;

    // Destruction du nom
    free((*personnage)->nom);
    (*personnage)->nom = NULL;

    // Destruction de l'entitee
    free((*personnage));
    (*personnage) = NULL;
}

/**
 * @fn detruire_mob
 * @brief Fonction qui detruit un mob
 * 
 * @param mob 
 */
extern void detruire_mob(entite_t **mob) {

    // Destruction de l'inventaire
    free((*mob)->inventaire->objet);
    (*mob)->inventaire->objet = NULL;

    free((*mob)->inventaire->nb);
    (*mob)->inventaire->nb = NULL;

    free((*mob)->inventaire);
    (*mob)->inventaire = NULL;

    // Destruction du nom
    free((*mob)->nom);
    (*mob)->nom = NULL;

    // Destruction de l'entitee
    free((*mob));
    (*mob) = NULL;
}
/**
 * @fn detruire_boss
 * @brief Fonction qui detruit un boss
 * 
 * @param boss 
 */
extern void detruire_boss(entite_t **boss) {

    // Destruction du nom
    free((*boss)->nom);
    (*boss)->nom = NULL;

    // Destruction de l'entitee
    free((*boss));
    (*boss) = NULL;
}

