#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "../head/name.h"
/**
 * \file name.c
 * \brief Fichier contenant les fonctions pour la gestion du nom du personnage
*/
/**
 * \fn char * name(SDL_Window * win, SDL_Renderer * screen, entite_t * personnage)
 * @brief Affiche le menu et gère les interactions textuelle avec celui-ci
 * @param win la fenêtre
 * @param screen le renderer
 * @param personnage le personnage
 * @return retourne le nom du personnage
 * @return retourne NULL si le joueur a choisi de quitter ou si une erreur est survenue sinon retourne le nom du personnage
*/
char * name(SDL_Window * win, SDL_Renderer * screen, entite_t * personnage){
    TTF_Init();

    //SDL_Window * win = SDL_CreateWindow("Highway to L2", 350, 150, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    //SDL_Renderer *screen =  SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Surface *image = IMG_Load("../img/background/background_name.png");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(screen, image);
    SDL_FreeSurface(image);
    

    TTF_Font * font = TTF_OpenFont("../font/necrosans.ttf", 25);
    SDL_Color color = {247,192,21};

    SDL_Surface * img_logo = IMG_Load("../img/background/logo.png");
    SDL_Texture * texture_img = SDL_CreateTextureFromSurface(screen, img_logo);
    SDL_Rect img_rect = {WINDOW_WIDTH/15, WINDOW_HEIGHT/3, WINDOW_WIDTH * 7 / 8, WINDOW_WIDTH * 2 / 8};
    SDL_FreeSurface(img_logo);
    img_logo = NULL;

    SDL_Surface * temp = TTF_RenderText_Solid(font, "Ecrire le pseudo de votre personnage", color);
    SDL_Texture * textImage = SDL_CreateTextureFromSurface(screen, temp);
    SDL_Rect saisieNom;
    saisieNom.w = temp->w;
    saisieNom.h = temp->h;
    saisieNom.x = WINDOW_WIDTH / 2 - saisieNom.w / 2;
    saisieNom.y = img_rect.y + img_rect.h * 9 / 10;
    SDL_FreeSurface(temp);
    temp = NULL;

    SDL_Surface * temp1 = TTF_RenderText_Solid(font, "Votre nom : ", color);
    SDL_Texture * textImage1 = SDL_CreateTextureFromSurface(screen, temp1);
    SDL_Rect demandeNom;
    demandeNom.w = 150;
    demandeNom.h = temp1->h;
    demandeNom.x = saisieNom.x - demandeNom.w;
    demandeNom.y = saisieNom.y;
    // = {WINDOW_WIDTH/15, img_rect.y + img_rect.h, 150, temp1->h};
    SDL_FreeSurface(temp1);
    temp1 = NULL;

    Button retour;
    retour.w = 200;
    retour.h = 50;
    retour.x = WINDOW_WIDTH / 2 - retour.w / 2 ;
    retour.y = WINDOW_HEIGHT - 45;
    retour.surface = IMG_Load("../img/button/back.png");
    SDL_Texture *texture_back = SDL_CreateTextureFromSurface(screen, retour.surface);
    SDL_Rect button_back = { retour.x, retour.y, retour.w, retour.h };

    SDL_StartTextInput();
    char * textInput = malloc(sizeof(char)*TEXT_SIZE);
    int textInputSize = 0;
    
    int run = 1;
    int x, y;
    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                   SDL_GetMouseState(&x, &y);
                    if (x >= retour.x && x <= retour.x + retour.w && y >= retour.y && y <= retour.y + retour.h){
                        run = 0;
                        printf("Menu\n");
                        SDL_StopTextInput();
                        SDL_DestroyTexture(textImage1);
                        SDL_DestroyTexture(textImage);
                        SDL_DestroyTexture(texture_background);
                        SDL_DestroyTexture(texture_img);
                        SDL_DestroyTexture(texture_back);
                        menu_interact(win, screen, personnage);
                    } 
                case SDL_TEXTINPUT:
                    if(textInputSize < TEXT_SIZE-1 && event.text.text[0] != ' '){
                        textInput[textInputSize] = event.text.text[0];
                        textInputSize++;
                        textInput[textInputSize] = '\0';
                        if(textImage){
                            SDL_DestroyTexture(textImage);
                            textImage = NULL;
                        }
                        temp = TTF_RenderText_Solid(font, textInput, color);
                        if(temp){
                            textImage = SDL_CreateTextureFromSurface(screen, temp);
                            saisieNom.h = temp->h;
                            saisieNom.w = temp->w;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_BACKSPACE && textInputSize>0){
                        textInputSize--;
                        textInput[textInputSize] = '\0';

                        temp = TTF_RenderText_Solid(font, textInput, color);
                        if(temp){
                            textImage = SDL_CreateTextureFromSurface(screen, temp);
                            saisieNom.h = temp->h;
                            saisieNom.w = temp->w;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                        else{
                            temp = TTF_RenderText_Solid(font, "Ecrire le pseudo de votre personnage", color);
                            textImage = SDL_CreateTextureFromSurface(screen, temp);
                            saisieNom.h = temp->h;
                            saisieNom.w = temp->w;
                            textInputSize = 0;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                    }
                    else if(event.key.keysym.sym == SDLK_RETURN && textInputSize>0 && strcmp(textInput,"")){
                        textInputSize++;
                        textInput[textInputSize] = '\0';
                        SDL_StopTextInput();
                        SDL_DestroyTexture(textImage1);
                        SDL_DestroyTexture(textImage);
                        SDL_DestroyTexture(texture_img);
                        SDL_DestroyTexture(texture_back);
                        SDL_DestroyTexture(texture_background);
                        run = 0;
                        return textInput;
                    }
                    else if(event.key.keysym.sym == SDLK_ESCAPE){
                        run = 0;
                        return NULL;
                    }
                    break;
                default: break;
            }
        }
        SDL_RenderClear(screen);
        SDL_RenderCopy(screen, texture_background, NULL, NULL);
        SDL_RenderCopy(screen, textImage, NULL, &saisieNom);
        SDL_RenderCopy(screen, textImage1, NULL, &demandeNom);
        SDL_RenderCopy(screen, texture_img, NULL, &img_rect);
        SDL_RenderCopy(screen, texture_back, NULL, &button_back);
        SDL_RenderPresent(screen);
    }
    SDL_StopTextInput();
    SDL_DestroyTexture(textImage1);
    SDL_DestroyTexture(textImage);
    SDL_DestroyTexture(texture_img);
    SDL_DestroyTexture(texture_back);
    SDL_DestroyTexture(texture_background);
    return NULL;
}
