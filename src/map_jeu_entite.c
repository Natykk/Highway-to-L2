/**
 * \file map_jeu_entite.c
 * \brief Fichier contenant les fonctions principal du jeu
*/
#include <stdbool.h>
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../head/entite.h"
#include "../head/mapBoss.h"
#include "../head/chemin.h"
#include "../head/inventaire.h"
#include "../head/sauvegarde.h"
#include "../head/attaques.h"
#include "../head/menu_cpt.h"
#include "../head/name.h"
int NumEtage = 0;
SDL_Texture *tab_tex[10] = {NULL};

#define TILE_SIZE 32
#define DIM_SALLE 25
#define DIM_SALLE 25

#define BAR_WIDTH 400
#define BAR_HEIGHT 10

int coords[9][2] = { 0 };
#define SPRITE_FRAMES 4 // Nombre de frames de l'animation
const int hauteur_fenetre = LONG_SALLE_BOSS * TILE_SIZE;
const int largeur_fenetre = LARG_SALLE_BOSS * TILE_SIZE;

/**
 * \fn charge_tex(SDL_Renderer *renderer,char *path,int bmp_flag)
 * @brief Charge une texture
 * @param renderer Le renderer
 * @param path Le chemin de la texture
 * @param bmp_flag Si la texture est au format bmp
 * @return La texture
 */
SDL_Texture *charge_tex(SDL_Renderer *renderer, char *path, int bmp_flag)
{
    SDL_Surface *surface = (bmp_flag == 1) ? SDL_LoadBMP(path) : IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture *choix_tex_niv(SDL_Renderer *renderer)
{
    if(tab_tex[0]!=NULL){
        for(int i=0;i<10;i++){
            if(tab_tex[i]!=NULL){
                SDL_DestroyTexture(tab_tex[i]);
            }
        }
    }
    tab_tex[2] = charge_tex(renderer, "../img/foret/wooden_door.png", 0); // Porte
    tab_tex[5] = charge_tex(renderer, "../img/personnage/1_north.png", 0);
    tab_tex[6] = charge_tex(renderer, "../img/personnage/1_south.png", 0);
    tab_tex[7] = charge_tex(renderer, "../img/personnage/1_side.png", 0);
    tab_tex[3]=charge_tex(renderer, "../img/personnage/marchand.png", 0);
    if (NumEtage == 0)
    { // Foret
        tab_tex[0] = charge_tex(renderer, "../img/foret/bush.png", 0); // Mur 
        tab_tex[1] = charge_tex(renderer, "../img/foret/floor_grass.png", 0); // Sol 
       
        tab_tex[4] = charge_tex(renderer, "../img/foret/souche.png", 0); // obstacle
        tab_tex[8] = charge_tex(renderer, "../img/foret/GreenSlime/GrnSheet.png", 0); // mob 1
        //tab_tex[9] = charge_tex(renderer, "../img/foret/BlueSlime/Blue_Idle1.png", 0);
    }
    else if (NumEtage == 1)
    { // Mine
        tab_tex[0] = charge_tex(renderer, "../img/mines/mur_mine.png", 0); // Mur 
        tab_tex[1] = charge_tex(renderer, "../img/mines/sol.jpg", 0); // Sol 
        // tab_tex[3]=charge_tex(renderer, "../img/mine/Idle-Sheet.png", 0);
        tab_tex[4] = charge_tex(renderer, "../img/mines/rock.png", 0); // obstacle
        tab_tex[8] = charge_tex(renderer, "../img/mines/GreySlime/Whitesheet.png", 0); // mob 1
    }
    else if (NumEtage == 2)
    { // Enfer
        tab_tex[0] = charge_tex(renderer, "../img/enfer/mur_enfer.png", 0); // Mur 
        tab_tex[1] = charge_tex(renderer, "../img/enfer/floor_hell.png", 0); // Sol 
        //tab_tex[3]=charge_tex(renderer, "../img/enfer/Idle-Sheet.png", 0);
        tab_tex[4] = charge_tex(renderer, "../img/enfer/rock.png", 0); // obstacle
        tab_tex[8] = charge_tex(renderer, "../img/enfer/RedSlime/GrnSheet.png", 0); // mob 1
    }
}
/**
 *  \fn float distance(entite_t* entite1, entite_t* entite2)
 *  \brief Calcule la distance entre deux entites
 *  @param entite1 L'entite 1
 *  @param entite2 L'entite 2
 *  @return La distance entre les deux entites
 */
float distance(entite_t *entite1, entite_t *entite2)
{
    if (entite1 != NULL && entite2 != NULL)
    {
        float dx = entite1->x - entite2->x;
        float dy = entite1->y - entite2->y;
        return sqrt(dx * dx + dy * dy);
    }
    return 100;
}
void sauvegarde_salle(t_salle *salle, t_salle *map)
{
    salle->nb_mobs = map->nb_mobs;
    salle->nb_porte = map->nb_porte;
    salle->num_salle = map->num_salle;
    salle->statut = map->statut;
    memcpy(salle->mob, map->mob, sizeof(map->mob));
    memcpy(salle->dim, map->dim, sizeof(map->dim));
}
/**
 * \fn transfert(t_salle salle, t_salle * map)
 *  \brief Transfert la salle dans la map
 *  @param salle La salle
 *  @param map La map
 *  @param type Le type de salle
 */
void transfert(t_salle *salle, t_salle *map, int type)
{
    // printf("Transfert de la salle %d\n",salle.num_salle);
    int i, j;

    map->nb_mobs = salle->nb_mobs;
    map->nb_porte = salle->nb_porte;
    map->num_salle = salle->num_salle;
    map->statut = salle->statut;
    if (type == 2)
    {
        for (i = 0; i <= LARG_MARCHAND; i++)
        {
            for (j = 0; j <= LONG_MARCHAND; j++)
            {
                map->dim[i][j] = salle->dim[i][j];
            }
        }
    }
    else if (type == 1)
    {
        for (i = 0; i < LARG_SALLE_BOSS; i++)
        {
            for (j = 0; j < LONG_SALLE_BOSS; j++)
            {
                map->dim[i][j] = salle->dim[i][j];
            }
        }
    }
    else
    {
        for (i = 0; i < salle->nb_mobs; i++)
        {
            map->mob[i] = salle->mob[i];

            // printf("Mob %s -> degats %f\n",map->mob[i]->nom,map->mob[i]->degats);
        }
        for (i = 0; i < DIM_SALLE; i++)
        {
            for (j = 0; j < DIM_SALLE; j++)
            {
                map->dim[i][j] = salle->dim[i][j];
            }
        }
    }
}
/**
 * \fn void changement(t_niv * niv,entite_t* perso, t_pos * posSalle, t_salle * map)
 * \brief Change de salle
 * @param niv Le niveau
 * @param perso Le personnage
 * @param posSalle La position de la salle
 * @param map La map
 *
 */
void changement(t_niv *niv, entite_t *perso, t_pos *posSalle, t_salle *map)
{
    if (map->nb_mobs <= 0)
    {
        // si tu est au moins a la deuxieme salle
        if (niv->etages[NumEtage].etage[posSalle->x][posSalle->y].statut != START)
        {
            printf("Sauvegarde de la salle %d\n", niv->etages[NumEtage].etage[posSalle->x][posSalle->y].num_salle);
            sauvegarde_salle(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map);
        }
        if (perso->dir == HAUT)
        {
            posSalle->y--;
            perso->y = DIM_SALLE - 2;
            perso->x = (DIM_SALLE / 2) - 1;
        }
        else if (perso->dir == DROITE)
        {
            posSalle->x++;
            perso->x = 1;
            perso->y = (DIM_SALLE / 2) - 1;
        }
        else if (perso->dir == BAS)
        {
            posSalle->y++;
            perso->y = 1;
            perso->x = (DIM_SALLE / 2) - 1;
        }
        else if (perso->dir == GAUCHE)
        {
            posSalle->x--;
            perso->x = DIM_SALLE - 2;
            perso->y = (DIM_SALLE / 2) - 1;
        }
        transfert(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map, 0);
        // map->num_salle=niv->etages[NumEtage].etage[posSalle->x][posSalle->y].num_salle;
        map->dim[perso->x][perso->y] = PERSO;
        if (niv->etages[NumEtage].boss == 1)
        {
            printf("Vous avez battu le boss\n");
            niv->etages[NumEtage].boss = 0;
            detruireSalleBoss(&niv->etages->Boss);
            niv->etages[NumEtage].marchand = 1;
        }
        else if (map->statut == EXIT)
        {
            printf("C\'est l'heure du boss\n");
            // initialise la matrice de la salle Boss
            niv->etages[NumEtage].Boss = genererSalleBoss(niv->etages->Boss);
            transfert(niv->etages[NumEtage].Boss, map, 1);
            map->nb_porte = 1;
            perso->x = LARG_SALLE_BOSS / 2;
            perso->y = 4;
            map->dim[perso->x][perso->y] = PERSO;
            niv->etages[NumEtage].boss = 1;
        }
        if (niv->etages[NumEtage].marchand == 1)
        {
            printf("C'est l'heure du marchand\n");
            // initialise la matrice de la salle Marchand
            niv->etages[NumEtage].Marchand = genererSalleMarchand(niv->etages->Marchand);
            transfert(niv->etages[NumEtage].Marchand, map, 2);
            map->nb_porte = 1;
            perso->y = 1;
            perso->x = (LARG_MARCHAND / 2) - 1;
            map->dim[perso->x][perso->y] = PERSO;
            sauvegarde(perso, NumEtage);
        }
        // printf("Salle n°%d\n", map->num_salle);
    }
}
/**
 * \fn void chemin_vers_perso(entite_t * perso, entite_t * mob, int map[][LONG_SALLE_BOSS])
 * \brief Calcul le chemin vers le perso
 * @param perso Le personnage
 * @param mob Le mob
 * @param map La map
 *
 */
void chemin_vers_perso(entite_t *perso, entite_t *mob, int map[][LONG_SALLE_BOSS])
{
    int mat[9][9];
    int i, j;

    int POSPERSX;
    int POSPERSY;
    // initialisation de la matrice mat
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            // met la valeurs tout autour de la matrice à 1
            if (i == 0 || i == 8 || j == 0 || j == 8)
            {
                mat[i][j] = 1;
            }
            // prend en compte les murs de la salle
            else if (map[i - 1][j - 1] == MUR)
            {
                mat[i][j] = 1;
            }
            // prend en compte les portes de la salle
            else if (map[i - 1][j - 1] == PORTE)
            {
                mat[i][j] = 1;
            }
            else{
                mat[i][j] = 0;
            }
        }
    }
    // Met à jour la position du mob par rapport à la matrice mat
    POSPERSX = perso->x - (mob->x - 4);
    POSPERSY = perso->y - (mob->y - 4);
    // Met à jour la position du personnage par rapport à la matrice mat
    mat[POSPERSX][POSPERSY] = 0;

    // Met à jour la position du mob par rapport à la matrice mat
    mat[4][4] = 0;

    chercher_chemin(4, 4, POSPERSX, POSPERSY, mat, coords);
    // conversion des coordonnées X et Y de la matrice mat  en coordonnées de la matrice map
    for (i = 0; i < 9; i++)
    {
        if (coords[i][0] == 0 || coords[i][1] == 0)
        {
            break;
        }
        coords[i][0] += (mob->x - 4);
        coords[i][1] += (mob->y - 4);
    }
}

/**
 * \fn void mouvement(t_salle *map, entite_t *pers, t_pos *posSalle, t_niv *niv)
 * \brief Fonction qui gère le déplacement du personnage
 * \param map Pointeur sur la salle
 * \param pers Pointeur sur le personnage
 * \param posSalle Pointeur sur la position de la salle
 * \param niv Pointeur sur le niveau
 * \return Rien
 */
void mouvement(t_salle *map, entite_t *pers, t_pos *posSalle, t_niv *niv, SDL_Renderer *renderer)
{
    int x = pers->x;
    int y = pers->y;
    if (pers->dir == HAUT)
    {
        if (map->dim[x][y - 1] == PORTE && pers->persoOuMob == 0)
        { // Si la case du haut est une porte
            map->dim[x][y] = VIDE;
            changement(niv, pers, posSalle, map);
        }
        if (map->dim[x][y - 1] == VIDE)
        {                // Si la case du haut n'est pas un mur
            pers->x = x; // On met à jour la position du perso
            pers->y = y - 1;
            if (pers->persoOuMob)
            {

                int ValMob = map->dim[x][y];
                map->dim[pers->x][pers->y] = ValMob;
            }
            else
            {
                map->dim[pers->x][pers->y] = PERSO;
            }
            // map[(y-1)*DIM_SALLE+x] = 5; // On met le perso sur la case du haut
            map->dim[x][y] = VIDE; // map[y*DIM_SALLE+x] = 0; // On met la case du perso à vide
            // printf("Bouge vers le haut\n");
        }
    }
    else if (pers->dir == BAS)
    {
        if (map->dim[x][y + 1] == PORTE && pers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            changement(niv, pers, posSalle, map);
        }
        else if (map->dim[x][y + 1] == VIDE)
        {
            pers->x = x;
            pers->y = y + 1;
            if (pers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[pers->x][pers->y] = ValMob;
            }
            else
            {
                map->dim[pers->x][pers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers le bas\n");
        }
    }
    else if (pers->dir == GAUCHE)
    {
        if (map->dim[x - 1][y] == PORTE && pers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            changement(niv, pers, posSalle, map);
        }
        else if (map->dim[x - 1][y] == VIDE)
        {
            pers->x = x - 1;
            pers->y = y;
            if (pers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[pers->x][pers->y] = ValMob;
            }
            else
            {
                map->dim[pers->x][pers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers la gauche\n");
        }
    }
    else if (pers->dir == DROITE)
    {
        if (map->dim[x + 1][y] == PORTE && pers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            // si on est dans la salle du marchand on change de niveau
            if (niv->etages[NumEtage].marchand == 1)
            {
                NumEtage++;
                niv->etages[NumEtage].marchand = 0;
                *posSalle = trouverSalle(1, &niv->etages[NumEtage]);
                transfert(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map, 0);
                pers->x = DIM_SALLE / 2;
                pers->y = DIM_SALLE / 2;
                choix_tex_niv(renderer);
            }
            else
            {
                changement(niv, pers, posSalle, map);
            }
        }
        else if (map->dim[x + 1][y] == VIDE)
        {
            pers->x = x + 1;
            pers->y = y;
            if (pers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[pers->x][pers->y] = ValMob;
            }
            else
            {
                map->dim[pers->x][pers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers la droite\n");
        }
    }
}
/**
 * \fn void perso_attack( t_salle * map,int attaque, entite_t* pers)
 * \brief Gère l'attaque du perso
 * @param map La map
 * @param attaque Si le perso attaque
 * @param pers Le personnage
 **/
int perso_attack(t_salle *map, int attaque, entite_t *pers, void (*attaque_pers)(proj_t, entite_t*,t_salle*),SDL_Window* window,SDL_Renderer* renderer,TTF_Font* police)
{
    int x = pers->x;
    int y = pers->y;
    proj_t proj = AUCUN_PROJ;
    if(pers->arbre != NULL){
        switch(pers->arbre->classe){
            case MAGE: proj = BOULE; break;
            case ARCHER: proj = FLECHE; break;
            default: proj = AUCUN_PROJ;
        }
    }else{
        proj = AUCUN_PROJ;
    }
    attaque_pers(proj, pers, map);
}

/**
 * \fn int enemy_attack(t_salle * map, entite_t* pers, SDL_Rect * rect)
 * \brief Fonction qui permet de faire attaquer les mobs
 * \param map la map
 * \param pers la position du joueur
 * \param rect les points de vie du joueur
 * \return 1 si le joueur a perdu des points de vie, 0 sinon
 */
int enemy_attack(t_salle *map, entite_t *pers, SDL_Rect *rect)
{
    int x = pers->x;
    int y = pers->y;
    if (rect->w > 0)
    {
        if (map->dim[x][y - 1] >= 10 && map->dim[x][y - 1] <= 21)
        { // si il y a un ennemi sur la case du bas
            // printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x][y-1])-10]->degats,map->mob[(map->dim[x][y-1])-10]->nom);
            // rect->w-=(int)(map->mob[(map->dim[x][y-1])-10]->degats);
            return 1;
        }
        if (map->dim[x][y + 1] >= 10 && map->dim[x][y + 1] <= 21)
        { // si il y a un ennemi sur la case du haut
            // printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x][y+1])-10]->degats,map->mob[(map->dim[x][y+1])-10]->nom);
            // rect->w-=(int)map->mob[(map->dim[x][y+1])-10]->degats;
            return 1;
        }
        if (map->dim[x - 1][y] >= 10 && map->dim[x - 1][y] <= 21)
        { // si il y a un ennemi sur la case de droite
            // printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x-1][y])-10]->degats,map->mob[(map->dim[x-1][y])-10]->nom);
            // rect->w-=(int)map->mob[(map->dim[x-1][y])-10]->degats;
            return 1;
        }
        if (map->dim[x + 1][y] >= 10 && map->dim[x + 1][y] <= 21)
        { // si il y a un ennemi sur la case de gauche
            // printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x+1][y])-10]->degats,map->mob[(map->dim[x+1][y])-10]->nom);
            // rect->w-=(int)(map->mob[(map->dim[x+1][y])-10]->degats);
            return 1;
        }
        if (rect->w < 250)
        { // si le perso n'est pas en combat
            rect->w += 2;
        }
    }
    return 0;
}

/**
 * \fn void interact(int attaque, t_salle *map, entite_t *pers, SDL_Rect *rect, Uint32 *lastTime, t_pos *posSalle, t_niv *niv)
 * \brief Fonction qui permet de faire interagir le joueur avec les mobs
 * \param attaque 1 si le joueur attaque, 0 sinon
 * \param map la map
 * \param pers le joueur
 * \param rect les points de vie du joueur
 * \param lastTime le temps du dernier tour
 * \param posSalle la position de la salle dans l'étage
 * \param niv le niveau
 * \return void
 */
void interact(int attaque, t_salle *map, entite_t *pers, Uint32 *lastTime, t_pos *posSalle, t_niv *niv, SDL_Renderer *renderer)
{
    int nbNULL = 0;
    for (int i = 0; i < map->nb_mobs; i++)
    {
        if (map->mob[i] == NULL)
        {
            nbNULL++;
        }
    }
    if (nbNULL == map->nb_mobs)
    {
        map->nb_mobs = 0;
    }
    for (int i = 0; i < map->nb_mobs; i++) // pour chaque mob présent sur la carte
    {
        int cheminX, cheminY;
        float dist;
        if (map->mob[i] != NULL && distance(pers, map->mob[i]) <= 4) // si le mob est à moins de 4 cases du joueur
        {
            for (int j = 0; j < 10; j++) // on réinitialise le tableau de coordonnées
            {
                coords[j][0] = 0;
                coords[j][1] = 0;
            }
            chemin_vers_perso(pers, map->mob[i], map->dim); // on calcule le chemin vers le joueur
            // on récupère les coordonnées de la première case du chemin
            cheminX = map->mob[i]->x - coords[0][0];
            cheminY = map->mob[i]->y - coords[0][1];
            // on change la direction du mob en fonction de la case suivante
            if (cheminX > 0) // si le mob est à droite du joueur
            {
                map->mob[i]->dir = 3;
            }
            if (cheminX < 0) // si le mob est à gauche du joueur
            {
                map->mob[i]->dir = 1;
            }
            if (cheminY > 0) // si le mob est en dessous du joueur
            {
                map->mob[i]->dir = 0;
            }
            if (cheminY < 0) // si le mob est au-dessus du joueur
            {
                map->mob[i]->dir = 2;
            }
            // on fait bouger le mob si il est pas mort
            if (map->mob[i] != NULL)
            { // si le mob n'est pas mort
                mouvement(map, map->mob[i], posSalle, niv, renderer);
            }
        }
        else // si le mob est trop loin pour attaquer
        {
            // on choisit une direction aléatoire pour le mob
            if (map->mob[i] != NULL)
            { // si le mob n'est pas mort
                map->mob[i]->dir = rand() % 4;
                mouvement(map, map->mob[i], posSalle, niv, renderer);
            }
        }
    }
}

/**
 *\fn void rendu(int map[][LONG_SALLE_BOSS],int tailleI,int tailleJ,SDL_Renderer *renderer,SDL_Texture* tab_tex[10],SDL_Rect dstRect,SDL_Rect Door,SDL_Rect srcRect,SDL_Rect PersRect,entite_t* perso,int attaque,int frame)
 * \brief Fonction qui permet de faire le rendu de la map
 * \param map la map
 * \param tailleI la taille de la map en largeur
 * \param tailleJ la taille de la map en hauteur
 * \param renderer le renderer
 * \param tab_tex le tableau de texture
 * \param dstRect la destination de la texture
 * \param Door la destination de la porte
 * \param srcRect la source de la texture
 * \param PersRect la destination du personnage
 * \param perso le personnage
 * \param attaque si le personnage attaque
 * \param frame la frame du personnage
 */
void rendu(int map[][LONG_SALLE_BOSS], int tailleI, int tailleJ, SDL_Renderer *renderer, SDL_Texture *tab_tex[10], SDL_Rect dstRect, SDL_Rect Door, SDL_Rect srcRect, SDL_Rect PersRect, entite_t *perso, int attaque, int frame)
{
    int tailleRenduX = tailleI * TILE_SIZE;
    int tailleRenduY = tailleJ * TILE_SIZE;

    // Détermination du point de départ pour le rendu
    int departX = (largeur_fenetre - tailleRenduX) / 2;
    int departY = (hauteur_fenetre - tailleRenduY) / 2;
    SDL_Rect salle = {(largeur_fenetre - tailleRenduX) / 2, (hauteur_fenetre - tailleRenduY) / 2,tailleRenduX, tailleRenduY};
    SDL_RenderCopy(renderer,tab_tex[1],NULL,&salle);
    for (int x = 0; x < tailleI; x++)
    {
        int posX = departX + x * TILE_SIZE;
        for (int y = 0; y < tailleJ; y++)
        { // On parcourt la map
            int posY = departY + y * TILE_SIZE;
            if (map[x][y] == PORTE)
            { // Porte
                SDL_Texture *DoorTex = tab_tex[2];
                dstRect.x = posX;
                dstRect.y = posY;
                Door.w = 16; // Largeur de la frame
                Door.y = 0;
                Door.h = 16; // Hauteur de la frame
                if (x == tailleI - 1)
                { // si la porte est a droite
                    SDL_RenderCopyEx(renderer, DoorTex, &Door, &dstRect, 90, NULL, SDL_FLIP_HORIZONTAL);
                }
                else if (x == 0)
                { // si la porte est a gauche
                    SDL_RenderCopyEx(renderer, DoorTex, &Door, &dstRect, 270, NULL, SDL_FLIP_NONE);
                }
                else if (y == tailleJ - 1)
                { // si la porte est en bas
                    SDL_RenderCopyEx(renderer, DoorTex, &Door, &dstRect, 0, NULL, SDL_FLIP_VERTICAL);
                }
                else if (y == 0)
                { // si la porte est en haut
                    SDL_RenderCopyEx(renderer, DoorTex, &Door, &dstRect, 0, NULL, SDL_FLIP_NONE);
                }
                else
                {
                    // coordonnées de la porte 
                    printf("x : %d y : %d | x==tailleI y==tailleJ\n", x, y);
                    SDL_RenderCopyEx(renderer, tab_tex[2], &Door, &dstRect, 0, NULL, SDL_FLIP_NONE);
                }
            }
            if (map[x][y] >= 10 && map[x][y] < 22)
            {
                SDL_Rect MobRect;
                MobRect.x = frame * 16; // Combien de Pixel on doit décaler pour afficher la bonne frame
                MobRect.w = 16;         // Largeur de la frame
                MobRect.y = 0;
                MobRect.h = 16; // Hauteur de la frame

                dstRect.x = posX; // Position de la frame
                dstRect.y = posY; // Position de la frame
                SDL_RenderCopyEx(renderer, tab_tex[8], &MobRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
               /* if (map[x][y] == 10)
                {
                    SDL_RenderCopyEx(renderer, tab_tex[8], &MobRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
                    // printf("Vie du mob : %d",map.mob[map.dim[x][y]-10].vie);
                }
                else
                {

                    SDL_RenderCopyEx(renderer, tab_tex[9], NULL, &dstRect, 0, NULL, SDL_FLIP_NONE);
                }*/
            }
            if (map[x][y] == PERSO)
            { // Si c'est le perso
                // printf("x = %d, y = %d perso trouvé\n",x,y);
                PersRect.x = frame * 20; // Combien de Pixel on doit décaler pour afficher la bonne frame
                PersRect.w = 20;         // Largeur de la frame
                PersRect.y = 0;
                PersRect.h = 24;        // Hauteur de la frame
                dstRect.x = posX;       // Position de la frame
                dstRect.y = posY;       // Position de la frame
                if (perso->dir == HAUT) // On affiche le perso dans la bonne direction
                    SDL_RenderCopyEx(renderer, tab_tex[5], &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
                if (perso->dir == BAS)
                    SDL_RenderCopyEx(renderer, tab_tex[6], &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
                if (perso->dir == GAUCHE)
                    SDL_RenderCopyEx(renderer, tab_tex[7], &PersRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
                if (perso->dir == DROITE)
                    SDL_RenderCopyEx(renderer, tab_tex[7], &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
                if (attaque)
                {
                    SDL_RenderCopy(renderer, tab_tex[0], &srcRect, &dstRect);
                }
            }
            if (map[x][y] == MUR)
            {                     // Si c'est un mur
                dstRect.x = posX; // Position du mur
                dstRect.y = posY;
                SDL_RenderCopy(renderer, tab_tex[0], &srcRect, &dstRect); // On affiche le mur
            }
            if (map[x][y] == OBSTACLE)
            {
                dstRect.x = posX; // Position de l'obstacle
                dstRect.y = posY;
                SDL_RenderCopy(renderer, tab_tex[4], NULL, &dstRect); // On affiche l'obstacle
            }
            if (map[x][y] == MARCHAND)
            {
                SDL_Rect Marchand;
                Marchand.x = frame * 47; // Combien de Pixel on doit décaler pour afficher la bonne frame
                Marchand.w = 47;         // Largeur de la frame
                Marchand.y = 0;
                Marchand.h = 38;        // Hauteur de la frame
                dstRect.x = posX;       // Position de la frame
                dstRect.y = posY; 
                SDL_RenderCopy(renderer, tab_tex[3], &Marchand, &dstRect); // On affiche l'obstacle
            }
        }
        // printf("\n");
    }

}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    entite_t * perso = NULL;
    perso = creer_personnage(perso);
    perso = init_inventaire_personnage(perso);
    SDL_Window *window = SDL_CreateWindow("Highway to L2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur_fenetre, hauteur_fenetre, 0); // On crée la fenêtre
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);                               // On crée le renderer
    if(menu(window, renderer, perso) == 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    
    if(!sauvegarde(perso, 0)){
        printf("problème lors de la sauvegarde\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    int i;
    
    t_niv *niv = malloc(sizeof(t_niv));
    genererNiv(niv);
    t_salle_boss *salle_boss;
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("../font/necrosans.ttf", 24);
    SDL_Rect PersRect;
    SDL_Rect MobRect;
    int frame;
    int attaque = 0;
    choix_tex_niv(renderer);

    t_salle map;                    // Matrice de la salle
    t_pos posSalle;                 // Position de la salle dans
    perso->x = (DIM_SALLE / 2) - 1; // Position du perso au millieu de la salle
    perso->y = (DIM_SALLE / 2) - 1;
    
    // posSalle = trouverSalle(1, &niv->etages[NumEtage]);

    // trouve la dernière salle du niveau
    for (i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (niv->etages[NumEtage].etage[i][j].statut == EXIT)
            {
                posSalle.x = i;
                posSalle.y = j;
            }
        }
    }

    transfert(&niv->etages[NumEtage].etage[posSalle.x][posSalle.y], &map, 0);

    map.dim[perso->x][perso->y] = PERSO;
    // affichage de la matrice de la salle

    void (*fonc_attaque)(proj_t, entite_t*, t_salle*) = NULL;
    init_liste_proj();

    SDL_Rect srcRect = {0, 0, TILE_SIZE / 2, TILE_SIZE / 2}; // Position de la texture
    SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};         // Position de la texture

    SDL_Rect Door;

    int max_vie = perso->vie;
    int mort = 0;

    SDL_Surface* redHealthBarSurface = IMG_Load("./IMG/red_healthbar.png");
    SDL_Texture* redHealthBarTexture = SDL_CreateTextureFromSurface(renderer, redHealthBarSurface);
    //SDL_FreeSurface(redHealthBarSurface);

    SDL_Surface* blackHealthBarSurface = IMG_Load("./IMG/black_healthbar.png");
    SDL_Texture* blackHealthBarTexture = SDL_CreateTextureFromSurface(renderer, blackHealthBarSurface);
    //SDL_FreeSurface(redHealthBarSurface);

    // Initialisation des variables de vie
    int maxHealth = perso->vie;

    // Calcul de la longueur de la barre de vie en pixels
    int barLength = (int)((float)perso->vie / (float)maxHealth * (float)BAR_WIDTH);
 
    // Création de la barre de vie
    SDL_Rect healthBarRect = {WINDOW_WIDTH/2 - BAR_WIDTH/2, WINDOW_HEIGHT - 2 * BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT};

    
    perso->dir = BAS;                 // Variable de déplacement
    Uint32 lastTime = SDL_GetTicks(); // Temps de la dernière mise à jour de l'animation
    Uint32 MajMove = SDL_GetTicks();
    Uint32 lastTimeInteract = SDL_GetTicks();
    int continuer = 1; // Variable de fin de boucle
    long int iboucle=0;

    printf("Avant boucle jeu");
    while (continuer)
    { // Boucle principale
        iboucle++;
        
        if(iboucle%50 == 0){
            perso->vie -= 2;
        }
        printf("%d\n", perso->vie);

        if(perso->vie <= 0){
            continuer = 0;
            mort = 1;
            break;
        }

        SDL_Event event;
        if (SDL_PollEvent(&event))
        { // On récupère les évènements
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                { // On récupère le code de la touche
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    perso->dir = HAUT;
                    mouvement(&map, perso, &posSalle, niv, renderer);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    perso->dir = GAUCHE;
                    mouvement(&map, perso, &posSalle, niv, renderer);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    perso->dir = BAS;
                    mouvement(&map, perso, &posSalle, niv, renderer);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    perso->dir = DROITE;
                    mouvement(&map, perso, &posSalle, niv, renderer);
                    break;
                case SDL_SCANCODE_ESCAPE:
                    continuer = 0;
                    break;
                case SDL_SCANCODE_SPACE:
                    attaque = 1;
                    if(perso->arbre != NULL){
                        switch(perso->arbre->classe){
                            case MAGE: fonc_attaque = attaque_proj; break;
                            case ARCHER: fonc_attaque = attaque_proj; break;
                            default: fonc_attaque = attaque_cac;
                        }
                    }else{
                        fonc_attaque = attaque_cac;
                    }
                    perso_attack(&map, attaque, perso, fonc_attaque,window,renderer,police);
                    // interact(attaque,&map,perso);
                    break;
                case SDL_SCANCODE_LSHIFT:
                    break;
                case SDL_SCANCODE_TAB:
                    SDL_RenderClear(renderer);
                    inv(renderer, window, perso);
                    SDL_RenderClear(renderer);
                    break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    attaque = 0;
                    break;
                }

                break;
            }
        }
        if(!liste_vide_proj())
            maj_proj(perso, &map);
        Uint32 currentTime = SDL_GetTicks(); // Temps actuel
        if (currentTime - lastTime >= 300)
        {                                        // Mettre à jour toutes les 300 ms
            frame = (frame + 1) % SPRITE_FRAMES; // Passer à la frame suivante
            lastTime = currentTime;              // Mettre à jour le temps de la dernière mise à jour
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); // On efface l'écran
        

        if (map.nb_mobs == 0)
        {                // Si il n'y a plus de mobs dans la salle
            Door.x = 16; // On prend la porte ouverte
        }
        else
        {
            Door.x = 0; // On prend la porte fermée
        }
        int i, j;
        if (niv->etages[NumEtage].boss == 1)
        {
            rendu(map.dim, LARG_SALLE_BOSS, LONG_SALLE_BOSS, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }
        else if (niv->etages[NumEtage].marchand == 1)
        {
            rendu(map.dim, LARG_MARCHAND, LONG_MARCHAND, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }
        else
        {
            rendu(map.dim, DIM_SALLE, DIM_SALLE, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }
        

        float healthPercentage = (float)perso->vie / (float)maxHealth;
        int healthBarWidth = (int)(healthPercentage * (float)healthBarRect.w);

        // Dessin de la barre de vie
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &healthBarRect);

        SDL_Rect redHealthBarRect = {healthBarRect.x, healthBarRect.y, healthBarWidth, healthBarRect.h};
        SDL_RenderCopy(renderer, redHealthBarTexture, NULL, &redHealthBarRect);

        SDL_Rect blackHealthBarRect = {healthBarRect.x + healthBarWidth, healthBarRect.y, healthBarRect.w - healthBarWidth, healthBarRect.h};
        SDL_RenderCopy(renderer, blackHealthBarTexture, NULL, &blackHealthBarRect);
        SDL_RenderPresent(renderer); // On affiche l'écran 


        if (SDL_GetTicks() - lastTimeInteract >= 500)
        {
            interact(attaque, &map, perso, &MajMove, &posSalle, niv, renderer);
            lastTimeInteract = SDL_GetTicks();
        }

    } // Fin boucle principale
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer); // On affiche l'écran 

    detruireNiv(&niv); // On libère la mémoire
    for (i = 0; i < 10; i++)
    {
        SDL_DestroyTexture(tab_tex[i]); // On détruit les textures
    }

    SDL_DestroyTexture(redHealthBarTexture);
    SDL_FreeSurface(redHealthBarSurface);

    SDL_DestroyTexture(blackHealthBarTexture);
    SDL_FreeSurface(blackHealthBarSurface);

    if(mort == 1){
        if(gameover(window, renderer, perso)){
            SDL_DestroyRenderer(renderer); // On détruit le renderer
            SDL_DestroyWindow(window);     // On détruit la fenêtre
            main();
        }
    }

    SDL_DestroyRenderer(renderer); // On détruit le renderer
    SDL_DestroyWindow(window);     // On détruit la fenêtre
    SDL_Quit();                  // On quitte la SDL
}
