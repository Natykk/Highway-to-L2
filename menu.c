#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "map_jeu.c"
#include <SDL2/SDL_mixer.h>
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
// Structure pour représenter un bouton
typedef struct {
  int x, y;
  int w, h;
  SDL_Surface* surface;
} Button;

// Initialisation de la fenêtre et de la surface de l'écran
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

// Initialisation des boutons
Button button1;
Button button2;

// Initialisation de l'image de fond
SDL_Surface* background = NULL;

void exit_all(){
    SDL_FreeSurface(background);
    SDL_FreeSurface(button1.surface);
    SDL_FreeSurface(button2.surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
  // Initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erreur SDL Init %s\n", SDL_GetError());
    return 1;
  }
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    // ajout du texte TTF 
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("necrosans.ttf", 65);
    
    
    
    



  // Création de la fenêtre
  window = SDL_CreateWindow("Menu Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Création de l'affichage a échoué SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  
  // Obtention de la surface de l'écran
  screenSurface = SDL_GetWindowSurface(window);
  
  // Chargement de l'image de fond
  background = IMG_Load("background.jpg");
  if (background == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "background.bmp", SDL_GetError());
    return 1;
  }
  
  // Initialisation des boutons
  button1.x = WINDOW_WIDTH  / 2 - (WINDOW_WIDTH  / 5);
  button1.y = WINDOW_HEIGHT / 2;
  button1.w = 100*3;
  button1.h = 50*3;
  button1.surface = TTF_RenderText_Blended(police, "Jouer", couleurNoire);
  
  button2.x = button1.x + button1.w + 100; 
  button2.y = WINDOW_HEIGHT / 2 ;
  button2.w = 100*3;
  button2.h = 50*3;
  button2.surface = TTF_RenderText_Blended(police, "Quitter", couleurNoire);

  // Boucle principale du menu
  bool running = true; 
  SDL_Event e; 
  while (running) {
    // Traitement des événements
    while (SDL_PollEvent(&e) != 0) {
      // Si l'utilisateur a cliqué sur la croix pour fermer la fenêtre, on quitte la boucle principale
      if (e.type == SDL_QUIT || (e.key.keysym.sym == SDLK_ESCAPE)) {
        running = false;
      }
    // Si l'utilisateur a cliqué sur le bouton 1
  if (e.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= button1.x && x <= button1.x + button1.w && y >= button1.y && y <= button1.y + button1.h) {
        exit_all();
        jeu();
    }
  }
  
  // Si l'utilisateur a cliqué sur le bouton 2
  if (e.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= button2.x && x <= button2.x + button2.w && y >= button2.y && y <= button2.y + button2.h) { 
      exit_all();
    }
  }
}

// Collage de l'image de fond sur la surface de l'écran
SDL_BlitSurface(background, NULL, screenSurface, NULL);

// Collage des boutons sur la surface de l'écran
SDL_Rect buttonRect1 = { button1.x, button1.y, button1.w, button1.h };
SDL_BlitSurface(button1.surface, NULL, screenSurface, &buttonRect1);

SDL_Rect buttonRect2 = { button2.x, button2.y, button2.w, button2.h };
SDL_BlitSurface(button2.surface, NULL, screenSurface, &buttonRect2);

// Mise à jour de la fenêtre
SDL_UpdateWindowSurface(window);
}

// Nettoyage
exit_all();

return 0;
}