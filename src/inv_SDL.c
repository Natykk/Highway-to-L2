#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../head/entite.h"

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
void affichage( SDL_Renderer *renderer, SDL_Window *window,entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing,TTF_Font *font,int total_width,int x_start,SDL_Texture* tab_tex[17]){
    int i;
    int nbObjet;
    char* nomObjet;
    char* DescObjet;
    

    


    // Initialisation de la police
    for (i = 0; i < num_rectangles; i++)
    {
        
        // tout les 6 rectangles, on descend d'une ligne (6 rectangles par ligne) on remet x au début
        int x = x_start + (i % 4) * (rect_width + rect_spacing);
        int y = 100 + (i / 4) * (rect_height + rect_spacing);
        
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = rect_width;
        rect.h = rect_height;



        // Afficher le nombre sous le rectangle
        SDL_Color color = {255, 255, 255, 255};
        char str[30];
        nbObjet = pers->inventaire->nb[i];
        nomObjet = pers->inventaire->objet[i].nom;
        if(nbObjet != 0){
            printf("nbObjet[%d] = %d\n",i,nbObjet);
        }
        sprintf(str, "%s:%d",nomObjet,nbObjet);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, str, color);
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        SDL_Rect text_rect;
        text_rect.x = x + rect_width/2 - text_surface->w/2;
        text_rect.y = y + rect_height;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        // affiche les textures des objets
        SDL_RenderCopy(renderer,tab_tex[i], NULL, &rect);
        
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }
}
int inv(SDL_Renderer* renderer,SDL_Window* window,entite_t* pers) {
    TTF_Init();
    SDL_SetWindowSize(window, 1100,900);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // on charge les textures des images de l'inventaire 
    SDL_Surface* Cailloux_surf = IMG_Load("../img/inv_items/Cailloux.png");
    SDL_Texture* Cailloux_Tex = SDL_CreateTextureFromSurface(renderer, Cailloux_surf);
    SDL_FreeSurface(Cailloux_surf);

    SDL_Surface* Coeur_de_Diable_surf = IMG_Load("../img/inv_items/Coeur_de_Diable.png");
    SDL_Texture* Coeur_de_Diable_Tex = SDL_CreateTextureFromSurface(renderer, Coeur_de_Diable_surf);
    SDL_FreeSurface(Coeur_de_Diable_surf);

    SDL_Surface* Corne_de_Diablotin_surf = IMG_Load("../img/inv_items/Corne_de_Diablotin.png");
    SDL_Texture* Corne_de_Diablotin_Tex = SDL_CreateTextureFromSurface(renderer, Corne_de_Diablotin_surf);
    SDL_FreeSurface(Corne_de_Diablotin_surf);

    SDL_Surface* Croquette_surf = IMG_Load("../img/inv_items/Croquette.png");
    SDL_Texture* Croquette_Tex = SDL_CreateTextureFromSurface(renderer, Croquette_surf);
    SDL_FreeSurface(Croquette_surf);

    SDL_Surface* Fourrure_surf = IMG_Load("../img/inv_items/Fourrure.png");
    SDL_Texture* Fourrure_Tex = SDL_CreateTextureFromSurface(renderer, Fourrure_surf);
    SDL_FreeSurface(Fourrure_surf);

    SDL_Surface* Green_Goo_surf = IMG_Load("../img/inv_items/Green_Goo.png");
    SDL_Texture* Green_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Green_Goo_surf);
    SDL_FreeSurface(Green_Goo_surf);

    SDL_Surface* Grey_Goo_surf = IMG_Load("../img/inv_items/Grey_Goo.png");
    SDL_Texture* Grey_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Grey_Goo_surf);
    SDL_FreeSurface(Grey_Goo_surf);

    SDL_Surface* Griffe_surf = IMG_Load("../img/inv_items/Griffe.png");
    SDL_Texture* Griffe_Tex = SDL_CreateTextureFromSurface(renderer, Griffe_surf);
    SDL_FreeSurface(Griffe_surf);

    SDL_Surface* Grimoire_surf = IMG_Load("../img/inv_items/Grimoire.png");
    SDL_Texture* Grimoire_Tex = SDL_CreateTextureFromSurface(renderer, Grimoire_surf);
    SDL_FreeSurface(Grimoire_surf);

    SDL_Surface* lance_surf = IMG_Load("../img/inv_items/lance.png");
    SDL_Texture* lance_Tex = SDL_CreateTextureFromSurface(renderer, lance_surf);
    SDL_FreeSurface(lance_surf);

    SDL_Surface* lance_pierre_surf = IMG_Load("../img/inv_items/lance_pierre.png");
    SDL_Texture* lance_pierre_Tex = SDL_CreateTextureFromSurface(renderer, lance_pierre_surf);
    SDL_FreeSurface(lance_pierre_surf);

    SDL_Surface* Massue_surf = IMG_Load("../img/inv_items/Massue.png");
    SDL_Texture* Massue_Tex = SDL_CreateTextureFromSurface(renderer, Massue_surf);
    SDL_FreeSurface(Massue_surf);

    SDL_Surface* Or_surf = IMG_Load("../img/inv_items/Or.png");
    SDL_Texture* Or_Tex = SDL_CreateTextureFromSurface(renderer, Or_surf);
    SDL_FreeSurface(Or_surf);

    SDL_Surface* Pioche_surf = IMG_Load("../img/inv_items/Pioche.png");
    SDL_Texture* Pioche_Tex = SDL_CreateTextureFromSurface(renderer, Pioche_surf);
    SDL_FreeSurface(Pioche_surf);

    SDL_Surface* Queue_de_Diablotin_surf = IMG_Load("../img/inv_items/Queue_de_Diablotin.png");
    SDL_Texture* Queue_de_Diablotin_Tex = SDL_CreateTextureFromSurface(renderer, Queue_de_Diablotin_surf);
    SDL_FreeSurface(Queue_de_Diablotin_surf);

    SDL_Surface* Red_Goo_surf = IMG_Load("../img/inv_items/Red_Goo.png");
    SDL_Texture* Red_Goo_Tex = SDL_CreateTextureFromSurface(renderer, Red_Goo_surf);
    SDL_FreeSurface(Red_Goo_surf);

    SDL_Surface* Tete_surf = IMG_Load("../img/inv_items/Tete.png");
    SDL_Texture* Tete_Tex = SDL_CreateTextureFromSurface(renderer, Tete_surf);
    SDL_FreeSurface(Tete_surf);


    SDL_Texture* tab_tex[17] = {Or_Tex,Green_Goo_Tex,Fourrure_Tex,Griffe_Tex,Grimoire_Tex,Grey_Goo_Tex,Pioche_Tex,lance_pierre_Tex,Cailloux_Tex,Massue_Tex,Red_Goo_Tex,Corne_de_Diablotin_Tex,Queue_de_Diablotin_Tex,lance_pierre_Tex,Coeur_de_Diable_Tex,Tete_Tex,Croquette_Tex};
    // on met une image de fond 
    SDL_Surface* backgroundSurface = IMG_Load("../img/background_comp.jpg");
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_FreeSurface(backgroundSurface);

    int num_rectangles = 17;
    int rect_width = 60;
    int rect_height = 60;
    int rect_spacing = 150;
    int total_width = (num_rectangles * rect_width) + ((num_rectangles - 1) * rect_spacing);
    int x_start = (((TILE_SIZE*MAP_HEIGHT) - total_width) / 2)+1450;

    TTF_Font* font = TTF_OpenFont("../font/necrosans.ttf", 24);
    
    int running = 1;
    Uint32 last_desc_time;
    SDL_Rect text_rect;
    SDL_Rect sous_text_rect;
    SDL_Surface* text_surface;
    SDL_Texture* text_texture; 
    
    while (running) { // Boucle principale
        SDL_Event event;
        
        
        while (SDL_PollEvent(&event)) { // On récupère les évènements
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) { // On récupère le code de la touche
                        case SDL_SCANCODE_TAB:
                            running = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;
                        last_desc_time = SDL_GetTicks();
                        for (int i = 0; i < num_rectangles; i++) {
                            int rect_x = x_start + (i % 4) * (rect_width + rect_spacing);
                            int rect_y = 100 + (i / 4) * (rect_height + rect_spacing);
                            if (x >= rect_x && x < rect_x + rect_width && y >= rect_y && y < rect_y + rect_height) {
                                // L'utilisateur a cliqué sur ce rectangle, afficher un texte
                                SDL_Color color = {255, 255, 255, 255};
                                char* DescObjet = pers->inventaire->objet[i].description;

                                char str[50];
                                sprintf(str, "%s",DescObjet);
                                text_surface = TTF_RenderText_Solid(font, str, color);
                                text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                                text_rect.x = (rect_x + rect_width)-100;
                                text_rect.y = rect_y-20;
                                text_rect.w = text_surface->w;
                                text_rect.h = text_surface->h;
                                
                                SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
                                SDL_FreeSurface(text_surface);
                                SDL_DestroyTexture(text_texture);

        

                                break;
                            }
                        }
                    }
                    break;
            }
        }
        affichage(renderer,window,pers, num_rectangles, rect_width, rect_height, rect_spacing,font,total_width,x_start,tab_tex);
        SDL_RenderPresent(renderer);
        if (SDL_GetTicks() - last_desc_time > 2000) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            last_desc_time = SDL_GetTicks();
        }
        

        
        
    }

    SDL_RenderClear(renderer);
    return 0;
}