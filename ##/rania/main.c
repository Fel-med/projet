#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"


int main()
{

menu win_enigme1;
screen scr;

int quitter=1, i, t, choix;
int window = 1;

i = init_SDL();
if (i) {
	printf("\nerror test") ;
	return 0;
}

t = init_ecran(&scr);
if (t) {
	printf("\nerror init_ecran") ;
	return 0;
}

//choix = 1; //menu principale




// first window
init_val_enigme(&win_enigme1);
choix = start(win_enigme1,scr);
printf("\nchoix : %d",choix);


puts("\n GOOD BYE o/a\n");

return 0;

}
