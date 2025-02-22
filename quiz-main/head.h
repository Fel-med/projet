#ifndef HEAD_H
#define HEAD_H	


#define MAX_QUESTION 256

typedef struct {
    char question[MAX_QUESTION];
    char choix1[50];
    char choix2[50];
    char choix3[50];
    char choix4[50];
    int reponse;  // Numéro de la réponse correcte (1-4)
} question;


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
	question question;
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
void afficher_question(SDL_Surface *win, TTF_Font *font, question q);
void charger_questions(const char *fichier, question questions[], int *nb_questions);
int lancer_quiz(SDL_Surface *win, TTF_Font *font, question questions[], int nb_questions);
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
