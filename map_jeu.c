#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "mapStruct.c"
#define PERSO 5
const int TILE_SIZE = 32;
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

void transfer(t_salle salle,int map[DIM_SALLE][DIM_SALLE]){
    int i, j;
    for(i=0; i<DIM_SALLE; i++){
        for(j=0; j<DIM_SALLE; j++){
            //printf("%d <- %d ",map[i][j], salle.dim[i][j]);
            map[i][j] = salle.dim[i][j];
        }
    }
}


/**
 * \fn void trouve_debut(t_niv niveau, int posSalle[2])
 * @brief Trouve la position du début du niveau
 *  @param niveau Le niveau
 * @param posSalle La position du début du niveau
 * 
*/
void trouve_salle(t_niv niveau, int posSalle[2],int salle){
    int i, j;
    
    for(i=0; i<DIM_ETAGE; i++){
        for(j=0; j<DIM_ETAGE; j++){
            //affichier_num_salle(&niveau.etages[0]);
            if(niveau.etages[0].etage[i][j].num_salle == salle){
                printf("Salle  N %d en pos %d-%d",niveau.etages[0].etage[i][j].num_salle,i,j);
                posSalle[0] = i;
                posSalle[1] = j;
            }
        }
        printf("\n");
    }
}

void changement(t_niv niv,int move, int posPerso[2],int posSalle[2], int map[DIM_SALLE][DIM_SALLE]){
    if(move==0){
        posSalle[0]--;
        posPerso[0]=DIM_SALLE-2;
    }
    if(move==1){
        posSalle[1]++;
        posPerso[1]=1;
    }
    if(move==2){
        posSalle[0]++;
        posPerso[0]=1;
    }
    if(move==3){
        posSalle[1]--;
        posPerso[1]=DIM_SALLE-2;
    }
    transfer(niv.etages[0].etage[posSalle[0]][posSalle[1]],map);
    map[posPerso[0]][posPerso[1]] = PERSO;
}

void mouvement(int map[DIM_SALLE][DIM_SALLE],int move, int posPerso[2], int posPorte[2], int posSalle[2], t_niv niv){
    int x = posPerso[0];
    int y = posPerso[1];
    if(move == 0){
        if(map[y-1][x] == PORTE){ // Si la case du haut est une porte
            changement(niv, move, posPerso,posSalle,map); 
        }
        if(map[y-1][x] != MUR && map[y-1][x] != PORTE){ // Si la case du haut n'est pas un mur
            map[y-1][x]=5;  //map[(y-1)*MAP_WIDTH+x] = 5; // On met le perso sur la case du haut
            map[y][x]=0;   //map[y*MAP_WIDTH+x] = 0; // On met la case du perso à vide
            posPerso[0] = x; // On met à jour la position du perso
            posPerso[1] = y-1;
            //printf("Bouge vers le haut\n");

        }
    }
    if(move == 2){
        if(map[y+1][x] == PORTE){
            changement(niv, move, posPerso,posSalle,map);
        }
        if(map[y+1][x] != MUR && map[y+1][x] != PORTE){
            map[y+1][x] = 5;
            map[y][x] = 0;
            posPerso[0] = x;
            posPerso[1] = y+1;
            //printf("Bouge vers le bas\n");
        }
    }
    if(move == 3){
        if(map[y][x-1] == PORTE){
            changement(niv, move, posPerso,posSalle,map);
        }
        if(map[y][x-1] != MUR && map[y][x-1] != PORTE){
            map[y][x-1] = 5;
            map[y][x] = 0;
            posPerso[0] = x-1;
            posPerso[1] = y;
            //printf("Bouge vers la gauche\n");
        }
    }
    if(move == 1){
        if(map[y][x+1] == PORTE){
           changement(niv, move, posPerso,posSalle,map);
        }
        if(map[y][x+1] != MUR && map[y][x+1] != PORTE){
            map[y][x+1] = 5;
            map[y][x] = 0;
            posPerso[0] = x+1;
            posPerso[1] = y;
            //printf("Bouge vers la droite\n");
        }
    }
    
}






int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT, 0); // On crée la fenêtre
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // On crée le renderer

  SDL_Surface* tileSurface = IMG_Load("brick.png"); // On charge l'image
  SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface); // On crée la texture
  SDL_FreeSurface(tileSurface); // On libère l'image maintenant qu'elle est dans la texture

  SDL_Surface* tileWall = IMG_Load("ground.png");
  SDL_Texture* WallTex = SDL_CreateTextureFromSurface(renderer, tileWall);
  SDL_FreeSurface(tileWall);

  SDL_Surface* surfaceDoor = IMG_Load("door.png");
  SDL_Texture* DoorTex = SDL_CreateTextureFromSurface(renderer, surfaceDoor);
  SDL_FreeSurface(surfaceDoor);

  SDL_Surface* tilePerso = IMG_Load("character.png"); 
  SDL_Texture* PersoTex = SDL_CreateTextureFromSurface(renderer, tilePerso);
  SDL_FreeSurface(tilePerso);
  t_niv niv;
  genererNiv(&niv);
  
  /*
  int map[100] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 5, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  };
  */
    int map[DIM_SALLE][DIM_SALLE]; // Matrice de la salle
    int posSalle[2]; // Position de la 1er salle
    int posPerso[2] = {DIM_SALLE/2,DIM_SALLE/2}; // Position du perso au millieu de la salle
    int posPorte[2]; // Position de la porte
    trouve_salle(niv, posSalle,1);
    transfer(niv.etages[0].etage[posSalle[0]][posSalle[1]],map);
    map[posPerso[0]][posPerso[1]] = 5;
   // affichage de la matrice de la salle

    printf("Position de la porte : %d %d",posPorte[0],posPorte[1]);
  SDL_Rect srcRect = {0, 0, TILE_SIZE/2, TILE_SIZE/2}; // Position de la texture
  SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE}; // Position de la texture
  
    int move = 0; // Variable de déplacement
    

  int fin=1; // Variable de fin de boucle
  while (fin) { // Boucle principale
    SDL_Event event;
    if (SDL_PollEvent(&event)) { // On récupère les évènements
        switch (event.type)
        {
        case SDL_QUIT:
            fin = 0;
            break;
        case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) // On récupère le code de la touche
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    move=0;
                    mouvement(map,move,posPerso, posPorte,posSalle, niv);
        
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    move=3;
                    mouvement(map,move,posPerso, posPorte,posSalle, niv);
           
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    move=2;
                    mouvement(map,move,posPerso, posPorte,posSalle, niv);
                 
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    move=1;
                    mouvement(map,move,posPerso, posPorte,posSalle, niv);
        
                    break;
                case SDL_SCANCODE_ESCAPE:
                    fin = 0;
                    break;
                }
                break;
            case SDL_KEYUP: 
                switch (event.key.keysym.scancode) 
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    move=-1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    move=-1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    move=-1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    move=-1;
                    break;
                }
                break;
    }
}

    SDL_RenderClear(renderer); // On efface l'écran

    for (int y = 0; y < MAP_HEIGHT; y++) { 
      for (int x = 0; x < MAP_WIDTH; x++) { // On parcourt la map
        int tile = map[y][x]; // On récupère la valeur de la case
        //printf("(%d) ",tile);
        if (tile == 0) { // Sol
            //printf("%d-%d sol |",x,y);
            dstRect.x = x * TILE_SIZE;
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer,WallTex,&srcRect, &dstRect);
        }
        if (tile == PORTE) { // Porte
            dstRect.x = x* TILE_SIZE;
            dstRect.y = y* TILE_SIZE;
            SDL_RenderCopy(renderer,DoorTex,&srcRect, &dstRect);
        }
        if (tile == PERSO) { // Si c'est le perso
            //printf("x = %d, y = %d perso trouvé\n",x,y);
            dstRect.x = x* TILE_SIZE;
            dstRect.y = y* TILE_SIZE;
            SDL_RenderCopy(renderer,PersoTex,&srcRect, &dstRect);
            
        }
        if(tile == 1){ // Si c'est un mur
            dstRect.x = x * TILE_SIZE;
            dstRect.y = y * TILE_SIZE;
            //printf("%d-%d mur |",x,y);
            SDL_RenderCopy(renderer,tileTexture,&srcRect, &dstRect);
        }
      }
      //printf("\n");
    }
        
    SDL_RenderPresent(renderer);
  } // Fin boucle principale

  SDL_DestroyTexture(tileTexture);
  SDL_DestroyTexture(WallTex);
  SDL_DestroyTexture(PersoTex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

}
