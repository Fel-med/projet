#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include "head.h"


int main(){

if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {
	printf("\nERROR-0 :%s",SDL_GetError());
	return 1;
}

if (TTF_Init() == -1) return 1;printf("\nttf");

SDL_Surface *scr = SDL_SetVideoMode(680, 480, 32, SDL_SWSURFACE);

SDL_Surface *text = NULL;

SDL_Surface *img = IMG_Load("palestine.jpg");
if (!img) return 1;printf("\nimg");

SDL_Color col = {255, 0, 0};
TTF_Font *police = TTF_OpenFont("font.TTF",24);
if (!police) return 1;printf("\npolice");

char txt[50] = "-->";
int done = 1;

SDL_Event event;

while (done){

SDL_BlitSurface(img, NULL, scr, NULL);

text = TTF_RenderText_Blended(police, txt, col);
SDL_BlitSurface(text, NULL, scr, NULL);

SDL_Flip(scr);

SDL_PollEvent(&event);

switch(event.type){
	case SDL_QUIT:
		done = 0;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) done = 0;
		else{
			text_change(event, txt);
			printf("\ntext : %s",txt);
		}
		while (event.type != SDL_KEYUP){
			SDL_PollEvent(&event);
			SDL_Delay(50);
			
		}
		break;
}

}

SDL_FreeSurface(text);
SDL_FreeSurface(img);
TTF_Quit();
SDL_Quit();

return 0;
}
