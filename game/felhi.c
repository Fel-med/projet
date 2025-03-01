#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <mysql/mysql.h>
#include "head.h"



int init_sdl(){
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

if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	printf("\nERROR-2 :%s",SDL_GetError());
	return 1;
}
return 0;
}
//*********************************************

int init_ecran(screen *ecr){
printf("\n***Loading...");
fflush(stdout);

ecr->ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
if (ecr->ecran == NULL) {
	printf("\nERROR-3 :%s",SDL_GetError());
	return 1;
}

ecr->mus = Mix_LoadMUS("./res_generale/music.ogg");
if (ecr->mus == NULL) {
	printf("\nERROR-4 :%s",SDL_GetError());
	return 1;
}

ecr->police = TTF_OpenFont("./res_generale/font.ttf", 40);
if (!ecr->police) {
        printf("ERROR-5 : %s\n", TTF_GetError());
        return 1;
    }

ecr->wav = Mix_LoadWAV("./res_generale/sound.wav");
if (ecr->wav == NULL) {
	printf("\nERROR-6 :%s",SDL_GetError());
	return 1;
}

ecr->fullscr = 0;

Mix_PlayMusic(ecr->mus, -1);
return 0;
}
//*********************************************

int init_button(menu *win){
win->img1.img1 = IMG_Load(win->img1.nom_img1);
win->img1.img2 = IMG_Load(win->img1.nom_img2);
win->img2.img1 = IMG_Load(win->img2.nom_img1);
win->img2.img2 = IMG_Load(win->img2.nom_img2);
if (win->img1.img1 == NULL || win->img2.img1 == NULL || win->img1.img2 == NULL || win->img2.img2 == NULL) {
	printf("\nERROR-7 :%s",SDL_GetError());
	return 1;
}

win->img1.img = win->img1.img1;
win->img2.img = win->img2.img1;

return 0;
}//*********************************************

void change(image *img, SDL_Event event){
SDL_Rect e = img->pos;
if (event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h && img->etat == 1){
	img->etat = 2;
	img->img = img->img2;
}
else if(!(event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h) && img->etat == 2){
	img->img = img->img1;
	img->etat = 1;
}
img->click = 1;
}
//*********************************************

int click(image *img, SDL_Event event, Mix_Chunk *wav){
SDL_Rect e = img->pos;
if (event.motion.x >= e.x && event.motion.x <= e.x + e.w && event.motion.y >= e.y && event.motion.y <= e.y + e.h && event.type == SDL_MOUSEBUTTONDOWN && img->click == 1){ 
	Mix_PlayChannel(-1,wav,0);
	img->click = 2;
	SDL_PollEvent(&event);
	while (event.type != SDL_MOUSEBUTTONUP){
		SDL_PollEvent(&event);
		SDL_Delay(20);
	}
	return 1;
}
return 0;
}
//*********************************************

void screen_affichage(menu win, screen ecr){
SDL_BlitSurface((win.bg).img, NULL, ecr.ecran, &(win.bg.pos));

SDL_BlitSurface((win.img1).img, NULL, ecr.ecran, &(win.img1.pos));
SDL_BlitSurface((win.img2).img, NULL, ecr.ecran, &(win.img2.pos));

SDL_Flip(ecr.ecran);

}
//*********************************************

void quit_sdl(menu *win, screen *ecr){

if (win->bg.img)
SDL_FreeSurface(win->bg.img);

if (win->img1.img)
SDL_FreeSurface(win->img1.img);

if (win->img2.img)
SDL_FreeSurface(win->img2.img);

}
//*********************************************

int init_bg(menu *win){
printf("\n***Background...");
fflush(stdout);

SDL_Surface *img = SDL_LoadBMP(win->bg.nom_img);
win->bg.img = SDL_DisplayFormat(img);
SDL_FreeSurface(img);
if (win->bg.img == NULL) {
	printf("\nERROR-8 :%s",SDL_GetError());
	return 1;
}

return 0;
}
//*********************************************

void init_val_1(menu *win){
//bg
strcpy(win->bg.nom_img,"./res-felhi/bg1.bmp");
win->bg.pos.x=0;
win->bg.pos.y=0;
//oui (sauvgarder)
strcpy(win->img1.nom_img1,"./res-felhi/y-1.tga");
strcpy(win->img1.nom_img2,"./res-felhi/y-2.tga");

win->img1.pos.h=100;
win->img1.pos.w=100;

win->img1.pos.x = SCREEN_WIDTH / 2 - win->img1.pos.w - 70;
win->img1.pos.y = SCREEN_HEIGHT / 2 - win->img1.pos.h + 120;

win->img1.etat=1;
win->img1.click=1;
//non (sauvgarder)
strcpy(win->img2.nom_img1,"./res-felhi/x-1.tga");
strcpy(win->img2.nom_img2,"./res-felhi/x-2.tga");
win->img2.pos.h=100;
win->img2.pos.w=100;


win->img2.pos.x= SCREEN_WIDTH / 2 - win->img2.pos.w + 155;
win->img2.pos.y= SCREEN_HEIGHT / 2 - win->img2.pos.h + 120;

win->img2.etat=1;
win->img2.click=1;
}
//*********************************************
void init_val_2(menu *win){
//bg
strcpy(win->bg.nom_img,"./res-felhi/bg2.bmp");
win->bg.pos.x=0;
win->bg.pos.y=0;
//nouvelle partie
strcpy(win->img1.nom_img1,"./res-felhi/nou-1.tga");
strcpy(win->img1.nom_img2,"./res-felhi/nou-2.tga");


win->img1.pos.h=164;
win->img1.pos.w=440;

win->img1.pos.x= SCREEN_WIDTH / 2 - win->img1.pos.w + 220;
win->img1.pos.y= SCREEN_HEIGHT / 2 - win->img1.pos.h;


win->img1.etat=1;
win->img1.click=1;
//charger
strcpy(win->img2.nom_img1,"./res-felhi/char-1.tga");
strcpy(win->img2.nom_img2,"./res-felhi/char-2.tga");


win->img2.pos.h=164;
win->img2.pos.w=440;


win->img2.pos.x= SCREEN_WIDTH / 2 - win->img2.pos.w + 220;
win->img2.pos.y= SCREEN_HEIGHT / 2 - win->img1.pos.h + 200;


win->img2.etat=1;
win->img2.click=1;
}
//*********************************************

int start(menu win, screen ecr){

int quitter=1, t1, t2;

t1 = init_bg(&win);
if (t1) {
	printf("\nerror init_bg") ;
	return 0;
}

t2 = init_button(&win);
if (t2) {
	printf("\nerror init_button") ;
	return 0;
}

//Uint32 lastup = SDL_GetTicks();
SDL_Event event;

int choix_1 = 0, choix_2 = 0;

while (quitter){
//Uint32 currentup = SDL_GetTicks();
//if (currentup - lastup < 16 ) continue;
//lastup = currentup;

screen_affichage(win,ecr);

SDL_WaitEvent(&event);

switch (event.type){

case SDL_QUIT:
	quitter = 0;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) quitter=0; //quitter
	break;
case SDL_MOUSEMOTION:
	change(&(win.img1), event);
	change(&(win.img2), event);
	break;
case SDL_MOUSEBUTTONDOWN:
	choix_1 = click(&(win.img1), event, ecr.wav);
	choix_2 = click(&(win.img2), event, ecr.wav);
	break;
}
if (choix_1 || choix_2) break; //quitter
SDL_Delay(16);
}

return (choix_1 * 2) + (choix_2 * 0); // returned 1 if no , else returned 2 if yes

quit_sdl(&win,&ecr);
}
//*********************************************

void sau(char file_name[], donne e){
FILE *f = fopen(file_name, "ab");
if (f == NULL) {
	printf("\nERROR 9");
	return;
}
fwrite(&e, sizeof(donne), 1, f);
fclose(f);
printf("\nyour data(s) saved\n");
fflush(stdout);
}
//*********************************************

void aff(char file_name[]){
FILE *f = fopen(file_name, "rb");
donne e;
if (f == NULL) {
	printf("\nERROR 10");
	return;
}

printf("\nthe Players:");

fread(&e, sizeof(donne), 1, f);
while(!feof(f)){
	printf("\nname: %s, the score: %d, the level : %d", e.user_name, e.score, e.level);
	fread(&e, sizeof(donne), 1, f);
}
printf("\n");
fclose(f);
}
//*********************************************

void save(donne e){

MYSQL *con = mysql_init(NULL);
if (con == NULL){
	printf("\nERROR 11 (1)");
	return;
}

if(mysql_real_connect(con, "192.168.0.170", "fel-med", "2005_felhimohmed", "game", 0, NULL, 0) == NULL){
	printf("ERROR 12 (1)");
	return;
}


char que[100];
sprintf(que, "SELECT COUNT(*) FROM player WHERE name='%s'", e.user_name);
mysql_query(con, que);

MYSQL_RES *res = mysql_store_result(con);
MYSQL_ROW row = mysql_fetch_row(res);
int exist = atoi(row[0]);
mysql_free_result(res);

if(exist) sprintf(que, "UPDATE player SET level=%d, score=%d WHERE name='%s'",e.level, e.score, e.user_name);
else sprintf(que, "INSERT INTO player VALUE ('%s', %d, %d)", e.user_name, e.score, e.level);

mysql_query(con, que);
mysql_close(con);
}
//*********************************************

void search(donne *e, char name[]){

MYSQL *con = mysql_init(NULL);
if (con == NULL){
	printf("\nERROR 11 (2)");
	return;
}

if(mysql_real_connect(con, "192.168.0.170", "fel-med", "2005_felhimohmed", "game", 0, NULL, 0) == NULL){
	printf("ERROR 12 (2)");
	return;
}

char que[100];
sprintf(que, "SELECT level, score FROM player WHERE name='%s'", name);
mysql_query(con, que);

MYSQL_RES *res = mysql_store_result(con);
MYSQL_ROW row = mysql_fetch_row(res);
if (row) {
e->level = atoi(row[0]);
e->score = atoi(row[1]);
}
else{
e->level = 0;
e->score = 0;
}
strcpy(e->user_name, name);

mysql_free_result(res);
mysql_close(con);
}
//*********************************************

void down(char file_name[]){

MYSQL *con = mysql_init(NULL);
if (con == NULL){
	printf("\nERROR 11 (3)");
	return;
}

if(mysql_real_connect(con, "192.168.0.170", "fel-med", "2005_felhimohmed", "game", 0, NULL, 0) == NULL){
	printf("ERROR 12 (3)");
	return;
}

FILE *f = fopen(file_name, "wb");
if (!f) return;

mysql_query(con, "SELECT level, score, name FROM player");
MYSQL_RES *res = mysql_store_result(con);
MYSQL_ROW row;

donne e;
while(row = mysql_fetch_row(res)){
strcpy(e.user_name ,row[2]);
e.score = atoi(row[1]);
e.level = atoi(row[0]);
fwrite(&e, sizeof(donne), 1, f);

}

fclose(f);
mysql_free_result(res);
mysql_close(con);
}
//*********************************************************

int start2(menu win, screen ecr){

int quitter=1, t1, t2;

t1 = init_bg(&win);
if (t1) {
	printf("\nerror init_bg") ;
	return 0;
}

t2 = init_button(&win);
if (t2) {
	printf("\nerror init_button") ;
	return 0;
}

//Uint32 lastup = SDL_GetTicks();
SDL_Event event;

int choix_1 = 0, choix_2 = 0;

while (quitter == 1){
//Uint32 currentup = SDL_GetTicks();
//if (currentup - lastup < 16 ) continue;
//lastup = currentup;

screen_affichage(win,ecr);

SDL_WaitEvent(&event);

switch (event.type){

case SDL_QUIT:
	quitter = 0;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) quitter=0; //quitter
	else if (event.key.keysym.sym == SDLK_n){
			 quitter=2; //quitter
			 choix_1 = 1;
	}
	break;
case SDL_MOUSEMOTION:
	change(&(win.img1), event);
	change(&(win.img2), event);
	break;
case SDL_MOUSEBUTTONDOWN:
	choix_1 = click(&(win.img1), event, ecr.wav);
	choix_2 = click(&(win.img2), event, ecr.wav);
	break;
}
if (choix_1 || choix_2) break; //quitter
SDL_Delay(16);
}

return (choix_1 * 9) + (choix_2 * 0); // returned 1 if nouvelle partie , else returned 2 if charger

quit_sdl(&win,&ecr);
}
















