#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_audio.h>

int main(){

SDL_Surface *ecran=NULL;
SDL_Surface *image=NULL;
SDL_Surface *text=NULL;
int quitter=1;
SDL_Rect posimg, postxt;
TTF_Font *police = NULL;
SDL_Color noire={0,0,0};
//Mix_Music *musique = NULL;
SDL_Event event;

const char msg[] = "we will never forget\nwe will never stop sharing";

if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {printf("ERROR-1");return 1;}

if (TTF_Init() < 0) {printf("ERROR-2");return 1;}

//if (SDL_OpenAudio( 44100 , _DEFAULT_SOURCE , 2 , 1024 ) < 0) {printf("ERROR-3");return 1;}

ecran = SDL_SetVideoMode(600,430,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
if (ecran == NULL) {printf("ERROR-4");return 1;}

image = IMG_Load("palestine.jpg");
if (image == NULL) {printf("ERROR-5");return 1;}

posimg.x = 50;
posimg.y = 50;

police = TTF_OpenFont("arial.ttf",24);
if (police == NULL) {printf("ERROR-6");return 1;}

postxt.x = 50;
postxt.y = 300;

/*musique = Mix_LoadMUS("music.mp3");
if (musique == NULL) {printf("ERROR-7");return 1;}

Mix_PlayMusic(musique, -1);*/


while (quitter){

SDL_BlitSurface(image,NULL,ecran,&posimg);
SDL_BlitSurface(text,NULL,ecran,&postxt);
SDL_Flip(ecran);
SDL_PollEvent(&event);

switch (event.type){

case SDL_QUIT:
	quitter = 0;
	break;
case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) quitter=0;
	break;
case SDL_MOUSEBUTTONDOWN:
	printf("clic de souris : x=%d, y=%d\n", event.button.x, event.button.y);
	break;

}
}










//SDL_FreeMusic(musique);
TTF_CloseFont(police);
SDL_FreeSurface(image);
SDL_FreeSurface(text);

//SDL_CloseAudio();
TTF_Quit();
SDL_Quit();

return 0;
}
