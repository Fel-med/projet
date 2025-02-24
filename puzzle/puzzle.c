#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int init(){
printf("\n***Initialiation...");
fflush(stdout);

if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {
	printf("\nERROR-0 :%s",SDL_GetError());
	return 1;
}

if (TTF_Init() < 0) {
	printf("\nERROR-1 :%s",SDL_GetError());
	return 1;
}

if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
	printf("\nERROR-2 :%s",SDL_GetError());
	return 1;
}
return 0;
}
//*********************************************

int init_ecran(screen *ecr){
printf("\n***Screen...");
fflush(stdout);

ecr->ecran = SDL_SetVideoMode(width_scr,hight_scr,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
if (ecr->ecran == NULL) {
	printf("\nERROR-3 :%s",SDL_GetError());
	return 1;
}

strcpy(ecr->nom_mus,"mus.ogg");

ecr->mus = Mix_LoadMUS(ecr->nom_mus);
if (ecr->mus == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}
Mix_PlayMusic(ecr->mus, -1);

ecr->police = TTF_OpenFont("arial.ttf", 24);
    if (ecr->police == NULL) return 1;

ecr->col.r = 34;
ecr->col.g = 139;
ecr->col.b = 34;

ecr->wav = Mix_LoadWAV("sound.wav");

return 0;
}
//*********************************************

int init_bg(menu *win){
printf("\n***Background...");
fflush(stdout);

strcpy(win->bg.nom_img,"bg.bmp");
win->bg.img = SDL_LoadBMP(win->bg.nom_img);
win->bg.img = SDL_DisplayFormat(win->bg.img);
if (win->bg.img == NULL) {
	printf("\nERROR-5 :%s",SDL_GetError());
	return 1;
}


return 0;
}
//*********************************************

void screen_affichage(menu win, screen ecr, squ **M, int n, int grid_size, int start_x, int start_y){


    SDL_FillRect(ecr.ecran, NULL, SDL_MapRGB(ecr.ecran->format, 0, 0, 0));
    SDL_BlitSurface(win.bg.img, NULL, ecr.ecran, &win.bg.pos);

    SDL_Rect tile_pos;  
    SDL_Surface *text_surf;  
    SDL_Color textColor = {255, 255, 255}; 


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

void quit(menu *win, screen *ecr){
Mix_FreeMusic(ecr->mus);
SDL_FreeSurface(win->bg.img);

//SDL_FreeSurface(win->img1.img);
//SDL_FreeSurface(win->img2.img);

TTF_CloseFont(ecr->police);

SDL_CloseAudio();
//Mix_FreeChunk(win->img1.wav);
//Mix_FreeChunk(win->img2.wav);
//TTF_Quit();
SDL_Quit();
}
//*********************************************

//int start(menu win, screen *ecr){}
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

void aff(int n, squ **M) {
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



