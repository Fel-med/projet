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
menu win1, win2;

int quitter=1, i, t, choix;

i = init_sdl();
if (i) {
	printf("\nerror test") ;
	return 0;
}

t = init_ecran(&scr);
if (t) {
	printf("\nerror init_ecran") ;
	return 0;
}

// first window
init_val_1(&win1);
start(win1,scr);

// second window
init_val_2(&win2);
start(win2,scr);

char playerName[20] = "";

choix = saisir_nom(scr,playerName);
printf("\nchoix 1 = %d",choix);

if (choix == 0) return 0;

choix = top_scores(scr,playerName);
printf("\nchoix 2 = %d",choix);

printf("\nvotre nom : %s",playerName);

quit(&scr);

return 0;
}
