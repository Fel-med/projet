#ifndef HEAD_H
#define HEAD_H	

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#define MAX_QUESTION 256

// Dimensions de l'écran
#define SCREEN_WIDTH 862
#define SCREEN_HEIGHT 480


#define tile_size 100
#define hight_scr 619
#define width_scr 1099

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

typedef struct {
    SDL_Rect position;
    SDL_Surface* normalImage;
    SDL_Surface* hoverImage;
    int isActive;
} Button2;

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

typedef struct {
	char ques[500];
	char rep_a[20];
	char rep_b[20];
	char rep_c[20];
	char rep_d[20];
	int rep;
}quiz;

typedef struct {
    int val;
    SDL_Rect pos;
}squ;

typedef struct {
    SDL_Surface *text;
    SDL_Rect pos;
    char msg[50];
}text;

typedef struct{
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Surface *img;
	int hidden;
}image2;


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
int start_enigme(menu win, screen ecr);
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


//******rania*******


int init_backg(menu *win);
int init_button_2(menu *win);
void init_val_enigme(menu *win);
void screen_aff(menu win, screen scr);
void quitter(menu *win);
void change_enigme(image *img, SDL_Event event);
int start_quizz(screen scr);
void screen_aff2(SDL_Surface *bg, quiz txt, screen scr);
void quit_sdl2(SDL_Surface *bg);


//******charrad*******

// the function to open the window
int menu_option(screen *scr);
SDL_Surface* create_window(int width, int height, int bpp, Uint32 flags);
SDL_Surface* load_image(const char* filename);
int init_ecran(screen *ecr);

// Fonctions pour les boutons
void create_buttons(Button2* buttons);
Button2 create_button(int x,int y,int w,int h,const char* normalPath,char*hoverPath);
int is_mouse_over_button(Button2* button,int mouseX,int mouseY);
void update_button_state(Button2* button, int mouseX, int mouseY);
void render_button(SDL_Surface* screen,Button2* button);
void handle_button_click(Button2* button,int* quitter,int* volume,SDL_Surface* ecran,int* showWindowModeText);

// Affichage de texte
void render_text(SDL_Surface* screen,const char* text,TTF_Font* font,SDL_Color color,SDL_Rect position);

// Plein écran
void toggle_fullscreen(SDL_Surface* screen);

// Boucle principale
void main_game_loop(SDL_Surface* ecran,SDL_Surface* image,SDL_Rect posecranimg,Button2* buttons, TTF_Font* font,TTF_Font* windowModeFont,Mix_Music* musique,int* quitter, int* volume,int* showWindowModeText,SDL_Color textColor);

// Nettoyage
void cleanup_resources(SDL_Surface* image, Button2* buttons, int buttonCount);


//********puzzle***********

int start_puzzle(menu win, screen *ecr);
void init_level_1(int *n, squ **M);
void init_level_2(int *n, squ **M);
void init_level_3(int *n, squ **M);
int valid(int n, squ **M, int x, int y, SDL_Event event);
void mov(int n, squ **M, int x, int y, int test);
int winn(int n, squ **M);
int init_bg_puzzle(menu *win);
int puzzle (screen ecr, int choix);
void quit_puzzle_puzzle(menu *win, screen *ecr);
void aff_puzzle(int n, squ **M);


//*************alaa*************


int menu_principale(screen scr);
void create_buttons2(Button2* buttons);
void main_game_loop2(SDL_Surface* ecran, SDL_Surface* image, SDL_Rect posecranimg, Button2* buttons, TTF_Font* font, int* quitter, SDL_Color textColor, SDL_Surface *logo, SDL_Rect pos_logo);
void handle_button_click2(Button2* button, int* quitter, SDL_Surface* ecran);


//************omar**************


void initImage(image2 *pic, char path[], int x, int y, int hidden);
void afficher_omar(image2 p, SDL_Surface **screen);
void liberer (image2 picture);
int joueur(screen scr);



#endif
