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
#include "../head/inv_SDL.h"
#include "../head/inventaire.h"
#include "../head/sauvegarde.h"
#include "../head/menu_cpt.h"
int flip_map = 0;
int coords[10][2];
int NumEtage = 0;

#define TILE_SIZE 32
#define DIM_SALLE 25
#define DIM_SALLE 25

const int SPRITE_FRAMES = 4;  // Nombre de frames de l'animation
const int SPRITE_WIDTH = 32;  // Largeur d'une frame
const int SPRITE_HEIGHT = 32; // Hauteur d'une frame


/*
 *  \fn float distance(entite_t* entite1, entite_t* entite2)
 *  \brief Calcule la distance entre deux entites
 *  @param entite1 L'entite 1
 *  @param entite2 L'entite 2
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
 *
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
 * \fn void changement(t_niv * niv,entite_t* posPerso, t_pos * posSalle, t_salle * map)
 * \brief Change de salle
 * @param niv Le niveau
 * @param posPerso La position du perso
 * @param posSalle La position de la salle
 * @param map La map
 *
 */
void changement(t_niv *niv, entite_t *posPerso, t_pos *posSalle, t_salle *map)
{
    if (map->nb_mobs <= 0)
    {
        // si les au moins la deuxieme salle
        if (niv->etages[NumEtage].etage[posSalle->x][posSalle->y].statut != START)
        {
            printf("Sauvegarde de la salle %d\n", niv->etages[NumEtage].etage[posSalle->x][posSalle->y].num_salle);
            sauvegarde_salle(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map);
        }
        if (posPerso->dir == HAUT)
        {
            posSalle->y--;
            posPerso->y = DIM_SALLE - 2;
            posPerso->x = (DIM_SALLE / 2) - 1;
        }
        else if (posPerso->dir == DROITE)
        {
            posSalle->x++;
            posPerso->x = 1;
            posPerso->y = (DIM_SALLE / 2) - 1;
        }
        else if (posPerso->dir == BAS)
        {
            posSalle->y++;
            posPerso->y = 1;
            posPerso->x = (DIM_SALLE / 2) - 1;
        }
        else if (posPerso->dir == GAUCHE)
        {
            posSalle->x--;
            posPerso->x = DIM_SALLE - 2;
            posPerso->y = (DIM_SALLE / 2) - 1;
        }
        transfert(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map, 0);
        // map->num_salle=niv->etages[NumEtage].etage[posSalle->x][posSalle->y].num_salle;
        map->dim[posPerso->x][posPerso->y] = PERSO;
        flip_map = rand() % 4;
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
            int Width = LARG_SALLE_BOSS * TILE_SIZE;
            int Height = LONG_SALLE_BOSS * TILE_SIZE;
            niv->etages[NumEtage].Boss = genererSalleBoss(niv->etages->Boss);
            transfert(niv->etages->Boss, map, 1);
            map->nb_porte = 1;
            posPerso->x = LARG_SALLE_BOSS / 2;
            posPerso->y = 4;
            map->dim[posPerso->x][posPerso->y] = PERSO;
            niv->etages[NumEtage].boss = 1;
        }
        if (niv->etages[NumEtage].marchand == 1)
        {
            printf("C'est l'heure du marchand\n");
            // initialise la matrice de la salle Marchand
            niv->etages[NumEtage].Marchand = genererSalleMarchand(niv->etages->Marchand);
            transfert(niv->etages->Marchand, map, 2);
            map->nb_porte = 1;
            posPerso->y = 1;
            posPerso->x = (LARG_MARCHAND / 2) - 1;
            map->dim[posPerso->x][posPerso->y] = PERSO;
            sauvegarde(posPerso, NumEtage);
        }
        // printf("Salle n°%d\n", map->num_salle);
    }
}
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
            else
            {
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
 * \fn void mouvement(t_salle * map,entite_t* posPers, t_pos * posSalle, t_niv * niv)
 * \brief Gère le mouvement du l'entite
 * @param map La map
 * @param posPers La position du perso
 * @param posSalle La position de la salle
 * @param niv Le niveau
 *
 *
 */
void mouvement(t_salle *map, entite_t *posPers, t_pos *posSalle, t_niv *niv)
{
    int x = posPers->x;
    int y = posPers->y;
    if (posPers->dir == HAUT)
    {
        if (map->dim[x][y - 1] == PORTE && posPers->persoOuMob == 0)
        { // Si la case du haut est une porte
            map->dim[x][y] = VIDE;
            changement(niv, posPers, posSalle, map);
        }
        if (map->dim[x][y - 1] == VIDE)
        {                   // Si la case du haut n'est pas un mur
            posPers->x = x; // On met à jour la position du perso
            posPers->y = y - 1;
            if (posPers->persoOuMob)
            {

                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob;
            }
            else
            {
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            // map[(y-1)*DIM_SALLE+x] = 5; // On met le perso sur la case du haut
            map->dim[x][y] = VIDE; // map[y*DIM_SALLE+x] = 0; // On met la case du perso à vide
            // printf("Bouge vers le haut\n");
        }
    }
    else if (posPers->dir == BAS)
    {
        if (map->dim[x][y + 1] == PORTE && posPers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            changement(niv, posPers, posSalle, map);
        }
        else if (map->dim[x][y + 1] == VIDE)
        {
            posPers->x = x;
            posPers->y = y + 1;
            if (posPers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob;
            }
            else
            {
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers le bas\n");
        }
    }
    else if (posPers->dir == GAUCHE)
    {
        if (map->dim[x - 1][y] == PORTE && posPers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            changement(niv, posPers, posSalle, map);
        }
        else if (map->dim[x - 1][y] == VIDE)
        {
            posPers->x = x - 1;
            posPers->y = y;
            if (posPers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob;
            }
            else
            {
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers la gauche\n");
        }
    }
    else if (posPers->dir == DROITE)
    {
        if (map->dim[x + 1][y] == PORTE && posPers->persoOuMob == 0)
        {
            map->dim[x][y] = VIDE;
            // si on est dans la salle du marchand on change de niveau
            if (niv->etages[NumEtage].marchand == 1)
            {
                NumEtage++;
                niv->etages[NumEtage].marchand = 0;
                *posSalle = trouverSalle(1, &niv->etages[NumEtage]);
                transfert(&niv->etages[NumEtage].etage[posSalle->x][posSalle->y], map, 0);
                posPers->x = DIM_SALLE / 2;
                posPers->y = DIM_SALLE / 2;
            }
            else
            {
                changement(niv, posPers, posSalle, map);
            }
        }
        else if (map->dim[x + 1][y] == VIDE)
        {
            posPers->x = x + 1;
            posPers->y = y;
            if (posPers->persoOuMob)
            {
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob;
            }
            else
            {
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            // printf("Bouge vers la droite\n");
        }
    }
}
/**
 * \fn void perso_attack( t_salle * map,int attaque, entite_t* posPers)
 * \brief Gère l'attaque du perso
 * @param map La map
 * @param attaque Si le perso attaque
 * @param posPers La position du perso
 **/
int perso_attack(t_salle *map, int attaque, entite_t *posPers,SDL_Window* window,SDL_Renderer* renderer,TTF_Font* police)
{
    int x = posPers->x;
    int y = posPers->y;
    if (attaque)
    {
        // printf("Vous attaquez !\n");
        switch (posPers->dir)
        {
        case HAUT:
            if (map->dim[x][y - 1] >= 10 && map->dim[x][y - 1] <= 21)
            { // si il y a un ennemi sur la case du haut
                map->mob[(map->dim[x][y - 1]) - 10]->vie -= 10;
                // printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x][y-1])-10]->vie);
                if (map->mob[(map->dim[x][y - 1]) - 10]->vie <= 0)
                {
                    looter(map->mob[(map->dim[x][y - 1]) - 10], posPers);
                    map->dim[x][y - 1] = VIDE;
                    map->nb_mobs--;
                }
            }
            if(map->dim[x][y-1]==MARCHAND){
                SDL_RenderClear(renderer);
                afficher_menu(window, renderer,posPers,police);
                
            }
            break;
        case BAS:
            if (map->dim[x][y + 1] >= 10 && map->dim[x][y + 1] <= 21)
            { // si il y a un ennemi sur la case du bas
                map->mob[(map->dim[x][y + 1]) - 10]->vie -= 10;
                // printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x][y+1])-10]->vie);
                if (map->mob[(map->dim[x][y + 1]) - 10]->vie <= 0)
                {
                    looter(map->mob[(map->dim[x][y + 1]) - 10], posPers);
                    map->dim[x][y + 1] = VIDE;
                    map->nb_mobs--;
                }
            }
            if(map->dim[x][y+1]==MARCHAND){
                SDL_RenderClear(renderer);

                afficher_menu(window, renderer,posPers,police);
            }
            break;
        case GAUCHE:
            if (map->dim[x - 1][y] >= 10 && map->dim[x - 1][y] <= 21)
            { // si il y a un ennemi sur la case de gauche
                map->mob[(map->dim[x - 1][y]) - 10]->vie -= 10;
                // printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x-1][y])-10]->vie);
                if (map->mob[(map->dim[x - 1][y]) - 10]->vie <= 0)
                {
                    looter(map->mob[(map->dim[x - 1][y]) - 10], posPers);
                    map->dim[x - 1][y] = VIDE;
                    map->nb_mobs--;
                }
            }
            if(map->dim[x-1][y]==MARCHAND){
                SDL_RenderClear(renderer);
                afficher_menu(window, renderer,posPers,police);
            }
            break;
        case DROITE:
            if (map->dim[x + 1][y] >= 10 && map->dim[x + 1][y] <= 21)
            { // si il y a un ennemi sur la case de droite
                map->mob[(map->dim[x + 1][y]) - 10]->vie -= 10;
                // printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x+1][y])-10]->vie);
                if (map->mob[(map->dim[x + 1][y]) - 10]->vie <= 0)
                {
                    looter(map->mob[(map->dim[x + 1][y]) - 10], posPers);
                    map->dim[x + 1][y] = VIDE;
                    map->nb_mobs--;
                }
            }
            if(map->dim[x+1][y]==MARCHAND){
                SDL_RenderClear(renderer);

                afficher_menu(window, renderer,posPers,police);
            }
            break;
        default:
            break;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * \fn int enemy_attack(t_salle * map, entite_t* posPers, SDL_Rect * rect)
 * \brief Fonction qui permet de faire attaquer les mobs
 * \param map la map
 * \param posPers la position du joueur
 * \param rect les points de vie du joueur
 * \return 1 si le joueur a perdu des points de vie, 0 sinon
 */
int enemy_attack(t_salle *map, entite_t *posPers, SDL_Rect *rect)
{
    int x = posPers->x;
    int y = posPers->y;
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

/*
 * \fn void mouvement(t_salle * map, entite_t * mob, t_pos * posSalle, t_niv * niv)
 * \brief Fonction qui permet de faire bouger les mobs
 * \param map la map
 * \param mob le mob
 * \param posSalle la position de la salle
 * \param niv le niveau
 */
void interact(int attaque, t_salle *map, entite_t *posPers, SDL_Rect *rect, Uint32 *lastTime, t_pos *posSalle, t_niv *niv)
{
    int x = posPers->x;
    int y = posPers->y;
    int Idmob= rand()%map->nb_mobs;
    int i, j;
    int cheminX;
    int cheminY;
    float dist;
    Uint32 currentTime = SDL_GetTicks();
    if (enemy_attack(map, posPers, rect) == 0 && attaque == 0)
    { // si le mob n'attaque pas et que le joueur n'attaque pas
        if (currentTime - (*lastTime) >= 500)
        { // si 1 seconde s'est écoulée
            // Idmob = rand()%map->nb_mobs;
            *lastTime = currentTime;
            if (map->nb_mobs > 0)
            {
                while (distance(posPers, map->mob[Idmob]) <= 4)
                {

                    for (i = 0; i < 20; i++)
                    {
                        coords[i][0] = 0;
                        coords[i][1] = 0;
                    }
                    chemin_vers_perso(posPers, map->mob[Idmob], map->dim);
                    // tant que n'est pas autour du perso
                    i = 0;
                    // on affiche les coordonnées du mob et du perso
                    // on calcule le chemin
                    cheminX = map->mob[Idmob]->x - coords[i][0];
                    cheminY = map->mob[Idmob]->y - coords[i][1];
                    // si le mob est a 1 case de distance du perso on ne bouge pas
                    // on regarde la différence entre les valeurs de coords et de la position du mob et on change vers la direction la plus appropriée
                    // on change la direction du mob
                    if (cheminX > 0)
                    { // si le mob est a droite du perso
                        map->mob[Idmob]->dir = 3;
                    }
                    if (cheminX < 0)
                    { // si le mob est a gauche du perso
                        map->mob[Idmob]->dir = 1;
                    }
                    if (cheminY > 0)
                    { // si le mob est en bas du perso
                        map->mob[Idmob]->dir = 0;
                    }
                    if (cheminY < 0)
                    { // si le mob est en haut du perso
                        map->mob[Idmob]->dir = 2;
                    }
                    // on fait bouger le mob
                    if(distance(posPers, map->mob[Idmob]) == 1){
                        break;
                    }
                    mouvement(map, map->mob[Idmob], posSalle, niv);
                }
                if(distance(posPers, map->mob[Idmob]) > 4)
                {
                    
                    map->mob[Idmob]->dir = rand() % 4;
                    mouvement(map, map->mob[Idmob], posSalle, niv);
                }
            }
        }
    }
    if (rect->w <= 0)
    {
        // printf("Vous êtes mort !\n");
    }
}
/*
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
/*
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
    // printf("tailleI : %d tailleJ : %d\n",tailleI,tailleJ);
    for (int x = 0; x < tailleI; x++)
    {
        for (int y = 0; y < tailleJ; y++)
        { // On parcourt la map
            if (map[x][y] == PORTE)
            { // Porte
                SDL_Texture *DoorTex = tab_tex[2];
                dstRect.x = x * TILE_SIZE;
                dstRect.y = y * TILE_SIZE;
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
                /*
                 MobRect.x = frame * 16; // Combien de Pixel on doit décaler pour afficher la bonne frame
                 MobRect.w = 16; // Largeur de la frame
                 MobRect.y = 0;
                 MobRect.h = 16; // Hauteur de la frame
                 */
                dstRect.x = x * TILE_SIZE; // Position de la frame
                dstRect.y = y * TILE_SIZE; // Position de la frame

                if (map[x][y] == 10)
                {
                    SDL_RenderCopyEx(renderer, tab_tex[8], NULL, &dstRect, 0, NULL, SDL_FLIP_NONE);
                    // printf("Vie du mob : %d",map.mob[map.dim[x][y]-10].vie);
                }
                else
                {
                    SDL_RenderCopyEx(renderer, tab_tex[9], NULL, &dstRect, 0, NULL, SDL_FLIP_NONE);
                    // printf("Vie du mob : %d",map.mob[map.dim[x][y]-10].vie);
                }
            }
            if (map[x][y] == PERSO)
            { // Si c'est le perso
                // printf("x = %d, y = %d perso trouvé\n",x,y);
                PersRect.x = frame * 20; // Combien de Pixel on doit décaler pour afficher la bonne frame
                PersRect.w = 20;         // Largeur de la frame
                PersRect.y = 0;
                PersRect.h = 24;           // Hauteur de la frame
                dstRect.x = x * TILE_SIZE; // Position de la frame
                dstRect.y = y * TILE_SIZE; // Position de la frame
                if (perso->dir == HAUT)    // On affiche le perso dans la bonne direction
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
            {                              // Si c'est un mur
                dstRect.x = x * TILE_SIZE; // Position du mur
                dstRect.y = y * TILE_SIZE;
                SDL_RenderCopy(renderer, tab_tex[0], &srcRect, &dstRect); // On affiche le mur
            }
            if (map[x][y] == OBSTACLE)
            {
                dstRect.x = x * TILE_SIZE; // Position de l'obstacle
                dstRect.y = y * TILE_SIZE;
                SDL_RenderCopy(renderer, tab_tex[4], &srcRect, &dstRect); // On affiche l'obstacle
            }
            if(map[x][y]== MARCHAND){
                dstRect.x = x * TILE_SIZE; // Position de l'obstacle
                dstRect.y = y * TILE_SIZE;
                SDL_RenderCopy(renderer, tab_tex[4], &srcRect, &dstRect); // On affiche l'obstacle
            }
        }
        // printf("\n");
    }
}

int main()
{
    int i;
    t_niv *niv = malloc(sizeof(t_niv));
    genererNiv(niv);
    entite_t *perso;
    t_salle_boss *salle_boss;
    perso = creer_personnage(perso);
    perso = init_inventaire_personnage(perso);
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("../font/necrosans.ttf", 24);
    SDL_Rect PersRect;
    SDL_Rect MobRect;
    int frame;
    int attaque = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    int Width = (TILE_SIZE * DIM_SALLE);
    int Height = (TILE_SIZE * DIM_SALLE);

    SDL_Window *window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0); // On crée la fenêtre
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);        // On crée le renderer

    SDL_Texture *tab_tex[10] = {charge_tex(renderer, "../img/brick.png", 0),
                                charge_tex(renderer, "../img/sol.jpg", 0),
                                charge_tex(renderer, "../img/wooden_door.png", 0),
                                charge_tex(renderer, "../img/Idle-Sheet.png", 0),
                                charge_tex(renderer, "../img/rock.png", 0),
                                charge_tex(renderer, "../img/1_north.png", 0),
                                charge_tex(renderer, "../img/1_south.png", 0),
                                charge_tex(renderer, "../img/1_side.png", 0),
                                charge_tex(renderer, "../img/GreenSlime/Grn_Idle1.png", 0),
                                charge_tex(renderer, "../img/BlueSlime/Blue_Idle1.png", 0)};
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

    SDL_Rect srcRect = {0, 0, TILE_SIZE / 2, TILE_SIZE / 2}; // Position de la texture
    SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};         // Position de la texture

    SDL_Rect Door;
    SDL_Rect rect; // Rectangle de vie
    rect.x = 50;   // Position du rectangle sur la largeur
    rect.y = 50;   // Position du rectangle sur la hauteur
    rect.w = 250;  // Largeur du rectangle
    rect.h = 50;   // Hauteur du rectangle

    perso->dir = BAS;                 // Variable de déplacement
    Uint32 lastTime = SDL_GetTicks(); // Temps de la dernière mise à jour de l'animation
    Uint32 MajMove = SDL_GetTicks();
    int continuer = 1; // Variable de fin de boucle
    while (continuer)
    { // Boucle principale

        SDL_Event event;
        if (SDL_PollEvent(&event))
        { // On récupère les évènements
            switch (event.type)
            {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                Width = event.window.data1;
                Height = event.window.data2;

                break;
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                { // On récupère le code de la touche
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    perso->dir = HAUT;
                    mouvement(&map, perso, &posSalle, niv);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    perso->dir = GAUCHE;
                    mouvement(&map, perso, &posSalle, niv);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    perso->dir = BAS;
                    mouvement(&map, perso, &posSalle, niv);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    perso->dir = DROITE;
                    mouvement(&map, perso, &posSalle, niv);
                    break;
                case SDL_SCANCODE_ESCAPE:
                    continuer = 0;
                    break;
                case SDL_SCANCODE_SPACE:
                    attaque = 1;
                    perso_attack(&map, attaque, perso,window,renderer,police);
                    // interact(attaque,&map,perso);
                    break;
                case SDL_SCANCODE_LSHIFT:
                    break;
                case SDL_SCANCODE_TAB:
                    SDL_RenderClear(renderer);
                    inv(renderer, window, perso);
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
        Uint32 currentTime = SDL_GetTicks(); // Temps actuel
        if (currentTime - lastTime >= 300)
        {                                        // Mettre à jour toutes les 300 ms
            frame = (frame + 1) % SPRITE_FRAMES; // Passer à la frame suivante
            lastTime = currentTime;              // Mettre à jour le temps de la dernière mise à jour
        }
        SDL_RenderClear(renderer); // On efface l'écran

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (flip_map % 2 == 1)
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (flip_map % 3 == 1)
        {
            flip = SDL_FLIP_VERTICAL;
        }
        SDL_RenderCopyEx(renderer, tab_tex[1], NULL, NULL, 0, NULL, flip); // On affiche le sol

        SDL_RenderDrawRect(renderer, &rect);              // on decide de dessiner un rectangle avec les coordonnées de rect
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // On defini la couleur du rectangle
                                                          // Un texte signale dans quel étage on est et quel salle on est
                                                          // info_map(&map,niv,police,couleurNoire,window);

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
            SDL_SetWindowSize(window, (TILE_SIZE * LARG_SALLE_BOSS), (TILE_SIZE * LONG_SALLE_BOSS));
            rendu(map.dim, LARG_SALLE_BOSS, LONG_SALLE_BOSS, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }
        else if (niv->etages[NumEtage].marchand == 1)
        {
            // SDL_SetWindowSize(window, (TILE_SIZE*LARG_MARCHAND), (TILE_SIZE*LONG_MARCHAND));
            rendu(map.dim, LARG_MARCHAND, LONG_MARCHAND, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }
        else
        {
            if (Width == (TILE_SIZE * LARG_SALLE_BOSS) && Height == (TILE_SIZE * LONG_SALLE_BOSS))
            {
                Width = (TILE_SIZE * DIM_SALLE);
                Height = (TILE_SIZE * DIM_SALLE);
            }
            SDL_SetWindowSize(window, Width, Height);
            rendu(map.dim, DIM_SALLE, DIM_SALLE, renderer, tab_tex, dstRect, Door, srcRect, PersRect, perso, attaque, frame); // on fais le rendu de la salle
        }

        SDL_RenderPresent(renderer); // On affiche l'écran
        interact(attaque, &map, perso, &rect, &MajMove, &posSalle, niv);
    } // Fin boucle principale

    detruireNiv(&niv); // On libère la mémoire
    for (i = 0; i < 10; i++)
    {
        SDL_DestroyTexture(tab_tex[i]); // On détruit les textures
    }
    SDL_DestroyRenderer(renderer); // On détruit le renderer
    SDL_DestroyWindow(window);     // On détruit la fenêtre
    SDL_Quit();                    // On quitte la SDL
}
