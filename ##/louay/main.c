#include <stdio.h>
#include <string.h>
#include "header.h" 


int main() {
SDL_Surface *screen = NULL, *background = NULL;
TTF_Font *font = NULL;
char playerName[20] = "";


int scoreCount = 3; 
int showScores = 0;
    int count=3;

    initSDL();

    SDL_Event event;
    int running = 1;
    while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        running = handleInput( event,topScores,scoreCount);
    }

    //renderTopScores(screen,background,font,topScores,count); // Afficher les scores
    renderMenu(); // Afficher l'écran de saisie

    SDL_Delay(16);
}

    cleanUp();
    return 0;
}


