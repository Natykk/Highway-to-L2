#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../head/chemin.h"

typedef struct element {int nombre; struct element* suivant;} t_element;
t_element* tete; //<! Pointeur sur le premier élément de la file
t_element* queue; //<! Pointeur sur le dernier élément de la file

/**
 * \fn void initfile(void)
 * @brief Initialise la file
 * 
*/
void initfile(void){
	tete = NULL;
	queue = NULL;
}
/**
 * \fn int filevide(void)
 * @brief Renvoie VRAI si la file est vide, FAUX sinon
 * @return int
*/
int filevide(void){
	return tete == NULL;
}
/**
 * \fn void ajouter(int v)
 * @brief Ajoute un élément à la file
 * @param v un entier quelquonque
 * 
*/
void ajouter(int v){
t_element* nouv;

nouv = malloc(sizeof(t_element));
nouv->nombre = v;
nouv->suivant = NULL;
if(filevide()){
    tete = nouv;
}
	
else{
    queue->suivant = nouv;
}
queue = nouv; 	
}
/**
 * \fn void retirer(int* v)
 * @brief Retire un élément de la file
 * @param v un entier quelquonque
*/
void retirer(int* v){
t_element* premier;

if(!filevide()){
	premier = tete;
	*v = premier->nombre;
	tete = premier->suivant;
	free(premier);
}
}
/**
 * \fn void afficher_file(void)
 * @brief Affiche la file
 * 
*/
void afficher_file(void){
    t_element* courant;
    t_element* courant2;
    courant = tete;
    courant2= courant->suivant;
    while(courant != NULL || courant2 != NULL){
        //printf("%d %d|", courant->nombre, courant2->nombre);
        if(courant2->suivant==NULL){
            break;
        }else{
            courant = courant2->suivant;
        }if(courant->suivant==NULL){
            break;
        }else{
            courant2 = courant->suivant;
        }
    }
    //printf("\n");
}
/**
 * \fn int valides(int i, int j)
 * @brief Renvoie VRAI si i et j désignent une case de la matrice
 * @param i coordonnée x
 * @param j coordonnée y
 * @return renvoie VRAI si i et j désignent une case de la matrice
*/
int valides(int i, int j){
// renvoie VRAI si i et j désignent une case de la matrice
	return(i>=0 && i<8 &&j>=0 && j<8);
}
/**
 * \fn void marquer_chemin(int lab[9][9],int x, int y,int coords[20][2])
 * @brief Marque le chemin le plus court a partir de lab[x][y]
 * @param lab matrice du labyrinthe
 * @param x coordonnée x
 * @param y coordonnée y
 * @param coords tableau de coordonnées
 * 
*/
void marquer_chemin(int lab[9][9],int x, int y,int coords[20][2]){
// Marque le chemin le plus court a partir de lab[x][y]
// Renvoie sa taille dans lgmin
    //printf("Marquage du chemin le plus court...\n");
    int marq=lab[x][y];
    int Maxmarq=marq;
    while(marq>1){
        coords[Maxmarq-marq][0]=x;
        coords[Maxmarq-marq][1]=y;
        if(valides(x-1, y) && lab[x-1][y]==marq-1) x--;
        else if(valides(x+1, y) && lab[x+1][y]==marq-1) x++;
        else if(valides(x, y-1) && lab[x][y-1]==marq-1) y--;
        else if(valides(x, y+1) && lab[x][y+1]==marq-1) y++;
        marq--;
    }
    coords[Maxmarq-marq][0]=x;
    coords[Maxmarq-marq][1]=y;
    //printf("\n\n\n");
}
/**
 * \fn int chercher_chemin(int xd, int yd, int xa, int ya,int lab[9][9],int coords[20][2])
 * @brief Cherche le chemin D -> A le plus court avec une file 
 * @param xd coordonnée x de départ
 * @param yd coordonnée y de départ
 * @param xa coordonnée x d'arrivée
 * @param ya coordonnée y d'arrivée
 * @param lab matrice du labyrinthe
 * @param coords tableau de coordonnées
 * @return renvoie VRAI si un chemin existe, FAUX sinon
*/
int chercher_chemin(int xd, int yd, int xa, int ya,int lab[9][9],int coords[20][2]){
// Cherche le chemin D -> A le plus court avec une file
// Renvoie VRAI si un chemin existe, FAUX sinon
    //printf("Cherche chemin le plus court...\n");
    int x, y, i;
    int trouve=0;
    lab[xd][yd]=1;
    initfile();
    ajouter(xd);
    ajouter(yd);
    while(!filevide() && !trouve){
        afficher_file();
        //printf("\n");
        retirer(&x);
        retirer(&y);
        i=lab[x][y];
        if(x==xa && y==ya){
            trouve=1;
        }
        else{
            if(lab[x+1][y]==0){
                lab[x+1][y]=i+1;
                ajouter(x+1);
                ajouter(y);
            }
            if(lab[x-1][y]==0){
                lab[x-1][y]=i+1;
                ajouter(x-1);
                ajouter(y);
            }
            if(lab[x][y-1]==0){
                lab[x][y-1]=i+1;
                ajouter(x);
                ajouter(y-1);
            }
            if(lab[x][y+1]==0){
                lab[x][y+1]=i+1;
                ajouter(x);
                ajouter(y+1);
            }
        }
    }
    if(trouve){
        printf("Chemin trouvé !\n");
        //printf("\n\n\n");
        marquer_chemin(lab,xa,ya,coords);
        return 1;
    } 
    else{
        //printf("Chemin non trouvé !\n");
        return 0;
    }
}
