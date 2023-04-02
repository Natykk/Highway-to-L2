#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "../head/name.h"

#define TEXT_SIZE 36

char * name(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
    Mix_Music * music = Mix_LoadMUS("../sound/name_choose.mp3");
    Mix_PlayMusic(music, 10);

    SDL_Window * win = SDL_CreateWindow("Highway to L2", 350, 150, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *screen =  SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);


    SDL_Surface *image = IMG_Load("../IMG/background_name.png");
    SDL_Texture *texture_background = SDL_CreateTextureFromSurface(screen, image);
    SDL_FreeSurface(image);

    TTF_Font * font = TTF_OpenFont("../font/necrosans.ttf", 20);
    SDL_Color color = {255,255,255,255};

    SDL_Surface * img_logo = IMG_Load("../IMG/logo.png");
    SDL_Texture * texture_img = SDL_CreateTextureFromSurface(screen, img_logo);
    SDL_Rect img_rect = {WINDOW_WIDTH/15, WINDOW_HEIGHT/3, WINDOW_WIDTH * 7 / 8, WINDOW_WIDTH * 2 / 8};
    SDL_FreeSurface(img_logo);
    img_logo = NULL;

    SDL_Surface * temp1 = TTF_RenderText_Solid(font, "Votre nom : ", color);
    SDL_Texture * textImage1 = SDL_CreateTextureFromSurface(screen, temp1);
    SDL_Rect demandeNom = {WINDOW_WIDTH * 1 / 5, 20, 100, temp1->h};
    SDL_FreeSurface(temp1);
    temp1 = NULL;

    SDL_Surface * temp = TTF_RenderText_Solid(font, "Ecrire le pseudo de votre personnage", color);
    SDL_Texture * textImage = SDL_CreateTextureFromSurface(screen, temp);
    SDL_Rect pos = {demandeNom.x + demandeNom.w, 20, temp->w, temp->h};
    SDL_FreeSurface(temp);
    temp = NULL;

    SDL_StartTextInput();
    char * textInput = malloc(sizeof(char)*TEXT_SIZE);
    int textInputSize = 0;
    int run = 1;
    while(run){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_TEXTINPUT:
                    if(textInputSize < TEXT_SIZE-1){
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
                            pos.h = temp->h;
                            pos.w = temp->w;
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
                            pos.h = temp->h;
                            pos.w = temp->w;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                        else{
                            temp = TTF_RenderText_Solid(font, "Ecrire le pseudo de votre personnage", color);
                            textImage = SDL_CreateTextureFromSurface(screen, temp);
                            pos.h = temp->h;
                            pos.w = temp->w;
                            textInputSize = 0;
                            SDL_FreeSurface(temp);
                            temp = NULL;
                        }
                    }
                    else if(event.key.keysym.sym == SDLK_RETURN && textInputSize>0){
                        SDL_StopTextInput();
                        Mix_HaltMusic();
                        Mix_CloseAudio();
                        SDL_DestroyTexture(textImage1);
                        SDL_DestroyTexture(textImage);
                        SDL_DestroyWindow(win);
                        Mix_Quit();
                        TTF_Quit();
                        SDL_Quit();
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
        SDL_RenderCopy(screen, textImage, NULL, &pos);
        SDL_RenderCopy(screen, textImage1, NULL, &demandeNom);
        SDL_RenderCopy(screen, texture_img, NULL, &img_rect);
        SDL_RenderPresent(screen);
        
   
    }
    SDL_StopTextInput();
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_DestroyTexture(textImage1);
    SDL_DestroyTexture(textImage);
    SDL_DestroyTexture(texture_img);
    SDL_DestroyWindow(win);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return NULL;
}

int main()
{
    printf("%s\n", name());
    return 1;
}
