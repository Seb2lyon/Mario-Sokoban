/*********************************************
 *          Developped by Seb2lyon           *
 *  Inspired by M@teo21 from Openclassrooms  *
 *              ---------------              *
 *                   v. 1.0                  *
 *                 08/03/2017                *
 *              ---------------              *
 *                  Enjoy ;)                 *
 *********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *menu = NULL;
    SDL_Rect positionMenu = {0};
    SDL_Event event = {0};
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL

    fenetre = SDL_SetVideoMode(FENETRE_L, FENETRE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Create window

    SDL_WM_SetCaption("Mario Sokoban", NULL); // Title + icon
    SDL_WM_SetIcon(IMG_Load("images/caisse.jpg"), NULL);

    while(continuer) // Menu's loop
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0; // Leave the app
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continuer = 0; // Leave the app
                }
                else if(event.key.keysym.sym == SDLK_KP1)
                {
                    menuJouer(fenetre); // Game
                }
                else if(event.key.keysym.sym == SDLK_KP2)
                {
                    menuEditeur(fenetre); // Editor
                }
                break;

            default:
                break;
        }

        // Show menu's screen
        menu = IMG_Load("images/menu.jpg");
        positionMenu.x = 0;
        positionMenu.y = 0;
        SDL_BlitSurface(menu, NULL, fenetre, &positionMenu);

        SDL_Flip(fenetre);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
