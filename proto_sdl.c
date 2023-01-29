#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (929)
#define WINDOW_HEIGHT (632)

// vitesse en pixels/seconde
#define SPEED (300)

int main(int argc, char* argv[])
{
    // tentative d'initialisation du système graphique et du timer
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Roguelike",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win)
    {
        printf("erreur creation fenetre: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    // créer un moteur de rendu, qui configure le matériel graphique
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("erreur creation renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // charger l'image en mémoire en utilisant la fonction de la bibliothèque SDL_image
    SDL_Surface* perso = IMG_Load("tank.png");
    if (!perso)
    {
        printf("erreur de creation de surface perso\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
	
	//charger la map en mémoire en utilisant la fonction de la bibliothèque SDL_image
	SDL_Surface* map = IMG_Load("sprite_map.png");
    if (!map)
    {
        printf("erreur de creation de surface map\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // charger les données de l'image dans la mémoire graphique
    SDL_Texture* tex_p = SDL_CreateTextureFromSurface(rend, perso);
	SDL_Texture* tex_m = SDL_CreateTextureFromSurface(rend, map);
    SDL_FreeSurface(perso);
	SDL_FreeSurface(map);
    if (!tex_p)
    {
        printf("erreur création de texture tex_p: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
	if (!tex_m)
    {
        printf("erreur création de texture tex_m: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // structure contenant la position et la taille du sprite
    SDL_Rect dest_p;
	SDL_Rect dest_m;
    // obtenir et mettre à l'échelle les dimensions de la texture
    SDL_QueryTexture(tex_p, NULL, NULL, &dest_p.w, &dest_p.h);


	dest_m.x = 0;
	dest_m.y = 0;
	SDL_QueryTexture(tex_m, NULL, NULL,  &(dest_m.w), &(dest_m.h));

    // démarrer le sprite au centre de l'écran
    float x_pos = (WINDOW_WIDTH - dest_p.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest_p.h) / 2;
    float x_vel = 0;
    float y_vel = 0;

    // garder la trace des entrées qui sont données
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    // mis à 1 lorsque le bouton de fermeture de la fenêtre est pressé
    int close_requested = 0;
    
    // boucle principale
    while (!close_requested)
    {
        // gere les evenements
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        // determine velocité
        x_vel = y_vel = 0;
        if (up && !down) y_vel = -SPEED;
        if (down && !up) y_vel = SPEED;
        if (left && !right) x_vel = -SPEED;
        if (right && !left) x_vel = SPEED;

        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // detection colision avec les murs
        if (x_pos <= 100) x_pos = 100;
        if (y_pos <= 100) y_pos = 100;
        if (x_pos >= (WINDOW_WIDTH-50) - dest_p.w) x_pos = (WINDOW_WIDTH-50) - dest_p.w;
        if (y_pos >= (WINDOW_HEIGHT-50) - dest_p.h) y_pos = (WINDOW_HEIGHT-50) - dest_p.h;

        // définir les positions dans la structure
        dest_p.y = (int) y_pos;
        dest_p.x = (int) x_pos;
        
        // nettoyer la fenêtre
        SDL_RenderClear(rend);

        // dessiner l'image sur la fenêtre
		SDL_RenderCopy(rend, tex_m, NULL, &dest_m);
        SDL_RenderCopy(rend, tex_p, NULL, &dest_p);
        SDL_RenderPresent(rend);

        // attendre 1/60e de seconde
        SDL_Delay(1000/60);
    }
    
    // free tout le bazard
    SDL_DestroyTexture(tex_p);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
