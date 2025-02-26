#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "head.h"
#include <stdio.h>



// the function to open the window
int menu_option(screen *scr){

    // Chargement des ressources
    SDL_Surface* background = load_image("bg3.png");

    if(!background) {
        cleanup_resources(background,NULL,0);
        return 1;
    }

    // Création des boutons
    Button buttons[4];
    create_buttons(buttons);

    // Variables de contrôle
    int quitter=1;
    int volume=50;
    int showWindowModeText=0;
    SDL_Color textColor={255, 255, 255}; // Blanc

    SDL_Rect posecranimg={0, 0, 800, 600};


    // Boucle principale
    while (quitter){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    quitter=0;
                    break;
                case SDL_MOUSEMOTION:
                    for (int i=0; i<4;i++){
                        update_button_state(&buttons[i],event.motion.x,event.motion.y);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i=0;i<4;i++){
                        if (is_mouse_over_button(&buttons[i],event.button.x,event.button.y)) {
                            handle_button_click(&buttons[i],&quitter,&volume,scr->ecran,&showWindowModeText);
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
        main_game_loop(scr->ecran,background,posecranimg,buttons,scr->police,scr->police,scr->mus,&quitter,&volume,&showWindowModeText,textColor);
    }

    // Nettoyage des ressources
    cleanup_resources(background,buttons,4);

    return 0;

}
//*********************************************

int init_ecran(screen *ecr){
printf("\nScreen loading...");
fflush(stdout);

ecr->ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
if (ecr->ecran == NULL) {
	printf("\nERROR-3 :%s",SDL_GetError());
	return 1;
}

ecr->mus = Mix_LoadMUS("music.ogg");
if (ecr->mus == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}

ecr->police = TTF_OpenFont("arial.ttf", 40);
if (!ecr->police) {
        printf("Erreur TTF_OpenFont : %s\n", TTF_GetError());
        return 1;
    }

ecr->wav = Mix_LoadWAV("sound.wav");
if (ecr->wav == NULL) {
	printf("\nERROR-7 :%s",SDL_GetError());
	return 1;
}
return 0;
puts("\ndone");
}
//*********************************************

// Initialize SDL subsystems
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }
    return 0;
}
//*********************************************

// Create a window
SDL_Surface* create_window(int width, int height, int bpp, Uint32 flags) {
    SDL_Surface* screen = SDL_SetVideoMode(width, height, bpp, flags);
    if (!screen) {
        fprintf(stderr, "Failed to create window: %s.\n", SDL_GetError());
    }
    return screen;
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
void create_buttons(Button* buttons) {
    buttons[0] = create_button(150, 180, 298, 107, "./res-charrad/button1.png", "./res-charrad/button1-2.png");
    buttons[1] = create_button(540, 195, 160, 82, "./res-charrad/exit.png", "./res-charrad/exit-2.png");
    buttons[2] = create_button(555, 400, 39, 40, "./res-charrad/up.png", "./res-charrad/up-2.png");
    buttons[3] = create_button(280, 400, 47, 40, "./res-charrad/down.png", "./res-charrad/down-2.png");
}
//*********************************************

// Create a button
    Button create_button(int x, int y, int w, int h, const char* normalPath, char* hoverPath) {
    Button button;
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
int is_mouse_over_button(Button* button, int mouseX, int mouseY) {
    return (mouseX >= button->position.x && mouseX <= button->position.x + button->position.w &&
            mouseY >= button->position.y && mouseY <= button->position.y + button->position.h);
}
//*********************************************

// Update button state based on mouse position
void update_button_state(Button* button, int mouseX, int mouseY) {
    button->isActive = is_mouse_over_button(button, mouseX, mouseY);
}
//*********************************************

// Render a button
void render_button(SDL_Surface* screen, Button* button) {
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
void handle_button_click(Button* button, int* quitter, int* volume, SDL_Surface* ecran, int* showWindowModeText) {

    if (button->position.x + plus == 150 && button->position.y + plus == 180) {
        printf("full screen btn clicked!\n");
        toggle_fullscreen(ecran);
        *showWindowModeText = 1; // Show "Window Mode" text
    } else if (button->position.x + plus == 540 && button->position.y + plus == 195) {
        printf("Quit button clicked!\n");
        *quitter = 0; // Exit the program
    } else if (button->position.x + plus == 555 && button->position.y + plus == 400) {
        printf("Volume Up button clicked!\n");
        *volume = (*volume + 5 > 100) ? 100 : *volume + 5;
        Mix_VolumeMusic(*volume);
    } else if (button->position.x + plus == 280 && button->position.y + plus == 400) {
        printf("Volume Down button clicked!\n");
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
void main_game_loop(SDL_Surface* ecran, SDL_Surface* image, SDL_Rect posecranimg, Button* buttons, TTF_Font* font, TTF_Font* windowModeFont, Mix_Music* musique, int* quitter, int* volume, int* showWindowModeText, SDL_Color textColor ) {
    SDL_Rect windowModeTextPos = {3300, 425},  volumeLevelTextPos = {330, 400}; // Positions for texts
    char volumeLevelText[50]; // Buffer to hold volume level text

    // Render background
    SDL_BlitSurface(image, &posecranimg, ecran, NULL);

    // Render buttons
    for (int i = 0; i < 4; i++) {
        render_button(ecran, &buttons[i]);
    }

    // Render "Window Mode" text if the flag is set
    if (*showWindowModeText) {
        render_text(ecran, "Window Mode", windowModeFont, textColor, windowModeTextPos);
    }

    // Render current volume level text
    snprintf(volumeLevelText, sizeof(volumeLevelText), "Volume: %d", *volume);
    render_text(ecran, volumeLevelText, windowModeFont, textColor, volumeLevelTextPos);

    SDL_Flip(ecran); // Update screen
}
//*********************************************

// Cleanup resources
void cleanup_resources(SDL_Surface* image, Button* buttons, int buttonCount) {
    if (image) SDL_FreeSurface(image);
    for (int i = 0; i < buttonCount; i++) {
        if (buttons[i].normalImage) SDL_FreeSurface(buttons[i].normalImage);
        if (buttons[i].hoverImage) SDL_FreeSurface(buttons[i].hoverImage);
    }
}
//*********************************************

void quit(screen *scr){

	if (scr->police) TTF_CloseFont(scr->police);

	SDL_CloseAudio();
    	TTF_Quit();
	SDL_Quit();

}
