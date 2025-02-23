#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"


int main(){

screen scr;

if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        exit(1);
    }

if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur IMG_Init : %s\n", IMG_GetError());
        exit(1);
    }

if (TTF_Init() == -1) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        exit(1);
    }

scr.ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
if (!scr.ecran) {
        printf("Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        exit(1);
    }

scr.police = TTF_OpenFont("./res/arial.ttf", 40);
if (!scr.police) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        exit(1);
    }
char playerName[20] = "";
int choix;

choix = saisir_nom(scr,playerName);

if (choix == 0) return 0;

choix = top_scores(scr,playerName);

printf("\nvotre nom : %s",playerName);

quit(&scr);

return 0;
}
