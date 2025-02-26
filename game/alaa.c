#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"


int menu_principale(screen scr){


    // Chargement des ressources
    SDL_Surface* background = load_image("./res-alaa/bg.png");

	SDL_Surface *logo = load_image("./res-alaa/logo.png");
	SDL_Rect pos_logo;
	pos_logo.x = 560;
	pos_logo.y = 10;

    if(!background) {
        cleanup_resources(background,NULL,0);
        return 1;
    }

    // Création des boutons
    Button2 buttons[5];
    create_buttons2(buttons);

    // Variables de contrôle
    int quitter=-1;
    int volume=50;
    int showWindowModeText=0;
    SDL_Color textColor={255, 255, 255}; // Blanc

    SDL_Rect posecranimg={0, 0, 800, 600};


    // Boucle principale
    while (quitter==-1){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    quitter=0;
                    break;
                case SDL_MOUSEMOTION:
                    for (int i=0; i<5;i++){
                        update_button_state(&buttons[i],event.motion.x,event.motion.y);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i=0;i<5;i++){
                        if (is_mouse_over_button(&buttons[i],event.button.x,event.button.y)) {
                            handle_button_click2(&buttons[i],&quitter,scr.ecran);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym==SDLK_ESCAPE){
                        quitter=0;
                    }
                    break;
            }
        }

        // Rendu principal
        main_game_loop2(scr.ecran,background,posecranimg,buttons,scr.police,&quitter,textColor,logo,pos_logo);
    }

    // Nettoyage des ressources
    cleanup_resources(background,buttons,5);

    return quitter;

}
//*********************************************

void create_buttons2(Button2 * buttons) {
    buttons[0] = create_button(100, 400, 298, 107, "./res-alaa/history-1.png", "./res-alaa/history-2.png");
    buttons[1] = create_button(100, 100, 160, 82, "./res-alaa/jouer-1.png", "./res-alaa/jouer-2.png");
    buttons[2] = create_button(100, 300, 39, 40, "./res-alaa/meui-1.png", "./res-alaa/meui-2.png");
    buttons[3] = create_button(100, 200, 47, 40, "./res-alaa/option-1.png", "./res-alaa/option-2.png");
    buttons[4] = create_button(550, 400, 47, 40, "./res-alaa/quitter-1.png", "./res-alaa/quitter-2.png");
}
//*********************************************

// Main game loop function
void main_game_loop2(SDL_Surface* ecran, SDL_Surface* image, SDL_Rect posecranimg, Button2* buttons, TTF_Font* font, int* quitter, SDL_Color textColor, SDL_Surface *logo, SDL_Rect pos_logo) {

    // Render background
    SDL_BlitSurface(image, &posecranimg, ecran, NULL);
    SDL_BlitSurface(logo, NULL, ecran, &pos_logo);

    // Render buttons
    for (int i = 0; i < 5; i++) 
        render_button(ecran, &buttons[i]);

    SDL_Flip(ecran); // Update screen
}





  /* buttons[0] = create_button(100, 400, 298, 107, "./res-alaa/history-1.png", "./res-alaa/history-2.png");
    buttons[1] = create_button(100, 100, 160, 82, "./res-alaa/jouer-1.png", "./res-alaa/jouer-2.png");
    buttons[2] = create_button(100, 300, 39, 40, "./res-alaa/meui-1.png", "./res-alaa/meui-2.png");
    buttons[3] = create_button(100, 200, 47, 40, "./res-alaa/option-1.png", "./res-alaa/option-2.png");
    buttons[4] = create_button(550, 400, 47, 40, "./res-alaa/quitter-1.png", "./res-alaa/quitter-2.png");*/

//*********************************************

// Handle button click
void handle_button_click2(Button2* button, int* quitter, SDL_Surface* ecran) {

    if (button->position.x == 100 && button->position.y == 400) {
        printf("history btn clicked!\n");
        *quitter = 4;
    } else if (button->position.x == 100 && button->position.y == 100) {
        printf("jouer btb clicked!\n");
        *quitter = 1;
    } else if (button->position.x == 100 && button->position.y == 300) {
        printf("meui btn clicked!\n");
        *quitter = 3;
    } else if (button->position.x == 100 && button->position.y == 200) {
        printf("option btn button clicked!\n");
        *quitter = 2;
    } else if (button->position.x == 550 && button->position.y == 400) {
        printf("quitter btn clicked!\n");
        *quitter = 0;
    }
}


