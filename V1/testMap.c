#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_X_MAP 10
#define TAILLE_Y_MAP 20

#define FERME -3
#define OUVERT -2
#define MUR -1
#define VIDE 0
#define BOUTON 1
#define PERS 2


typedef struct Perso_pos{
    int x,y;
}t_pos;

typedef struct bouton{
    int x, y;
}t_btn;

typedef struct porte{
    int x, y, statut;
    t_btn bouton;
}t_porte;

void affichage(int map[TAILLE_X_MAP][TAILLE_Y_MAP]){
    int i, j;
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            if(map[i][j]==PERS){
                printf("P");
            }
            else if(map[i][j]==MUR){   
                printf("\u25A3");
            }
            else if(map[i][j]==VIDE || map[i][j]==OUVERT){
                printf("\u25A2");
            }
            else if(map[i][j]==BOUTON){
                printf("B");
            }
            else if(map[i][j]==FERME){
                printf("F");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void remplissageMap(int map[TAILLE_X_MAP][TAILLE_Y_MAP], t_pos pers, t_porte porte){
    int i, j;
    map[porte.x][porte.y]=porte.statut;
    map[porte.bouton.x][porte.bouton.y]=BOUTON;
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            if(i==0 || i==TAILLE_X_MAP-1 || j==0 || j==TAILLE_Y_MAP-1){
                map[i][j]=MUR;
            }
            else if(i==TAILLE_X_MAP/2 && j!=TAILLE_Y_MAP/2){
                map[i][j]=MUR;
            }
            else if(i==porte.x && j==porte.y){
                map[i][j]=porte.statut;
            }
            else if(i==porte.bouton.x && j==porte.bouton.y){
                map[i][j]=BOUTON;
            }
            else if(i==pers.x && j==pers.y){
                map[i][j]=PERS;
            }
            else{
                map[i][j]=VIDE;
            }
        }
    }
}

int est_valide(int map[TAILLE_X_MAP][TAILLE_Y_MAP], int x, int y){
    if(map[x][y]==MUR || map[x][y]==FERME){
        return 0;
    }
    else{
        return 1;
    }
}


int main(){
    int map[TAILLE_X_MAP][TAILLE_Y_MAP];
    t_porte porte = {TAILLE_X_MAP/2, TAILLE_Y_MAP/2, FERME ,{3,4}};
    t_pos pers = {1,1};
    remplissageMap(map, pers, porte);

    system("clear");
    affichage(map);

    printf("OBJECTIF : Aller sur la case du bouton !\n");
    char direction;
    int prev_x;
    int prev_y;

    while(porte.statut!=OUVERT){
        prev_x = pers.x;
        prev_y = pers.y;

        do{
            printf("Saisir une direction (z(haut),s(bas),q(gauche),d(droite)) : ");
            scanf("%c", &direction);
            /*
            if(direction!='z' && direction!='s' && direction!='q' && direction!='d'){
                printf("Caractère inconnu : Saisir uniquement z, s, q ou d\n");
            }
            */
        }while(direction!='z' && direction!='s' && direction!='q' && direction!='d');
        
        switch(direction){
            case 'z': 
                if(est_valide(map, pers.x-1, pers.y)){
                    pers.x--;
                }
                else{
                    printf("Direction impossible : mur ou porte fermé !\n");
                    sleep(1);
                }
                break;
            case 's': 
                if(est_valide(map, pers.x+1, pers.y)){
                    pers.x++;
                }
                else{
                    printf("Direction impossible : mur ou porte fermé !\n");
                    sleep(1);
                }
                break;
            case 'd': 
                if(est_valide(map, pers.x, pers.y+1)){
                    pers.y++;
                }
                else{
                    printf("Direction impossible : mur ou porte fermé !\n");
                    sleep(1);
                }
                break;
            case 'q': 
                if(est_valide(map, pers.x, pers.y-1)){
                    pers.y--;
                }
                else{
                    printf("Direction impossible : mur ou porte fermé !\n");
                    sleep(1);
                }
                break;
        }
        if(pers.x!=prev_x || pers.y!=prev_y){
            map[prev_x][prev_y]=VIDE;
            map[pers.x][pers.y]=PERS;
            if(pers.x==porte.bouton.x && pers.y==porte.bouton.y){
                porte.statut=OUVERT;
                map[porte.x][porte.y]=porte.statut;
            }
        }
        system("clear");
        affichage(map);
    }
    map[porte.x][porte.y] = OUVERT;
    printf("Félicitation la porte est ouverte !\n");

    return 0;
}