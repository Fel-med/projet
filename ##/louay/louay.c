#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_ttf.h> 


int saisir_nom(screen scr){

SDL_Surface *bg = NULL;


// Initialisation des scores
Playerscore topScores[3] = {
    {"Player1", 95},
    {"Player2", 88},
    {"player3", 0}  // Le joueur entré sera ici
};


// Bouton Valider uniquement
Button btnValidate = {{100, 150, 75, 25}, NULL, NULL, 0}; // Taille réduite

// Boîte blanche pour la saisie du nom
SDL_Rect inputBox = {300, 200, 200, 40}; // Position et taille de la boîte
SDL_Color boxColor = {255, 255, 255};   // Blanc
SDL_Color textColor = {0, 0, 0};        // Noir (pour le texte)



char playerName[20] = "";
int scoreCount = 3;
int count=3;
int running = 1;

initSDL(&scr, &bg, &btnValidate);

SDL_Event event;

while (running) {
    while (SDL_PollEvent(&event)) {
        running = handleInput(event);
    }

    //renderTopScores(screen,background,font,topScores,count); // Afficher les scores
    renderMenu(&scr, textColor, inputBox, boxColor, bg, btnValidate, playerName); // Afficher l'écran de saisie

    SDL_Flip(scr);

    SDL_Delay(16);
}

    cleanUp(&bg, &btnValidate, &scr);
    return 0;


}





//The functions:
void renderMenu(SDL_Surface *scr, SDL_Color textColor, SDL_Rect inputBox, SDL_Color boxColor, SDL_Surface bg, button btnValidate, char playerName[]) {
    int count =3;
    SDL_BlitSurface(bg, NULL, *scr, NULL);

        // Dessiner la boîte blanche
        SDL_Surface *whiteBox = SDL_CreateRGBSurface(SDL_SWSURFACE, inputBox.w, inputBox.h, 32, 0, 0, 0, 0);
        SDL_FillRect(whiteBox, NULL, SDL_MapRGB(scr->format, 255, 255, 255)); // Remplir en blanc
        SDL_BlitSurface(whiteBox, NULL, scr, &inputBox);
        SDL_FreeSurface(whiteBox);

        // Afficher le texte "Pseudo" à gauche de la boîte blanche
        SDL_Surface *pseudoText = TTF_RenderText_Blended(scr->police, "Pseudo:", textColor);
        if (pseudoText) {
            SDL_Rect pseudoPos = {inputBox.x - pseudoText->w - 10, inputBox.y + (inputBox.h - pseudoText->h) / 2}; // Aligné verticalement
            SDL_BlitSurface(pseudoText, NULL, *scr, &pseudoPos);
            SDL_FreeSurface(pseudoText);
        }

        // Afficher le texte du joueur dans la boîte
        if (strlen(playerName) > 0) {
            SDL_Surface *textSurface = TTF_RenderText_Blended(scr->police, playerName, textColor);
            if (textSurface) {
                SDL_Rect textPos = {inputBox.x + 5, inputBox.y + (inputBox.h - textSurface->h) / 2}; // Centré verticalement
                SDL_BlitSurface(textSurface, NULL, *scr, &textPos);
                SDL_FreeSurface(textSurface);
            }
        }

        // Dessiner le bouton Valider
        SDL_Rect destValidate = {
            btnValidate.rect.x,
            btnValidate.rect.y,
            btnValidate.rect.w,
            btnValidate.rect.h
        };
SDL_Surface *btnValidateImg = btnValidate.hovered ? btnValidate.hoverImage : btnValidate.image;
        SDL_BlitSurface(btnValidateImg, NULL, *scr, &destValidate);
    
}









int handleInput(SDL_Event event) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN){
            	printf("Nom du joueur validé : %s\n", playerName);
		return 0;
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(playerName) > 0) {
            playerName[strlen(playerName) - 1] = '\0'; // Efface un caractère
        } else {
            char key = event.key.keysym.unicode;
            if (strlen(playerName) < 19 && key >= 32 && key <= 126) { // Limite à 19 caractères
                char tmp[2] = {key, '\0'};
                strncat(playerName, tmp, 1);
            }
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;

        btnValidate.hovered = (x > btnValidate.rect.x &&
                               x < btnValidate.rect.x + btnValidate.rect.w &&
                               y > btnValidate.rect.y &&
                               y < btnValidate.rect.y + btnValidate.rect.h);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (btnValidate.hovered) {
                printf("Nom du joueur validé : %s\n", playerName);
		return 0;
        }
    }
	return 1;
}



void renderText(const char *text, int x, int y, screen *scr, SDL_Color textColor) {
    if (strlen(text) == 0) return;
    SDL_Surface *message = TTF_RenderText_Blended(scr->police, text, textColor);
    if (!message) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }
    SDL_Rect dest = {x, y, 0, 0};
    SDL_BlitSurface(message, NULL, *scr, &dest);
    SDL_FreeSurface(message);
}



void initSDL(screen *scr, SDL_Surface *bg, button *btnValidate) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur IMG_Init : %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init : %s\n", TTF_GetError());
        exit(1);
    }

    scr->ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!scr->ecran) {
        printf("Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        exit(1);
    }

    scr->police = TTF_OpenFont("arial.ttf", 40);
    if (!font) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        exit(1);
    }

    SDL_EnableUNICODE(1);

    *bg = loadImage("island.jpg");
    btnValidate->image = loadImage("validate.jpg");
    btnValidate->hoverImage = loadImage("12.jpg");

    if (!background || !btnValidate.image || !btnValidate.hoverImage) {
        printf("Erreur: Une ou plusieurs images n'ont pas été chargées correctement.\n");
        exit(1);
    }

    // Position du bouton en bas à droite
    btnValidate.rect.x = SCREEN_WIDTH - btnValidate.rect.w - 95;
    btnValidate.rect.y = SCREEN_HEIGHT - btnValidate.rect.h - 110;
}


SDL_Surface* loadImage(const char *filename) {
    SDL_Surface *loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        printf("Erreur: Impossible de charger %s : %s\n", filename, IMG_GetError());
        return NULL;
    }
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}




// Nettoyage des ressources
void cleanUp(SDL_Surface *bg, button *btnValidate, screen *scr) {
    if (*bg) SDL_FreeSurface(*bg);
    if (btnValidate->image) SDL_FreeSurface(btnValidate->image);
    if (btnValidate->hoverImage) SDL_FreeSurface(btnValidate->hoverImage);
    if (scr->police) TTF_CloseFont(scr->police);
    TTF_Quit();
    SDL_Quit();
}



