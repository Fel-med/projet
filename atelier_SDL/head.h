#ifndef HEAD_H
#define HEAD_H

typedef struct{
	SDL_Surface *img;
	SDL_Rect pos;
	SDL_Surface *ecran;
	Mix_Music *mus;
}bg;

typedef struct{
	SDL_Surface *text;
	SDL_Rect pos;
	SDL_Color col;
	char msg[50];
	TTF_Font *police;
}text;


int test();

int init_bg(bg *img);

int init_txt(text *txt);

void screen(bg *img, text *txt, text mes);

void quit(bg *img, text *txt, text *mes);

#endif
