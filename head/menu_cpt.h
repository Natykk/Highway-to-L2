#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/arbre.h"
#include "../head/entite.h"
#include "../head/itoa.h"

#define SDL_MAIN_HANDLED
#define TILE_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 25
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TAILLE_CASE 50
#define TAILLE_CHAINE_COMPETENCE 80
#define TAILLE_CHAINE_NOM 80
#define TAILLE_CASE_ITEM_RES 280

void construire_chaine(char *result, int nb_obj, int nb_obj_requis, char *nom_obj);
int in_rect(int x, int y, struct SDL_Rect *r);
void afficher_comp(char *path, SDL_Renderer *renderer, SDL_Rect rect);
void afficher_background(SDL_Window *window, SDL_Renderer *renderer);
void afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite);
void afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite);
void afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite);
void afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite);
void afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite);
int afficher_competence_SDL(SDL_Window *window, SDL_Renderer *renderer, char *path_comp, entite_t *entite, t_competence competence);
