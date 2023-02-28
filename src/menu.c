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
// Structure pour représenter un bouton

// Initialisation de la fenêtre et de la surface de l'écran


// Initialisation des boutons


// Initialisation de l'image de fond


int menu(SDL_Renderer *renderer,SDL_Window *window) {
  SDL_RenderClear(renderer);
  SDL_Surface *screenSurface = NULL; 
  SDL_Surface *background = NULL;
  SDL_Surface *background2 = NULL;
  Button button1, button2,button3,button4;


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("../music/musique.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    // ajout du texte TTF 
    TTF_Init();

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("../font/necrosans.ttf", 65);


  // Obtention de la surface de l'écran
  screenSurface = SDL_GetWindowSurface(window);
  
  // Chargement de l'image de fond
  background = IMG_Load("../img/background_comp.jpg");
  background2 = IMG_Load("../img/background_comp.jpg");
  if (background == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "background.bmp", SDL_GetError());
    return 1;
  }
  
  
   // Initialisation des boutons
  button1.x = 50;
  button1.y = 100;
  button1.w = 100*3;
  button1.h = 50*3;
  button1.surface = TTF_RenderText_Blended(police, "Comp1", couleurNoire);
  
  button2.x = button1.x + 300; 
  button2.y = button1.y;
  button2.w = 100*3;
  button2.h = 50*3;
  button2.surface = TTF_RenderText_Blended(police, "Comp2", couleurNoire);

  button3.x = button2.x + 300; 
  button3.y = button2.y;
  button3.w = 100*3;
  button3.h = 50*3;
  button3.surface = TTF_RenderText_Blended(police, "Comp3", couleurNoire);
  
  button4.x = button3.x + 300; 
  button4.y = button2.y;
  button4.w = 100*3;
  button4.h = 50*3;
  button4.surface = TTF_RenderText_Blended(police, "Comp4", couleurNoire);


  // Boucle principale du menu
  int running = 1; 
  SDL_Event e; 
  while (running) {
    // Traitement des événements
    while (SDL_PollEvent(&e) != 0) {
      // Si l'utilisateur a cliqué sur la croix pour fermer la fenêtre, on quitte la boucle principale
      if (e.type == SDL_QUIT || (e.key.keysym.sym == SDLK_ESCAPE)) {
        Mix_HaltMusic();
        running = 0;
      }
    // Si l'utilisateur a cliqué sur le bouton 1
  if (e.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= button1.x && x <= button1.x + button1.w && y >= button1.y && y <= button1.y + button1.h) {
        Mix_HaltMusic();
        SDL_FreeSurface(background);
        SDL_FreeSurface(button1.surface);
        SDL_FreeSurface(button2.surface);
        return 0;
    }
  }
  
  // Si l'utilisateur a cliqué sur le bouton 2
  if (e.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= button2.x && x <= button2.x + button2.w && y >= button2.y && y <= button2.y + button2.h) { 
        Mix_HaltMusic();
        SDL_FreeSurface(background);
        SDL_FreeSurface(button1.surface);
        SDL_FreeSurface(button2.surface);
      return 1;
    }
  }
}
SDL_Rect backgroundRect;
backgroundRect.x=1024;
backgroundRect.y=0;
SDL_BlitSurface(background2,NULL,screenSurface,&backgroundRect);
SDL_BlitSurface(background, NULL, screenSurface, NULL);

// Collage des boutons sur la surface de l'écran
SDL_Rect buttonRect1 = { button1.x, button1.y, button1.w, button1.h };
SDL_BlitSurface(button1.surface, NULL, screenSurface, &buttonRect1);

SDL_Rect buttonRect2 = { button2.x, button2.y, button2.w, button2.h };
SDL_BlitSurface(button2.surface, NULL, screenSurface, &buttonRect2);

SDL_Rect buttonRect3 = { button3.x, button3.y, button3.w, button3.h };
SDL_BlitSurface(button3.surface, NULL, screenSurface, &buttonRect3);

SDL_Rect buttonRect4 = { button4.x, button4.y, button4.w, button4.h };
SDL_BlitSurface(button4.surface, NULL, screenSurface, &buttonRect4);

// Mise à jour de la fenêtre
SDL_UpdateWindowSurface(window);
}

}