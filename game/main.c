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
menu win1, win2, win_enigme1;

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


printf("\nLet's bigun\n");

joueur_menu(scr);
/*
printf("Choose difficulty level:\n1. Easy (3x3)\n2. Medium (4x4)\n3. Hard (5x5)\n");
int choice;
scanf("%d", &choice);

//puzzle (scr, 1); error//////////////////////

*/




// first window
/*init_val_enigme(&win_enigme1);
init_val_1(&win1);
init_val_2(&win2);


//int rep[3];

choix = -1;


while (choix != 0){
printf("\nll");

switch (window){
case 1: // first window - do you want to save?
	choix = start(win1,scr);
	break;

case 2: // second window - nouvelle/charger partie
	choix = start(win2,scr);
	break;

case 3: // third window - saisir_nom
	choix = saisir_nom(scr,playerName);
	break;

case 4: // fourth window - top scores
	choix = top_scores(scr,playerName);
	break;
case 5:
	choix = start_enigme(win_enigme1,scr);
	break;
case 6:
	start_quizz(scr);
	/*int res = rep[0]+rep[1]+rep[2];
	printf("/nyour scrore : %d + %d + %d = %d",rep[0],rep[1],rep[2],res);/
	break;
case 7:
	choix = menu_principale(scr);
	break;
case 8:
	choix = menu_option(&scr);
	break;

default:
	choix = 0;
}
printf("\nchoix = %d",choix);
window++;
}

printf("\nvotre nom : %s",playerName);*/
quit(&scr);

puts("\nadios\n");

return 0;
}
