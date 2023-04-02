#ifndef __ITOA__
#define __ITOA__

#include <stdio.h>
#include <stdlib.h>

void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* itoa(int value, char* buffer, int base);

#endif