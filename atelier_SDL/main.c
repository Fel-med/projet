#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int main(){

text mes;
mes.text = NULL;
text txt;
bg img;

text position;
position.pos.x = 50;
position.pos.y = 20;

SDL_Event event;

int quitter=1, i, t1, t2;

i = test();
if (i) {printf("error test") ; return 0;}

t1 = init_bg(&img);
if (t1) {printf("error init_bg") ; return 0;}

t2 = init_txt(&txt);
if (t2) {printf("error init_txt") ; return 0;}


while (quitter){

screen(&img, &txt, mes);

SDL_WaitEvent(&event);

switch (event.type){

case SDL_QUIT:
	quitter = 0;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) quitter=0;
	break;
case SDL_MOUSEBUTTONDOWN:
	sprintf(mes.msg,"clic de souris : x=%d, y=%d", event.button.x, event.button.y);
	mes.text = TTF_RenderText_Blended (txt.police, mes.msg, txt.col);
	break;
}
}

quit(&img, &txt, &mes);

return 0;
}
