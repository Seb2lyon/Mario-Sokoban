#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "fichier.h"

void menuJouer(SDL_Surface *ecran)
{
    SDL_Surface *instruction = NULL, *jouer = NULL, *surface = NULL, *victoire = NULL;
    SDL_Rect positionInstruction = {0}, positionJouer = {0}, positionSurface = {0}, positionVictoire = {0};
    SDL_Event event = {0};
    Personnage mario = {0, 0, 0};
    FILE *fichier = NULL;
    int grille[NOMBRE_CASES_L][NOMBRE_CASES_H] = {{0}}, infos = 1, jeu = 1, nouvelleGrille = 1, numeroGrille = 1, orientationMario = 1, nombreObjectif = 0, gagne = 1, i = 0, j = 0;

    SDL_EnableKeyRepeat(100, 100);

    // Catch the level
    fichier = fopen("config/grille.lvl", "r");
    fscanf(fichier, "%d", &numeroGrille);

    if(numeroGrille < 1)
    {
        numeroGrille = 1;
    }
    else if(numeroGrille > NOMBRE_GRILLES)
    {
        numeroGrille = NOMBRE_GRILLES;
    }

    fclose(fichier);

    // Instructionns page
    instruction = IMG_Load("images/instructions_jeu.jpg");
    positionInstruction.x = 0;
    positionInstruction.y = 0;
    SDL_BlitSurface(instruction, NULL, ecran, &positionInstruction);

    SDL_Flip(ecran);

    // Instructions page's loop
    while(infos)
    {
        SDL_WaitEvent(&event);

        // Events' loop
        switch(event.type)
        {
            case SDL_KEYDOWN: // Go to game page
                infos = 0;
                break;

            case SDL_MOUSEBUTTONUP: // Go to game page
                infos = 0;
                break;

            default:
                break;
        }
    }

    SDL_FreeSurface(instruction);

    // Game page's loop
    while(jeu)
    {
        SDL_WaitEvent(&event);

        // Events' loop
        switch(event.type)
        {
            case SDL_QUIT:
                jeu = 0; // Back to menu
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Back to menu
                        SDL_EnableKeyRepeat(0, 0);
                        jeu = 0;
                        SDL_EnableKeyRepeat(100, 100);
                        break;

                    case SDLK_PAGEUP: // Next level
                        SDL_EnableKeyRepeat(0, 0);
                        if(numeroGrille < NOMBRE_GRILLES)
                        {
                            numeroGrille++;
                            nouvelleGrille = 1;
                        }
                        SDL_EnableKeyRepeat(100, 100);
                        break;

                    case SDLK_PAGEDOWN: // Previous level
                        SDL_EnableKeyRepeat(0, 0);
                        if(numeroGrille >= 2)
                        {
                            numeroGrille--;
                            nouvelleGrille = 1;
                        }
                        SDL_EnableKeyRepeat(100, 100);
                        break;

                    case SDLK_UP: // Up arrow key
                        orientationMario = 2;

                        if(mario.y - 1 >= 0 && (grille[mario.x][mario.y - 1] == 0 || grille[mario.x][mario.y - 1] == 3)) // If corridor or objective
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x][mario.y - 1] == 3) // If Mario go to an objective
                            {
                                mario.objectif = 1;
                            }

                            grille[mario.x][mario.y - 1] = 4;
                            mario.y = mario.y - 1;
                        }
                        else if(mario.y - 2 < NOMBRE_CASES_L && (grille[mario.x][mario.y - 1] == 2 || grille[mario.x][mario.y - 1] == 5) && (grille[mario.x][mario.y - 2] == 0 || grille[mario.x][mario.y - 2] == 3)) // If box
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x][mario.y - 1] == 5) // If the box is well located
                            {
                                mario.objectif = 1;
                            }

                            if(grille[mario.x][mario.y - 2] == 3) // If the box move to an objective
                            {
                                grille[mario.x][mario.y - 2] = 5;
                            }
                            else
                            {
                                grille[mario.x][mario.y - 2] = 2;
                            }
                            grille[mario.x][mario.y - 1] = 4;
                            mario.y = mario.y - 1;
                        }
                        break;

                    case SDLK_DOWN: // Down arrow key
                        orientationMario = 1;

                        if(mario.y + 1 < NOMBRE_CASES_H && (grille[mario.x][mario.y + 1] == 0 || grille[mario.x][mario.y + 1] == 3)) // If corridor or objective
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x][mario.y + 1] == 3) // If Mario go to an objective
                            {
                                mario.objectif = 1;
                            }

                            grille[mario.x][mario.y + 1] = 4;
                            mario.y = mario.y + 1;
                        }
                        else if(mario.y + 2 < NOMBRE_CASES_L && (grille[mario.x][mario.y + 1] == 2 || grille[mario.x][mario.y + 1] == 5) && (grille[mario.x][mario.y + 2] == 0 || grille[mario.x][mario.y + 2] == 3)) // If box
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x][mario.y + 1] == 5) // If the box is well located
                            {
                                mario.objectif = 1;
                            }

                            if(grille[mario.x][mario.y + 2] == 3) // If the box move to an objective
                            {
                                grille[mario.x][mario.y + 2] = 5;
                            }
                            else
                            {
                                grille[mario.x][mario.y + 2] = 2;
                            }
                            grille[mario.x][mario.y + 1] = 4;
                            mario.y = mario.y + 1;
                        }
                        break;

                    case SDLK_RIGHT: // Right arrow key
                        orientationMario = 3;

                        if(mario.x + 1 < NOMBRE_CASES_L && (grille[mario.x + 1][mario.y] == 0 || grille[mario.x + 1][mario.y] == 3)) // If corridor or objective
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x + 1][mario.y] == 3) // If Mario go to an objective
                            {
                                mario.objectif = 1;
                            }

                            grille[mario.x + 1][mario.y] = 4;
                            mario.x = mario.x + 1;
                        }
                        else if(mario.x + 2 < NOMBRE_CASES_L && (grille[mario.x + 1][mario.y] == 2 || grille[mario.x + 1][mario.y] == 5) && (grille[mario.x + 2][mario.y] == 0 || grille[mario.x + 2][mario.y] == 3)) // If box
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x + 1][mario.y] == 5) // If the box is well located
                            {
                                mario.objectif = 1;
                            }

                            if(grille[mario.x + 2][mario.y] == 3) // If the box move to an objective
                            {
                                grille[mario.x + 2][mario.y] = 5;
                            }
                            else
                            {
                                grille[mario.x + 2][mario.y] = 2;
                            }
                            grille[mario.x + 1][mario.y] = 4;
                            mario.x = mario.x + 1;
                        }
                        break;

                    case SDLK_LEFT: // Left arrow key
                        orientationMario = 4;

                        if(mario.x - 1 >= 0 && (grille[mario.x - 1][mario.y] == 0 || grille[mario.x - 1][mario.y] == 3)) // If cooridor or objective
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x - 1][mario.y] == 3) // If Mario go to an objective
                            {
                                mario.objectif = 1;
                            }

                            grille[mario.x - 1][mario.y] = 4;
                            mario.x = mario.x - 1;
                        }
                        else if(mario.x - 2 >= 0 && (grille[mario.x - 1][mario.y] == 2 || grille[mario.x - 1][mario.y] == 5) && (grille[mario.x - 2][mario.y] == 0 || grille[mario.x - 2][mario.y] == 3))
                        {
                            if(mario.objectif) // If Mario is on an objective
                            {
                                grille[mario.x][mario.y] = 3;
                                mario.objectif = 0;
                            }
                            else
                            {
                                grille[mario.x][mario.y] = 0;
                            }

                            if(grille[mario.x - 1][mario.y] == 5) // If the box is well located
                            {
                                mario.objectif = 1;
                            }

                            if(grille[mario.x - 2][mario.y] == 3) // If the box move to an objective
                            {
                                grille[mario.x - 2][mario.y] = 5;
                            }
                            else
                            {
                                grille[mario.x - 2][mario.y] = 2;
                            }
                            grille[mario.x - 1][mario.y] = 4;
                            mario.x = mario.x - 1;
                        }
                        break;

                    case SDLK_r:
                        SDL_EnableKeyRepeat(0, 0);
                        nouvelleGrille = 1;
                        SDL_EnableKeyRepeat(100, 100);
                        break;

                    case SDLK_s:
                        SDL_EnableKeyRepeat(0, 0);
                        fichier = fopen("config/grille.lvl", "w+");
                        fprintf(fichier, "%d", numeroGrille);
                        fclose(fichier);
                        SDL_EnableKeyRepeat(100, 100);
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }

        // Background
        jouer = SDL_CreateRGBSurface(SDL_HWSURFACE, FENETRE_L, FENETRE_H, 32, 0, 0, 0, 0);
        SDL_FillRect(jouer, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        positionJouer.x = 0;
        positionJouer.y = 0;
        SDL_BlitSurface(jouer, NULL, ecran, &positionJouer);

        if(nouvelleGrille)
        {
            // Fill the window
            recupererGrille(grille, numeroGrille);
            orientationMario = 1;
            mario.x = 0;
            mario.y = 0;
            mario.objectif = 0;
            nouvelleGrille = 0;
        }

        nombreObjectif = 0;

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
                        nombreObjectif++;
                        break;
                    case 4:
                        if(mario.objectif) // If Mario is on an objective
                        {
                            surface = IMG_Load("images/objectif.png");
                            positionSurface.x = j * CASE_L;
                            positionSurface.y = i * CASE_H;
                            SDL_BlitSurface(surface, NULL, ecran, &positionSurface);
                            SDL_FreeSurface(surface);
                        }
                        switch(orientationMario)
                        {
                            case 1:
                                surface = IMG_Load("images/mario_bas.gif");
                                break;
                            case 2:
                                surface = IMG_Load("images/mario_haut.gif");
                                break;
                            case 3:
                                surface = IMG_Load("images/mario_droite.gif");
                                break;
                            case 4:
                                surface = IMG_Load("images/mario_gauche.gif");
                                break;
                            default:
                                break;
                        }
                        mario.x = j;
                        mario.y = i;
                        break;
                    case 5:
                        surface = IMG_Load("images/caisse_ok.jpg");
                        break;
                    default:
                        break;
                }
                positionSurface.x = j * CASE_L;
                positionSurface.y = i * CASE_H;
                SDL_BlitSurface(surface, NULL, ecran, &positionSurface);
                SDL_FreeSurface(surface);
            }
        }

        SDL_Flip(ecran);

        if(nombreObjectif == 0 && mario.objectif == 0) // If all the objectives are filled
        {
            if(numeroGrille == NOMBRE_GRILLES)
            {
                victoire = IMG_Load("images/bravo_fin.jpg");
            }
            else
            {
                victoire = IMG_Load("images/bravo.jpg");
            }
            positionVictoire.x = (ecran->w / 2) - (victoire->w / 2);
            positionVictoire.y = (ecran->h / 2) - (victoire->h / 2);
            SDL_BlitSurface(victoire, NULL, ecran, &positionVictoire);
            SDL_Flip(ecran);
            SDL_FreeSurface(victoire);
            gagne = 1;

            while(gagne)
            {
                SDL_WaitEvent(&event);

                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        if(numeroGrille < NOMBRE_GRILLES)
                        {
                            nouvelleGrille = 1;
                            numeroGrille++;
                            gagne = 0;
                        }
                        break;

                    case SDL_QUIT:
                        gagne = 0;
                        jeu = 0;
                        break;

                    default:
                        break;
                }
            }
        }

        SDL_FreeSurface(jouer);
    }
}
