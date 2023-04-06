#include <stdio.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
// Structure pour représenter un bouton
/**
 * \file menu.c
 * \brief Fichier contenant les fonctions pour le menu
 * 
*/
#include "../head/name.h"
#include "../head/inventaire.h"
#include "../head/sauvegarde.h"
/**
 * \fn int fempty(char * fname)
 * @brief Vérifie si un fichier est vide
 * @param fname le nom du fichier
 * @return retourne 1 si le fichier est vide, 0 sinon
*/
int fempty(char * fname){
  FILE * lect = fopen(fname, "r");
  int empty = 1;
  if(lect){
    fgetc(lect);
    if(!feof(lect)){
      empty = 0;
    }
    fclose(lect);
  }
  return empty;
}
/**
 * \fn int fileExists(char * fname)
 * @brief Vérifie si un fichier existe
 * @param fname le nom du fichier
 * @return retourne 1 si le fichier existe, 0 sinon
*/
int fileExists(char * fname){
  if(!access(fname, F_OK)){
    return 1;
  }
  else{
    return 0;
  }
}
/**
 * \fn int menu_interact(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage)
 * @brief Affiche le menu et gère les interactions avec celui-ci
 * @param window la fenêtre
 * @param renderer le renderer
 * @param personnage le personnage
 * @return retourne 1 si le joueur a choisi de quitter, 0 sinon
*/
int menu_interact(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage){
    SDL_Surface *image = IMG_Load("../img/background/background_name.png");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Surface * img_logo = IMG_Load("../img/logo.png");
    SDL_Texture * texture_img = SDL_CreateTextureFromSurface(renderer, img_logo);
    SDL_Rect img_rect = {WINDOW_WIDTH/15, WINDOW_HEIGHT/3, WINDOW_WIDTH * 7 / 8, WINDOW_WIDTH * 2 / 8};
    SDL_FreeSurface(img_logo);
    img_logo = NULL;

    // Initialisation des boutons
    Button nouv_partie;
    Button continuer;
    Button quitter;

    nouv_partie.x = WINDOW_WIDTH * 1 / 15 ;
    nouv_partie.y = WINDOW_HEIGHT * 6 / 10;
    nouv_partie.w = 200;
    nouv_partie.h = 75;
    nouv_partie.surface = IMG_Load("../img/button/newgame.png");
    SDL_Texture *texture_nouv_partie = SDL_CreateTextureFromSurface(renderer, nouv_partie.surface);
    SDL_Rect buttonNouv_partie = { nouv_partie.x, nouv_partie.y, nouv_partie.w, nouv_partie.h };
    
    continuer.x = nouv_partie.x + nouv_partie.w + 10; 
    continuer.y = WINDOW_HEIGHT * 6 / 10 ;
    continuer.w = 200;
    continuer.h = 75;
    
    if(!fempty("../sauv/sauvegarde.txt") && fileExists("../sauv/sauvegarde.txt")){
      continuer.surface = IMG_Load("../img/button/continue.png");
    }
    else{
      continuer.surface = IMG_Load("../img/button/continue_dark.png");
    }
    SDL_Texture *texture_continuer = SDL_CreateTextureFromSurface(renderer, continuer.surface);
    SDL_Rect buttonContinuer = { continuer.x, continuer.y, continuer.w, continuer.h };
    
    quitter.x = continuer.x + continuer.w + 10; 
    quitter.y = WINDOW_HEIGHT * 6 / 10 + 5;
    quitter.w = 200;
    quitter.h = 65;
    quitter.surface = IMG_Load("../img/button/quit.png");
    SDL_Texture *texture_quitter = SDL_CreateTextureFromSurface(renderer, quitter.surface);
    SDL_Rect buttonQuitter = { quitter.x, quitter.y, quitter.w, quitter.h };

    char * player_name = malloc(sizeof(char)*TEXT_SIZE);
    player_name = NULL;
    
    int x, y;
    int run = 1;
    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_KEYDOWN:
                  if(event.key.keysym.sym == SDLK_ESCAPE){
                    run = 0;
                    break;
                  }
                case SDL_MOUSEBUTTONUP:
                   SDL_GetMouseState(&x, &y);
                    if (x >= nouv_partie.x && x <= nouv_partie.x + nouv_partie.w && y >= nouv_partie.y && y <= nouv_partie.y + nouv_partie.h){
                      printf("Nouv_partie\n");
                      SDL_DestroyTexture(texture_continuer);
                      SDL_DestroyTexture(texture_quitter);
                      SDL_DestroyTexture(texture_nouv_partie);
                      SDL_DestroyTexture(texture_img);
                      SDL_DestroyTexture(texture_background);
                      personnage->nom = name(window, renderer, personnage);
                      run = 0;
                    } 
                    else if((x >= continuer.x && x <= continuer.x + continuer.w && y >= continuer.y && y <= continuer.y + continuer.h) && (!fempty("../sauv/sauvegarde.txt") && fileExists("../sauv/sauvegarde.txt"))){
                      /*
                      SDL_DestroyTexture(texture_continuer);
                      SDL_DestroyTexture(texture_quitter);
                      SDL_DestroyTexture(texture_nouv_partie);
                      SDL_DestroyTexture(texture_img);
                      SDL_DestroyTexture(texture_background);
                      */
                      chargement(&personnage);
                      run=0;
                    }
                    else if(x >= quitter.x && x <= quitter.x + quitter.w && y >= quitter.y && y <= quitter.y + quitter.h){
                      printf("Quitter\n");
                      run=0;
                    }
                    break;
                default: break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture_background, NULL, NULL);
        SDL_RenderCopy(renderer, texture_nouv_partie, NULL, &buttonNouv_partie);
        SDL_RenderCopy(renderer, texture_continuer, NULL, &buttonContinuer);
        SDL_RenderCopy(renderer, texture_quitter, NULL, &buttonQuitter);
        SDL_RenderCopy(renderer, texture_img, NULL, &img_rect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture_continuer);
    SDL_DestroyTexture(texture_quitter);
    SDL_DestroyTexture(texture_nouv_partie);
    SDL_DestroyTexture(texture_img);
    SDL_DestroyTexture(texture_background);
    return 1;
}
/**
 * \fn int menu(SDL_Window* window ,SDL_Renderer* renderer ,entite_t * personnage)
 * @brief Fonction qui initialise le menu
 * @param window La fenêtre
 * @param renderer Le renderer
 * @param personnage Le personnage
 * @return 0
 * 
*/
int menu(SDL_Window* window ,SDL_Renderer* renderer ,entite_t * personnage){
  //SDL_Init(SDL_INIT_EVERYTHING);

  /* Initialisation de la piste audio de fond */
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
  Mix_Music * music = Mix_LoadMUS("../sound/name_choose.mp3");
  Mix_PlayMusic(music, -1);

  
  /* Interactions du menu */
  menu_interact(window, renderer, personnage);

  /* Fermeture de la piste audio de fond */
  printf("Fermeture audio...");
  Mix_HaltMusic();
  Mix_CloseAudio();
  Mix_Quit();
  printf("...OK?\n");

  return 0;
}
