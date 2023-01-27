#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define TAILLE_X_MAP 10
#define TAILLE_Y_MAP 10

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
            else if(map[i][j]==FERME){
                printf("#");
            }
            else if(map[i][j]==MUR){   
                printf("@");
            }
            else if(map[i][j]==VIDE){
                printf(" ");
            }
            else if(map[i][j]==BOUTON){
                printf("B");
            }
            
            else if(map[i][j]==OUVERT){
                printf("~");
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
    printf("Bouton : %d, %d\n", porte.bouton.x, porte.bouton.y);
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            if(i==porte.x && j==porte.y){
                map[i][j]=porte.statut;
            }
            else if(i==porte.bouton.x && j==porte.bouton.y){
                map[i][j]=BOUTON;
            }
            else if(i==pers.x && j==pers.y){
                map[i][j]=PERS;
            }
            else if(i==0 || i==TAILLE_X_MAP-1 || j==0 || j==TAILLE_Y_MAP-1){
                map[i][j]=MUR;
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

int parametrage(int map[TAILLE_X_MAP][TAILLE_Y_MAP]){
    struct bouton btn;
    btn.x=1;
    btn.y=1;

        
    do{
        btn.y=rand()%TAILLE_Y_MAP-1;
        btn.x=rand()%TAILLE_X_MAP-1;
    }while((btn.x%TAILLE_X_MAP-1)<1 || (btn.y%TAILLE_Y_MAP-1)<1); // Cherche des coordonnées aléatoires correcte pour le bouton
    t_porte porte = {porte.x, porte.y, FERME , {btn.x, btn.y}};
    porte.x=1;
    porte.y=1;
    //printf("Bouton genere en %d, %d\n", btn.x, btn.y);
    
    do{
        porte.y=rand()%TAILLE_Y_MAP;
        porte.x=rand()%TAILLE_X_MAP;
    }while((porte.x!=0 || porte.y!=0) && (porte.x==porte.y) && (porte.x==btn.x && porte.y==btn.y)); // Cherche des coordonnées aléatoires correcte pour la porte
    //printf("Porte genere en %d, %d\n", porte.x, porte.y);
    t_pos pers = {2,2};
    remplissageMap(map, pers, porte);

    //system("clear");
    affichage(map);

    printf("OBJECTIF : Aller sur la case du bouton !\n");
    char direction;
    int prev_x;
    int prev_y;

    while((pers.x != porte.x) || (pers.y != porte.y)){ // Tant que le perso n'est pas sur la porte
        if(porte.statut==OUVERT){
            printf("La porte est ouverte !\n");
        } 
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
    printf("Les coordonnées du la porte sont : %d, %d\n", porte.x, porte.y);
    printf("Les coordonnées de perso sont : %d, %d\n", pers.x, pers.y);
    printf("Félicitation la porte est ouverte !\n");
    return 0;
}
void nettoyage(int map[TAILLE_X_MAP][TAILLE_Y_MAP]){
    int i, j;
    for(i=0; i<TAILLE_X_MAP; i++){
        for(j=0; j<TAILLE_Y_MAP; j++){
            map[i][j]=VIDE;
        }
    }
}
int main(){
    int map[TAILLE_X_MAP][TAILLE_Y_MAP];
    srand(time(NULL));
    parametrage(map);
    nettoyage(map);
    parametrage(map);
    return 0;
}