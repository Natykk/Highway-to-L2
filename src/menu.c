#include <stdio.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 600
// Structure pour représenter un bouton

#include "../head/name.h"

typedef struct {
  int x, y;
  int w, h;
  SDL_Surface* surface;
} Button;

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

int fileExists(char * fname){
  if(!access(fname, F_OK)){
    return 1;
  }
  else{
    return 0;
  }
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
    Mix_Music * music = Mix_LoadMUS("../sound/name_choose.mp3");
    Mix_PlayMusic(music, -1);

    SDL_Window * window = SDL_CreateWindow("Highway to L2", 350, 150, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer * renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface *image = IMG_Load("../IMG/background_name.png");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Surface * img_logo = IMG_Load("../IMG/logo.png");
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
    nouv_partie.surface = IMG_Load("../IMG/newgame.png");
    SDL_Texture *texture_nouv_partie = SDL_CreateTextureFromSurface(renderer, nouv_partie.surface);
    SDL_Rect buttonNouv_partie = { nouv_partie.x, nouv_partie.y, nouv_partie.w, nouv_partie.h };
    
    continuer.x = nouv_partie.x + nouv_partie.w + 10; 
    continuer.y = WINDOW_HEIGHT * 6 / 10 ;
    continuer.w = 200;
    continuer.h = 75;
    
    if(!fempty("../sauv/sauvegarde.txt") && fileExists("../sauv/sauvegarde.txt")){
      continuer.surface = IMG_Load("../IMG/continue.png");
    }
    else{
      continuer.surface = IMG_Load("../IMG/continue_dark.png");
    }
    SDL_Texture *texture_continuer = SDL_CreateTextureFromSurface(renderer, continuer.surface);
    SDL_Rect buttonContinuer = { continuer.x, continuer.y, continuer.w, continuer.h };

    quitter.x = continuer.x + continuer.w + 10; 
    quitter.y = WINDOW_HEIGHT * 6 / 10 + 5;
    quitter.w = 200;
    quitter.h = 65;
    quitter.surface = IMG_Load("../IMG/quit.png");
    SDL_Texture *texture_quitter = SDL_CreateTextureFromSurface(renderer, quitter.surface);
    SDL_Rect buttonQuitter = { quitter.x, quitter.y, quitter.w, quitter.h };
    
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
                      run=0;
                      printf("nom : %s\n", name());
                      Mix_HaltMusic();
                      Mix_CloseAudio();
                      SDL_DestroyTexture(texture_img);
                      SDL_DestroyWindow(window);
                      Mix_Quit();
                      TTF_Quit();
                      SDL_Quit();
                    } 
                    else if((x >= continuer.x && x <= continuer.x + continuer.w && y >= continuer.y && y <= continuer.y + continuer.h) && (!fempty("../sauv/sauvegarde.txt") && fileExists("../sauv/sauvegarde.txt"))){
                      printf("Continuer\n");
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

    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_DestroyTexture(texture_img);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
