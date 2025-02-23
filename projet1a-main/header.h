#ifndef HEADER_H
#define HEADER_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

// Dimensions de l'écran
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


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





// Déclaration des variables globales
extern SDL_Surface *screen, *background;
extern TTF_Font *font;
extern char playerName[20];
extern int running;
extern Button btnValidate;
extern SDL_Rect inputBox;
extern SDL_Color boxColor, textColor;
extern int scoreCount;


// Déclaration des scores
extern Playerscore topScores[3];
extern int scoreCount;
extern int showScores;



// Fonctions
SDL_Surface* loadImage(const char *filename);
void initSDL();
void renderText(const char *text, int x, int y);
void renderMenu();
int handleInput(SDL_Event event, Playerscore topScores[], int scoreCount);
void cleanUp();


void renderTopScores(SDL_Surface *screen, SDL_Surface *background, TTF_Font *font, Playerscore topScores[], int count);

#endif
