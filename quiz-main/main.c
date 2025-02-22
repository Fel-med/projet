
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"


int main()
{

menu win1, win2;


// first window
init_val_1(&win1);


// second window
init_val_2(&win2);

start(win1);

 SDL_Surface *screen;
    TTF_Font *font;
    question questions[10];
    int nb_questions;
    init_SDL();

    // Création de la fenêtre
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    if (!screen) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("Quiz SDL", NULL);

    // Chargement de la police
    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Erreur TTF: %s\n", TTF_GetError());
        return 1;
    }

    // Charger les questions
    charger_questions("quiz.txt", questions, &nb_questions);

    // Lancer le quiz
    int score = lancer_quiz(screen, font, questions, nb_questions);

    // Afficher le score
    printf("Votre score: %d/%d\n", score, nb_questions);

    // Libération des ressources
    TTF_CloseFont(font);
    SDL_Quit();
    return 0;


puts("\n GOOD BYE o/a\n");

return 0;

}
