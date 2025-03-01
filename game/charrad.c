#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "head.h"
#include <stdio.h>



// the function to open the window
int menu_option(screen *scr){

    // Chargement des ressources
    SDL_Surface* background = load_image("./res-charrad/bg3.png");

    if(!background) {
        cleanup_resources(background,NULL,0);
        return 1;
    }

    // Création des boutons
    Button2 buttons[5];
    create_buttons(buttons);

    // Variables de contrôle
    int quitter=1;
    int volume=50;
    int fullscr=0;
    SDL_Color textColor={255, 255, 255}; // Blanc

    SDL_Rect posecranimg={0, 0, 800, 600};


    // Boucle principale
    while (quitter != 0 && quitter != 7){
        SDL_Event event;
	//SDL_Delay(2000);
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
                            handle_button_click(&buttons[i],&quitter,&volume,scr->ecran,&fullscr,scr->wav);
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym==SDLK_ESCAPE){
                        quitter=0;
                    }
		     handle_key_click(&quitter,&volume,scr->ecran,&fullscr,event);
                    break;
            }
        }

        // Rendu principal
        main_game_loop(scr->ecran,background,posecranimg,buttons,scr->police,scr->police,scr->mus,&quitter,&volume,&fullscr,textColor);
    }

    // Nettoyage des ressources
    cleanup_resources(background,buttons,4);
    scr->fullscr = fullscr;
    return quitter;

}
//*********************************************

// Load an image
SDL_Surface* load_image(const char* filename) {
    SDL_Surface* loadedImage = IMG_Load(filename);
    if (!loadedImage) {
        printf("Failed to load image '%s': %s\n",filename, IMG_GetError());
    }
    return loadedImage;
}
//*********************************************

// Create buttons
void create_buttons(Button2* buttons) {
    buttons[0] = create_button(150, 180, 298, 107, "./res-charrad/button1.png", "./res-charrad/button1-2.png");
    buttons[1] = create_button(540, 195, 160, 82, "./res-charrad/exit.png", "./res-charrad/exit-2.png");
    buttons[2] = create_button(555, 400, 39, 40, "./res-charrad/up.png", "./res-charrad/up-2.png");
    buttons[3] = create_button(280, 400, 47, 40, "./res-charrad/down.png", "./res-charrad/down-2.png");
    buttons[4] = create_button(100, 100, 150, 60, "./res-charrad/initial-1.jpg", "./res-charrad/initial-2.jpg");
}
//*********************************************

// Create a button
Button2 create_button(int x, int y, int w, int h, const char* normalPath, char* hoverPath) {
    Button2 button;
    button.position.x = x;
    button.position.y = y;
    button.position.w = w;
    button.position.h = h;
    button.normalImage = IMG_Load(normalPath);
    button.hoverImage = IMG_Load(hoverPath);
    if(!button.normalImage){
	printf("failed to load image:%s\n",normalPath);
	}
     if(!button.hoverImage){
	printf("failed to load hover image:%s\n",hoverPath);
	}
    button.isActive = 0;
    return button;
}
//*********************************************

// Check if the mouse is over a button
int is_mouse_over_button(Button2* button, int mouseX, int mouseY) {
    return (mouseX >= button->position.x && mouseX <= button->position.x + button->position.w &&
            mouseY >= button->position.y && mouseY <= button->position.y + button->position.h);
}
//*********************************************

// Update button state based on mouse position
void update_button_state(Button2* button, int mouseX, int mouseY) {
    button->isActive = is_mouse_over_button(button, mouseX, mouseY);
}
//*********************************************

// Render a button
void render_button(SDL_Surface* screen, Button2* button) {
    // Declare a surface pointer for the image to render
    SDL_Surface* image = NULL;

    // Determine which image to render based on the button's active state
    if (button->isActive) {
        image = button->hoverImage; // Use hover image if the button is active
    } else {
        image = button->normalImage; // Use normal image otherwise
    }

    // Ensure the image is valid before rendering
    if (!image) {
        printf("Error: Button image is NULL. Cannot render button.\n");
        return;
    }

    // Render the button image at its position
    if (SDL_BlitSurface(image, NULL, screen, &button->position) < 0) {
        printf("Error rendering button: %s\n", SDL_GetError());
    }
}
//*********************************************

// Render text on the screen
void render_text(SDL_Surface* screen, const char* text, TTF_Font* font, SDL_Color color, SDL_Rect position) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (!textSurface) {
        printf("Failed to render text: %s\n", TTF_GetError());
        return;
    }
    SDL_BlitSurface(textSurface, NULL, screen, &position);
    SDL_FreeSurface(textSurface); // Free the text surface after rendering
}
//*********************************************


// Handle button click
void handle_button_click(Button2* button, int* quitter, int* volume, SDL_Surface* ecran, int* showWindowModeText, Mix_Chunk *wav) {

    if (button->position.x == 150 && button->position.y == 180 && *showWindowModeText == 0) {
        printf("full screen btn clicked!\n");
	Mix_PlayChannel(-1,wav,0);
        toggle_fullscreen(ecran);
        *showWindowModeText = 1;
    }else if (button->position.x == 100 && button->position.y == 100 && *showWindowModeText == 1) {
        printf("initial screen btn clicked!\n");
	Mix_PlayChannel(-1,wav,0);
        toggle_fullscreen(ecran);
        *showWindowModeText = 0;
    } else if (button->position.x == 540 && button->position.y == 195) {
        printf("return button clicked!\n");
	Mix_PlayChannel(-1,wav,0);
	*quitter = 7;
    } else if (button->position.x == 555 && button->position.y == 400) {
        printf("Volume Up button clicked!\n");
	Mix_PlayChannel(-1,wav,0);
        *volume = (*volume + 5 > 100) ? 100 : *volume + 5;
        Mix_VolumeMusic(*volume);
    } else if (button->position.x == 280 && button->position.y == 400) {
        printf("Volume Down button clicked!\n");
	Mix_PlayChannel(-1,wav,0);
        *volume = (*volume - 5 < 0) ? 0 : *volume - 5;
        Mix_VolumeMusic(*volume);
    }
}
//*********************************************

// Toggle fullscreen/windowed mode
void toggle_fullscreen(SDL_Surface* screen) {
    if (SDL_WM_ToggleFullScreen(screen) == 0) {
        printf("Failed to toggle fullscreen: %s\n", SDL_GetError());
    }
}
//*********************************************

// Main game loop function
void main_game_loop(SDL_Surface* ecran, SDL_Surface* image, SDL_Rect posecranimg, Button2* buttons, TTF_Font* font, TTF_Font* windowModeFont, Mix_Music* musique, int* quitter, int* volume, int* showWindowModeText, SDL_Color textColor ) {
    SDL_Rect windowModeTextPos = {3300, 425},  volumeLevelTextPos = {330, 400}; // Positions for texts
    char volumeLevelText[50]; // Buffer to hold volume level text

    // Render background
    SDL_BlitSurface(image, &posecranimg, ecran, NULL);

    // Render buttons
    for (int i = 0; i < 5; i++) {
	if ( (i == 0 && * showWindowModeText == 1) || (i == 4 && * showWindowModeText == 0) )
		buttons[i].isActive = 1;
	render_button(ecran, &buttons[i]);
    }

    // Render current volume level text
    snprintf(volumeLevelText, sizeof(volumeLevelText), "Volume: %d", *volume);
    render_text(ecran, volumeLevelText, windowModeFont, textColor, volumeLevelTextPos);

    SDL_Flip(ecran); // Update screen
}
//*********************************************

// Cleanup resources
void cleanup_resources(SDL_Surface* image, Button2* buttons, int buttonCount) {
    if (image) SDL_FreeSurface(image);
    for (int i = 0; i < buttonCount; i++) {
        if (buttons[i].normalImage) SDL_FreeSurface(buttons[i].normalImage);
        if (buttons[i].hoverImage) SDL_FreeSurface(buttons[i].hoverImage);
    }
}
//**********************************************

void handle_key_click(int* quitter, int* volume, SDL_Surface* ecran, int* showWindowModeText, SDL_Event event) {

    if (event.key.keysym.sym==SDLK_EQUALS ) {
        printf("Volume Up button clicked!\n");
        *volume = (*volume + 5 > 100) ? 100 : *volume + 5;
        Mix_VolumeMusic(*volume);
    } else if (event.key.keysym.sym==SDLK_MINUS ) {
        printf("Volume Down button clicked!\n");
        *volume = (*volume - 5 < 0) ? 0 : *volume - 5;
        Mix_VolumeMusic(*volume);
    }
}



