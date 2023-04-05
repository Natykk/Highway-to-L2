
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "../head/menu_cpt.h"
#include "../head/itoa.h"
#include "../head/inventaire.h"

/**
 * @file menu_cpt.c
 * @author GEORGET Rémy
 * @brief
 * @date 2023-03-24
 */

/**
 * @fn construire_chaine_objets
 * @brief Fonction qui construit la chaine des objets sur le format suivant : "Nom_Objet : Nb_Obj --> Nb_Obj_Requis"
 *
 * @param result
 * @param nb_obj
 * @param competence
 */
void construire_chaine_objets(char *result, int nb_obj, int nb_obj_requis, char *nom_obj)
{
    char nombre_obj[8];
    itoa(nb_obj, nombre_obj, 10);

    char nombre_requis[8];
    itoa(nb_obj_requis, nombre_requis, 10);

    // Nom :
    strcat(nom_obj, " : ");

    // Nom : Nombre_Obj
    strcat(nom_obj, nombre_obj);

    // Nom : Nombre_Obj /
    strcat(nom_obj, " / ");

    strcat(nom_obj, nombre_requis);

    strcpy(result, nom_obj);
}

/**
 * @fn construire_chaine_buff
 * @brief Fonction qui permet de constr uire la chaine des buffs sur le format suivant : "Stats : xBuffs"
 *
 * @param i
 * @param buff
 * @return char*
 */
int construire_chaine_buff(char *result, int i, int buff)
{
    char nombre[2];

    char chaine_vie[20] = "Vie       : x";
    char chaine_degats[20] = "Degats    : x";
    char chaine_att_s[20] = "Att speed : x";
    char chaine_depl[20] = "Move speed: x";
    char chaine_perim[20] = "Detection : +";

    if (buff != 1)
    {
        switch (i)
        {
        case 0:
            itoa(buff, nombre, 10);
            strcat(chaine_vie, nombre);
            strcpy(result, chaine_vie);
            break;

        case 1:
            itoa(buff, nombre, 10);
            strcat(chaine_degats, nombre);
            strcpy(result, chaine_degats);
            break;

        case 2:
            itoa(buff, nombre, 10);
            strcat(chaine_att_s, nombre);
            strcpy(result, chaine_att_s);
            break;

        case 3:
            itoa(buff, nombre, 10);
            strcat(chaine_depl, nombre);
            strcpy(result, chaine_depl);
            break;

        case 4:
            itoa(buff, nombre, 10);
            strcat(chaine_perim, nombre);
            strcpy(result, chaine_perim);
            break;

        default:
            printf("Erreur sur l'indice de i dans la fonction constuire_chaine_buff \n");
            break;
        }
        return 1;
    }

    else
    {
        return 0;
    }
}
/**
 * @fn check_valid_cpt
 * @brief Fonction qui affiche les message d'erreurs pour le débloquage des compétences
 * 
 * @param renderer 
 * @param font 
 * @param color 
 * @param check 
 */
int check_valid_cpt(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, SDL_Rect rect, int check)
{

    SDL_Surface *surface;
    SDL_Texture *texture;

    switch (check)
    {
    case -4:
        surface = TTF_RenderText_Solid(font, "Erreur lugubre...", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        return 0;

    case -3:
        surface = TTF_RenderText_Solid(font, "Comment ça ? Tu essaies de débloquer une compétence qui n'appartient pas a cet arbre !", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        return 0;

    case -2:
        surface = TTF_RenderText_Solid(font, "Vous manquez de ressources pour débloquer la compétence !", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        return 0;

    case -1:
        surface = TTF_RenderText_Solid(font, "Vous n'avez pas aquis la compétence précédente !", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        return 0;

    case 0:
        surface = TTF_RenderText_Solid(font, "Vous avez déja cette compétence !", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        return 0;

    case 1:
        return 1;
    }
}


/**
 * @fn in_rect
 * @brief Fonction qui permet de verifier si on clique dans un rectangle
 *
 * @param x
 * @param y
 * @param r
 * @return int
 */
int in_rect(int x, int y, struct SDL_Rect *r)
{
    return (x >= r->x) && (y >= r->y) && (x < r->x + r->w) && (y < r->y + r->h);
}

/**
 * @fn afficher_comp
 * @brief Fonction qui permet d'afficher une competence
 *
 * @param path
 * @param renderer
 * @param rect
 */
void afficher_comp(char *path, SDL_Renderer *renderer, SDL_Rect rect)
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Erreur lors du chargement de l'image \n");
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

/**
 * @fn afficher_background
 * @brief Fonction qui permet d'afficher le background du menu
 *construire_chaine_o
 * @param window
 * @param renderer
 */
void afficher_background(SDL_Window *window, SDL_Renderer *renderer)
{
    // Affichage d'une image de fond
    SDL_Surface *image = IMG_Load("../img/background_comp.jpg");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture_background, NULL, NULL);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture_background);
}

/**
 * @fn afficher_arbre_assassin
 * @brief Fonction qui affiche l'arbre de competences de l'assassin
 *
 * @param window
 * @param renderer
 */
int afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* assassin,TTF_Font* font)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Color color = {255, 255, 255, 255};

    


    while (running1)
    {

        afficher_background(window, renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* -------------------------------------------------------------------------- */
        /*                              Dessin des lignes                             */
        /* -------------------------------------------------------------------------- */

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 3); // 1
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 3); // 2

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 2); // 3
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 1 / 2); // 4
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 1 / 2); // 5
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 2); // 6

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3); // 7
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3); // 8
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3); // 9
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3); // 10

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 11
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 12

        /* -------------------------------------------------------------------------- */
        /*        Ajout des rectangles au bout des lignes pour les compétences        */
        /* -------------------------------------------------------------------------- */


        SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect2 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect3 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect4 = {WINDOW_WIDTH * 1 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect5 = {WINDOW_WIDTH * 3 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect6 = {WINDOW_WIDTH * 5 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect7 = {WINDOW_WIDTH * 7 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect8 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect9 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect10 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 5 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect_ret = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 5 / 6, 120, TAILLE_CASE};

        surface = TTF_RenderText_Solid(font, "Retour", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_ret);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(20);


        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        //afficher_comp(assassin->competence[0]->name_img, renderer, rect1);

        afficher_comp(assassin->competence[1]->name_img, renderer, rect2);
        afficher_comp(assassin->competence[2]->name_img, renderer, rect3);

        afficher_comp(assassin->competence[3]->name_img, renderer, rect4);
        afficher_comp(assassin->competence[4]->name_img, renderer, rect5);
        afficher_comp(assassin->competence[5]->name_img, renderer, rect6);
        afficher_comp(assassin->competence[6]->name_img, renderer, rect7);

        afficher_comp(assassin->competence[7]->name_img, renderer, rect8);
        afficher_comp(assassin->competence[8]->name_img, renderer, rect9);

        afficher_comp(assassin->competence[9]->name_img, renderer, rect10);
        SDL_Delay(20);
        SDL_RenderPresent(renderer);

        running = 1;

        while (running)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = 0;
                    running1 = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_TAB:
                        running = 0;
                        running1 = 0;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        x = event.button.x;
                        y = event.button.y;
                        
                        if(in_rect(x, y, &rect_ret)) 
                        {
                            return 1;
                        }
                        else if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[0]->name_img, entite, &cpt_assassin[0], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[1]->name_img, entite, &cpt_assassin[1], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[2]->name_img, entite, &cpt_assassin[2], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[3]->name_img, entite, &cpt_assassin[3], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[4]->name_img, entite, &cpt_assassin[4], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[5]->name_img, entite, &cpt_assassin[5], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[6]->name_img, entite, &cpt_assassin[6], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[7]->name_img, entite, &cpt_assassin[7], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[8]->name_img, entite, &cpt_assassin[8], assassin,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, assassin->competence[9]->name_img, entite, &cpt_assassin[9], assassin,font);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @fn afficher_arbre_guerrier
 * @brief Fonction qui permet d'afficher l'arbre de competences du guerrier
 *
 * @param window
 * @param renderer
 */
int afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* guerrier,TTF_Font* font)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    SDL_Surface *surface;
    SDL_Texture *texture;


    SDL_Color color = {255, 255, 255, 255};



    while (running1)
    {

        afficher_background(window, renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* -------------------------------------------------------------------------- */
        /*                              Dessin des lignes                             */
        /* -------------------------------------------------------------------------- */

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 3); // 1
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 1 / 3); // 2
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 1 / 3); // 3
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 3); // 4

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2); // 5
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2); // 6
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2); // 7
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2); // 8

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3); // 9
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3); // 10
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3); // 11
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3); // 12

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 13
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 14

        /* -------------------------------------------------------------------------- */
        /*        Ajout des rectangles au bout des lignes pour les competences        */
        /* -------------------------------------------------------------------------- */

        SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect2 = {WINDOW_WIDTH * 1 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect3 = {WINDOW_WIDTH * 3 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect4 = {WINDOW_WIDTH * 5 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect5 = {WINDOW_WIDTH * 7 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect6 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect7 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect8 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect9 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect10 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 5 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect_ret = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 5 / 6, 120, TAILLE_CASE};

        surface = TTF_RenderText_Solid(font, "Retour", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_ret);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(20);
        

        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp(guerrier->competence[0]->name_img, renderer, rect1);

        afficher_comp(guerrier->competence[1]->name_img, renderer, rect2);
        afficher_comp(guerrier->competence[2]->name_img, renderer, rect3);
        afficher_comp(guerrier->competence[3]->name_img, renderer, rect4);
        afficher_comp(guerrier->competence[4]->name_img, renderer, rect5);

        afficher_comp(guerrier->competence[5]->name_img, renderer, rect6);
        afficher_comp(guerrier->competence[6]->name_img, renderer, rect7);

        afficher_comp(guerrier->competence[7]->name_img, renderer, rect8);
        afficher_comp(guerrier->competence[8]->name_img, renderer, rect9);

        afficher_comp(guerrier->competence[9]->name_img, renderer, rect10);
        SDL_Delay(20);
        SDL_RenderPresent(renderer);

        running = 1;

        while (running)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = 0;
                    running1 = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_TAB:
                        running = 0;
                        running1 = 0;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        x = event.button.x;
                        y = event.button.y;

                        if(in_rect(x, y, &rect_ret)) 
                        {
                            return 1;
                        }
                        else if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[0]->name_img, entite, &cpt_guerrier[0], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[1]->name_img, entite, &cpt_guerrier[1], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[2]->name_img, entite, &cpt_guerrier[2], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[3]->name_img, entite, &cpt_guerrier[3], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[4]->name_img, entite, &cpt_guerrier[4], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[5]->name_img, entite, &cpt_guerrier[5], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[6]->name_img, entite, &cpt_guerrier[6], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[7]->name_img, entite, &cpt_guerrier[7], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[8]->name_img, entite, &cpt_guerrier[8], guerrier,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, guerrier->competence[9]->name_img, entite, &cpt_guerrier[9], guerrier,font);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @fn afficher_arbre_mage
 * @brief Fonction qui permet d'afficher l'arbre de competences du guerrier
 *
 * @param window
 * @param renderer
 */
int afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* mage,TTF_Font* font)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Color color = {255, 255, 255, 255};


    while (running1)
    {
        SDL_Delay(20);
        afficher_background(window, renderer);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* -------------------------------------------------------------------------- */
        /*                              Dessin des Lignes                             */
        /* -------------------------------------------------------------------------- */

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 3); // 1
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 3); // 2

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2); // 3
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2); // 4

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 2 / 8, WINDOW_HEIGHT * 2 / 3); // 5
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 2 / 3); // 6
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 2 / 3); // 7
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 2 / 3); // 8
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 2 / 3); // 9

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 2 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 10
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 11
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 12
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 5 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 13
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 14

        /* -------------------------------------------------------------------------- */
        /*        Ajout des rectangles au bout des lignes pour les compétences        */
        /* -------------------------------------------------------------------------- */

        SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect2 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect3 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect4 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect5 = {WINDOW_WIDTH * 2 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect6 = {WINDOW_WIDTH * 3 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect7 = {WINDOW_WIDTH * 4 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect8 = {WINDOW_WIDTH * 5 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect9 = {WINDOW_WIDTH * 6 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect10 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 5 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect_ret = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 5 / 6, 120, TAILLE_CASE};

        surface = TTF_RenderText_Solid(font, "Retour", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_ret);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(20);
 
        
        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp(mage->competence[0]->name_img, renderer, rect1);

        afficher_comp(mage->competence[1]->name_img, renderer, rect2);
        afficher_comp(mage->competence[2]->name_img, renderer, rect3);

        afficher_comp(mage->competence[3]->name_img, renderer, rect4);

        afficher_comp(mage->competence[4]->name_img, renderer, rect5);
        afficher_comp(mage->competence[5]->name_img, renderer, rect6);
        afficher_comp(mage->competence[6]->name_img, renderer, rect7);
        afficher_comp(mage->competence[7]->name_img, renderer, rect8);
        afficher_comp(mage->competence[8]->name_img, renderer, rect9);

        afficher_comp(mage->competence[9]->name_img, renderer, rect10);
        SDL_Delay(20);
        SDL_RenderPresent(renderer);
        
        running = 1;

        while (running)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = 0;
                    running1 = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_TAB:
                        running = 0;
                        running1 = 0;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        x = event.button.x;
                        y = event.button.y;

                        if(in_rect(x, y, &rect_ret)) 
                        {
                            return 1;
                        }
                        else if (in_rect(x, y, &rect1))
                        {
                            SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[0]->name_img, entite, &cpt_mage[0], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[1]->name_img, entite, &cpt_mage[1], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[2]->name_img, entite, &cpt_mage[2], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[3]->name_img, entite, &cpt_mage[3], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[4]->name_img, entite, &cpt_mage[4], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[5]->name_img, entite, &cpt_mage[5], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[6]->name_img, entite, &cpt_mage[6], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[7]->name_img, entite, &cpt_mage[7], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[8]->name_img, entite, &cpt_mage[8], mage,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {   SDL_Delay(20);
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_competence_SDL(window, renderer, mage->competence[9]->name_img, entite, &cpt_mage[9], mage,font);
                            running = 0;
                        }
                    }
                }
            }
        }
    }

    
    
}

/**
 * @fn afficher_arbre_archer
 * @brief Fonction qui permet [d]'afficher l'arbre de competences de l'archer
 *
 * @param window
 * @param renderer
 */
int afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre *archer,TTF_Font* font) 
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    SDL_Surface *surface;
    SDL_Texture *texture;


    SDL_Color color = {255, 255, 255, 255};


    while (running1)
    {
        SDL_Delay(20);
        afficher_background(window, renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* -------------------------------------------------------------------------- */
        /*                              Dessin des Lignes                             */
        /* -------------------------------------------------------------------------- */

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 3); // 1
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 1 / 3); // 2
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 6, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 3); // 3

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2); // 4
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2); // 5
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2); // 6
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2); // 7

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 2 / 3); // 8
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 2 / 3); // 9
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 2 / 3); // 10
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 2 / 3); // 11

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 12
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 13
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 2 / 3, WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 5 / 6); // 14

        /* -------------------------------------------------------------------------- */
        /*        Ajout des rectangles au bout des lignes pour les compétences        */
        /* -------------------------------------------------------------------------- */

        SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect2 = {WINDOW_WIDTH * 1 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect3 = {WINDOW_WIDTH * 4 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect4 = {WINDOW_WIDTH * 7 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect5 = {WINDOW_WIDTH * 1 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect6 = {WINDOW_WIDTH * 3 / 4 - TILE_SIZE / 2, WINDOW_HEIGHT * 1 / 2 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect7 = {WINDOW_WIDTH * 1 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect8 = {WINDOW_WIDTH * 4 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};
        SDL_Rect rect9 = {WINDOW_WIDTH * 7 / 8 - TILE_SIZE / 2, WINDOW_HEIGHT * 2 / 3 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect10 = {WINDOW_WIDTH * 1 / 2 - TILE_SIZE / 2, WINDOW_HEIGHT * 5 / 6 - TILE_SIZE / 2, TAILLE_CASE, TAILLE_CASE};

        SDL_Rect rect_ret = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 5 / 6, 120, TAILLE_CASE};

        surface = TTF_RenderText_Solid(font, "Retour", color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_ret);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(20);


        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        for (int i = 0; i < 10; i++)
        {
            printf("%s \n", archer->competence[i]->name_img);
        }

        afficher_comp(archer->competence[0]->name_img, renderer, rect1);

        afficher_comp(archer->competence[1]->name_img, renderer, rect2);
        afficher_comp(archer->competence[2]->name_img, renderer, rect3);
        afficher_comp(archer->competence[3]->name_img, renderer, rect4);

        afficher_comp(archer->competence[4]->name_img, renderer, rect5);
        afficher_comp(archer->competence[5]->name_img, renderer, rect6);

        afficher_comp(archer->competence[6]->name_img, renderer, rect7);
        afficher_comp(archer->competence[7]->name_img, renderer, rect8);
        afficher_comp(archer->competence[8]->name_img, renderer, rect9);

        afficher_comp(archer->competence[9]->name_img, renderer, rect10);
        SDL_Delay(20);
        SDL_RenderPresent(renderer);

        running = 1;

        while (running)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = 0;
                    running1 = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_TAB:
                        running = 0;
                        running1 = 0;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        x = event.button.x;
                        y = event.button.y;
                        
                        if(in_rect(x, y, &rect_ret)) 
                        {
                            return 1;
                        }
                        else if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[0]->name_img, entite, &cpt_archer[0], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[1]->name_img, entite, &cpt_archer[1], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[2]->name_img, entite, &cpt_archer[2], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[3]->name_img, entite, &cpt_archer[3], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[4]->name_img, entite, &cpt_archer[4], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[5]->name_img, entite, &cpt_archer[5], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[6]->name_img, entite, &cpt_archer[6], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[7]->name_img, entite, &cpt_archer[7], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[8]->name_img, entite, &cpt_archer[8], archer,font);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, archer->competence[9]->name_img, entite, &cpt_archer[9], archer,font);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
    
  
}

/**
 * @fn afficher_menu
 * @brief Fonction qui permet d'afficher un menu complet avec la possibilité de choisir entre les 4 arbres de compétences
 *
 * @param window
 * @param renderer
 * @param entite
 */
void afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite,TTF_Font* font)
{
    SDL_Delay(10);
    SDL_RenderClear(renderer);

    afficher_background(window,renderer);

    int rect_width = 120;
    int rect_height = 50;

    int running = 1;
    int running1 = 1;

    t_arbre* archer;
    t_arbre* guerrier;
    t_arbre* mage;
    t_arbre* assassin;

    init_arbre(&archer, cpt_archer, ARCHER);
    init_arbre(&mage, cpt_mage, MAGE);
    init_arbre(&guerrier, cpt_guerrier, GUERRIER);
    init_arbre(&assassin, cpt_assassin, ASSASSIN);

    SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect2 = {WINDOW_WIDTH * 5 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect3 = {WINDOW_WIDTH * 9 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect4 = {WINDOW_WIDTH * 13 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect_quit = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 5 / 6, rect_width, rect_height};

    SDL_Texture *texture;
    SDL_Surface *surface;

    SDL_Event event;

    int x, y;

    if (font == NULL)
    {
        printf("Erreur lors du chargement de la police \n");
    }
    
    while(running1) {

        //SDL_RenderClear(renderer);

        //afficher_background(window, renderer);

        SDL_Color color_red = {255, 0, 0, 255};
        surface = TTF_RenderText_Solid(font, "Guerrier", color_red);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect1);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Color color_green = {0, 255, 0, 255};
        surface = TTF_RenderText_Solid(font, "Archer", color_green);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect2);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Color color_purple = {186, 85, 238, 255};
        surface = TTF_RenderText_Solid(font, "Assassin", color_purple);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect3);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Color color_blue = {0, 0, 255};
        surface = TTF_RenderText_Solid(font, "Mage", color_blue);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect4);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Color color_white = {255, 255, 255};
        surface = TTF_RenderText_Solid(font, "Quitter", color_white);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_quit);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        SDL_Delay(20);
        SDL_RenderPresent(renderer);

        running = 1;

        while (running)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_TAB:
                        running = 0;
                        break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        x = event.button.x;
                        y = event.button.y;

                        if(in_rect(x, y, &rect_quit)) {
                            running = 0;
                            running1 = 0;
                        }

                        if (in_rect(x, y, &rect1))
                        {   
                            
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_arbre_guerrier(window, renderer, entite, guerrier,font);
                            SDL_RenderClear(renderer);
                            afficher_background(window,renderer);
                            running = 0;
                        }

                        if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_arbre_archer(window, renderer, entite, archer,font);
                            SDL_RenderClear(renderer);
                            afficher_background(window,renderer);
                            running = 0;
                        }

                        if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_arbre_assassin(window, renderer, entite, assassin,font);
                            SDL_RenderClear(renderer);
                            afficher_background(window,renderer);
                            running = 0;
                        }

                        if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            
                            running1 = afficher_arbre_mage(window, renderer, entite, mage,font);
                            SDL_RenderClear(renderer);
                            afficher_background(window,renderer);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @fn afficher_competence_SDL
 * @brief Affichage d'une compétences avec :
 *        --> L'affichage de l'image
 *        --> L'affichage du résume des items pour la competence
 *        --> Un bouton débloquer et un bouton retour
 *
 * @param window
 * @param renderer
 * @param path_comp
 * @param entite
 * @param competence
 * @return int
 */
int afficher_competence_SDL(SDL_Window *window,SDL_Renderer *renderer,char *path_comp,entite_t *entite,t_competence *competence,t_arbre *arbre,TTF_Font* font)
{
    int x, y;

    int running = 1;
    int rang_obj = 0;
    int check;

    int nb_obj_requis;
    int nb_obj_entite;

    char chaine[TAILLE_CHAINE_COMPETENCE];
    char nom_obj[50];

    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Event event;
    SDL_Delay(20);
    afficher_background(window, renderer);

    if (font == NULL)
    {
        printf("Erreur lors du chargement de la police \n");
    }

    SDL_Color color = {255, 255, 255, 255};

    /* -------------------------------------------------------------------------- */
    /*                   Rectangle d'affichage de la competence                   */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 2 / 8, TAILLE_CASE * 3 / 2, TAILLE_CASE * 3 / 2};
    afficher_comp(path_comp, renderer, rect1);

    /* -------------------------------------------------------------------------- */
    /*                       Rectangle d'affichage du nom                         */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect_obj_nom = {WINDOW_WIDTH * 1 / 20, WINDOW_HEIGHT * 1 / 8, TAILLE_CASE * 5, TAILLE_CASE};

    /* -------------------------------------------------------------------------- */
    /*                 Rectangles d'affichage des boutons de sortie                */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect_deb = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 12 / 16, 120, TAILLE_CASE};
    SDL_Rect rect_ret = {WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 12 / 16, 120, TAILLE_CASE};

    /* -------------------------------------------------------------------------- */
    /*                      Rectangles d'affichage des erreurs                    */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect_err = {WINDOW_WIDTH * 1 / 6, WINDOW_HEIGHT * 15 / 16, 400, TAILLE_CASE};

    int tab[5] =
        {
            (int)competence->buff.buff_vie,
            (int)competence->buff.buff_degat,
            (int)competence->buff.buff_vit_att,
            (int)competence->buff.buff_vit_depl,
            (int)competence->buff.perim_detect
        };

    for (int i = 0; i < 5; i++)
    {
        SDL_Rect rect_buff = {WINDOW_WIDTH * 1 / 16, WINDOW_HEIGHT * (6 + i * 2) / 16, 200, TAILLE_CASE - 10};
        int check = construire_chaine_buff(chaine, i, tab[i]);
        if (check == 1)
        {

            surface = TTF_RenderText_Solid(font, chaine, color);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Delay(20);
            SDL_RenderCopy(renderer, texture, NULL, &rect_buff);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }

    /* -------------------------------------------------------------------------- */
    /*                         Affichage des objets requis                        */
    /* -------------------------------------------------------------------------- */

    for (int i = 0; i < competence->taille_tab_obj_nec; i++)
    {
        strcpy(nom_obj, competence->obj_necessaires->objet[i].nom);

        rang_obj = acces_obj(nom_obj);

        nb_obj_entite = entite->inventaire->nb[rang_obj];
        nb_obj_requis = competence->obj_necessaires->nb[i];

        construire_chaine_objets(chaine, nb_obj_entite, nb_obj_requis, nom_obj);

        SDL_Rect rect_obj = {WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * (i + 1) / 8, TAILLE_CASE_ITEM_RES, TAILLE_CASE};

        surface = TTF_RenderText_Solid(font, chaine, color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect_obj);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    surface = TTF_RenderText_Solid(font, "Debloquer", color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect_deb);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, "Retour", color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect_ret);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, competence->nom, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect_obj_nom);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_Delay(20);
    SDL_RenderPresent(renderer);

    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_TAB:
                    return 0;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    x = event.button.x;
                    y = event.button.y;
                    if(in_rect(x, y, &rect_deb)) {
                        check = competence_debloquer(entite, competence, arbre);
                        return 1;
                    }

                    if (in_rect(x, y, &rect_ret))
                    {
                        return 1;
                    }
                }
            }
        }
    }
}
/*
    int main()
    {

        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *window = SDL_CreateWindow("Arbre de C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        afficher_background(window, renderer);

        int running = 1;
        int x, y;

        SDL_Event event;

        entite_t *personnage = creer_personnage(personnage);
        personnage = init_inventaire_personnage(personnage);

        for (int i = 0; i < NB_OBJET; i++)
        {
            personnage->inventaire->nb[i] = 100;
        }

        afficher_menu(window, renderer, personnage);

        detruire_entitee(personnage);

        TTF_Quit();
        return 0;
    }
    */