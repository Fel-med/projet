#include "head.h"
#include <stdio.h>

int main(int argc,char* argv[]) {
    if (init_sdl()!=0) {
        return 1;
    }

    // Création de la fenêtre
    SDL_Surface* ecran=create_window(862,619,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(!ecran)return 1;

    // Chargement des ressources
    SDL_Surface* background=load_image("bg3.png");
    Mix_Music* musique=load_music("music.mp3");
    TTF_Font* font=load_font("font.ttf",24);

    if(!background || !musique || !font) {
        cleanup_resources(background,musique,font,NULL,0);
        return 1;
    }

    // Lancement de la musique
    Mix_PlayMusic(musique,-1);

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
                            handle_button_click(&buttons[i],&quitter,&volume,ecran,&showWindowModeText);
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
        main_game_loop(ecran,background,posecranimg,buttons,font,font,musique,&quitter,&volume,&showWindowModeText,textColor);
    }

    // Nettoyage des ressources
    cleanup_resources(background,musique,font,buttons,4);

    return 0;
}
