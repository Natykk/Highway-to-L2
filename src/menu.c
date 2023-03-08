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

int menu(SDL_Renderer* renderer,SDL_Window* window) {
    //SDL_Init(SDL_INIT_VIDEO);
    //SDL_Window* window = SDL_CreateWindow("Arbre de C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Dessin des éléments graphiques de l'arbre
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // affichage d'une image de fond
    SDL_Surface* image = IMG_Load("../img/background_comp.jpg");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture2, NULL, NULL);
    SDL_FreeSurface(image);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 400, 50, 400, 150);
    SDL_RenderDrawLine(renderer, 250, 250, 400, 150);

    SDL_RenderDrawLine(renderer, 250, 250, 150, 350);
    SDL_RenderDrawLine(renderer, 250, 250, 350, 350);

    SDL_RenderDrawLine(renderer, 150, 350, 250, 450);
    SDL_RenderDrawLine(renderer, 350, 350, 250, 450);

    SDL_RenderDrawLine(renderer, 250, 450, 400, 550);


    SDL_RenderDrawLine(renderer, 400, 150, 550, 250);
    SDL_RenderDrawLine(renderer, 550, 250, 450, 350);
    SDL_RenderDrawLine(renderer, 550, 250, 650, 350);

    SDL_RenderDrawLine(renderer, 450, 350, 550, 450);
    SDL_RenderDrawLine(renderer, 650, 350, 550, 450);

    SDL_RenderDrawLine(renderer, 550, 450, 400, 550);
    
    // Ajout des rectangles au bout des lignes pour les compétences
    SDL_Rect rect1 = { 400, 50, 50, 50 };
    SDL_Rect rect2 = { 250, 250, 50, 50 };
    SDL_Rect rect3 = { 150, 350, 50, 50 };
    SDL_Rect rect4 = { 350, 350, 50, 50 };
    SDL_Rect rect5 = { 250, 450, 50, 50 };
    SDL_Rect rect6 = { 400, 150, 50, 50 };
    SDL_Rect rect7 = { 550, 250, 50, 50 };
    SDL_Rect rect8 = { 450, 350, 50, 50 };
    SDL_Rect rect9 = { 650, 350, 50, 50 };
    SDL_Rect rect10 = { 550, 450, 50, 50 };

    // Ajout de la couleur des rectangles gris
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
    SDL_RenderFillRect(renderer, &rect4);
    SDL_RenderFillRect(renderer, &rect5);
    SDL_RenderFillRect(renderer, &rect6);
    SDL_RenderFillRect(renderer, &rect7);
    SDL_RenderFillRect(renderer, &rect8);
    SDL_RenderFillRect(renderer, &rect9);
    SDL_RenderFillRect(renderer, &rect10);

    // Ajout des textes
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("../font/necrosans.ttf", 18);
    // SDL couleur noir 
    
    SDL_Color color_txt = { 0, 0, 0 };
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "C 1", color_txt);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect1);

    surface = TTF_RenderText_Solid(font, "C2", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);

    surface = TTF_RenderText_Solid(font, "C 3", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect3);

    surface = TTF_RenderText_Solid(font, "C 4", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect4);

    surface = TTF_RenderText_Solid(font, "C 5", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect5);

    surface = TTF_RenderText_Solid(font, "C 6", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect6);

    surface = TTF_RenderText_Solid(font, "C 7", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect7);

    surface = TTF_RenderText_Solid(font, "C 8", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect8);

    surface = TTF_RenderText_Solid(font, "C 9", color_txt);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect9);

    surface = TTF_RenderText_Solid(font, "C 10", color_txt);
    // affiche le texte sur le rectangle
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect10);

    
    

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
                        case SDL_SCANCODE_LSHIFT:
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