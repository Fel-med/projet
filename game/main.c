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

char playerName[20] = "";
int quitter=1, i, t, choix;
int window = 1;

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

choix = 1; //menu principale


while (choix != 0){

switch (window){
case 1: // first window - do you want to save?
	init_val_1(&win1);
	choix = start(win1,scr);
	break;

case 2: // second window - nouvelle/charger partie
	init_val_2(&win2);
	choix = start(win2,scr);
	break;

case 3: // third window - saisir_nom
	choix = saisir_nom(scr,playerName);
	break;

case 4: // fourth window - top scores
	choix = top_scores(scr,playerName);
	break;
default:
	choix = 0;
}
printf("\nchoix = %d",choix);
window++;
}

printf("\nvotre nom : %s",playerName);
quit(&scr);

puts("\nadios\n");

return 0;
}
