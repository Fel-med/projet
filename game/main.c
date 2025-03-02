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
donne d;

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

//down("file.bin");
//aff("file.bin");

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


int rep[3] = {0,0,0};
int window = 7;
strcpy(d.user_name,"");
d.score = 0;
d.level = 0;
int quitter = 1, res;


while (window != 0){

switch (window){
case 1: // first window - do you want to save?   ****cv****
	window = start(win1,scr);
	break;

case 2: // second window - nouvelle/charger partie   ****cv****
	window = start2(win2,scr);
	break;

case 3: // third window - saisir_nom   ****cv****
	Mix_HaltMusic();
	window = saisir_nom(scr,d.user_name);
	Mix_PlayMusic(scr.mus, -1);
	break;

case 4: // fourth window - top scores  "ne9es 8ne mt3 victory"
	Mix_HaltMusic();
	SDL_Delay(20);
	Mix_PlayMusic(scr.mus2, 0);
	window = top_scores(scr,d.user_name);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 5: // 5eme window - enigme    ****cv****
	Mix_HaltMusic();
	window = start_enigme(win_enigme1,scr);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 6: // 6eme window - quizz   ****cv****
	Mix_HaltMusic();
	window = start_quizz(scr,rep);
	res = rep[0]+rep[1]+rep[2];
	d.score += res;
	printf("\nyour scrore : %d + %d + %d = %d",rep[0],rep[1],rep[2],res);
	Mix_PlayMusic(scr.mus, -1);
	break;
case 7: // 7eme window - menu principale   ****cv****  "ne9es history"
	window = menu_principale(scr);
	break;
case 8: // 8eme window - menu option   ****CV****
	window = menu_option(&scr);
	break;
case 9: // 9eme window - joueur menu   ****cv****
	window = joueur_menu(scr,&d);
	break;
case 10:// 10eme window - the puzzle   ****cv****
	window = puzzle (scr, 1, &res);
	d.score += res;
	break;
default:
	window = 0;
}
SDL_FillRect(scr.ecran, NULL, SDL_MapRGB(scr.ecran->format, 0, 0, 0));
printf("\nthe window = %d",window);
}

printf("\nvotre nom : %s , score = %d, input = %d, avatar = %d",d.user_name,d.score,d.input,d.avatar);
quit(&scr);

puts("\nadios\n");

return 0;
}
