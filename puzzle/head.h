#ifndef HEAD_H
#define HEAD_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>



typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	char nom_mus[50];
	SDL_Color col;
	TTF_Font *police;
	Mix_Chunk *wav;
}screen;

typedef struct{
	SDL_Rect pos;
	SDL_Surface *img;
	char nom_img[50];
}bg;

typedef struct{
	SDL_Rect pos;
	SDL_Surface *img;
	char nom_img1[50];
	char nom_img2[50];
	int etat;
	int click;
}image;

typedef struct{
	int lev;
	bg bg;
	image img1;
	image img2;
}menu;

typedef struct {
    int val;
    SDL_Rect pos;
}squ;

typedef struct {
    SDL_Surface *text;
    SDL_Rect pos;
    char msg[50];
}text;


#define tile_size 100
#define hight_scr 619
#define width_scr 1099


int init();
int init_ecran(screen *ecran); 
int init_bg(menu *win);
int init_button(menu *win);
//void change(image *img, SDL_Event event);// change the image (hover)
//int click(image *img, SDL_Event event); // 1:not clicked , 2:clicked
void screen_affichage(menu win, screen ecr, squ **M, int n, int grid_size, int start_x, int start_y); 
void quit(menu *win, screen *ecr);
int start(menu win, screen *ecr);




// Puzzle functions
void init_level_1(int *n, squ **M);
void init_level_2(int *n, squ **M);
void init_level_3(int *n, squ **M);
int valid(int n, squ **M, int x, int y, SDL_Event event);
void mov(int n, squ **M, int x, int y, int test);
int winn(int n, squ **M);


#endif
