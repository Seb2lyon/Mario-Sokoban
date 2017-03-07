#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

void recupererGrille(int grille[][NOMBRE_CASES_L], int niveau)
{
    FILE *fichier = NULL;
    int i = 0, j = 0, debut = 0;

    fichier = fopen("config/niveaux.lvl", "r+");

    debut = (niveau - 1) * (NOMBRE_CASES_TOTAL + 1);

    fseek(fichier, debut, 0);

    for(i = 0; i < NOMBRE_CASES_H; i++)
    {
        for(j = 0; j < NOMBRE_CASES_L; j++)
        {
            switch(fgetc(fichier))
            {
                case '0':
                    grille[j][i] = 0;
                    break;
                case '1':
                    grille[j][i] = 1;
                    break;
                case '2':
                    grille[j][i] = 2;
                    break;
                case '3':
                    grille[j][i] = 3;
                    break;
                case '4':
                    grille[j][i] = 4;
                    break;
                case '5':
                    grille[j][i] = 5;
                    break;
                default:
                    break;
            }
        }
    }

    fclose(fichier);
}

void enregistrerGrille(int grille[][NOMBRE_CASES_L], int niveau)
{
    FILE *fichier = NULL;
    int i = 0, j = 0, debut = 0;

    fichier = fopen("config/niveaux.lvl", "r+");

    debut = (niveau - 1) * (NOMBRE_CASES_TOTAL + 1);

    fseek(fichier, debut, 0);

    for(i = 0; i < NOMBRE_CASES_H; i++)
    {
        for(j = 0; j < NOMBRE_CASES_L; j++)
        {
            fprintf(fichier, "%d", grille[j][i]);
        }
    }

    fclose(fichier);
}
