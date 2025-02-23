#ifndef HEAD_H
#define HEAD_H	


#include <SDL/SDL.h>

// Dimensions de l'écran
#define SCREEN_WIDTH 862
#define SCREEN_HEIGHT 619

typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	TTF_Font *police;
	char nom_mus[50];
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
	int level;
}donne;

// Définition de la structure des scores
typedef struct {
    char name[20];
    int score;
} Playerscore;

// Structure pour le bouton
typedef struct {
    SDL_Rect rect;
    SDL_Surface *image;
    SDL_Surface *hoverImage;
    int hovered;
} Button;





int saisir_nom(screen scr, char playerName[]);

int top_scores(screen scr, char playerName[]);

void renderMenu(screen *scr, SDL_Color textColor, SDL_Rect inputBox, SDL_Color boxColor, SDL_Surface *bg, Button btnValidate, char playerName[]);

int handleInput(SDL_Event event, char playerName[], Button *btnValidate);

int handleInput2(SDL_Event event, Button *btnValidate1, Button *btnValidate2);

void renderText(const char *text, int x, int y, screen *scr, SDL_Color textColor);

void init1(SDL_Surface **bg, Button *btnValidate);

void init2(SDL_Surface **bg, Button *btnValidate1, Button *btnValidate2);

SDL_Surface* loadImage(const char *filename);

void cleanUp(SDL_Surface **bg, Button *btnValidate);

void quit(screen *scr);

void charger(Playerscore *topScores);

SDL_Surface* loadImageBMP(const char *filename);

void renderTopScores(screen *scr, SDL_Surface *background, TTF_Font *font, Playerscore topScores[], int count, Button btnValidate1, Button btnValidate2);




#endif
