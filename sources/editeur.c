#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "fichier.h"

void menuEditeur(SDL_Surface *ecran)
{
    SDL_Surface *instruction = NULL, *editeur = NULL, *surface = NULL, *curseur = NULL;
    SDL_Rect positionInstruction = {0}, positionEditeur = {0}, positionSurface = {0}, positionCurseur = {0};
    SDL_Event event = {0};
    int grille[NOMBRE_CASES_L][NOMBRE_CASES_H] = {{0}}, infos = 1, edition = 1, numeroGrille = 1, nouvelleGrille = 1, souris = 0, nlleSurface = 1, curseurSurface = 1, marioUnique = 0, mario = 0, i = 0, j = 0;

    // Instructions page
    instruction = IMG_Load("images/instructions.jpg");
    positionInstruction.x = 0;
    positionInstruction.y = 0;
    SDL_BlitSurface(instruction, NULL, ecran, &positionInstruction);

    SDL_Flip(ecran);

    // Innstructions page's loop
    while(infos)
    {
        SDL_WaitEvent(&event);

        // Events' loop
        switch(event.type)
        {
            case SDL_KEYDOWN: // Go to edition page
                infos = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Go to edition page
                infos = 0;
                break;

            default:
                break;
        }
    }

    SDL_FreeSurface(instruction);

    SDL_WarpMouse(ecran->w / 2, ecran->h / 2);

    curseur = IMG_Load("images/mur.jpg");
    curseurSurface = 1;
    positionCurseur.x = (ecran->w / 2) + 10;
    positionCurseur.y = (ecran->h / 2) + 10;

    // Edition page's loop
    while(edition)
    {
        SDL_WaitEvent(&event);

        // Events' loop
        switch(event.type)
        {
            case SDL_QUIT:
                edition = 0; // Back to menu
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Back to menu
                        edition = 0;
                        break;

                    case SDLK_PAGEUP: // Next level
                        if(numeroGrille < NOMBRE_GRILLES)
                        {
                            numeroGrille++;
                            nouvelleGrille = 1;
                        }
                        break;

                    case SDLK_PAGEDOWN: // Previous level
                        if(numeroGrille >= 2)
                        {
                            numeroGrille--;
                            nouvelleGrille = 1;
                        }
                        break;

                    case SDLK_KP1: // Wall with cursor (Keypad)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/mur.jpg");
                        curseurSurface = 1;
                        break;

                    case SDLK_1: // Wall with cursor (numeric key)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/mur.jpg");
                        curseurSurface = 1;
                        break;

                    case SDLK_KP2: // Box with cursor (Keypad)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/caisse.jpg");
                        curseurSurface = 2;
                        break;

                    case SDLK_2: // Box with cursor (numeric key)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/caisse.jpg");
                        curseurSurface = 2;
                        break;

                    case SDLK_KP3: // Box OK with cursor (Keypad)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/caisse_ok.jpg");
                        curseurSurface = 5;
                        break;

                    case SDLK_3: // Box OK with cursor (numeric key)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/caisse_ok.jpg");
                        curseurSurface = 5;
                        break;

                    case SDLK_KP4: // Objective with cursor (Keypad)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/objectif.png");
                        curseurSurface = 3;
                        break;

                    case SDLK_4: // Objective with cursor (numeric key)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/objectif.png");
                        curseurSurface = 3;
                        break;

                    case SDLK_KP5: // Mario with cursor (Keypad)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/mario_bas.gif");
                        curseurSurface = 4;
                        break;

                    case SDLK_5: // Mario with cursor (numeric key)
                        SDL_FreeSurface(curseur);
                        curseur = IMG_Load("images/mario_bas.gif");
                        curseurSurface = 4;
                        break;

                    case SDLK_s:
                        mario = 0;
                        for(j = 0; j < NOMBRE_CASES_H; j++)
                        {
                            for(i = 0; i < NOMBRE_CASES_L; i++)
                            {
                                if(grille[j][i] == 4)
                                {
                                    mario = 1;
                                }
                            }
                        }
                        if(mario)
                        {
                            enregistrerGrille(grille, numeroGrille);
                        }
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN: // Mouse button down
                if(event.button.button == SDL_BUTTON_LEFT) // If left click
                {
                    if(!marioUnique || curseurSurface != 4) // If there's no Mario placed
                    {
                        nlleSurface = curseurSurface;
                        grille[event.button.x / CASE_L][event.button.y / CASE_H] = nlleSurface;
                        souris = 1;
                    }
                }
                else if(event.button.button == SDL_BUTTON_RIGHT) // If right click
                {
                    nlleSurface = 0;
                    grille[event.button.x / CASE_L][event.button.y / CASE_H] = nlleSurface;
                    souris = 1;
                }
                break;

            case SDL_MOUSEBUTTONUP: // Release the mouse mutton
                souris = 0;
                break;

            case SDL_MOUSEMOTION: // Movement of the mouse
                positionCurseur.x = (event.motion.x) + 10;
                positionCurseur.y = (event.motion.y) + 10;
                if(nlleSurface != 4) // If the cursor's shape is Mario
                {
                    if(souris) // If the mouse button is pressed, we fill the surfaces during the movement
                    {
                        grille[event.motion.x / CASE_L][event.motion.y / CASE_H] = nlleSurface;
                    }
                }
                break;

            default:
                break;
        }

        // Background
        editeur = SDL_CreateRGBSurface(SDL_HWSURFACE, FENETRE_L, FENETRE_H, 32, 0, 0, 0, 0);
        SDL_FillRect(editeur, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        positionEditeur.x = 0;
        positionEditeur.y = 0;
        SDL_BlitSurface(editeur, NULL, ecran, &positionEditeur);

        marioUnique = 0;

        if(nouvelleGrille)
        {
            // Filling the screen
            recupererGrille(grille, numeroGrille);
            nouvelleGrille = 0;
        }

        for(i = 0; i < NOMBRE_CASES_H; i++)
        {
            for(j = 0; j < NOMBRE_CASES_L; j++)
            {
                switch(grille[j][i])
                {
                    case 0:
                        surface = SDL_CreateRGBSurface(SDL_HWSURFACE, CASE_L, CASE_H, 32, 0, 0, 0, 0);
                        SDL_FillRect(surface, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                        break;
                    case 1:
                        surface = IMG_Load("images/mur.jpg");
                        break;
                    case 2:
                        surface = IMG_Load("images/caisse.jpg");
                        break;
                    case 3:
                        surface = IMG_Load("images/objectif.png");
                        break;
                    case 4:
                        surface = IMG_Load("images/mario_bas.gif");
                        marioUnique = 1;
                        break;
                    case 5:
                        surface = IMG_Load("images/caisse_ok.jpg");
                        break;
                    default:
                        break;
                }
                positionSurface.x = j * CASE_L ;
                positionSurface.y = i * CASE_H;
                SDL_BlitSurface(surface, NULL, ecran, &positionSurface);
                SDL_FreeSurface(surface);
            }
        }
        SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
        SDL_Flip(ecran);

        SDL_FreeSurface(editeur);
    }

    SDL_FreeSurface(curseur);
}
