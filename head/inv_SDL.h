#ifndef __INV_SDL__
#define __INV_SDL__
void affichage( SDL_Renderer *renderer, SDL_Window *window,entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing,TTF_Font *font,int total_width,int x_start,SDL_Texture* tab_tex[17]);
int inv(SDL_Renderer* renderer,SDL_Window* window,entite_t* pers);
#endif