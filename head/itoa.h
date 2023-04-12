#ifndef __ITOA__
#define __ITOA__

#include <stdio.h>
#include <stdlib.h>
/**
 * \file itoa.h
 * \brief Fichier contenant les prototypes de fonctions pour la gestion des conversions de type
*/
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* itoa(int value, char* buffer, int base);

#endif