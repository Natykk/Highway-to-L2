#ifndef __MENU_CPT__
#define __MENU_CPT__

#include <SDL2/SDL.h>

#include "arbre.h"

#define SDL_MAIN_HANDLED
#define TILE_SIZE 32 
#define WINDOW_WIDTH (35*TILE_SIZE)
#define WINDOW_HEIGHT (25*TILE_SIZE)
#define TAILLE_CASE 50
#define TAILLE_CHAINE_COMPETENCE 80
#define TAILLE_CHAINE_NOM 80
#define TAILLE_CASE_ITEM_RES 280

/**
 * \fn construire_chaine_objets(char *result, int nb_obj, int nb_obj_requis, char *nom_obj)
 * \brief Fonction qui construit la chaine de caractère qui sera affichée dans le menu de l'inventaire
 * \param result Chaine de caractère qui sera affichée dans le menu de l'inventaire
 * \param nb_obj Nombre d'objets de ce type que le joueur possède
 * \param nb_obj_requis Nombre d'objets de ce type que le joueur doit posséder pour débloquer la compétence associée
 * \param nom_obj Nom de l'objet que le joueur doit poseéder
 * 
*/
void construire_chaine_objets(char *result, int nb_obj, int nb_obj_requis, char *nom_obj);
/**
 * \fn construire_chaine_buff(char *result, int i, int buff)
 * \brief Fonction qui construit la chaine de caractère qui sera affichée dans le menu de l'inventaire
 * \param result Chaine de caractère qui sera affichée dans le menu de l'inventaire
 * \param i Indice de la compétence
 * \param buff Valeur du buff
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
 * 
*/
int construire_chaine_buff(char *result, int i, int buff);
/**
 * \fn int in_rect(int x, int y, struct SDL_Rect *r)
 * \brief Fonction qui vérifie si un point est dans un rectangle
 * \param x Abscisse du point
 * \param y Ordonnée du point
 * \param r Pointeur sur le rectangle
 * \return 1 si le point est dans le rectangle, 0 sinon
 * 
*/
int in_rect(int x, int y, struct SDL_Rect *r);
/**
 * \fn void afficher_comp(char *path, SDL_Renderer *renderer, SDL_Rect rect)
 * \brief Fonction qui affiche une compétence
 * \param path Chemin vers l'image de la compétence
 * \param renderer Pointeur sur le renderer
 * \param rect Rectangle dans lequel afficher la compétence
 * 
*/
void afficher_comp(char *path, SDL_Renderer *renderer, SDL_Rect rect);
/**
 * 
 * \fn void afficher_background(SDL_Window *window, SDL_Renderer *renderer)
 * \brief Fonction qui affiche le fond d'écran
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * 
*/
void afficher_background(SDL_Window *window, SDL_Renderer *renderer);
/**
 * 
 * \fn afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* assassin,TTF_Font* font)
 * \brief Fonction qui affiche l'arbre assassin
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param entite Pointeur sur l'entité
 * \param assassin Pointeur sur l'arbre assassin
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
*/
int afficher_arbre_assassin(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* assassin,TTF_Font* font);
/**
 * 
 * \fn afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* guerrier,TTF_Font* font)
 * \brief Fonction qui affiche l'arbre guerrier
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param entite Pointeur sur l'entité
 * \param guerrier Pointeur sur l'arbre guerrier
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
*/
int afficher_arbre_guerrier(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* guerrier,TTF_Font* font);
/**
 * 
 * \fn afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* mage,TTF_Font* font)
 * \brief Fonction qui affiche l'arbre mage
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param entite Pointeur sur l'entité
 * \param mage Pointeur sur l'arbre mage
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
*/
int afficher_arbre_mage(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* mage,TTF_Font* font);
/**
 * \fn afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* archer,TTF_Font* font)
 * \brief Fonction qui affiche l'arbre archer
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param entite Pointeur sur l'entité
 * \param archer Pointeur sur l'arbre archer
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
*/
int afficher_arbre_archer(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite, t_arbre* archer,TTF_Font* font);
/**
 * \fn afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite,TTF_Font* font)
 * \brief Fonction qui affiche le menu des compétences
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param entite Pointeur sur l'entité
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
*/
void afficher_menu(SDL_Window *window, SDL_Renderer *renderer, entite_t *entite,TTF_Font* font);
/**
 * \fn afficher_competence_SDL(SDL_Window *window,SDL_Renderer *renderer,char *path_comp,entite_t *entite,t_competence *competence,t_arbre *arbre,TTF_Font* font)
 * \brief Fonction qui affiche une compétence
 * \param window Pointeur sur la fenêtre
 * \param renderer Pointeur sur le renderer
 * \param path_comp Chemin vers l'image de la compétence
 * \param entite Pointeur sur l'entité
 * \param competence Pointeur sur la compétence
 * \param arbre Pointeur sur l'arbre
 * \param font Pointeur sur la police
 * \return 0 si la fonction s'est bien déroulée, -1 sinon
 * 
*/
int afficher_competence_SDL(SDL_Window *window,SDL_Renderer *renderer,char *path_comp,entite_t *entite,t_competence *competence,t_arbre *arbre,TTF_Font* font);


#endif
