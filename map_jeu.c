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
const int SPRITE_FRAMES = 4; // Nombre de frames de l'animation
const int SPRITE_WIDTH =32; // Largeur d'une frame
const int SPRITE_HEIGHT = 32; // Hauteur d'une frame
int flip_map=0;
/**
 * \fn transfer(t_salle salle,int map[DIM_SALLE][DIM_SALLE])
 *  \brief Transfert la salle dans la map
 *  @param salle La salle
 *  @param map La map
 *  
*/
void transfert(t_salle salle, t_salle * map){
    int i, j;
    for(i=0; i<DIM_SALLE; i++){
        for(j=0; j<DIM_SALLE; j++){
            map->dim[i][j] = salle.dim[i][j];
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
/*
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
*/
/**
 * \fn void changement(t_niv niv,int move, int posPerso[2],int posSalle[2], int map[DIM_SALLE][DIM_SALLE])
 *  @brief Change de salle
 *  @param niv Le niveau
 *  @param move La direction du changement
 *  @param posPerso La position du personnage
 *  @param posSalle La position de la salle
 *  @param map La map de la salle
 *  
*/
void changement(t_niv * niv, t_dir move, t_pos * posPerso, t_pos * posSalle, t_salle * map){
    if(move==HAUT){
        posSalle->y--;
        posPerso->y=DIM_SALLE-2;
        posPerso->x=(DIM_SALLE/2)-1;
    }
    else if(move==DROITE){
        posSalle->x++;
        posPerso->x=1;
        posPerso->y=(DIM_SALLE/2)-1;
    }
    else if(move==BAS){
        posSalle->y++;
        posPerso->y=1;
        posPerso->x=(DIM_SALLE/2)-1;
    }
    else if(move==GAUCHE){
        posSalle->x--;
        posPerso->x=DIM_SALLE-2;
        posPerso->y=(DIM_SALLE/2)-1;
    }
    if(niv->etages[0].etage[posSalle->x][posSalle->y].statut==EXIT){
        printf("C\'est la fin !\n");
    }
    transfert(niv->etages[0].etage[posSalle->x][posSalle->y], map);
    map->num_salle=niv->etages[0].etage[posSalle->x][posSalle->y].num_salle;
    map->dim[posPerso->x][posPerso->y] = PERSO;
    flip_map=rand()%4;
    printf("Salle n°%d\n", map->num_salle);
    //printf("Salle %d-%d\n",posSalle->x, posSalle->y);
    //printf("PosPerso %d-%d\n",posPerso->x, posPerso->y);
}
/**
 * \fn void mouvement(int map[DIM_SALLE][DIM_SALLE],int move, int posPerso[2], int posPorte[2], int posSalle[2], t_niv niv)
 * @brief Déplace le perso dans la salle
 * @param map La salle
 * @param move La direction du mouvement
 * @param posPerso La position du perso
 * @param posPorte La position de la porte
 * @param posSalle La position de la salle
 * @param niv Le niveau
 * 
*/
void mouvement(t_salle * map, t_dir move, t_pos * posPers, t_pos * posSalle, t_niv * niv){
    int x = posPers->x;
    int y = posPers->y;
    if(move == HAUT){
        if(map->dim[x][y-1] == PORTE){ // Si la case du haut est une porte
            changement(niv, move, posPers, posSalle, map); 
        }
        if(map->dim[x][y-1] != MUR && map->dim[x][y-1] != PORTE && map->dim[x][y-1] != OBSTACLE){ // Si la case du haut n'est pas un mur
            posPers->x = x; // On met à jour la position du perso
            posPers->y = y-1;
            map->dim[posPers->x][posPers->y] = PERSO;  //map[(y-1)*MAP_WIDTH+x] = 5; // On met le perso sur la case du haut
            map->dim[x][y] = VIDE;   //map[y*MAP_WIDTH+x] = 0; // On met la case du perso à vide
            //printf("Bouge vers le haut\n");
        }
    }
    else if(move == BAS){
        if(map->dim[x][y+1] == PORTE){
            changement(niv, move, posPers, posSalle, map);
        }
        else if(map->dim[x][y+1] != MUR && map->dim[x][y+1] != PORTE && map->dim[x][y+1] != OBSTACLE){
            posPers->x = x;
            posPers->y = y+1;
            map->dim[posPers->x][posPers->y] = PERSO;
            map->dim[x][y] = VIDE;
            //printf("Bouge vers le bas\n");
        }
    }
    else if(move == GAUCHE){
        if(map->dim[x-1][y] == PORTE){
            changement(niv, move, posPers, posSalle, map);
        }
        else if(map->dim[x-1][y] != MUR && map->dim[x-1][y] != PORTE && map->dim[x-1][y] != OBSTACLE){
            posPers->x = x-1;
            posPers->y = y;
            map->dim[posPers->x][posPers->y] = PERSO;
            map->dim[x][y] = VIDE;
            //printf("Bouge vers la gauche\n");
        }
    }
    else if(move == DROITE){
        if(map->dim[x+1][y] == PORTE){
           changement(niv, move, posPers, posSalle, map);
        }
        else if(map->dim[x+1][y] != MUR && map->dim[x+1][y] != PORTE && map->dim[x+1][y] != OBSTACLE){
            posPers->x = x+1;
            posPers->y = y;
            map->dim[posPers->x][posPers->y] = PERSO;
            map->dim[x][y] = VIDE;
            //printf("Bouge vers la droite\n");
        }
    }
}



SDL_Texture* charge_tex(SDL_Renderer *renderer,char *path,int bmp_flag){
    SDL_Texture* texture = NULL;
    if(bmp_flag==1){
        SDL_Surface *surface = SDL_LoadBMP(path);
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }else{
        SDL_Surface *surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
    
    return texture;
}


int main() {
    t_niv * niv = malloc(sizeof(t_niv));
    genererNiv(niv);
    SDL_Rect PersRect;
    int frame;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  TILE_SIZE * MAP_WIDTH, TILE_SIZE * MAP_HEIGHT, 0); // On crée la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // On crée le renderer

    SDL_Texture* Mur = charge_tex(renderer,"brick.png",0);
    SDL_Texture* Sol = charge_tex(renderer,"sol.jpg",0);
    SDL_Texture* DoorTex = charge_tex(renderer,"door.png",0);
    SDL_Texture* PersoTex = charge_tex(renderer,"Idle-Sheet.png",0);
    SDL_Texture* ObTex = charge_tex(renderer,"rock.png",0);
    SDL_Texture* PersoNorth = charge_tex(renderer,"1_north.png",0);
    SDL_Texture* PersoSouth = charge_tex(renderer,"1_south.png",0);
    SDL_Texture* PersoSide = charge_tex(renderer,"1_side.png",0);
    
    t_salle map; // Matrice de la salle
    t_pos posSalle; // Position de la 1er salle
    t_pos posPerso = {(DIM_SALLE/2)-1,(DIM_SALLE/2)-1}; // Position du perso au millieu de la salle
    posSalle = trouverSalle(1, &niv->etages[0]);
    //trouve_salle(niv, posSalle,1);
    transfert(niv->etages[0].etage[posSalle.x][posSalle.y], &map);
    map.num_salle=niv->etages[0].etage[posSalle.x][posSalle.y].num_salle;

    map.dim[posPerso.x][posPerso.y] = PERSO;
   // affichage de la matrice de la salle

    SDL_Rect srcRect = {0, 0, TILE_SIZE/2, TILE_SIZE/2}; // Position de la texture
    SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE}; // Position de la texture

    t_dir move = BAS; // Variable de déplacement
    Uint32 lastTime = SDL_GetTicks(); // Temps de la dernière mise à jour de l'animation
    int continuer=1; // Variable de fin de boucle
    while (continuer) { // Boucle principale
    SDL_Event event;
    if (SDL_PollEvent(&event)) { // On récupère les évènements
        switch (event.type){
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode){ // On récupère le code de la touche
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            move=HAUT;
                            mouvement(&map, move, &posPerso, &posSalle, niv);
                            break;

                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            move=GAUCHE;
                            mouvement(&map, move, &posPerso, &posSalle, niv);
                            break;

                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            move=BAS;
                            mouvement(&map, move, &posPerso, &posSalle, niv);
                            break;

                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            move=DROITE;
                            mouvement(&map, move, &posPerso, &posSalle, niv);
                            break;

                        case SDL_SCANCODE_ESCAPE:
                            continuer = 0;
                            break;
                        }
                    break;

            case SDL_KEYUP: 
                switch (event.key.keysym.scancode){
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        //move=AUCUN;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        //move=AUCUN;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        //move=AUCUN;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        //move=AUCUN;
                        break;
                    }
                break;
        }
    }
     Uint32 currentTime = SDL_GetTicks(); // Temps actuel
    if (currentTime - lastTime >= 300) { // Mettre à jour toutes les 300 ms
      frame = (frame + 1) % SPRITE_FRAMES; // Passer à la frame suivante
      lastTime = currentTime; // Mettre à jour le temps de la dernière mise à jour
    }
    
    SDL_RenderClear(renderer); // On efface l'écran
    SDL_RenderCopyEx(renderer,Sol,NULL,NULL,90*flip_map,NULL,SDL_FLIP_NONE); // On affiche le sol
    for (int x = 0; x < MAP_HEIGHT; x++) { 
      for (int y = 0; y < MAP_WIDTH; y++) { // On parcourt la map
        if (map.dim[x][y] == PORTE) { // Porte
                dstRect.x = x* TILE_SIZE; 
                dstRect.y = y* TILE_SIZE;
            if(y==(DIM_SALLE-1) && x==(DIM_SALLE/2)-1){ // Si la porte est en bas
                SDL_RenderCopyEx(renderer,DoorTex,&srcRect, &dstRect,180,NULL,SDL_FLIP_NONE);
            }if(y==(DIM_SALLE/2)-1 && x==0){ // Si la porte est à gauche
                SDL_RenderCopyEx(renderer,DoorTex,&srcRect, &dstRect,270,NULL,SDL_FLIP_NONE);
            }if(y==(DIM_SALLE/2)-1 && x==(DIM_SALLE-1)){ // Si la porte est en haut
                SDL_RenderCopyEx(renderer,DoorTex,&srcRect, &dstRect,90,NULL,SDL_FLIP_NONE); 
            }if(y==0 && x==(DIM_SALLE/2)-1){ // Si la porte est à gauche
                SDL_RenderCopyEx(renderer,DoorTex,&srcRect, &dstRect,0,NULL,SDL_FLIP_NONE); 
            }
        }
        if (map.dim[x][y] == PERSO) { // Si c'est le perso
            //printf("x = %d, y = %d perso trouvé\n",x,y);
            PersRect.x = frame * 20; // Combien de Pixel on doit décaler pour afficher la bonne frame
            PersRect.w = 20; // Largeur de la frame
            PersRect.y = 0;  
            PersRect.h = 24; // Hauteur de la frame
            dstRect.x = x * TILE_SIZE; // Position de la frame
            dstRect.y = y * TILE_SIZE; // Position de la frame
            if(move==HAUT) // On affiche le perso dans la bonne direction
                SDL_RenderCopyEx(renderer, PersoNorth, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE); 
            if(move==BAS)
                SDL_RenderCopyEx(renderer, PersoSouth, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
            if(move==GAUCHE)
                SDL_RenderCopyEx(renderer, PersoSide, &PersRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
            if(move==DROITE)
                SDL_RenderCopyEx(renderer, PersoSide, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
        }
        if(map.dim[x][y] == MUR){ // Si c'est un mur
            dstRect.x = x * TILE_SIZE; // Position du mur
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer, Mur, &srcRect, &dstRect); // On affiche le mur
        }
        if(map.dim[x][y]==OBSTACLE){
            dstRect.x = x * TILE_SIZE; // Position de l'obstacle
            dstRect.y = y * TILE_SIZE;
            SDL_RenderCopy(renderer,ObTex, &srcRect, &dstRect); // On affiche l'obstacle
        }
      }
      //printf("\n");
    }

    SDL_RenderPresent(renderer); // On affiche l'écran
    } // Fin boucle principale

    detruireNiv(&niv); // On libère la mémoire
    SDL_DestroyTexture(Mur); // On détruit les textures 
    SDL_DestroyTexture(Sol);
    SDL_DestroyTexture(PersoTex);
    SDL_DestroyRenderer(renderer); // On détruit le renderer
    SDL_DestroyWindow(window); // On détruit la fenêtre
    SDL_Quit(); // On quitte la SDL

}
