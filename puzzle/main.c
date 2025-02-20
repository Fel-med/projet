#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int main() {
    text mes;
    mes.text = NULL;
    bg img;
    menu win;
    screen ecr;

    SDL_Event event;
    int quitter = 1, n, x, y, valid_move;

    printf("Choose difficulty level:\n1. Easy (3x3)\n2. Medium (4x4)\n3. Hard (5x5)\n");
    int choice;
    scanf("%d", &choice);

    squ **M;
    int grid_size = n * tile_size, start_x, start_y; 
    if (choice == 1) {
        n = 3;
	start_x = (width_scr - tile_size) / 2 - 90;
	start_y = (hight_scr - tile_size) / 2 - 80;
    } else if (choice == 2) {
        n = 4;
	start_x = (width_scr - tile_size) / 2 - 155;
	start_y = (hight_scr - tile_size) / 2 - 140;
    } else {
        n = 5;
	start_x = (width_scr - tile_size) / 2 - 210;
	start_y = (hight_scr - tile_size) / 2 - 200;
    }

    M = (squ **)malloc(n * sizeof(squ *));
    for (int i = 0; i < n; i++) {
        M[i] = (squ *)malloc(n * sizeof(squ));
    }

    if (choice == 1) init_level_1(&n, M);
    else if (choice == 2) init_level_2(&n, M);
    else init_level_3(&n, M);

    if (init()) {
        printf("SDL Initialization Error\n");
        return 1;
    }

    if (init_ecran(&ecr)) {
        printf("ecran Initialization Error\n");
        return 1;
    }

    if (init_bg(&win)) {
        printf("Background Initialization Error\n");
        return 1;
    }


    while (quitter) {
        screen_affichage(win, ecr, M, n, grid_size, start_x, start_y);

        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quitter = 0;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) quitter = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
		Mix_PlayChannel(-1,ecr.wav,0);
                x = (event.button.y - start_y ) / tile_size;
                y = (event.button.x - start_x ) / tile_size ;

		if (x<n && x>=0 && y<n && y>=0){

                	valid_move = valid(n, M, x, y, event);
                	if (valid_move) {
                    	mov(n, M, x, y, valid_move);
                    	if (winn(n, M)) {
                        	printf("You won!\n");
                        	quitter = 0;
                    	}
                	}
		}
                break;
        }
    }

    quit(&win, &ecr);

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);

    return 0;
}
