#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../head/mapStruct.h"
#include "../head/entite.h"
#include "../head/menu.h"
#define  TILE_SIZE  32
#define  MAP_WIDTH   25
#define  MAP_HEIGHT  25
#define PERSO 5
const int SPRITE_FRAMES = 4; // Nombre de frames de l'animation
const int SPRITE_WIDTH =32; // Largeur d'une frame
const int SPRITE_HEIGHT = 32; // Hauteur d'une frame
int flip_map=0;
int etage_act=0;

/*
*  \fn float distance(entite_t* entite1, entite_t* entite2)
*  \brief Calcule la distance entre deux entites
*  @param entite1 L'entite 1
*  @param entite2 L'entite 2
*/
float distance(entite_t* entite1, entite_t* entite2) {
    float dx = entite1->x - entite2->x;
    float dy = entite1->y - entite2->y;
    return sqrt(dx*dx + dy*dy);
}
/**
 * \fn transfert(t_salle salle, t_salle * map)
 *  \brief Transfert la salle dans la map
 *  @param salle La salle
 *  @param map La map
 *  
*/
void transfert(t_salle salle, t_salle * map){
    printf("Transfert de la salle %d\n",salle.num_salle);
    int i, j;
    map->nb_mobs = salle.nb_mobs;
    map->nb_porte = salle.nb_porte;
    map->num_salle = salle.num_salle;
    map->statut = salle.statut;
    for(i=0; i<salle.nb_mobs; i++){
        map->mob[i] = salle.mob[i];


        //printf("Mob %s -> degats %f\n",map->mob[i]->nom,map->mob[i]->degats);
    }
    for(i=0; i<DIM_SALLE; i++){
        for(j=0; j<DIM_SALLE; j++){
            map->dim[i][j] = salle.dim[i][j];
            
        }
    }
}

/*
*  \fn void changement_etage(t_niv* niv,entite_t* posPerso,t_salle* map, t_pos* posSalle)
*  \brief Change d'étage
*  @param niv Le niveau
*  @param posPerso La position du perso
*  @param map La map
*  @param posSalle La position de la salle
*
*/
void changement_etage(t_niv* niv,entite_t* posPerso,t_salle* map, t_pos* posSalle){
    etage_act++;
    posPerso->x = (DIM_SALLE/2)-1; // Position du perso au millieu de la salle
    posPerso->y = (DIM_SALLE/2)-1;
    *posSalle = trouverSalle(1, &niv->etages[etage_act]);
    transfert(niv->etages[etage_act].etage[posSalle->x][posSalle->y], map);
    map->num_salle=niv->etages[etage_act].etage[posSalle->x][posSalle->y].num_salle;
    map->dim[posPerso->x][posPerso->y] = PERSO;
    flip_map=rand()%4;
    printf("Nouvelle etage !\n");
}

/**
 * \fn void changement(t_niv * niv,entite_t* posPerso, t_pos * posSalle, t_salle * map)
 * \brief Change de salle
 * @param niv Le niveau
 * @param posPerso La position du perso
 * @param posSalle La position de la salle
 * @param map La map
 *  
*/
void changement(t_niv * niv,entite_t* posPerso, t_pos * posSalle, t_salle * map){
    if(map->nb_mobs<=0){
    if(posPerso->dir==HAUT){
        posSalle->y--;
        posPerso->y=DIM_SALLE-2;
        posPerso->x=(DIM_SALLE/2)-1;
    }
    else if(posPerso->dir==DROITE){
        posSalle->x++;
        posPerso->x=1;
        posPerso->y=(DIM_SALLE/2)-1;
    }
    else if(posPerso->dir==BAS){
        posSalle->y++;
        posPerso->y=1;
        posPerso->x=(DIM_SALLE/2)-1;
    }
    else if(posPerso->dir==GAUCHE){
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
    }
}
void chemin_vers_perso(entite_t* perso,entite_t* mob,t_salle* map){
    float dist = distance(perso,mob);
    printf("Distance Entre perso et %s : %f\n",mob->nom,dist);
}
/**
 * \fn void mouvement(t_salle * map,entite_t* posPers, t_pos * posSalle, t_niv * niv)
 * \brief Gère le mouvement du l'entite
 * @param map La map
 * @param posPers La position du perso
 * @param posSalle La position de la salle
 * @param niv Le niveau
 * 
 * 
*/
void mouvement(t_salle * map,entite_t* posPers, t_pos * posSalle, t_niv * niv){
    int x = posPers->x;
    int y = posPers->y;
    if(posPers->dir==HAUT){
        if(map->dim[x][y-1] == PORTE && posPers->persoOuMob==0){ // Si la case du haut est une porte
            changement(niv,posPers, posSalle, map); 
        }
        if(map->dim[x][y-1] == VIDE){ // Si la case du haut n'est pas un mur
            posPers->x = x; // On met à jour la position du perso
            posPers->y = y-1;
            if(posPers->persoOuMob){
                
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob; 
            }else{
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            //map[(y-1)*MAP_WIDTH+x] = 5; // On met le perso sur la case du haut
            map->dim[x][y] = VIDE;   //map[y*MAP_WIDTH+x] = 0; // On met la case du perso à vide
            //printf("Bouge vers le haut\n");
        }
    }
    else if(posPers->dir == BAS){
        if(map->dim[x][y+1] == PORTE && posPers->persoOuMob==0){
            changement(niv,posPers, posSalle, map);
        }
        else if(map->dim[x][y+1] == VIDE){
            posPers->x = x;
            posPers->y = y+1;
            if(posPers->persoOuMob){
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob; 
            }else{
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            //printf("Bouge vers le bas\n");
        }
    }
    else if(posPers->dir == GAUCHE){
        if(map->dim[x-1][y] == PORTE && posPers->persoOuMob==0){
            changement(niv,posPers, posSalle, map);
        }
        else if(map->dim[x-1][y] == VIDE){
            posPers->x = x-1;
            posPers->y = y;
            if(posPers->persoOuMob){
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob; 
            }else{
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            //printf("Bouge vers la gauche\n");
        }
    }
    else if(posPers->dir == DROITE){
        if(map->dim[x+1][y] == PORTE && posPers->persoOuMob==0){
           changement(niv,posPers, posSalle, map);
        }
        else if(map->dim[x+1][y] == VIDE){
            posPers->x = x+1;
            posPers->y = y;
            if(posPers->persoOuMob){
                int ValMob = map->dim[x][y];
                map->dim[posPers->x][posPers->y] = ValMob; 
            }else{
                map->dim[posPers->x][posPers->y] = PERSO;
            }
            map->dim[x][y] = VIDE;
            //printf("Bouge vers la droite\n");
        }
    }
}
/**
 * \fn void perso_attack( t_salle * map,int attaque, entite_t* posPers)
 * \brief Gère l'attaque du perso
 * @param map La map
 * @param attaque Si le perso attaque
 * @param posPers La position du perso
 **/
int perso_attack( t_salle * map,int attaque, entite_t* posPers){
    int x = posPers->x;
    int y = posPers->y;
    if(attaque){
        //printf("Vous attaquez !\n");
        switch (posPers->dir)
        {
        case HAUT:
            if(map->dim[x][y-1] >= 10 && map->dim[x][y-1]<=21){ // si il y a un ennemi sur la case du haut
                map->mob[(map->dim[x][y-1])-10]->vie -= 10;
                //printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x][y-1])-10]->vie);
                if(map->mob[(map->dim[x][y-1])-10]->vie<=0){
                    looter(map->mob[(map->dim[x][y-1])-10],posPers);
                    map->dim[x][y-1] = VIDE;
                    map->nb_mobs--;
                }
            }
            break;
        case BAS:
            if(map->dim[x][y+1] >= 10 && map->dim[x][y+1]<=21){ // si il y a un ennemi sur la case du bas
                map->mob[(map->dim[x][y+1])-10]->vie -= 10;
                //printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x][y+1])-10]->vie);
                if(map->mob[(map->dim[x][y+1])-10]->vie<=0){
                    looter(map->mob[(map->dim[x][y+1])-10],posPers);
                    map->dim[x][y+1] = VIDE;
                    map->nb_mobs--;
                }
            }

            break;
        case GAUCHE:
            if(map->dim[x-1][y] >= 10 && map->dim[x-1][y]<=21){ // si il y a un ennemi sur la case de gauche
                map->mob[(map->dim[x-1][y])-10]->vie -= 10;
                //printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x-1][y])-10]->vie);
                if(map->mob[(map->dim[x-1][y])-10]->vie<=0){
                    looter(map->mob[(map->dim[x-1][y])-10],posPers);
                    map->dim[x-1][y] = VIDE;
                    map->nb_mobs--;
                }
            }
            break;
        case DROITE:
            if(map->dim[x+1][y] >= 10 && map->dim[x+1][y]<=21){ // si il y a un ennemi sur la case de droite
                map->mob[(map->dim[x+1][y])-10]->vie -= 10;
                //printf("Vous avez infligé 10 point de dégats au mob il lui reste %d !\n",map->mob[(map->dim[x+1][y])-10]->vie);
                if(map->mob[(map->dim[x+1][y])-10]->vie<=0){
                    looter(map->mob[(map->dim[x+1][y])-10],posPers);
                    map->dim[x+1][y] = VIDE;
                    map->nb_mobs--;
                }
            }
            break;
        default:
            break;
        }
        return 1;
    }else{
        return 0;
    }
    afficher_inventaire(posPers);
}

/*
* \fn int enemy_attack(t_salle * map, entite_t* posPers, SDL_Rect * rect)
* \brief Fonction qui permet de faire attaquer les mobs
* \param map la map
* \param posPers la position du joueur
* \param rect les points de vie du joueur
* \return 1 si le joueur a perdu des points de vie, 0 sinon
*/
int enemy_attack(t_salle * map, entite_t* posPers, SDL_Rect * rect){
    int x = posPers->x;
    int y = posPers->y;
    if(rect->w > 0){ 
        if(map->dim[x][y-1] >= 10 && map->dim[x][y-1]<=21){ // si il y a un ennemi sur la case du bas
            //printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x][y-1])-10]->degats,map->mob[(map->dim[x][y-1])-10]->nom);
            //rect->w-=(int)(map->mob[(map->dim[x][y-1])-10]->degats);
            return 1;
        }if(map->dim[x][y+1] >= 10 && map->dim[x][y+1]<=21){ // si il y a un ennemi sur la case du haut
            //printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x][y+1])-10]->degats,map->mob[(map->dim[x][y+1])-10]->nom);
            //rect->w-=(int)map->mob[(map->dim[x][y+1])-10]->degats;
            return 1;
        }if(map->dim[x-1][y] >= 10 && map->dim[x-1][y]<=21){ // si il y a un ennemi sur la case de droite
            //printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x-1][y])-10]->degats,map->mob[(map->dim[x-1][y])-10]->nom);
            //rect->w-=(int)map->mob[(map->dim[x-1][y])-10]->degats;
            return 1;
        }if(map->dim[x+1][y] >= 10 && map->dim[x+1][y]<=21){ // si il y a un ennemi sur la case de gauche
            //printf("Vous avez perdu %d points de vie ! avec le mob %s\n",map->mob[(map->dim[x+1][y])-10]->degats,map->mob[(map->dim[x+1][y])-10]->nom);
            //rect->w-=(int)(map->mob[(map->dim[x+1][y])-10]->degats);
            return 1;
        }if(rect->w<250){ // si le perso n'est pas en combat
            rect->w+=2;
        }   
    }
    return 0;
}

/*
* \fn void mouvement(t_salle * map, entite_t * mob, t_pos * posSalle, t_niv * niv)
* \brief Fonction qui permet de faire bouger les mobs
* \param map la map
* \param mob le mob
* \param posSalle la position de la salle
* \param niv le niveau
*/
void interact(int attaque,t_salle * map, entite_t* posPers,SDL_Rect * rect,Uint32* lastTime,t_pos * posSalle,t_niv * niv){
    int x = posPers->x;
    int y = posPers->y;
    int mob;
    float dist;
    Uint32 currentTime = SDL_GetTicks();
    if ( enemy_attack(map,posPers,rect) == 0 && attaque==0){
        if(currentTime - (*lastTime) >= 200){
        //printf("Mouvement du mob\n");
        *lastTime = currentTime; 
        if(map->nb_mobs>0){
            mob = rand()%map->nb_mobs;
            int sens = rand()%4;
            map->mob[mob]->dir = sens;
            dist = distance(posPers,map->mob[mob]);
            if(dist <= 4){
                
            }else{
                mouvement(map,map->mob[mob],posSalle,niv);
            }
        }
        }
    }if(rect->w<=0){
        printf("Vous êtes mort !\n");
    }
}   
/*
* \fn charge_tex(SDL_Renderer *renderer,char *path,int bmp_flag)
* @brief Charge une texture
* @param renderer Le renderer
* @param path Le chemin de la texture
* @param bmp_flag Si la texture est au format bmp
* @return La texture
*/
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
    entite_t * perso ;
    perso=creer_personnage(perso);
    perso=init_inventaire_personnage(perso);
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("../font/necrosans.ttf", 30);
    SDL_Rect PersRect;
    SDL_Rect MobRect;
    int frame;
    int attaque=0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Roguelike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  (TILE_SIZE * MAP_WIDTH)+400, TILE_SIZE * MAP_HEIGHT,0); // On crée la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // On crée le renderer

    SDL_Texture* Mur = charge_tex(renderer,"../img/brick.png",0);
    SDL_Texture* Sol = charge_tex(renderer,"../img/sol.jpg",0);
    SDL_Texture* DoorTex = charge_tex(renderer,"../img/wooden_door.png",0);
    SDL_Texture* PersoTex = charge_tex(renderer,"../img/Idle-Sheet.png",0);
    SDL_Texture* ObTex = charge_tex(renderer,"../img/rock.png",0);
    SDL_Texture* PersoNorth = charge_tex(renderer,"../img/1_north.png",0);
    SDL_Texture* PersoSouth = charge_tex(renderer,"../img/1_south.png",0);
    SDL_Texture* PersoSide = charge_tex(renderer,"../img/1_side.png",0);
    SDL_Texture* MobTex = charge_tex(renderer,"../img/GreenSlime/Grn_Idle1.png",0);
    SDL_Texture* MobTex2 = charge_tex(renderer,"../img/BlueSlime/Blue_Idle1.png",0);

    t_salle map; // Matrice de la salle
    t_pos posSalle; // Position de la salle dans 
    perso->x = (DIM_SALLE/2)-1; // Position du perso au millieu de la salle
    perso->y = (DIM_SALLE/2)-1;
    posSalle = trouverSalle(1, &niv->etages[0]);
    //trouve_salle(niv, posSalle,1);
    transfert(niv->etages[0].etage[posSalle.x][posSalle.y], &map);

    map.num_salle=niv->etages[0].etage[posSalle.x][posSalle.y].num_salle;
    //niv->etages[0].etage[posSalle.x][posSalle.y].mob[0].x = 1;


    map.dim[perso->x][perso->y] = PERSO;
   // affichage de la matrice de la salle

    SDL_Rect srcRect = {0, 0, TILE_SIZE/2, TILE_SIZE/2}; // Position de la texture
    SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE}; // Position de la texture

    SDL_Rect Door;
    SDL_Rect rect; // Rectangle de vie
    rect.x = (TILE_SIZE * MAP_WIDTH)+50; // Position du rectangle sur la largeur
    rect.y = 50; // Position du rectangle sur la hauteur
    rect.w = 250; // Largeur du rectangle
    rect.h = 50; // Hauteur du rectangle
   
    perso->dir = BAS; // Variable de déplacement
    Uint32 lastTime = SDL_GetTicks(); // Temps de la dernière mise à jour de l'animation
    Uint32 MajMove = SDL_GetTicks();
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
                            perso->dir=HAUT;
                            mouvement(&map,perso, &posSalle, niv);
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            perso->dir=GAUCHE;
                            mouvement(&map,perso, &posSalle, niv);
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            perso->dir=BAS;
                            mouvement(&map,perso, &posSalle, niv);
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            perso->dir=DROITE;
                            mouvement(&map,perso, &posSalle, niv);
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            continuer = 0;
                            break;
                        case SDL_SCANCODE_SPACE:
                            attaque=1;
                            perso_attack(&map,attaque,perso);
                            //interact(attaque,&map,perso);
                            break;
                        case SDL_SCANCODE_LSHIFT:
                            SDL_RenderClear(renderer);
                            //menu(renderer,window);
                            SDL_RenderClear(renderer);
                            break;
                        }
                    break;

            case SDL_KEYUP: 
                switch (event.key.keysym.scancode){
                    case SDL_SCANCODE_SPACE:
                        attaque=0;
                        break;
                    }

                break;
        }
    }      
     Uint32 currentTime = SDL_GetTicks(); // Temps actuel
    if (currentTime - lastTime >= 300) { // Mettre à jour toutes les 300 ms
      frame = (frame + 1) % SPRITE_FRAMES;// Passer à la frame suivante
      lastTime = currentTime; // Mettre à jour le temps de la dernière mise à jour
    }
    
    SDL_RenderClear(renderer); // On efface l'écran

    if(flip_map%2){
        SDL_RenderCopyEx(renderer,Sol,NULL,NULL,0,NULL,SDL_FLIP_HORIZONTAL); // On affiche le sol
    }
    else if(flip_map%3){
        SDL_RenderCopyEx(renderer,Sol,NULL,NULL,0,NULL,SDL_FLIP_VERTICAL); // On affiche le sol
    }else{
        SDL_RenderCopy(renderer,Sol,NULL,NULL); // On affiche le sol
    }

    SDL_RenderDrawRect(renderer, &rect); // on decide de dessiner un rectangle avec les coordonnées de rect
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // On defini la couleur du rectangle
    // Un texte signale dans quel étage on est et quel salle on est
    //info_map(&map,niv,police,couleurNoire,window);

     if(map.nb_mobs==0){ // Si il n'y a plus de mobs dans la salle
        Door.x = 16; // On prend la porte ouverte
    }else{
        Door.x = 0; // On prend la porte fermée
    }


    for (int x = 0; x < MAP_HEIGHT; x++) { 
      for (int y = 0; y < MAP_WIDTH; y++) { // On parcourt la map
        if (map.dim[x][y] == PORTE) { // Porte
                dstRect.x = x* TILE_SIZE; 
                dstRect.y = y* TILE_SIZE;
                Door.w = 16; // Largeur de la frame
                Door.y = 0;  
                Door.h = 16; // Hauteur de la frame
            if(y==(DIM_SALLE-1) && x==(DIM_SALLE/2)-1){ // Si la porte est en bas
                SDL_RenderCopyEx(renderer,DoorTex,&Door, &dstRect,180,NULL,SDL_FLIP_NONE);
            }if(y==(DIM_SALLE/2)-1 && x==0){ // Si la porte est à gauche
                SDL_RenderCopyEx(renderer,DoorTex,&Door, &dstRect,270,NULL,SDL_FLIP_NONE);
            }if(y==(DIM_SALLE/2)-1 && x==(DIM_SALLE-1)){ // Si la porte est en haut
                SDL_RenderCopyEx(renderer,DoorTex,&Door, &dstRect,90,NULL,SDL_FLIP_NONE); 
            }if(y==0 && x==(DIM_SALLE/2)-1){ // Si la porte est à gauche
                SDL_RenderCopyEx(renderer,DoorTex,&Door, &dstRect,0,NULL,SDL_FLIP_NONE); 
            }
        }
        if(map.dim[x][y]>=10 && map.dim[x][y]<22){
           /*
            MobRect.x = frame * 16; // Combien de Pixel on doit décaler pour afficher la bonne frame
            MobRect.w = 16; // Largeur de la frame
            MobRect.y = 0;  
            MobRect.h = 16; // Hauteur de la frame
            */
            dstRect.x = x * TILE_SIZE; // Position de la frame
            dstRect.y = y * TILE_SIZE; // Position de la frame
            
            if(map.dim[x][y]==10){
                SDL_RenderCopyEx(renderer, MobTex, NULL, &dstRect, 0, NULL, SDL_FLIP_NONE);
                //printf("Vie du mob : %d",map.mob[map.dim[x][y]-10].vie);
            }
            else{
                SDL_RenderCopyEx(renderer, MobTex2, NULL, &dstRect, 0, NULL, SDL_FLIP_NONE);
                //printf("Vie du mob : %d",map.mob[map.dim[x][y]-10].vie);
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
            if(perso->dir==HAUT) // On affiche le perso dans la bonne direction
                SDL_RenderCopyEx(renderer, PersoNorth, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE); 
            if(perso->dir==BAS)
                SDL_RenderCopyEx(renderer, PersoSouth, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
            if(perso->dir==GAUCHE)
                SDL_RenderCopyEx(renderer, PersoSide, &PersRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
            if(perso->dir==DROITE)
                SDL_RenderCopyEx(renderer, PersoSide, &PersRect, &dstRect, 0, NULL, SDL_FLIP_NONE);
            if(attaque){
                SDL_RenderCopy(renderer, Mur, &srcRect, &dstRect);
            }
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
    interact(attaque,&map,perso,&rect,&MajMove,&posSalle,niv);
    } // Fin boucle principale

    detruireNiv(&niv); // On libère la mémoire
    SDL_DestroyTexture(Mur); // On détruit les textures 
    SDL_DestroyTexture(Sol);
    SDL_DestroyTexture(PersoTex);
    SDL_DestroyRenderer(renderer); // On détruit le renderer
    SDL_DestroyWindow(window); // On détruit la fenêtre
    SDL_Quit(); // On quitte la SDL

}
