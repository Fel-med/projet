#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int test(){

printf("\ntest");

if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {printf("\nERROR-0 :%s",SDL_GetError()); return 1;}

if (TTF_Init() < 0) {printf("\nERROR-1 :%s",SDL_GetError()); return 1;}

if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0) {printf("\nERROR-2 :%s",SDL_GetError()); return 1;}

return 0;

}


int init_bg(bg *img){

printf("\nbg");

img->ecran = SDL_SetVideoMode(600,430,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
if (img->ecran == NULL) {printf("\nERROR-3 :%s",SDL_GetError());return 1;}

img->img = IMG_Load("palestine.jpg");
if (img->img == NULL) {printf("\nERROR-4 :%s",SDL_GetError());return 1;}

img->mus = Mix_LoadMUS("palestine.mp3");
if (img->mus == NULL) {printf("\nERROR-5 :%s",SDL_GetError());return 1;}
Mix_PlayMusic(img->mus, -1);

img->pos.x = 0;
img->pos.y = 0;

printf("\nfin1");

return 0;

}


int init_txt(text *txt){

printf("\ntxt");

txt->police = TTF_OpenFont("arial.ttf",24);
if (txt->police == NULL) {printf("\nERROR-6 :%s",SDL_GetError());return 1;}

strcpy(txt->msg , "we will never forget\nwe will never stop sharing");

SDL_Color col = {255,0,0};
txt->col =col;

txt->text = TTF_RenderText_Blended (txt->police, txt->msg, col);

txt->pos.x = 70;
txt->pos.y = 400;

printf("\nfin2");

return 0;

}


void screen(bg *img, text *txt, text mes){

SDL_FillRect(img->ecran, NULL, SDL_MapRGB(img->ecran->format,0,0,0));
SDL_BlitSurface(img->img, NULL, img->ecran, &(img->pos));
SDL_BlitSurface(txt->text, NULL, img->ecran, &(txt->pos));
SDL_BlitSurface(mes.text, NULL, img->ecran, &(mes.pos));
SDL_Flip(img->ecran);

}

void quit(bg *img, text *txt, text *mes){

Mix_FreeMusic(img->mus);
SDL_FreeSurface(img->img);

SDL_FreeSurface(txt->text);
TTF_CloseFont(txt->police);

SDL_FreeSurface(mes->text);
TTF_CloseFont(mes->police);

SDL_CloseAudio();
TTF_Quit();
SDL_Quit();

}


