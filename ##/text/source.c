#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include "head.h"


void text_change(SDL_Event event, char txt[]){

SDLKey k = event.key.keysym.sym;

if ( (k >= SDLK_a && k <= SDLK_z) || (k >= SDLK_0 && k <= SDLK_9) ){
	if (strlen(txt) < taille_max){
		txt[strlen(txt)] = (char)k;
		txt[strlen(txt)] = '\0';
}
}

else if (k == SDLK_BACKSPACE && strlen(txt) > 0) {
	txt[strlen(txt)-1] = '\0';
}

else if (k == SDLK_SPACE)
	if (strlen(txt) < taille_max){
		txt[strlen(txt)] = ' ';
		txt[strlen(txt)] = '\0';
}

}
