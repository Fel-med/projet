#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"




int init_menu_puzzle(menu *win){
printf("\n***Background...");
fflush(stdout);

strcpy(win->bg.nom_img,"./puzzle/bg.bmp");
win->bg.img = SDL_LoadBMP(win->bg.nom_img);
win->bg.img = SDL_DisplayFormat(win->bg.img);
if (win->bg.img == NULL) {
	printf("\nERROR-5 :%s",SDL_GetError());
	return 1;
}

win->img1.img1 = IMG_Load("./puzzle/return-1.jpg");
win->img1.img = win->img1.img1;
win->img1.img2 = IMG_Load("./puzzle/return-2.jpg");
if (win->img1.img1 == NULL || win->img1.img2 == NULL || win->img1.img == NULL) {
	printf("\nERROR btn :%s",SDL_GetError());
	return 1;
}

win->img1.pos.h=(win->img1.img1)->h;
win->img1.pos.w=(win->img1.img1)->w;
win->img1.pos.x = SCREEN_WIDTH - 100;
win->img1.pos.y = SCREEN_HEIGHT - 100;
win->img1.click = 1;
win->img1.etat = 1;

return 0;
}
//*********************************************

void screen_affichage_puzzle(menu win, screen ecr, squ **M, int n, int grid_size, int start_x, int start_y){


    SDL_FillRect(ecr.ecran, NULL, SDL_MapRGB(ecr.ecran->format, 0, 0, 0));
    SDL_BlitSurface(win.bg.img, NULL, ecr.ecran, NULL);
    SDL_BlitSurface(win.img1.img, NULL, ecr.ecran, &(win.img1.pos));

    SDL_Rect tile_pos;  
    SDL_Surface *text_surf;  
    SDL_Color textColor = {255, 255, 255}; 
    SDL_Color col = {34, 139, 34} ;


    int screen_width = ecr.ecran->w;
    int screen_height = ecr.ecran->h;
    int total_size = tile_size * n;  

    start_x = (screen_width - total_size) / 2;
    start_y = (screen_height - total_size) / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tile_pos.x = start_x + j * tile_size;
            tile_pos.y = start_y + i * tile_size;
            tile_pos.w = tile_size; 
            tile_pos.h = tile_size;

            if (M[i][j].val != 0) {
                SDL_FillRect(ecr.ecran, &tile_pos, SDL_MapRGB(ecr.ecran->format, 139, 69, 19)); 

                char str[3];
                sprintf(str, "%d", M[i][j].val);

                text_surf = TTF_RenderText_Blended(ecr.police, str, textColor);

                SDL_Rect number_pos;
                number_pos.x = tile_pos.x + (tile_pos.w - text_surf->w) / 2;
                number_pos.y = tile_pos.y + (tile_pos.h - text_surf->h) / 2;

                SDL_BlitSurface(text_surf, NULL, ecr.ecran, &number_pos);

                SDL_FreeSurface(text_surf);
            }
        }
    }

    // Update the screen
    SDL_Flip(ecr.ecran);


}
//*********************************************

// Level 1: 3x3 Board (Easy)
void init_level_1(int *n, squ **M) {
    *n = 3; // Set size to 3x3
    M[0][0].val = 1;  M[0][1].val = 0;  M[0][2].val = 4;
    M[1][0].val = 2;  M[1][1].val = 5;  M[1][2].val = 3;
    M[2][0].val = 8;  M[2][1].val = 7;  M[2][2].val = 6;
}
//*********************************************

// Level 2: 4x4 Board (Medium)
void init_level_2(int *n, squ **M) {
    *n = 4; // Set size to 4x4
    M[0][0].val = 5;  M[0][1].val = 8;   M[0][2].val = 15;   M[0][3].val = 9;
    M[1][0].val = 1;   M[1][1].val = 11;  M[1][2].val = 14;   M[1][3].val = 6;
    M[2][0].val = 12;  M[2][1].val = 0;   M[2][2].val = 2;   M[2][3].val = 3;
    M[3][0].val = 4;   M[3][1].val = 10;  M[3][2].val = 7;   M[3][3].val = 13; 
}
//*********************************************

// Level 3: 5x5 Board (Hard)
void init_level_3(int *n, squ **M) {
    *n = 5; // Set size to 5x5
    M[0][0].val = 8;  M[0][1].val = 4;  M[0][2].val = 6;  M[0][3].val = 15;   M[0][4].val = 13;
    M[1][0].val = 24;   M[1][1].val = 0;  M[1][2].val = 16;   M[1][3].val = 9;  M[1][4].val = 10;
    M[2][0].val = 5;   M[2][1].val = 1;   M[2][2].val = 11;  M[2][3].val = 22;  M[2][4].val = 17;
    M[3][0].val = 2;   M[3][1].val = 24;   M[3][2].val = 3;  M[3][3].val = 18;  M[3][4].val = 12;
    M[4][0].val = 23;   M[4][1].val = 20;  M[4][2].val = 7;  M[4][3].val = 14;  M[4][4].val = 19;
}
//*********************************************

void aff_puzzle(int n, squ **M) {
    int i, j;
    printf("\nCurrent Board:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (M[i][j].val == 0)
                printf("  \t");  // Empty space
            else
                printf("%d\t", M[i][j].val);
        }
        printf("\n");
    }
}
//*********************************************

int valid(int n, squ **M, int x, int y, SDL_Event event) {
    if (x != 0 && M[x - 1][y].val == 0) return 1; // Up
    if (x != n - 1 && M[x + 1][y].val == 0) return 3; // Down
    if (y != 0 && M[x][y - 1].val == 0) return 4; // Left
    if (y != n - 1 && M[x][y + 1].val == 0) return 2; // Right
    return 0;
}
//*********************************************

void mov(int n, squ **M, int x, int y, int test) {
    int temp = M[x][y].val;
    switch (test) {
        case 1:  // Move Up
            M[x][y].val = M[x - 1][y].val;
            M[x - 1][y].val = temp;
            break;
        case 2:  // Move Right
            M[x][y].val = M[x][y + 1].val;
            M[x][y + 1].val = temp;
            break;
        case 3:  // Move Down
            M[x][y].val = M[x + 1][y].val;
            M[x + 1][y].val = temp;
            break;
        case 4:  // Move Left
            M[x][y].val = M[x][y - 1].val;
            M[x][y - 1].val = temp;
            break;
    }
}
//*********************************************

int winn(int n, squ **M) {
    int c = 1, i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == n - 1 && j == n - 1)
                return (M[i][j].val == 0);  // Last element should be 0
            if (M[i][j].val != c++)
                return 0;
        }
    }
    return 1;
}





int puzzle (screen ecr, int choice){
    text mes;
    mes.text = NULL;
    bg img;
    menu win;
    if (init_menu_puzzle(&win)) return 0;

    SDL_Event event;
    int quitter = -1, n, x, y, valid_move;
    

    squ **M;
    int grid_size = n * tile_size, start_x, start_y; 
    if (choice == 1) {
        n = 3;
	start_x = (SCREEN_WIDTH - tile_size) / 2 - 90;
	start_y = (SCREEN_HEIGHT - tile_size) / 2 - 80;
    } else if (choice == 2) {
        n = 4;
	start_x = (SCREEN_WIDTH - tile_size) / 2 - 155;
	start_y = (SCREEN_HEIGHT - tile_size) / 2 - 140;
    } else {
        n = 5;
	start_x = (SCREEN_WIDTH - tile_size) / 2 - 210;
	start_y = (SCREEN_HEIGHT - tile_size) / 2 - 200;
    }

    M = (squ **)malloc(n * sizeof(squ *));
    for (int i = 0; i < n; i++) {
        M[i] = (squ *)malloc(n * sizeof(squ));
    }

    if (choice == 1) init_level_1(&n, M);
    else if (choice == 2) init_level_2(&n, M);
    else init_level_3(&n, M);

/*
    if (init_bg_puzzle(&win)) {
        printf("Background Initialization Error\n");
        return 1;
    }
*/
    int choix = 0;


    while (quitter == -1) {
        screen_affichage_puzzle(win, ecr, M, n, grid_size, start_x, start_y);

        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quitter = 0;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) quitter = 0;
                break;
	    case SDL_MOUSEMOTION:
		change(&(win.img1),event);
		break;
            case SDL_MOUSEBUTTONDOWN:
		choix = click(&(win.img1), event, ecr.wav);
		printf("\nx:%d y:%d",event.button.y,event.button.x);
                x = ((event.button.y - start_y ) / tile_size);
                y = ((event.button.x - start_x ) / tile_size);

		if (x<n && x>=0 && y<n && y>=0){
			Mix_PlayChannel(-1,ecr.wav,0);
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
	if (choix) quitter = 5;
    }

    
    SDL_FreeSurface(win.bg.img);
    SDL_FreeSurface(win.img1.img);
    SDL_FreeSurface(win.img1.img1);
    //if(win.img1.img2 != NULL) SDL_FreeSurface(win.img1.img2);

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);

    return quitter;
}



