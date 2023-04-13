#ifndef __ITOA__
#define __ITOA__

#include <stdio.h>
#include <stdlib.h>
/**
 * \file itoa.h
 * \brief Fichier contenant les prototypes de fonctions pour la gestion des conversions de type
*/
/**
 * \fn void swap(char *x, char *y)
 * \brief Fonction permettant de permuter deux variables
 *  \param x Pointeur sur la première variable
 * \param y Pointeur sur la deuxième variable
 * 
*/
void swap(char *x, char *y);

/**
 * \fn char* reverse(char *buffer, int i, int j)
 * \brief Fonction permettant de retourner une chaine de caractère
 *  \param buffer Pointeur sur la chaine de caractère
 * \param i Indice de début de la chaine
 * \param j Indice de fin de la chaine
 * 
*/
char* reverse(char *buffer, int i, int j);

/**
 * \fn char* itoa(int value, char* buffer, int base)
 * \brief Fonction permettant de convertir un entier en chaine de caractère
 * \param value Entier à convertir
 * \param buffer Pointeur sur la chaine de caractère
 * \param base Base de la conversion
 * \return Pointeur sur la chaine de caractère
 * 
*/
char* itoa(int value, char* buffer, int base);

#endif