#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../head/menu.h"
#define  TILE_SIZE  32
#define  MAP_WIDTH   25
#define  MAP_HEIGHT  25


/**
    *\brief Affiche l'inventaire d'une entité donnée en utilisant SDL_Renderer.Cette fonction affiche l'inventaire de l'entité donnée en créant une grille rectangulaire d'articles et de leurs quantités.
    *\param renderer Pointeur vers un objet SDL_Renderer utilisé pour afficher l'inventaire à l'écran.
    *\param window Pointeur vers un objet SDL_Window représentant la fenêtre dans laquelle l'inventaire est affiché.
    *\param pers Pointeur vers un objet entite_t représentant l'entité dont l'inventaire est affiché.
    *\return 0 si la fonction s'exécute avec succès.
**/
int inv(SDL_Renderer* renderer,SDL_Window* window,entite_t* pers) {
   SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../font/necrosans.ttf", 24);

    int num_rectangles = 23;
    int rect_width = 50;
    int rect_height = 60;
    int rect_spacing = 50;

    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    int total_width = (num_rectangles * rect_width) + ((num_rectangles - 1) * rect_spacing);
    int x_start = ((window_width - total_width) / 2)+850;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


    // on met une image de fond 
    SDL_Surface* backgroundSurface = IMG_Load("../img/background_comp.jpg");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_FreeSurface(backgroundSurface);

    int i;
    int nbObjet;
    for (i = 0; i < num_rectangles; i++)
    {
        
        // tout les 6 rectangles, on descend d'une ligne (6 rectangles par ligne) on remet x au début
        int x = x_start + (i % 6) * (rect_width + rect_spacing);
        int y = 100 + (i / 6) * (rect_height + rect_spacing);
        

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = rect_width;
        rect.h = rect_height;

        SDL_RenderFillRect(renderer, &rect);

        // Afficher le nombre sous le rectangle
        SDL_Color color = {255, 255, 255, 255};
        char str[10];
        nbObjet = pers->inventaire->nb[i];
        sprintf(str, "%d", nbObjet);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, str, color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect;
        text_rect.x = x + rect_width/2 - text_surface->w/2;
        text_rect.y = y + rect_height;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    SDL_RenderPresent(renderer);
    int running = 1;
  while (running) { // Boucle principale
    
  SDL_Event event;
  if (SDL_PollEvent(&event)) { // On récupère les évènements
        switch (event.type){
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode){ // On récupère le code de la touche
                        case SDL_SCANCODE_TAB:
                            running = 0;
                            break;
                    }
                break;
        }
    }
  }

    SDL_RenderClear(renderer);
    return 0;
}