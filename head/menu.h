#include "../head/entite.h"

typedef struct {
  int x, y;
  int w, h;
  SDL_Surface* surface;
} Button;

/* Fonctions */

int menu(SDL_Renderer *renderer, SDL_Window *window);
int inv(SDL_Renderer *renderer, SDL_Window *window,entite_t *pers);

