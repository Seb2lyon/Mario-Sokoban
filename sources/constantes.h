#ifndef CONSTANTES
#define CONSTANTES

#define NOMBRE_CASES_L 12
#define NOMBRE_CASES_H 12
#define CASE_L 34
#define CASE_H 34
#define FENETRE_L CASE_L * NOMBRE_CASES_L
#define FENETRE_H CASE_H * NOMBRE_CASES_H
#define NOMBRE_CASES_TOTAL NOMBRE_CASES_H * NOMBRE_CASES_L
#define NOMBRE_GRILLES 200

typedef struct Personnage Personnage;

struct Personnage
{
    int x;
    int y;
    int objectif;
};

#endif // CONSTANTES
