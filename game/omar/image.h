#ifndef image_H
#define image_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_W 1083
#define SCREEN_H 500

typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	Mix_Chunk *wav;
	TTF_Font *police;
}screen;

typedef struct{
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Surface *img;
	int hidden;
}image2;

void initImage(image2 *pic, char path[], int x, int y, int hidden);
void afficher_omar(image2 p, SDL_Surface **screen);
void liberer (image2 picture);
int joueur(screen scr);

#endif
