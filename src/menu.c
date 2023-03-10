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
int const TailleRect = 50;

void guerrier(SDL_Renderer* renderer,SDL_Window* window){
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 400, 50, 400, 150); // ligne verticale gauche
    SDL_RenderDrawLine(renderer, 250, 250, 400, 150); // ligne verticale droite

    SDL_RenderDrawLine(renderer, 250, 250, 150, 350); //
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

    SDL_Rect rect1 = { 400-(TailleRect/2), 50-(TailleRect/2), 50, 50 };
    SDL_Rect rect3 = { 250-(TailleRect/2), 250-(TailleRect/2), 50, 50 };
    SDL_Rect rect5 = { 150-(TailleRect/2), 350-(TailleRect/2), 50, 50 };
    SDL_Rect rect6 = { 350-(TailleRect/2), 350-(TailleRect/2), 50, 50 };
    SDL_Rect rect9 = { 250-(TailleRect/2), 450-(TailleRect/2), 50, 50 };
    SDL_Rect rect2 = { 400-(TailleRect/2), 150-(TailleRect/2), 50, 50 };
    SDL_Rect rect4 = { 550-(TailleRect/2), 250-(TailleRect/2), 50, 50 };
    SDL_Rect rect7 = { 450-(TailleRect/2), 350-(TailleRect/2), 50, 50 };
    SDL_Rect rect8 = { 650-(TailleRect/2), 350-(TailleRect/2), 50, 50 };
    SDL_Rect rect10 = {550-(TailleRect/2), 450-(TailleRect/2), 50, 50 };
    SDL_Rect rect11 = {400-(TailleRect/2), 550-(TailleRect/2), 50, 50 };  // 650
    SDL_Rect tab_rect[11] = { rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, rect9, rect10 , rect11 };

    // Ajout de la couleur des rectangles gris
   /* SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
    SDL_RenderFillRect(renderer, &rect4);
    SDL_RenderFillRect(renderer, &rect5);
    SDL_RenderFillRect(renderer, &rect6);
    SDL_RenderFillRect(renderer, &rect7);
    SDL_RenderFillRect(renderer, &rect8);
    SDL_RenderFillRect(renderer, &rect9);
    SDL_RenderFillRect(renderer, &rect10);*/  
    // Ajout des textes
    
    TTF_Font* font = TTF_OpenFont("../font/necrosans.ttf", 18);
    // SDL couleur noir 
    
    SDL_Color color_txt = { 0, 0, 0 };
    SDL_Color color = { 0, 0, 0, 255 };

    char* tabC[11]={"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10","C11"};
    for(int i=0;i<11;i++){
        SDL_Surface* surface = TTF_RenderText_Solid(font,tabC[i], color_txt);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &tab_rect[i]);
    }

}

void mage(SDL_Renderer* renderer,SDL_Window* window) {

    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, 400, 50, 300, 150);// Niv 0 vers Gauche
    SDL_RenderDrawLine(renderer, 400, 50, 500, 150); // Niv 0 vers Droite

    SDL_RenderDrawLine(renderer, 300, 150, 400, 250);// Niv 1 Gauche
    SDL_RenderDrawLine(renderer, 500, 150, 400, 250);// Niv 1 Droite

    SDL_RenderDrawLine(renderer, 400, 250, 200, 350);// Niv 2 Tout a gauche
    SDL_RenderDrawLine(renderer, 400, 250, 300, 350);// Niv 2 Gauche
    SDL_RenderDrawLine(renderer, 400, 250, 500, 350);// Niv 2 Droite
    SDL_RenderDrawLine(renderer, 400, 250, 600, 350);// Niv 2 Tout a droite

    SDL_RenderDrawLine(renderer, 200, 350, 400, 450);// Niv 3 Tout a gauche vers millieu
    SDL_RenderDrawLine(renderer, 300, 350, 400, 450);// Niv 3 Gauche vers millieu
    SDL_RenderDrawLine(renderer, 500, 350, 400, 450);// Niv 3 Droite vers millieu
    SDL_RenderDrawLine(renderer, 600, 350, 400, 450);// Niv 3 Tout a droite vers millieu
    
    // Ajout des rectangles centré sur le bout des lignes pour affiché les compétences

    SDL_Rect rect1 = { 400-(TailleRect/2),  50-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect2 = { 300-(TailleRect/2), 150-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect3 = { 500-(TailleRect/2), 150-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect4 = { 200-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect5 = { 200-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect6 = { 300-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect7 = { 400-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect8 = { 500-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect9 = { 600-(TailleRect/2), 350-(TailleRect/2), TailleRect, TailleRect };
    SDL_Rect rect10 = { 400-(TailleRect/2),450-(TailleRect/2), TailleRect, TailleRect };


    SDL_Color color_txt = { 255, 255, 255 };
    TTF_Font* font = TTF_OpenFont("../font/necrosans.ttf", 20);

    SDL_Rect tab_rect[10] = { rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8, rect9, rect10};

    char* tabC[10]={"C1","C2","C3","C4","C5","C6","C7","C8","C9","C10"};
    for(int i=0;i<10;i++){
        SDL_Surface* surface = TTF_RenderText_Solid(font,tabC[i], color_txt);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &tab_rect[i]);
    }
    // remplissage de toute les rectangles
    /*for(int i=0;i<10;i++){
        SDL_RenderFillRect(renderer, &tab_rect[i]);
    }*/


}
int menu(SDL_Renderer* renderer,SDL_Window* window) {
    TTF_Init();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // affichage d'une image de fond
    SDL_Surface* image = IMG_Load("../img/background_comp.jpg");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture2, NULL, NULL);
    SDL_FreeSurface(image);
    
    guerrier(renderer,window);
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