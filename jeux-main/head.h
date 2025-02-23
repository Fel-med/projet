#ifndef HEAD_H
#define HEAD_H	


#define MAX_QUESTION 256




typedef struct{
	SDL_Rect pos;
	SDL_Surface *img;
	char nom_img[50];
	SDL_Surface *ecran;
	Mix_Music *mus;
	char nom_mus[50];
}bg;


typedef struct{
	SDL_Rect pos;
	SDL_Surface *img;
	char nom_img1[50];
	char nom_img2[50];
	Mix_Chunk *wav;
	int etat;
	int click;
}image;

typedef struct{
	int lev;
	bg bg;
	image img1;
	image img2;
}menu;

typedef struct{
	int score;
	char user_name[20];
}donne;

// returned 0 : vaild, returned 1 : error

// general functions :
int init_SDL();
//void init_SDL();

int init_bg(menu *win);
int init_button(menu *win);
void init_val_1(menu *win);
void init_val_2(menu *win);
void change(image *img, SDL_Event event);
int click(image *img, SDL_Event event); // 1:not clicked , 2:clicked
void screen(menu win);
void quit(menu *win);
int start(menu win);




#endif
