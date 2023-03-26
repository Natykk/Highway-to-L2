#include "../head/menu_cpt.h"

/**
 * @file menu_cpt.c
 * @author GEORGET Rémy
 * @brief
 * @date 2023-03-24
 */

/**
 * @fn construire_chaine
 * @brief Fonction qui construit la chaine sur le format suivant : "Nom_Objet : Nb_Obj --> Nb_Obj_Requis"
 *
 * @param result
 * @param nb_obj
 * @param competence
 */
void construire_chaine(char *result, int nb_obj, int nb_obj_requis, char *nom_obj)
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

    // Nom : Nombre_Obj / Nombre_Obj_Requis
    strcat(nom_obj, nombre_requis);

    // Copie dans la chaine result
    strcpy(result, nom_obj);
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
 *
 * @param window
 * @param renderer
 */
void afficher_background(SDL_Window *window, SDL_Renderer *renderer)
{
    // Affichage d'une image de fond
    SDL_Surface *image = IMG_Load("background_comp.jpg");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture_background, NULL, NULL);
    SDL_FreeSurface(image);
    SDL_DestroyTexture(texture_background);
    SDL_RenderPresent(renderer);
}

/**
 * @fn afficher_arbre_assassin
 * @brief Fonction qui affiche l'arbre de competences de l'assassin
 *
 * @param window
 * @param renderer
 */
void afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

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

        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp("IMG/competences/assassin/FR_l.png", renderer, rect1);

        afficher_comp("IMG/competences/assassin/CM_l.png", renderer, rect2);
        afficher_comp("IMG/competences/assassin/CI_l.png", renderer, rect3);

        afficher_comp("IMG/competences/assassin/CP_l.png", renderer, rect4);
        afficher_comp("IMG/competences/assassin/EP_l.png", renderer, rect5);
        afficher_comp("IMG/competences/assassin/SM_l.png", renderer, rect6);
        afficher_comp("IMG/competences/assassin/MO_l.png", renderer, rect7);

        afficher_comp("IMG/competences/assassin/BC_l.png", renderer, rect8);
        afficher_comp("IMG/competences/assassin/BF_l.png", renderer, rect9);

        afficher_comp("IMG/competences/assassin/CF_l.png", renderer, rect10);

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

                        if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/FR_l.pn", entite, entite->arbre->competence[0]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/CM_l.pn", entite, entite->arbre->competence[1]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/CI_l.pn", entite, entite->arbre->competence[2]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/CP_l.pn", entite, entite->arbre->competence[3]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/EP_l.pn", entite, entite->arbre->competence[4]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/SM_l.pn", entite, entite->arbre->competence[5]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/MO_l.pn", entite, entite->arbre->competence[6]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/BC_l.pn", entite, entite->arbre->competence[7]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/BF_l.pn", entite, entite->arbre->competence[8]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            afficher_competence_SDL(window, renderer, "IMG/competences/assassin/CF_l.pn", entite, entite->arbre->competence[9]);
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
void afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

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

        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp("IMG/competences/guerrier/RG_l.png", renderer, rect1);

        afficher_comp("IMG/competences/guerrier/K_l.png", renderer, rect2);
        afficher_comp("IMG/competences/guerrier/GB_l.png", renderer, rect3);
        afficher_comp("IMG/competences/guerrier/E2M_l.png", renderer, rect4);
        afficher_comp("IMG/competences/guerrier/H_l.png", renderer, rect5);

        afficher_comp("IMG/competences/guerrier/BN_l.png", renderer, rect6);
        afficher_comp("IMG/competences/guerrier/AH_l.png", renderer, rect7);

        afficher_comp("IMG/competences/guerrier/BG_l.png", renderer, rect8);
        afficher_comp("IMG/competences/guerrier/BSL_l.png", renderer, rect9);

        afficher_comp("IMG/competences/guerrier/RB_l.png", renderer, rect10);

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

                        if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/RG_l.pn", entite, entite->arbre->competence[0]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/K_l.png", entite, entite->arbre->competence[1]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/GB_l.pn", entite, entite->arbre->competence[2]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/E2M_l.p", entite, entite->arbre->competence[3]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/H_l.png", entite, entite->arbre->competence[4]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/BN_l.pn", entite, entite->arbre->competence[5]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/AH_l.pn", entite, entite->arbre->competence[6]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/BG_l.pn", entite, entite->arbre->competence[7]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/BSL_l.p", entite, entite->arbre->competence[8]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/guerrier/RB_l.pn", entite, entite->arbre->competence[9]);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
    SDL_Quit();
    TTF_Quit();
}

/**
 * @fn afficher_arbre_mage
 * @brief Fonction qui permet d'afficher l'arbre de competences du guerrier
 *
 * @param window
 * @param renderer
 */
void afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    while (running1)
    {
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

        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp("IMG/competences/mage/BMS_l.png", renderer, rect1);

        afficher_comp("IMG/competences/mage/GG_l.png", renderer, rect2);
        afficher_comp("IMG/competences/mage/BA_l.png", renderer, rect3);

        afficher_comp("IMG/competences/mage/BC_l.png", renderer, rect4);

        afficher_comp("IMG/competences/mage/ME_l.png", renderer, rect5);
        afficher_comp("IMG/competences/mage/MT_l.png", renderer, rect6);
        afficher_comp("IMG/competences/mage/MF_l.png", renderer, rect7);
        afficher_comp("IMG/competences/mage/MN_l.png", renderer, rect8);
        afficher_comp("IMG/competences/mage/MC_l.png", renderer, rect9);

        afficher_comp("IMG/competences/mage/AM_l.png", renderer, rect10);

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

                        if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/BMS_l.png", entite, entite->arbre->competence[0]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/GG_l.png", entite, entite->arbre->competence[1]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/BA_l.png", entite, entite->arbre->competence[2]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/BC_l.png", entite, entite->arbre->competence[3]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/ME_l.png", entite, entite->arbre->competence[4]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/MT_l.png", entite, entite->arbre->competence[5]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/MF_l.png", entite, entite->arbre->competence[6]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/MN_l.png", entite, entite->arbre->competence[7]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/MC_l.png", entite, entite->arbre->competence[8]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/mage/AM_l.png", entite, entite->arbre->competence[9]);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
    SDL_Quit();
    TTF_Quit();
}

/**
 * @fn afficher_arbre_archer
 * @brief Fonction qui permet d'afficher l'arbre de competences de l'archer
 *
 * @param window
 * @param renderer
 */
void afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite)
{

    int running = 1;
    int running1 = 1;
    int x, y;

    SDL_Event event;

    while (running1)
    {
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

        /* -------------------------------------------------------------------------- */
        /*                          Affichage des competences                         */
        /* -------------------------------------------------------------------------- */

        afficher_comp("IMG/competences/archer/DF_l.png", renderer, rect1);

        afficher_comp("IMG/competences/archer/AS_l.png", renderer, rect2);
        afficher_comp("IMG/competences/archer/AE_l.png", renderer, rect3);
        afficher_comp("IMG/competences/archer/AV_l.png", renderer, rect4);

        afficher_comp("IMG/competences/archer/MN_l.png", renderer, rect5);
        afficher_comp("IMG/competences/archer/BH_l.png", renderer, rect6);

        afficher_comp("IMG/competences/archer/FP_l.png", renderer, rect7);
        afficher_comp("IMG/competences/archer/FG_l.png", renderer, rect8);
        afficher_comp("IMG/competences/archer/FV_l.png", renderer, rect9);

        afficher_comp("IMG/competences/archer/SU_l.png", renderer, rect10);

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

                        if (in_rect(x, y, &rect1))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/DF_l.png", entite, entite->arbre->competence[0]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect2))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/AS_l.png", entite, entite->arbre->competence[1]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect3))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/AE_l.png", entite, entite->arbre->competence[2]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect4))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/AV_l.png", entite, entite->arbre->competence[3]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect5))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/MN_l.png", entite, entite->arbre->competence[4]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect6))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/BH_l.png", entite, entite->arbre->competence[5]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect7))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/FP_l.png", entite, entite->arbre->competence[6]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect8))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/FG_l.png", entite, entite->arbre->competence[7]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect9))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/FV_l.png", entite, entite->arbre->competence[8]);
                            running = 0;
                        }
                        else if (in_rect(x, y, &rect10))
                        {
                            SDL_RenderClear(renderer);
                            running1 = afficher_competence_SDL(window, renderer, "IMG/competences/archer/SU_l.png", entite, entite->arbre->competence[9]);
                            running = 0;
                        }
                    }
                }
            }
        }
    }
    SDL_Quit();
    TTF_Quit();
}

/**
 * @fn afficher_menu
 * @brief Fonction qui permet d'afficher un menu complet avec la possibilité de choisir entre les 4 arbres de compétences
 *
 * @param window
 * @param renderer
 * @param entite
 */
void afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite)
{
    TTF_Init();

    int rect_width = 120;
    int rect_height = 50;

    int running = 1;

    SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect2 = {WINDOW_WIDTH * 5 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect3 = {WINDOW_WIDTH * 9 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};
    SDL_Rect rect4 = {WINDOW_WIDTH * 13 / 16, WINDOW_HEIGHT * 1 / 2, rect_width, rect_height};

    SDL_Texture *texture;
    SDL_Surface *surface;

    SDL_Event event;

    int x, y;

    TTF_Font *font = TTF_OpenFont("necrosans.ttf", 24);
    if (font == NULL)
    {
        printf("Erreur lors du chargement de la police \n");
    }

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

    SDL_RenderPresent(renderer);

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
                    if (in_rect(x, y, &rect1))
                    {
                        SDL_RenderClear(renderer);
                        afficher_arbre_guerrier(window, renderer, entite);
                        running = 0;
                    }

                    if (in_rect(x, y, &rect2))
                    {
                        SDL_RenderClear(renderer);
                        afficher_arbre_archer(window, renderer, entite);
                        running = 0;
                    }

                    if (in_rect(x, y, &rect3))
                    {
                        SDL_RenderClear(renderer);
                        afficher_arbre_assassin(window, renderer, entite);
                        running = 0;
                    }

                    if (in_rect(x, y, &rect4))
                    {
                        SDL_RenderClear(renderer);
                        afficher_arbre_mage(window, renderer, entite);
                        running = 0;
                    }
                }
            }
        }
    }
    SDL_Quit();
    TTF_Quit();
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
int afficher_competence_SDL(SDL_Window *window,
                            SDL_Renderer *renderer,
                            char *path_comp,
                            entite_t *entite,
                            t_competence competence)
{
    TTF_Init();
    int x, y;

    int running = 1;
    int rang_obj = 0;

    int nb_obj_requis;
    int nb_obj_entite;

    char chaine[TAILLE_CHAINE_COMPETENCE];
    char nom_obj[TAILLE_CHAINE_NOM];

    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Event event;
    afficher_background(window, renderer);

    TTF_Font *font = TTF_OpenFont("necrosans.ttf", 24);
    if (font == NULL)
    {
        printf("Erreur lors du chargement de la police \n");
    }

    SDL_Color color = {255, 255, 255, 255};

    /* -------------------------------------------------------------------------- */
    /*                   Rectangle d'affichage de la competence                   */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect1 = {WINDOW_WIDTH * 1 / 8, WINDOW_HEIGHT * 3 / 8, TAILLE_CASE * 2, TAILLE_CASE * 2};
    afficher_comp(path_comp, renderer, rect1);

    /* -------------------------------------------------------------------------- */
    /*                  Rectangles d'affichage de l'inventaire                 */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect_obj1 = {WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 1 / 8, TAILLE_CASE, TAILLE_CASE};
    SDL_Rect rect_obj2 = {WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 2 / 8, TAILLE_CASE, TAILLE_CASE};
    SDL_Rect rect_obj3 = {WINDOW_WIDTH * 1 / 2, WINDOW_HEIGHT * 3 / 8, TAILLE_CASE, TAILLE_CASE};

    /* -------------------------------------------------------------------------- */
    /*                 Rectangle d'affichage des boutons de sortie                */
    /* -------------------------------------------------------------------------- */

    SDL_Rect rect_deb = {WINDOW_WIDTH * 6 / 8, WINDOW_HEIGHT * 12 / 16, 120, TAILLE_CASE};
    SDL_Rect rect_ret = {WINDOW_WIDTH * 4 / 8, WINDOW_HEIGHT * 12 / 16, 120, TAILLE_CASE};

    for (int i = 0; i < competence.taille_tab_obj_nec; i++)
    {

        strcpy(nom_obj, competence.obj_necessaires->objet[i].nom);

        rang_obj = acces_obj(nom_obj);

        nb_obj_entite = entite->inventaire->nb[rang_obj];
        nb_obj_requis = competence.obj_necessaires->nb[i];

        construire_chaine(chaine, nb_obj_entite, nb_obj_requis, nom_obj);

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

                    if (in_rect(x, y, &rect_deb))
                    {
                        return 0;
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

/**/
int main() {


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arbre de C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    afficher_background(window,renderer);

    int running = 1;
    int x,y;

    SDL_Event event;

    entite_t* personnage = creer_personnage(personnage);
    personnage = init_inventaire_personnage(personnage);
    init_arbre(&personnage->arbre, cpt_mage, MAGE);

    for(int i = 0; i < NB_OBJET; i++) {
        personnage->inventaire->nb[i] = i;
    }

    afficher_menu(window, renderer, personnage);

    detruire_arbre(&personnage->arbre);
    detruire_entitee(personnage);

    return 0;
    
}
