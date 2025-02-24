#ifndef HEAD_H
#define HEAD_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

// Dimensions de l'écran
#define SCREEN_WIDTH 862
#define SCREEN_HEIGHT 619

// Structure pour un bouton
typedef struct {
    SDL_Rect position;
    SDL_Surface* normalImage;
    SDL_Surface* hoverImage;
    int isActive;
} Button;


typedef struct{
	SDL_Surface *ecran;
	Mix_Music *mus;
	Mix_Chunk *wav;
	TTF_Font *police;
}screen;

// the function to open the window
int menu_option(screen *scr);

// Fonctions d'initialisation
int init_sdl();
SDL_Surface* create_window(int width, int height, int bpp, Uint32 flags);
SDL_Surface* load_image(const char* filename);
Mix_Music* load_music(const char* filename);
TTF_Font* load_font(const char* filename,int size);
int init_ecran(screen *ecr);

// Fonctions pour les boutons
void create_buttons(Button* buttons);
Button create_button(int x,int y,int w,int h,const char* normalPath,char*hoverPath);
int is_mouse_over_button(Button* button,int mouseX,int mouseY);
void update_button_state(Button* button, int mouseX, int mouseY);
void render_button(SDL_Surface* screen,Button* button);
void handle_button_click(Button* button,int* quitter,int* volume,SDL_Surface* ecran,int* showWindowModeText);

// Affichage de texte
void render_text(SDL_Surface* screen,const char* text,TTF_Font* font,SDL_Color color,SDL_Rect position);

// Plein écran
void toggle_fullscreen(SDL_Surface* screen);

// Boucle principale
void main_game_loop(SDL_Surface* ecran,SDL_Surface* image,SDL_Rect posecranimg,Button* buttons, 
                    TTF_Font* font,TTF_Font* windowModeFont,Mix_Music* musique,int* quitter, 
                    int* volume,int* showWindowModeText,SDL_Color textColor);

// Nettoyage
void cleanup_resources(SDL_Surface* image, Button* buttons, int buttonCount);
void quit(screen *scr);

#endif
