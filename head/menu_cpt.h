#ifndef __MENU_CPT__
#define __MENU_CPT__

#include <SDL2/SDL.h>

#include "arbre.h"

#define SDL_MAIN_HANDLED
#define TILE_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 25
#define WINDOW_WIDTH (35*TILE_SIZE)
#define WINDOW_HEIGHT (25*TILE_SIZE)
#define TAILLE_CASE 50
#define TAILLE_CHAINE_COMPETENCE 80
#define TAILLE_CHAINE_NOM 80
#define TAILLE_CASE_ITEM_RES 280

void construire_chaine_objets(char *result, int nb_obj, int nb_obj_requis, char *nom_obj);
int construire_chaine_buff(char *result, int i, int buff);
int in_rect(int x, int y, struct SDL_Rect *r);
void afficher_comp(char *path, SDL_Renderer *renderer, SDL_Rect rect);
void afficher_background(SDL_Window *window, SDL_Renderer *renderer);
int afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* assassin,TTF_Font* font);
int afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* guerrier,TTF_Font* font);
int afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* mage,TTF_Font* font);
int afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* archer,TTF_Font* font);
void afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite,TTF_Font* font);
int afficher_competence_SDL(SDL_Window *window,SDL_Renderer *renderer,char *path_comp,entite_t *entite,t_competence *competence,t_arbre *arbre,TTF_Font* font);

#endif
