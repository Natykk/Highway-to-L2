#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef __NAME__
#define __NAME__

#include "entite.h"
#include "menu_cpt.h"

#define TEXT_SIZE 33
/**
 * \struct Button
 * \brief Structure contenant les informations d'un bouton
 * \details Cette structure est utilisée pour la création des boutons
 * 
*/
typedef struct {
  int x, y; //<! Position du bouton
  int w, h; //<! Taille du bouton
  SDL_Surface* surface; //<! Surface du bouton
} Button;
/**
 * \fn char * name(SDL_Window * win, SDL_Renderer * screen, entite_t * personnage)
 * \brief Fonction qui affiche le nom du joueur
 * \param win Pointeur sur la fenêtre
 * \param screen Pointeur sur le renderer
 * \param personnage Pointeur sur le personnage
 * \return Le nom du joueur
 * 
*/
char * name(SDL_Window * win, SDL_Renderer * screen, entite_t * personnage);
/**
 * \fn int menu_interact(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage)
 * \brief Fonction qui gère les interactions avec le menu
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param personnage Pointeur sur le personnage
 * \return 0 si le joueur a quitté le jeu, 1 sinon
 * 
*/
int menu_interact(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage);
/**
 * \fn int menu(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage)
 * \brief Fonction qui affiche le menu
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param personnage Pointeur sur le personnage
 * \return 0 si le joueur a quitté le jeu, 1 sinon
*/
int menu(SDL_Window * window, SDL_Renderer * renderer,entite_t * personnage);
/**
 * \fn void affichage(SDL_Renderer *renderer, SDL_Window *window,entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing,TTF_Font *font,int total_width,int x_start,SDL_Texture* tab_tex[17])
 * \brief Fonction qui affiche l'inventaire
 * \param renderer Pointeur sur le renderer
 * \param window Pointeur sur la fenêtre
 * \param pers Pointeur sur le personnage
 * \param num_rectangles Nombre d'items (rectangles) à afficher
 * \param rect_width Largeur des rectangles
 * \param rect_height Hauteur des rectangles
 * \param rect_spacing Espace entre les rectangles
 * \param font Pointeur sur la police d'écriture
 * \param total_width Largeur totale de la fenêtre
 * \param x_start Position x de départ
 * \param tab_tex Tableau de textures
 * 
*/
void affichage( SDL_Renderer *renderer, SDL_Window *window,entite_t *pers, int num_rectangles, int rect_width, int rect_height, int rect_spacing,TTF_Font *font,int total_width,int x_start,SDL_Texture* tab_tex[17]);
/**
 * \fn int inv(SDL_Renderer* renderer,SDL_Window* window,entite_t* pers)
 * \brief Fonction qui gère l'inventaire
 * \param renderer Pointeur sur le renderer
 * \param window Pointeur sur la fenêtre
 * \param pers Pointeur sur le personnage
 * \return 0 si le joueur a quitté le jeu, 1 sinon
 */
int inv(SDL_Renderer* renderer,SDL_Window* window,entite_t* pers);
/**
 * \fn int gameover(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage)
 * \brief Fonction qui gère l'écran de fin de partie
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param personnage Pointeur sur le personnage
 * \return 0 si le joueur a quitté le jeu, 1 sinon
*/
int gameover(SDL_Window * window, SDL_Renderer * renderer, entite_t * personnage);

#endif