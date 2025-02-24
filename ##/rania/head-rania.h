#ifndef HEAD_H
#define HEAD_H	


#define MAX_QUESTION 256


// Dimensions de l'écran
#define SCREEN_WIDTH 862
#define SCREEN_HEIGHT 619


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

typedef struct{
	int score;
	char user_name[20];
}donne;

typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	Mix_Chunk *wav;
	TTF_Font *police;
}screen;

// returned 0 : vaild, returned 1 : error

// general functions :
int init_SDL();
//void init_SDL();

int init_backg(menu *win);
int init_button(menu *win);
void init_val_enigme(menu *win);
void change(image *img, SDL_Event event);
int click(image *img, SDL_Event event, Mix_Chunk *wav); // 1:not clicked , 2:clicked
void screen_aff(menu win, screen scr);
void quitter(menu *win);
int start(menu win, screen scr);
void quit_sdl(menu *win, screen *ecr);
int init_ecran(screen *ecr);



#endif
