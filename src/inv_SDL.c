#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include </home/remy/SDL2/include/SDL2/SDL.h>
#include </home/remy/SDL2/include/SDL2/SDL_timer.h>
#include </home/remy/SDL2/include/SDL2/SDL_image.h>
#include </home/remy/SDL2/include/SDL2/SDL_mixer.h>
#include </home/remy/SDL2/include/SDL2/SDL_ttf.h>
#include "../head/entite.h"

#define TILE_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 25

/**
 * \fn void affichage(SDL_Renderer *renderer, SDL_Window *window, entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing, TTF_Font *font, int total_width, int x_start, SDL_Texture *tab_tex[17])
 * @brief Affiche l'inventaire
 * @param renderer le renderer
 * @param window la fenetre
 * @param pers le personnage
 * @param num_rectangles le nombre d'items dans l'inventaire
 * @param rect_width la largeur des rectangles contenant les items
 * @param rect_height la hauteur des rectangles contenant les items
 * @param rect_spacing l'espace entre les items
 * @param font la police
 * @param total_width la largeur totale de l'inventaire
 * @param x_start la position de départ en x
 * @param tab_tex le tableau de textures
 * 
*/
void affichage(SDL_Renderer *renderer, SDL_Window *window, entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing, TTF_Font *font, int total_width, int x_start, SDL_Texture *tab_tex[17])
{
    int i;
    int nbObjet;
    char *nomObjet;
    char *DescObjet;

    // Initialisation de la police
    for (i = 0; i < num_rectangles; i++)
    {

        // tout les 6 rectangles, on descend d'une ligne (6 rectangles par ligne) on remet x au début
        int x = x_start + (i % 4) * (rect_width + rect_spacing);
        int y = 100 + (i / 4) * (rect_height + rect_spacing);

        SDL_Rect rect; // rectangle de l'objet
        rect.x = x;
        rect.y = y;
        rect.w = rect_width;
        rect.h = rect_height;

        // Afficher le nombre sous le rectangle
        SDL_Color color = {255, 255, 255, 255};
        char str[30];
        nbObjet = pers->inventaire->nb[i]; // nombre d'objet
        nomObjet = pers->inventaire->objet[i].nom; // nom de l'objet
        sprintf(str, "%s:%d", nomObjet, nbObjet);  // concatène le nom et le nombre
        SDL_Surface *text_surface = TTF_RenderText_Solid(font, str, color); // surface du texte
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // texture du texte
        SDL_Rect text_rect;
        text_rect.x = x + rect_width / 2 - text_surface->w / 2; // centre le texte
        text_rect.y = y + rect_height;
        text_rect.w = text_surface->w; // largeur du texte
        text_rect.h = text_surface->h; // hauteur du texte
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect); // affiche le texte
        // affiche les textures des objets
        SDL_RenderCopy(renderer, tab_tex[i], NULL, &rect); // affiche l'objet

        SDL_FreeSurface(text_surface); // libère la surface
        SDL_DestroyTexture(text_texture); // libère la texture
    }
}
/**
 * \fn int inv(SDL_Renderer *renderer, SDL_Window *window, entite_t *pers)
 * @brief Affiche l'inventaire
 * @param renderer le renderer
 * @param window la fenetre
 * @param pers le personnage
 * @return 0 si tout s'est bien passé
*/
int inv(SDL_Renderer *renderer, SDL_Window *window, entite_t *pers)
{
    TTF_Init();
    SDL_SetWindowSize(window, 1100, 900);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // on charge les textures des images de l'inventaire
    SDL_Surface *Cailloux_surf = IMG_Load("../IMG/items/Cailloux.png");
    SDL_Texture *Cailloux_Tex = SDL_CreateTextureFromSurface(renderer, Cailloux_surf);
    SDL_FreeSurface(Cailloux_surf);

    SDL_Surface *Coeur_de_Diable_surf = IMG_Load("../IMG/items/Coeur_de_Diable.png");
    SDL_Texture *Coeur_de_Diable_Tex = SDL_CreateTextureFromSurface(renderer, Coeur_de_Diable_surf);
    SDL_FreeSurface(Coeur_de_Diable_surf);

    SDL_Surface *Corne_de_Diablotin_surf = IMG_Load("../IMG/items/Corne_de_Diablotin.png");
    SDL_Texture *Corne_de_Diablotin_Tex = SDL_CreateTextureFromSurface(renderer, Corne_de_Diablotin_surf);
    SDL_FreeSurface(Corne_de_Diablotin_surf);

    SDL_Surface *Croquette_surf = IMG_Load("../IMG/items/Croquette.png");
    SDL_Texture *Croquette_Tex = SDL_CreateTextureFromSurface(renderer, Croquette_surf);
    SDL_FreeSurface(Croquette_surf);

    SDL_Surface *Fourrure_surf = IMG_Load("../IMG/items/Fourrure.png");
    SDL_Texture *Fourrure_Tex = SDL_CreateTextureFromSurface(renderer, Fourrure_surf);
    SDL_FreeSurface(Fourrure_surf);

    SDL_Surface *Green_Goo_surf = IMG_Load("../IMG/items/Green_Goo.png");
    SDL_Texture *Green_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Green_Goo_surf);
    SDL_FreeSurface(Green_Goo_surf);

    SDL_Surface *Grey_Goo_surf = IMG_Load("../IMG/items/Grey_Goo.png");
    SDL_Texture *Grey_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Grey_Goo_surf);
    SDL_FreeSurface(Grey_Goo_surf);

    SDL_Surface *Griffe_surf = IMG_Load("../IMG/items/Griffe.png");
    SDL_Texture *Griffe_Tex = SDL_CreateTextureFromSurface(renderer, Griffe_surf);
    SDL_FreeSurface(Griffe_surf);

    SDL_Surface *Grimoire_surf = IMG_Load("../IMG/items/Grimoire.png");
    SDL_Texture *Grimoire_Tex = SDL_CreateTextureFromSurface(renderer, Grimoire_surf);
    SDL_FreeSurface(Grimoire_surf);

    SDL_Surface *lance_surf = IMG_Load("../IMG/items/lance.png");
    SDL_Texture *lance_Tex = SDL_CreateTextureFromSurface(renderer, lance_surf);
    SDL_FreeSurface(lance_surf);

    SDL_Surface *lance_pierre_surf = IMG_Load("../IMG/items/lance_pierre.png");
    SDL_Texture *lance_pierre_Tex = SDL_CreateTextureFromSurface(renderer, lance_pierre_surf);
    SDL_FreeSurface(lance_pierre_surf);

    SDL_Surface *Massue_surf = IMG_Load("../IMG/items/Massue.png");
    SDL_Texture *Massue_Tex = SDL_CreateTextureFromSurface(renderer, Massue_surf);
    SDL_FreeSurface(Massue_surf);

    SDL_Surface *Or_surf = IMG_Load("../IMG/items/Or.png");
    SDL_Texture *Or_Tex = SDL_CreateTextureFromSurface(renderer, Or_surf);
    SDL_FreeSurface(Or_surf);

    SDL_Surface *Pioche_surf = IMG_Load("../IMG/items/Pioche.png");
    SDL_Texture *Pioche_Tex = SDL_CreateTextureFromSurface(renderer, Pioche_surf);
    SDL_FreeSurface(Pioche_surf);

    SDL_Surface *Queue_de_Diablotin_surf = IMG_Load("../IMG/items/Queue_de_Diablotin.png");
    SDL_Texture *Queue_de_Diablotin_Tex = SDL_CreateTextureFromSurface(renderer, Queue_de_Diablotin_surf);
    SDL_FreeSurface(Queue_de_Diablotin_surf);

    SDL_Surface *Red_Goo_surf = IMG_Load("../IMG/items/Red_Goo.png");
    SDL_Texture *Red_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Red_Goo_surf);
    SDL_FreeSurface(Red_Goo_surf);

    SDL_Surface *Tete_surf = IMG_Load("../IMG/items/Tete.png");
    SDL_Texture *Tete_Tex = SDL_CreateTextureFromSurface(renderer, Tete_surf);
    SDL_FreeSurface(Tete_surf);
    // on met les textures dans un tableau
    SDL_Texture *tab_tex[17] = {Or_Tex, Green_Goo_Tex, Fourrure_Tex, Griffe_Tex, Grimoire_Tex, Grey_Goo_Tex, Pioche_Tex, lance_pierre_Tex, Cailloux_Tex, Massue_Tex, Red_Goo_Tex, Corne_de_Diablotin_Tex, Queue_de_Diablotin_Tex, lance_pierre_Tex, Coeur_de_Diable_Tex, Tete_Tex, Croquette_Tex};
    // on met une image de fond
    SDL_Surface *backgroundSurface = IMG_Load("../img/background_comp.jpg");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_FreeSurface(backgroundSurface);

    int num_rectangles = 17;
    int rect_width = 60;
    int rect_height = 60;
    int rect_spacing = 150;
    int total_width = (num_rectangles * rect_width) + ((num_rectangles - 1) * rect_spacing);// 17 * 60 + 16 * 150 = 2550
    int x_start = (((TILE_SIZE * MAP_HEIGHT) - total_width) / 2) + 1450; 

    TTF_Font *font = TTF_OpenFont("../font/necrosans.ttf", 24);

    int running = 1;
    Uint32 last_desc_time;
    SDL_Rect text_rect;
    SDL_Rect sous_text_rect;
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;

    while (running)
    { // Boucle principale
        SDL_Event event;

        while (SDL_PollEvent(&event))
        { // On récupère les évènements
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                { // On récupère le code de la touche
                case SDL_SCANCODE_TAB:
                    running = 0;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int x = event.button.x;
                    int y = event.button.y;
                    last_desc_time = SDL_GetTicks();
                    for (int i = 0; i < num_rectangles; i++)
                    {
                        int rect_x = x_start + (i % 4) * (rect_width + rect_spacing);
                        int rect_y = 100 + (i / 4) * (rect_height + rect_spacing);
                        if (x >= rect_x && x < rect_x + rect_width && y >= rect_y && y < rect_y + rect_height)
                        {
                            // L'utilisateur a cliqué sur ce rectangle, afficher un texte
                            SDL_Color color = {255, 255, 255, 255};
                            char *DescObjet = pers->inventaire->objet[i].description;

                            char str[50];
                            sprintf(str, "%s", DescObjet);
                            text_surface = TTF_RenderText_Solid(font, str, color); // Création de la surface
                            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // Création de la texture
                            text_rect.x = (rect_x + rect_width) - 100; // Position du texte
                            text_rect.y = rect_y - 20; 
                            text_rect.w = text_surface->w;
                            text_rect.h = text_surface->h;

                            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect); // Affichage de la texture
                            SDL_FreeSurface(text_surface);
                            SDL_DestroyTexture(text_texture);

                            break;
                        }
                    }
                }
                break;
            }
        }
        affichage(renderer, window, pers, num_rectangles, rect_width, rect_height, rect_spacing, font, total_width, x_start, tab_tex);
        SDL_RenderPresent(renderer);
        if (SDL_GetTicks() - last_desc_time > 2000) // Si le texte est affiché depuis plus de 2 secondes
        {
            SDL_RenderClear(renderer); // On efface l'écran
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            last_desc_time = SDL_GetTicks();
        }
    }

    SDL_RenderClear(renderer);
    return 0;
}