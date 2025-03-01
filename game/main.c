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

if(init_sdl()) {
	printf("\nerror test") ;
	return 0;
}

if(init_ecran(&scr)) {
	printf("\nerror init_ecran") ;
	return 0;
}


printf("\nLet's bigun\n");


/*printf("Choose difficulty level:\n1. Easy (3x3)\n2. Medium (4x4)\n3. Hard (5x5)\n");
int choice;
scanf("%d", &choice);
*/



/*
 1:do you want to save?
 2:nouvelle/charger partie
 3:saisir_nom
 4:top scores
 5:enigme
 6:quizz
 7:menu principale
 8:menu option
 9:joueur menu
 0:quitter
*/


// first window
init_val_enigme(&win_enigme1);
init_val_1(&win1);
init_val_2(&win2);


int score = 0;
int rep[3] = {0,0,0};
int window = 7;
char playerName[20] = "";
int quitter = 1, res;


while (window != 0){

switch (window){
case 1: // first window - do you want to save? CVVVVV
	window = start(win1,scr);
	break;

case 2: // second window - nouvelle/charger partie CVVVV
	window = start2(win2,scr);
	break;

case 3: // third window - saisir_nom  CVVVVVVVVV
	Mix_HaltMusic();
	window = saisir_nom(scr,playerName);
	Mix_PlayMusic(scr.mus, -1);
	break;

case 4: // fourth window - top scores  "ne9es 8ne mt3 victory"
	Mix_HaltMusic();
	window = top_scores(scr,playerName);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 5: // 5eme window - enigme   CVVVVVVV
	Mix_HaltMusic();
	window = start_enigme(win_enigme1,scr);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 6: // 6eme window - quizz  "ne9se button && 3 rep"
	Mix_HaltMusic();
	window = start_quizz(scr,rep);
	res = rep[0]+rep[1]+rep[2];
	printf("\nyour scrore : %d + %d + %d = %d",rep[0],rep[1],rep[2],res);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 7: // 7eme window - menu principale  CVVVVVVVVVVVVVVV
	window = menu_principale(scr);
	break;
case 8: // 8eme window - menu option   CVVVVVVV
	window = menu_option(&scr);
	break;
case 9: // 9eme window - joueur menu  "wa9tch ykon valide"
	window = joueur_menu(scr);
	break;
case 10:// 10eme window - the puzzle  CVVVVVVVV
	window = puzzle (scr, 1, &score);
	break;
default:
	window = 0;
}
SDL_FillRect(scr.ecran, NULL, SDL_MapRGB(scr.ecran->format, 0, 0, 0));
printf("\nthe window = %d",window);
}

printf("\nvotre nom : %s , score = %d",playerName,score);
quit(&scr);

puts("\nadios\n");

return 0;
}
