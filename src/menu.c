#include <stdio.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <openssl/sha.h>
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

    SDL_Surface * img_logo = IMG_Load("../img/background/logo.png");
    SDL_Texture * texture_img = SDL_CreateTextureFromSurface(renderer, img_logo);
    SDL_Rect img_rect = {WINDOW_WIDTH/15, WINDOW_HEIGHT/3, WINDOW_WIDTH * 7 / 8, WINDOW_WIDTH * 2 / 8};
    SDL_FreeSurface(img_logo);
    img_logo = NULL;

    FILE* f_hash = NULL;
    FILE* f_hash1 = NULL;
    FILE* f_hash2 = NULL;
    char hash_sauvegarder[(SHA256_DIGEST_LENGTH*2) + 1];
    f_hash1 = fopen("./sauv/sauvegarde.hash", "r");
    f_hash2 = fopen("../sauv/sauvegarde.hash", "r");
    if((f_hash1 && f_hash2) || (f_hash2 && !f_hash1)){
      f_hash = f_hash2;
      fclose(f_hash1);
    }
    else if(f_hash1 && !f_hash2){
      f_hash = f_hash1;
      fclose(f_hash2);
    }

    if (f_hash != NULL) {
        fscanf(f_hash, "%s", hash_sauvegarder);
        fclose(f_hash);
    }
    else {
        printf("Erreur ouverture fichier hash\n");

    }

    char sha256_after[(SHA256_DIGEST_LENGTH*2)+1];
    if (sha256_file("../sauv/sauvegarde_crypt.data", sha256_after) != 0 && sha256_file("./sauv/sauvegarde_crypt.data", sha256_after)) {
        printf("Erreur dans le calcul du hash du menu\n");
    }
    int hash_flag = 0;
    if (strcmp(sha256_after,hash_sauvegarder) == 0) {
        printf("hash match\n");
        hash_flag = 1;
    } else {
        printf("hash match pas\n");
        hash_flag = 0;
    }

    // Initialisation des boutons
    Button nouv_partie;
    Button continuer;
    Button quitter;

    continuer.w = 200;
    continuer.h = 75;
    continuer.x = WINDOW_WIDTH / 2 - continuer.w/2; 
    continuer.y = img_rect.y + img_rect.h * 4 / 5 + 5;
    printf("fempty et fileExist ./sauv/sauvgarde_crypt.data %d\n",(!fempty("./sauv/sauvegarde_crypt.data") && fileExists("./sauv/sauvegarde_crypt.data")));
    printf("fempty et fileExist ../sauv/sauvgarde_crypt.data %d\n",(!fempty("../sauv/sauvegarde_crypt.data") && fileExists("../sauv/sauvegarde_crypt.data")));
    printf("hash_flag %d\n",hash_flag);
    if(((!fempty("./sauv/sauvegarde_crypt.data") && fileExists("./sauv/sauvegarde_crypt.data")) || (!fempty("../sauv/sauvegarde_crypt.data") && fileExists("../sauv/sauvegarde_crypt.data"))) && hash_flag == 1 ){
      continuer.surface = IMG_Load("../img/button/continue.png");
    }
    else{
      continuer.surface = IMG_Load("../img/button/continue_dark.png");
    }
    SDL_Texture *texture_continuer = SDL_CreateTextureFromSurface(renderer, continuer.surface);
    SDL_Rect buttonContinuer = { continuer.x, continuer.y, continuer.w, continuer.h };

    nouv_partie.w = 200;
    nouv_partie.h = 75;
    nouv_partie.x = continuer.x - nouv_partie.w;
    nouv_partie.y = continuer.y;
    nouv_partie.surface = IMG_Load("../img/button/newgame.png");
    SDL_Texture *texture_nouv_partie = SDL_CreateTextureFromSurface(renderer, nouv_partie.surface);
    SDL_Rect buttonNouv_partie = { nouv_partie.x, nouv_partie.y, nouv_partie.w, nouv_partie.h };
    
    quitter.w = 200;
    quitter.h = 65;
    quitter.x = continuer.x + continuer.w; 
    quitter.y = continuer.y + 5;
    quitter.surface = IMG_Load("../img/button/quit.png");
    SDL_Texture *texture_quitter = SDL_CreateTextureFromSurface(renderer, quitter.surface);
    SDL_Rect buttonQuitter = { quitter.x, quitter.y, quitter.w, quitter.h };

    char * player_name = malloc(sizeof(char)*TEXT_SIZE);
    player_name = NULL;
    
    int debut_jeu = 0;
    int x, y;
    int run = 1;
    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = 0;
                    debut_jeu = 0;
                    break;
                case SDL_KEYDOWN:
                  if(event.key.keysym.sym == SDLK_ESCAPE){
                    run = 0;
                    debut_jeu = 0;
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
                      debut_jeu = 1;
                    } 
                    else if((x >= continuer.x && x <= continuer.x + continuer.w && y >= continuer.y && y <= continuer.y + continuer.h) && (!fempty("../sauv/sauvegarde_crypt.data") && fileExists("../sauv/sauvegarde_crypt.data")) ){
                      /*
                      SDL_DestroyTexture(texture_continuer);
                      SDL_DestroyTexture(texture_quitter);
                      SDL_DestroyTexture(texture_nouv_partie);
                      SDL_DestroyTexture(texture_img);
                      SDL_DestroyTexture(texture_background);
                      */
                      chargement(&personnage,"0123456789abcdef");
                      run=0;
                      debut_jeu = 1;
                    }
                    else if(x >= quitter.x && x <= quitter.x + quitter.w && y >= quitter.y && y <= quitter.y + quitter.h){
                      printf("Quitter\n");
                      run=0;
                      debut_jeu = 0;
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
    return debut_jeu;
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
int menu(SDL_Window* window ,SDL_Renderer* renderer, entite_t * personnage){
  /* Initialisation de la piste audio de fond */
  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
  Mix_Music * music = Mix_LoadMUS("../music/menu.mp3");
  Mix_PlayMusic(music, -1);

  
  /* Interactions du menu */
  int retour_menu = menu_interact(window, renderer, personnage);

  /* Fermeture de la piste audio de fond */
  Mix_HaltMusic();
  Mix_CloseAudio();
  Mix_Quit();

  return retour_menu;
}


int gameover(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage){
  SDL_RenderClear(renderer);
  Button menu_button;
  Button quitter;

  menu_button.x = WINDOW_WIDTH / 2 - 200 ;
  menu_button.y = WINDOW_HEIGHT * 6 / 10;
  menu_button.w = 200;
  menu_button.h = 75;
  menu_button.surface = IMG_Load("../img/button/menu.png");
  SDL_Texture *texture_menu = SDL_CreateTextureFromSurface(renderer, menu_button.surface);
  SDL_Rect menu_partie = { menu_button.x, menu_button.y, menu_button.w, menu_button.h };

  quitter.x = WINDOW_WIDTH / 2; 
  quitter.y = menu_button.y + 5;
  quitter.w = 200;
  quitter.h = 65;
  quitter.surface = IMG_Load("../img/button/quit.png");
  SDL_Texture *texture_quitter = SDL_CreateTextureFromSurface(renderer, quitter.surface);
  SDL_Rect buttonQuitter = { quitter.x, quitter.y, quitter.w, quitter.h };

  SDL_Surface * gameover = IMG_Load("../img/background/gameover.png");
  SDL_Texture * texture_gameover = SDL_CreateTextureFromSurface(renderer, gameover);
  SDL_Rect img_rect = {WINDOW_WIDTH/15, WINDOW_HEIGHT / 5, WINDOW_WIDTH * 7 / 8, WINDOW_HEIGHT * 2 / 3};
  SDL_FreeSurface(gameover);
  gameover = NULL;

  Mix_Init(MIX_INIT_MP3);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
  Mix_Music * music = Mix_LoadMUS("../sound/mort.mp3");
  Mix_PlayMusic(music, 1);

  int x, y;
  int run = 1;
  while(run){
      SDL_Event event;
      while(SDL_PollEvent(&event)){
          switch(event.type){
              case SDL_QUIT:
                  run = 0;
                  break;
              case SDL_MOUSEBUTTONUP:
                  SDL_GetMouseState(&x, &y);
                  if (x >= menu_button.x && x <= menu_button.x + menu_button.w && y >= menu_button.y && y <= menu_button.y + menu_button.h){
                    SDL_DestroyTexture(texture_menu);
                    SDL_DestroyTexture(texture_gameover);
                    run = 0;
                    return 1;
                  } 
                  else if (x >= quitter.x && x <= quitter.x + quitter.w && y >= quitter.y && y <= quitter.y + quitter.h){
                    SDL_DestroyTexture(texture_menu);
                    SDL_DestroyTexture(texture_gameover);
                    run = 0;
                    return 0;
                  } 
              default: break;
          }
      }
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture_quitter, NULL, &buttonQuitter);
      SDL_RenderCopy(renderer, texture_menu, NULL, &menu_partie);
      SDL_RenderCopy(renderer, texture_gameover, NULL, &img_rect);
      SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(texture_menu);
  SDL_DestroyTexture(texture_gameover);
  SDL_DestroyTexture(texture_quitter);

  Mix_HaltMusic();
  Mix_CloseAudio();
  Mix_Quit();
  return 0;
}
/*
int main(){
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window = SDL_CreateWindow("Arbre de C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  entite_t * personnage = creer_personnage(personnage);
  menu(window, renderer, personnage);
  if(gameover(window, renderer, personnage)){
    menu(window, renderer, personnage);
  }
  SDL_Quit();
}
*/