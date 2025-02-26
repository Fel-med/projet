#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int init_backg(menu *win){
printf("\n***Background...");

win->bg.img = SDL_LoadBMP(win->bg.nom_img);
win->bg.img = SDL_DisplayFormat(win->bg.img);
if (win->bg.img == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}

return 0;
}
//*********

int init_button_2(menu *win){
win->img1.img = IMG_Load(win->img1.nom_img1);
win->img2.img = IMG_Load(win->img2.nom_img1);
if (win->img1.img == NULL || win->img2.img == NULL) {
	printf("\nERROR-6 :%s",SDL_GetError());
	return 1;
}

return 0;
}


void screen_aff(menu win, screen scr){
SDL_BlitSurface((win.bg).img, NULL, scr.ecran, &(win.bg.pos));

SDL_BlitSurface((win.img1).img, NULL, scr.ecran, &(win.img1.pos));
SDL_BlitSurface((win.img2).img, NULL, scr.ecran, &(win.img2.pos));

SDL_Flip(scr.ecran);


}


void quitter(menu *win){
SDL_FreeSurface(win->bg.img);

SDL_FreeSurface(win->img1.img);
SDL_FreeSurface(win->img2.img);
}
//*********************************************



void init_val_enigme(menu *win){

//bg
strcpy(win->bg.nom_img,"./res-rania/bg.bmp");
win->bg.pos.x=0;
win->bg.pos.y=0;


//btn 1
strcpy(win->img1.nom_img1,"./res-rania/btn1.tga");
strcpy(win->img1.nom_img2,"./res-rania/btn1-2.tga");
printf("\nhi %s",win->img1.nom_img1);
fflush(stdout);
win->img1.pos.h=100;
win->img1.pos.w=160;
win->img1.pos.x = SCREEN_WIDTH / 2 - win->img1.pos.w - 100;
win->img1.pos.y = SCREEN_HEIGHT / 2 - win->img1.pos.h + 120;
win->img1.etat=1;
win->img1.click=1;

//btn 2
strcpy(win->img2.nom_img1,"./res-rania/btn2.tga");
strcpy(win->img2.nom_img2,"./res-rania/btn2-2.tga");
win->img2.pos.h=100;
win->img2.pos.w=160;
win->img2.pos.x = SCREEN_WIDTH / 2 - win->img2.pos.w + 180;
win->img2.pos.y = SCREEN_HEIGHT / 2 - win->img2.pos.h + 120;
win->img2.etat=1;
win->img2.click=1;
}
//**************************

int start_enigme(menu win, screen scr){

int quitter=1, t1, t2;


t1 = init_backg(&win);
if (t1) {
	printf("\nerror init_bg") ;
	return 0;
}

t2 = init_button_2(&win);
if (t2) {
	printf("\nerror init_button") ;
	return 0;
}

SDL_Event event;

int choix_1 = 0, choix_2 = 0;
while (quitter){

screen_aff(win, scr);

SDL_PollEvent(&event);

switch (event.type){

case SDL_QUIT:
	quitter = 0;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) quitter=0; //quitter
	break;
case SDL_MOUSEMOTION:
	change_enigme(&(win.img1), event);
	change_enigme(&(win.img2), event);
	break;
case SDL_MOUSEBUTTONDOWN:
	choix_1 = click(&(win.img1), event, scr.wav);
	choix_2 = click(&(win.img2), event, scr.wav);
	break;
}
if (choix_1 || choix_2) break; //quitter
SDL_Delay(10);
}

return (choix_1 * 2) + choix_2; // returned 2 if yes , else returned 1 if no

quit_sdl(&win,&scr);
}



//*************************

void change_enigme(image *img, SDL_Event event){
SDL_Rect e = img->pos;
if (event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h && img->etat == 1){
	img->etat = 2;
	img->img = IMG_Load(img->nom_img2);
}
else if(!(event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h) && img->etat == 2){
	img->img = IMG_Load(img->nom_img1);
	img->etat = 1;
}
img->click = 1;
}


//******************************************



int start_quizz(screen scr){


SDL_Surface *bg = SDL_LoadBMP("./res-rania/bg.bmp");
if (!bg) {
	printf("\nerror init_bgg") ;
	return 0;
return bg;
}


quiz txt[]= {
	{"who are you ?","me","you","we","it",1},
	{"what's 5+100 ?","50","500","105","150",3},
	{"hi, are you smart ?","yes","maybe","nope","idk",3},
};


int count, rep[] = {0,0,0};

SDL_Event event;
count = 0;

int choix_1 = 0, choix_2 = 0, choix_3 = 0, choix_4 = 0 , choix = 0;
while (count < 3 && choix != -1){

screen_aff2(bg,txt[count],scr);


SDL_PollEvent(&event);

switch (event.type){

case SDL_QUIT:
	choix = -1;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE){
		 choix = -1; //quitter
		 break;
		}
	if (event.key.keysym.sym == SDLK_a) choix_1 = 1;
	else if (event.key.keysym.sym == SDLK_b) choix_2 = 1;
	else if (event.key.keysym.sym == SDLK_c) choix_3 = 1;
	else if (event.key.keysym.sym == SDLK_d) choix_4 = 1;
	choix = (choix_4 * 4) + (choix_3 * 3) + (choix_2 * 2) + choix_1; //quitter
	break;
}


if (choix != -1 && choix !=0 && count<3){
	rep[count] = choix;
	printf("\nhi : %d",choix);
	count++;
	choix = choix_1 = choix_2 = choix_3 = choix_4 = 0;
	SDL_PollEvent(&event);
	while (event.type != SDL_KEYUP){
		SDL_PollEvent(&event);
		SDL_Delay(20);
	}
	
}


SDL_Delay(10);
}


return rep; // returned 2 if yes , else returned 1 if no

quit_sdl2(bg);
}




//**************************


void screen_aff2(SDL_Surface *bg, quiz txt, screen scr){

SDL_BlitSurface(bg, NULL, scr.ecran, NULL);

SDL_Color col = {200,250,30};

SDL_Surface *t1 = TTF_RenderText_Blended(scr.police, txt.ques, col);
SDL_Surface *t2 = TTF_RenderText_Blended(scr.police, txt.rep_a, col);
SDL_Surface *t3 = TTF_RenderText_Blended(scr.police, txt.rep_b, col);
SDL_Surface *t4 = TTF_RenderText_Blended(scr.police, txt.rep_c, col);
SDL_Surface *t5 = TTF_RenderText_Blended(scr.police, txt.rep_d, col);



SDL_Rect pos1 = {431, 150, 0, 0};
SDL_Rect pos2 = {216, 260, 0, 0};
SDL_Rect pos3 = {657, 260, 0, 0};
SDL_Rect pos4 = {216, 410, 0, 0};
SDL_Rect pos5 = {657, 410, 0, 0};


SDL_BlitSurface(t1, NULL, scr.ecran, &pos1);
SDL_BlitSurface(t2, NULL, scr.ecran, &pos2);
SDL_BlitSurface(t3, NULL, scr.ecran, &pos3);
SDL_BlitSurface(t4, NULL, scr.ecran, &pos4);
SDL_BlitSurface(t5, NULL, scr.ecran, &pos5);

SDL_Flip(scr.ecran);

SDL_FreeSurface(t1);
SDL_FreeSurface(t2);
SDL_FreeSurface(t3);
SDL_FreeSurface(t4);
SDL_FreeSurface(t5);

}
//****************************

void quit_sdl2(SDL_Surface *bg){
    if (bg) SDL_FreeSurface(bg);
}








