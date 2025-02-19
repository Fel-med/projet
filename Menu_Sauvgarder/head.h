#ifndef HEAD_H
#define HEAD_H	

typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
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

// if the function returned 0 : vaild,if not returned 1 : error

// general functions :
int init();
int init_ecran(screen *ecran); 
int init_bg(menu *win);
int init_button(menu *win);
void change(image *img, SDL_Event event);// change the image (hover)
int click(image *img, SDL_Event event); // 1:not clicked , 2:clicked
void screen_affichage(menu win, screen ecr); 
void quit(menu *win, screen *ecr); // librerer
int start(menu win, screen *ecr); // the main function

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


#endif
