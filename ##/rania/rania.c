#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

// Initialisation de la SDL
int init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("Erreur TTF: %s\n", TTF_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
	printf("\nERROR-2 :%s",SDL_GetError());
	return 1;
}
return 0;
}


/*****/
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

int init_button(menu *win){
printf("\nhello %s",win->img1.nom_img1);
win->img1.img = IMG_Load(win->img1.nom_img1);
win->img2.img = IMG_Load(win->img2.nom_img1);
if (win->img1.img == NULL || win->img2.img == NULL) {
	printf("\nERROR-6 :%s",SDL_GetError());
	return 1;
}

return 0;
}


void change(image *img, SDL_Event event){
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


int click(image *img, SDL_Event event, Mix_Chunk *wav){
SDL_Rect e = img->pos;
if (event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h && event.type == SDL_MOUSEBUTTONDOWN && img->click == 1){ 
	Mix_PlayChannel(-1,wav,0);
	img->click = 2;
	SDL_Delay(20);
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
win->lev = 1;

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

int start(menu win, screen scr){

int quitter=1, t1, t2;

if (init_backg(&win)) {
	printf("\nerror init_bg") ;
	return 0;
}

t2 = init_button(&win);
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
	change(&(win.img1), event);
	change(&(win.img2), event);
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


















//**************************************************

void quit_sdl(menu *win, screen *ecr){

SDL_FreeSurface(win->bg.img);

SDL_FreeSurface(win->img1.img);
SDL_FreeSurface(win->img2.img);

}
//*********************************************

int init_ecran(screen *ecr){
printf("\n***Screen...");
fflush(stdout);

ecr->ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
if (ecr->ecran == NULL) {
	printf("\nERROR-3 :%s",SDL_GetError());
	return 1;
}

ecr->mus = Mix_LoadMUS("./res-rania/music.ogg");
if (ecr->mus == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}

ecr->police = TTF_OpenFont("./res-rania/font.ttf", 40);
if (!ecr->police) {
        printf("ERROR-5 : %s\n", TTF_GetError());
        return 1;
    }

ecr->wav = Mix_LoadWAV("./res-rania/sound.wav");
if (ecr->wav == NULL) {
	printf("\nERROR-6 :%s",SDL_GetError());
	return 1;
}

Mix_PlayMusic(ecr->mus, -1);
return 0;
}



///************************************

int quizz(menu win, screen scr){

int quitter=1, t1, t2;

if (init_backg(&win)) {
	printf("\nerror init_bg") ;
	return 0;
}

t2 = init_button(&win);
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
	change(&(win.img1), event);
	change(&(win.img2), event);
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

















