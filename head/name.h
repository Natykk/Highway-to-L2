#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef __NAME__
#define __NAME__

#include "entite.h"
#include "menu_cpt.h"

#define TEXT_SIZE 33

typedef struct {
  int x, y;
  int w, h;
  SDL_Surface* surface;
} Button;

char * name(SDL_Window * win, SDL_Renderer * screen, entite_t * personnage);
int menu_interact(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage);
int menu(SDL_Window * window, SDL_Renderer * renderer,entite_t * personnage);

#endif