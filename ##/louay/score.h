#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h> // Pour utiliser "bool"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

// Définition de la structure des scores
typedef struct {
    char name[20];
    int score;
} Playerscore;

// Déclaration des scores
extern Playerscore topScores[3];
extern int scoreCount;
extern bool showScores;

void renderTopScores(SDL_Surface *screen, SDL_Surface *background, TTF_Font *font, Playerscore topScores[], int count);

#endif


