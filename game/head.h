#ifndef HEAD_H
#define HEAD_H	

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

// Dimensions de l'écran
#define SCREEN_WIDTH 1099
#define SCREEN_HEIGHT 650


typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	Mix_Chunk *wav;
	TTF_Font *police;
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
	SDL_Surface *img1;
	SDL_Surface *img2;
	int etat;
	int click;
}image;

typedef struct{
	int score;
	char user_name[20];
	int level;
}donne;

typedef struct{
	bg bg;
	image img1;
	image img2;
}menu;

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

// if the function returned 0 : vaild,if not returned 1 : error



//******felhi*******

int init_sdl();
int init_ecran(screen *ecr);
int init_button(menu *win);
void change(image *img, SDL_Event event);
int click(image *img, SDL_Event event, Mix_Chunk *wav);
void screen_affichage(menu win, screen ecr);
void quit_sdl(menu *win, screen *ecr);
int start(menu win, screen ecr);
int init_bg(menu *win);



// yes or no
void init_val_1(menu *win);

// enregistre / charger
void init_val_2(menu *win);

// mech tebe3kom XD
void sau(char file_name[], donne e);
void aff(char file_name[]);

// mysql
void save(donne e); //sauvgarder les donnes
void search(donne *e, char name[]); //chercher pour le jouer
void down(char file_name[]); //remplir le ficher par les joueurs (pour louay)






//******louay*******




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
