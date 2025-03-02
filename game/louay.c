#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"


int saisir_nom(screen scr, char playerName[]){

SDL_Surface *bg = NULL;


// Bouton Valider uniquement
Button btnValidate = {{100, 150, 75, 25}, NULL, NULL, 0}; // Taille réduite

// Boîte blanche pour la saisie du nom
SDL_Rect inputBox = {320, 230, 350, 70}; // Position et taille de la boîte
SDL_Color boxColor = {255, 255, 255};   // Blanc
SDL_Color textColor = {0, 0, 0};        // Noir (pour le texte)



int scoreCount = 3;
int count=3;

init1(&bg, &btnValidate);
int choix = -1;

SDL_Event event;

while (choix == -1) {
    while (SDL_PollEvent(&event)) {
        choix = handleInput(event,playerName,&btnValidate,scr.wav);
    }

    renderMenu(&scr, textColor, inputBox,  boxColor, bg, btnValidate, playerName);

    SDL_Flip(scr.ecran);

    SDL_Delay(16);
}

    cleanUp(&bg, &btnValidate);
    return choix;


}
//*********************************************************************************

int top_scores(screen scr, char playerName[]){

SDL_Surface *bg = NULL;


// Initialisation des scores
Playerscore topScores[3] = {
    {"", 0},
    {"", 0},
    {"", 0}  // Le joueur entré sera ici
};


charger(topScores);


// Boutons
Button btnValidate1 = {{100, 150, 131, 38}, NULL, NULL, 0}; // Taille réduite
Button btnValidate2 = {{165, 150, 131, 38}, NULL, NULL, 0}; // Taille réduite



int scoreCount = 3;
int count=3;

init2(&bg, &btnValidate1, &btnValidate2);

SDL_Event event;
int choix = -1;

while (choix == -1) {
    while (SDL_PollEvent(&event)) {
        choix = handleInput2(event,&btnValidate1,&btnValidate2,scr.wav);
    }

renderTopScores(&scr,bg,scr.police,topScores,count,btnValidate1,btnValidate2); // Afficher les scores

    SDL_Flip(scr.ecran);

    SDL_Delay(16);
}

    cleanUp(&bg, &btnValidate1);
    if (btnValidate2.image) SDL_FreeSurface(btnValidate2.image);
    if (btnValidate2.hoverImage) SDL_FreeSurface(btnValidate2.hoverImage);
    
    return choix;


}
//*********************************************************************************









//The functions:
void renderMenu(screen *scr, SDL_Color textColor, SDL_Rect inputBox, SDL_Color boxColor, SDL_Surface *bg, Button btnValidate, char playerName[]) {
    int count =3;
    SDL_BlitSurface(bg, NULL, scr->ecran, NULL);

       // Dessiner la boîte blanche
        SDL_Surface *whiteBox = SDL_CreateRGBSurface(SDL_SWSURFACE, inputBox.w, inputBox.h, 32, 0, 0, 0, 0);
        SDL_FillRect(whiteBox, NULL, SDL_MapRGB((scr->ecran)->format, 255, 255, 255)); // Remplir en blanc
        SDL_BlitSurface(whiteBox, NULL, scr->ecran, &inputBox);
        SDL_FreeSurface(whiteBox);

        // Afficher le texte "Pseudo" à gauche de la boîte blanche
        SDL_Surface *pseudoText = TTF_RenderText_Blended(scr->police, "Name:", textColor);
        if (pseudoText) {
            SDL_Rect pseudoPos = {inputBox.x - pseudoText->w - 10, inputBox.y + (inputBox.h - pseudoText->h) / 2}; // Aligné verticalement
            SDL_BlitSurface(pseudoText, NULL, scr->ecran, &pseudoPos);
            SDL_FreeSurface(pseudoText);
        }

        // Afficher le texte du joueur dans la boîte
        if (strlen(playerName) > 0) {
            SDL_Surface *textSurface = TTF_RenderText_Blended(scr->police, playerName, textColor);
        if (textSurface) {
            SDL_Rect textPos = {inputBox.x + 5, inputBox.y + (inputBox.h - textSurface->h) / 2}; // Centré verticalement
            SDL_BlitSurface(textSurface, NULL, scr->ecran, &textPos);
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
        SDL_BlitSurface(btnValidateImg, NULL, scr->ecran, &destValidate);
}
//*********************************************************************************

//returned : 0->quitter, 1->entre ou valider ou hit the key "enter", 2->nothing
int handleInput(SDL_Event event, char playerName[], Button *btnValidate, Mix_Chunk *wav) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) return 0;
	if(event.key.keysym.sym == SDLK_RETURN){
		SDL_PollEvent(&event);
		while (event.type != SDL_KEYUP){
		SDL_PollEvent(&event);
		SDL_Delay(20);
		}
		return 4;
	}
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

        btnValidate->hovered = (x > btnValidate->rect.x &&
                               x < btnValidate->rect.x + btnValidate->rect.w &&
                               y > btnValidate->rect.y &&
                               y < btnValidate->rect.y + btnValidate->rect.h);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (btnValidate->hovered) {
		Mix_PlayChannel(-1,wav,0);
		SDL_PollEvent(&event);
		while (event.type != SDL_MOUSEBUTTONUP){
			SDL_PollEvent(&event);
			SDL_Delay(20);
		}
		return 4;
        }
    }
    return -1;
}

//returned : 0->quitter, 1->return ou hit the key "enter", 2->nothing, 3->enigme
int handleInput2(SDL_Event event, Button *btnValidate1, Button *btnValidate2, Mix_Chunk *wav) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) return 0;
    if (event.type == SDL_KEYDOWN) 
	if (event.key.keysym.sym == SDLK_e) return 5;
    if (event.type == SDL_MOUSEMOTION) {
        int x = event.motion.x;
        int y = event.motion.y;

        	btnValidate1->hovered = (x > btnValidate1->rect.x &&
                               	x < btnValidate1->rect.x + btnValidate1->rect.w &&
                               	y > btnValidate1->rect.y &&
                               	y < btnValidate1->rect.y + btnValidate1->rect.h);

		btnValidate2->hovered = (x > btnValidate2->rect.x &&
                               	x < btnValidate2->rect.x + btnValidate2->rect.w &&
                               	y > btnValidate2->rect.y &&
                               	y < btnValidate2->rect.y + btnValidate2->rect.h);
        }
    
    if (event.type == SDL_MOUSEBUTTONDOWN) {
	if (btnValidate1->hovered){
		Mix_PlayChannel(-1,wav,0);
		SDL_PollEvent(&event);
		while (event.type != SDL_MOUSEBUTTONUP){
			SDL_PollEvent(&event);
			SDL_Delay(20);
		}
		return  7; //button return
	}
	else if (btnValidate2->hovered){
		Mix_PlayChannel(-1,wav,0);
		SDL_PollEvent(&event);
		while (event.type != SDL_MOUSEBUTTONUP){
			SDL_PollEvent(&event);
			SDL_Delay(20);
		}
		return 0; //button quitter
	}
    }
    return -1;
}
//*********************************************************************************

void renderText(const char *text, int x, int y, screen *scr, SDL_Color textColor) {
    if (strlen(text) == 0) return;
    SDL_Surface *message = TTF_RenderText_Blended(scr->police, text, textColor);
    if (!message) {
        printf("ERROR 13 : %s\n", TTF_GetError());
        return;
    }
    SDL_Rect dest = {x, y, 0, 0};
    SDL_BlitSurface(message, NULL, scr->ecran, &dest);
    SDL_FreeSurface(message);
}
//*********************************************************************************

void init1(SDL_Surface **bg, Button *btnValidate) {
    

    SDL_EnableUNICODE(1);

    *bg = loadImageBMP("./res-louay/bg.bmp");
    btnValidate->image = loadImage("./res-louay/valid-1.tga");
    btnValidate->hoverImage = loadImage("./res-louay/valid-2.tga");

    if (!*bg || !btnValidate->image || !btnValidate->hoverImage) {
        printf("ERROR 14: Une ou plusieurs images n'ont pas été chargées correctement.\n");
        exit(1);
    }

    // Position du bouton en bas à droite
    btnValidate->rect.x = SCREEN_WIDTH - btnValidate->rect.w - 200;
    btnValidate->rect.y = SCREEN_HEIGHT - btnValidate->rect.h - 80;
}
//*********************************************************************************


void init2(SDL_Surface **bg, Button *btnValidate1, Button *btnValidate2) {
    

    SDL_EnableUNICODE(1);

    *bg = loadImage("./res-louay/bg.bmp");


    btnValidate1->image = loadImage("./res-louay/retur-1.tga");
    btnValidate1->hoverImage = loadImage("./res-louay/retur-2.tga");

    btnValidate2->image = loadImage("./res-louay/quit-1.tga");
    btnValidate2->hoverImage = loadImage("./res-louay/quit-2.tga");

    if (!*bg || !btnValidate1->image || !btnValidate1->hoverImage || !btnValidate2->image || !btnValidate2->hoverImage) {
        printf("ERROR 15: Une ou plusieurs images n'ont pas été chargées correctement.\n");
        exit(1);
    }

    // Position du bouton return (2) en bas à droite
    btnValidate1->rect.x = SCREEN_WIDTH - btnValidate1->rect.w - 135;
    btnValidate1->rect.y = SCREEN_HEIGHT - btnValidate1->rect.h - 80;
    // Position du bouton quit (2) en bas à droite
    btnValidate2->rect.x = SCREEN_WIDTH - btnValidate2->rect.w - 280;
    btnValidate2->rect.y = SCREEN_HEIGHT - btnValidate2->rect.h - 80;
}
//*********************************************************************************

SDL_Surface* loadImage(const char *filename) {
    SDL_Surface *loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        printf("ERROR 16: Impossible de charger %s : %s\n", filename, IMG_GetError());
        return NULL;
    }
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}
//*********************************************************************************

SDL_Surface* loadImageBMP(const char *filename) {
    SDL_Surface *loadedImage = SDL_LoadBMP(filename);
    if (!loadedImage) {
        printf("ERROR 17: Impossible de charger %s : %s\n", filename, IMG_GetError());
        return NULL;
    }
    SDL_Surface *optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    SDL_FreeSurface(loadedImage);
    return optimizedImage;
}
//*********************************************************************************

// Nettoyage des ressources
void cleanUp(SDL_Surface **bg, Button *btnValidate) {
    if (*bg) SDL_FreeSurface(*bg);
    if (btnValidate->image) SDL_FreeSurface(btnValidate->image);
    if (btnValidate->hoverImage) SDL_FreeSurface(btnValidate->hoverImage);
}
//*********************************************************************************

void quit(screen *scr){

	if (scr->police) TTF_CloseFont(scr->police);
	if (scr->mus) Mix_FreeMusic(scr->mus);
	if (scr->mus2) Mix_FreeMusic(scr->mus2);
	if (scr->wav) Mix_FreeChunk(scr->wav);

	SDL_CloseAudio();
    	TTF_Quit();
	SDL_Quit();

}
//*********************************************************************************

void renderTopScores(screen *scr, SDL_Surface *background, TTF_Font *font, Playerscore topScores[], int count, Button btnValidate1, Button btnValidate2) {
    SDL_Color orange = {0, 0, 0}; // Couleur orange
    SDL_Color white = {255, 255, 255}; // Couleur pour le titre

    // Afficher l'arrière-plan
    SDL_BlitSurface(background, NULL, scr->ecran, NULL);


    // Position du premier score
    SDL_Rect scorePos = {(scr->ecran)->w / 2 - 100, 200}; // Centré horizontalement

    for (int i = 0; i < count; i++) {
        char scoreText[50];
        sprintf(scoreText, "%d. %s - %d", i + 1, topScores[i].name, topScores[i].score);
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, scoreText, orange);
        if (textSurface) {
            SDL_BlitSurface(textSurface, NULL, scr->ecran, &scorePos);
            SDL_FreeSurface(textSurface);
        }
        scorePos.y += 40; // Espacement entre les scores
    }

	SDL_Rect destValidate1 = {
            btnValidate1.rect.x,
            btnValidate1.rect.y,
            btnValidate1.rect.w,
            btnValidate1.rect.h
        };
	SDL_Surface *btnValidateImg1 = btnValidate1.hovered ? btnValidate1.hoverImage : btnValidate1.image;
        SDL_BlitSurface(btnValidateImg1, NULL, scr->ecran, &destValidate1);


	SDL_Rect destValidate2 = {
            btnValidate2.rect.x,
            btnValidate2.rect.y,
            btnValidate2.rect.w,
            btnValidate2.rect.h
        };
	SDL_Surface *btnValidateImg2 = btnValidate2.hovered ? btnValidate2.hoverImage : btnValidate2.image;
        SDL_BlitSurface(btnValidateImg2, NULL, scr->ecran, &destValidate2);

}
//*********************************************************************************

void charger(Playerscore *topScores){

FILE *f = fopen("file.bin","rb");
donne t[100], tmp;
int n=0, j, max;

while(fread(t+n, sizeof(donne), 1, f)==1) n++;


for(int i=0 ; i<n ; i++){
	max = i;
	for(j=i+1 ; j<n; j++){
		if (t[max].score < t[j].score) max = j;
	}
	tmp = t[i];
	t[i] = t[max];
	t[max] = tmp;
}


topScores[0].score = t[0].score;
strcpy(topScores[0].name , t[0].user_name);

topScores[1].score = t[1].score;
strcpy(topScores[1].name , t[1].user_name);

topScores[2].score = t[2].score;
strcpy(topScores[2].name , t[2].user_name);


fclose(f);

}




