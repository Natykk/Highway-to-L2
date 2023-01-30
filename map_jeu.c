#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#define MUR 1
#define VIDE 0
#define PORTE 2
#define PERSO 5
const int TILE_SIZE = 16;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

void mouvement(int map[100],int move, int posPerso[2]){
    int x = posPerso[0];
    int y = posPerso[1];
    if(move == 0){
        if(map[(y-1)*MAP_WIDTH+x] != MUR){ // Si la case du haut n'est pas un mur
            map[(y-1)*MAP_WIDTH+x] = 5; // On met le perso sur la case du haut
            map[y*MAP_WIDTH+x] = 0; // On met la case du perso à vide
            posPerso[0] = x; // On met à jour la position du perso
            posPerso[1] = y-1;
            printf("Bouge vers le haut\n");

        }
    }
    if(move == 2){
        if(map[(y+1)*MAP_WIDTH+x] != MUR){
            map[(y+1)*MAP_WIDTH+x] = 5;
            map[y*MAP_WIDTH+x] = 0;
            posPerso[0] = x;
            posPerso[1] = y+1;
            printf("Bouge vers le bas\n");
        }
    }
    if(move == 3){
        if(map[y*MAP_WIDTH+x-1] != MUR){
            map[y*MAP_WIDTH+x-1] = 5;
            map[y*MAP_WIDTH+x] = 0;
            posPerso[0] = x-1;
            posPerso[1] = y;
            printf("Bouge vers la gauche\n");
        }
    }
    if(move == 1){
        if(map[y*MAP_WIDTH+x+1] != MUR){
            map[y*MAP_WIDTH+x+1] = 5;
            map[y*MAP_WIDTH+x] = 0;
            posPerso[0] = x+1;
            posPerso[1] = y;
            printf("Bouge vers la droite\n");
        }
    }
}



void jeu() {
  //SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SIZE * MAP_WIDTH, TILE_SIZE * MAP_HEIGHT, 0); // On crée la fenêtre
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // On crée le renderer

  SDL_Surface* tileSurface = IMG_Load("brick.png"); // On charge l'image
  SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface); // On crée la texture
  SDL_FreeSurface(tileSurface); // On libère l'image maintenant qu'elle est dans la texture

  SDL_Surface* tileWall = IMG_Load("ground.png");
  SDL_Texture* WallTex = SDL_CreateTextureFromSurface(renderer, tileWall);
  SDL_FreeSurface(tileWall);

  SDL_Surface* tilePerso = IMG_Load("character.png"); 
  SDL_Texture* PersoTex = SDL_CreateTextureFromSurface(renderer, tilePerso);
  SDL_FreeSurface(tilePerso);

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

  SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE}; // Position de la texture
  SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE}; // Position de la texture
  
    int move = 0; // Variable de déplacement
    int posPerso[2] = {1,1}; // Position du perso
    

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
                    mouvement(map,move,posPerso);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    move=3;
                    mouvement(map,move,posPerso);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    move=2;
                    mouvement(map,move,posPerso);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    move=1;
                    mouvement(map,move,posPerso);
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
        int tile = map[y * MAP_WIDTH + x]; // On récupère la valeur de la case
        if (tile == 0) { // Sol
            dstRect.x = x * TILE_SIZE;
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer,WallTex,&srcRect, &dstRect);
          continue;
        }
        if (tile == 5) { // Si c'est le perso
            printf("x = %d, y = %d perso trouvé\n",x,y);
            dstRect.x = x* TILE_SIZE;
            dstRect.y = y* TILE_SIZE;
            SDL_RenderCopy(renderer,PersoTex,&srcRect, &dstRect);
            
        }
        if(tile == 1){ // Si c'est un mur
            dstRect.x = x * TILE_SIZE;
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer,tileTexture,&srcRect, &dstRect);
        }
      }
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
