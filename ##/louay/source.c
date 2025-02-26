#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_ttf.h> 

SDL_Surface *screen = NULL, *background = NULL;
TTF_Font *font = NULL;
char playerName[20] = "";
int running = 1;

// Initialisation des scores
Playerscore topScores[3] = {
    {"Player1", 95},
    {"Player2", 88},
    {"player3", 0}  // Le joueur entré sera ici
};

int scoreCount = 3; 
int showScores = 0;

// Bouton Valider uniquement
Button btnValidate = {{100, 150, 75, 25}, NULL, NULL, 0}; // Taille réduite

// Boîte blanche pour la saisie du nom
SDL_Rect inputBox = {300, 200, 200, 40}; // Position et taille de la boîte
SDL_Color boxColor = {255, 255, 255};   // Blanc
SDL_Color textColor = {0, 0, 0};        // Noir (pour le texte)

// Fonction pour charger une image avec vérification
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

// Initialisation de SDL
void initSDL() {
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

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Erreur SDL_SetVideoMode : %s\n", SDL_GetError());
        exit(1);
    }

    font = TTF_OpenFont("arial.ttf", 40);
    if (!font) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        exit(1);
    }

    SDL_EnableUNICODE(1);

    background = loadImage("island.jpg");
    btnValidate.image = loadImage("validate.jpg");
    btnValidate.hoverImage = loadImage("12.jpg");

    if (!background || !btnValidate.image || !btnValidate.hoverImage) {
        printf("Erreur: Une ou plusieurs images n'ont pas été chargées correctement.\n");
        exit(1);
    }

    // Position du bouton en bas à droite
    btnValidate.rect.x = SCREEN_WIDTH - btnValidate.rect.w - 95;
    btnValidate.rect.y = SCREEN_HEIGHT - btnValidate.rect.h - 110;
}

// Affichage du texte
void renderText(const char *text, int x, int y) {
    if (strlen(text) == 0) return;
    SDL_Surface *message = TTF_RenderText_Blended(font, text, textColor);
    if (!message) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }
    SDL_Rect dest = {x, y, 0, 0};
    SDL_BlitSurface(message, NULL, screen, &dest);
    SDL_FreeSurface(message);
}

void renderTopScores(SDL_Surface *screen, SDL_Surface *background, TTF_Font *font, Playerscore topScores[], int count) {
    SDL_Color orange = {0, 0, 0}; // Couleur orange
    SDL_Color white = {255, 255, 255}; // Couleur pour le titre

    // Afficher l'arrière-plan
    SDL_BlitSurface(background, NULL, screen, NULL);

    // Afficher le titre "Top Scores"
    SDL_Rect titlePos = {screen->w / 2 - 50, 50}; // Centré horizontalement
    SDL_Surface *titleSurface = TTF_RenderText_Blended(font, "Top Scores", white);
    if (titleSurface) {
        SDL_BlitSurface(titleSurface, NULL, screen, &titlePos);
        SDL_FreeSurface(titleSurface);
    }

    // Position du premier score
    SDL_Rect scorePos = {screen->w / 2 - 100, 100}; // Centré horizontalement

    for (int i = 0; i < count; i++) {
        char scoreText[50];
        sprintf(scoreText, "%d. %s - %d", i + 1, topScores[i].name, topScores[i].score);
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, scoreText, orange);
        if (textSurface) {
            SDL_BlitSurface(textSurface, NULL, screen, &scorePos);
            SDL_FreeSurface(textSurface);
        }
        scorePos.y += 40; // Espacement entre les scores
    }

    SDL_Flip(screen); // Mettre à jour l'affichage
}


void renderMenu(Playerscore topScores[], int scoreCount) {
    int count =3;
	printf("hi");
     renderTopScores(screen,background,font,topScores,count);
    SDL_BlitSurface(background, NULL, screen, NULL);

    if (!showScores) {
        // Dessiner la boîte blanche
        SDL_Surface *whiteBox = SDL_CreateRGBSurface(SDL_SWSURFACE, inputBox.w, inputBox.h, 32, 0, 0, 0, 0);
        SDL_FillRect(whiteBox, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // Remplir en blanc
        SDL_BlitSurface(whiteBox, NULL, screen, &inputBox);
        SDL_FreeSurface(whiteBox);

        // Afficher le texte "Pseudo" à gauche de la boîte blanche
        SDL_Surface *pseudoText = TTF_RenderText_Blended(font, "Pseudo:", textColor);
        if (pseudoText) {
            SDL_Rect pseudoPos = {inputBox.x - pseudoText->w - 10, inputBox.y + (inputBox.h - pseudoText->h) / 2}; // Aligné verticalement
            SDL_BlitSurface(pseudoText, NULL, screen, &pseudoPos);
            SDL_FreeSurface(pseudoText);
        }

        // Afficher le texte du joueur dans la boîte
        if (strlen(playerName) > 0) {
            SDL_Surface *textSurface = TTF_RenderText_Blended(font, playerName, textColor);
            if (textSurface) {
                SDL_Rect textPos = {inputBox.x + 5, inputBox.y + (inputBox.h - textSurface->h) / 2}; // Centré verticalement
                SDL_BlitSurface(textSurface, NULL, screen, &textPos);
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
        SDL_BlitSurface(btnValidateImg, NULL, screen, &destValidate);
    } else {
        // Afficher les meilleurs scores
       renderTopScores(screen,background,font,topScores,count);
    }

    SDL_Flip(screen);
}

// Gestion des entrées utilisateur
int handleInput(SDL_Event event, Playerscore topScores[], int scoreCount) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) return 0;
    if (event.type == SDL_KEYDOWN) {
	//if () return 0;
        if (event.key.keysym.sym == SDLK_RETURN) {
            printf("Nom du joueur validé : %s\n", playerName);
            showScores = 1; // Activer l'affichage des scores
            renderMenu(topScores, scoreCount); // Rafraîchir l'écran avec les scores
        } else if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(playerName) > 0) {
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
	    strncpy(topScores[3].name,playerName,19);
	    topScores[3].score=(rand()%100)+1;
            showScores = 1; // Activer l'affichage des scores
            renderMenu(topScores, scoreCount); // Rafraîchir l'écran avec les scores
        }
    }
	return 1;
}


// Nettoyage des ressources
void cleanUp() {
    if (background) SDL_FreeSurface(background);
    if (btnValidate.image) SDL_FreeSurface(btnValidate.image);
    if (btnValidate.hoverImage) SDL_FreeSurface(btnValidate.hoverImage);
    if (font) TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}



//players'sscore

