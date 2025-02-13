#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"



int init(){
printf("\n**Initialiation...");

if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {
	printf("\nERROR-0 :%s",SDL_GetError());
	return 1;
}

if (TTF_Init() < 0) {
	printf("\nERROR-1 :%s",SDL_GetError());
	return 1;
}

if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
	printf("\nERROR-2 :%s",SDL_GetError());
	return 1;
}
return 0;
}
//*********************************************

int init_bg(menu *win){
printf("\n***Background...");

win->bg.ecran = SDL_SetVideoMode(1100,700,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
if (win->bg.ecran == NULL) {
	printf("\nERROR-3 :%s",SDL_GetError());
	return 1;
}

win->bg.img = IMG_Load(win->bg.nom_img);
win->bg.img = SDL_DisplayFormat(win->bg.img);
if (win->bg.img == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}

win->bg.mus = Mix_LoadMUS(win->bg.nom_mus);
if (win->bg.mus == NULL) {
	printf("\nERROR-5 :%s",SDL_GetError());
	return 1;
}
Mix_PlayMusic(win->bg.mus, -1);

return 0;
}
//*********************************************

int init_button(menu *win){
win->img1.img = IMG_Load(win->img1.nom_img1);
win->img2.img = IMG_Load(win->img2.nom_img1);
if (win->img1.img == NULL || win->img2.img == NULL) {
	printf("\nERROR-6 :%s",SDL_GetError());
	return 1;
}

win->img1.wav = Mix_LoadWAV("./res/sound.wav");
win->img2.wav = Mix_LoadWAV("./res/sound.wav");
if ((win->img1).wav == NULL || (win->img2).wav == NULL) {
	printf("\nERROR-7 :%s",SDL_GetError());
	return 1;
}

return 0;
}
//*********************************************

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
//*********************************************

int click(image *img, SDL_Event event){
SDL_Rect e = img->pos;
if (event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h && event.type == SDL_MOUSEBUTTONDOWN && img->click == 1){ 
	Mix_PlayChannel(-1,img->wav,0);
	img->click = 2;
	SDL_Delay(20);
	return 1;
}
return 0;
}
//*********************************************

void screen(menu win){
SDL_BlitSurface((win.bg).img, NULL, win.bg.ecran, &(win.bg.pos));

SDL_BlitSurface((win.img1).img, NULL, win.bg.ecran, &(win.img1.pos));
SDL_BlitSurface((win.img2).img, NULL, win.bg.ecran, &(win.img2.pos));

SDL_Flip(win.bg.ecran);
//SDL_UpdateRect((win.bg).ecran,0,0,0,0);

}
//*********************************************

void quit(menu *win){
Mix_FreeMusic(win->bg.mus);
SDL_FreeSurface(win->bg.img);

SDL_FreeSurface(win->img1.img);
SDL_FreeSurface(win->img2.img);

//TTF_CloseFont(police);

SDL_CloseAudio();
Mix_FreeChunk(win->img1.wav);
Mix_FreeChunk(win->img2.wav);
//TTF_Quit();
SDL_Quit();
}
//*********************************************

void init_val_1(menu *win){
win->lev = 1;
//bg
strcpy(win->bg.nom_img,"./res/bg1.bmp");
strcpy(win->bg.nom_mus,"./res/music.ogg");
win->bg.pos.x=0;
win->bg.pos.y=0;
//oui (sauvgarder)
strcpy(win->img1.nom_img1,"./res/y-1.tga");
strcpy(win->img1.nom_img2,"./res/y-2.tga");
win->img1.pos.x=360;
win->img1.pos.y=350;
win->img1.pos.h=100;
win->img1.pos.w=100;
win->img1.etat=1;
win->img1.click=1;
//non (sauvgarder)
strcpy(win->img2.nom_img1,"./res/x-1.tga");
strcpy(win->img2.nom_img2,"./res/x-2.tga");
win->img2.pos.x=600;
win->img2.pos.y=350;
win->img2.pos.h=100;
win->img2.pos.w=100;
win->img2.etat=1;
win->img2.click=1;
}
//*********************************************
void init_val_2(menu *win){
win->lev = 1;
//bg
strcpy(win->bg.nom_img,"./res/bg2.bmp");
strcpy(win->bg.nom_mus,"./res/music.ogg");
win->bg.pos.x=0;
win->bg.pos.y=0;
//nouvelle partie
strcpy(win->img1.nom_img1,"./res/nou-1.tga");
strcpy(win->img1.nom_img2,"./res/nou-2.tga");
win->img1.pos.x=320;
win->img1.pos.y=110;
win->img1.pos.h=190;
win->img1.pos.w=450;
win->img1.etat=1;
win->img1.click=1;
//charger
strcpy(win->img2.nom_img1,"./res/char-1.tga");
strcpy(win->img2.nom_img2,"./res/char-2.tga");
win->img2.pos.x=320;
win->img2.pos.y=330;
win->img2.pos.h=190;
win->img2.pos.w=450;
win->img2.etat=1;
win->img2.click=1;
}
//*********************************************

int start(menu win){

int quitter=1, i, t1, t2;

i = init();
if (i) {
	printf("\nerror test") ;
	return 0;
}

t1 = init_bg(&win);
if (t1) {
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

screen(win);

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
	choix_1 = click(&(win.img1), event);
	choix_2 = click(&(win.img2), event);
	break;
}
if (choix_1 || choix_2) break; //quitter
SDL_Delay(10);
}

return (choix_1 * 2) + choix_2; // returned 2 if yes , else returned 1 if no

quit(&win);
}
//*********************************************

void sau(char file_name[], donne e){
FILE *f = fopen(file_name, "ab");
if (f == NULL) {
	printf("\nERROR 7");
	return;
}
fwrite(&e, sizeof(donne), 1, f);
fclose(f);
printf("\nyour data(s) saved\n");
}
//*********************************************

void aff(char file_name[]){
FILE *f = fopen(file_name, "rb");
donne e;
if (f == NULL) {
	printf("\nERROR 7");
	return;
}
fread(&e, sizeof(donne), 1, f);
while(!feof(f)){
	printf("\nthe score: %d, name: %s",e.score, e.user_name);
	fread(&e, sizeof(donne), 1, f);
}
fclose(f);
}









