#include "image.h"
#include <SDL/SDL_mixer.h>

int main(){

	screen scr;
	//Needed Intialization
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	scr.ecran=SDL_SetVideoMode(1083,500,32,SDL_HWSURFACE|SDL_SRCALPHA|SDL_DOUBLEBUF);
//Show Screen Errors
	if (!scr.ecran)
	{
		printf("unable to set 1083x500 video:%s\n",SDL_GetError());
		return 1;
	}
		
	//Show Audio Errors
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",Mix_GetError());
	}

	//Load Sound and Init Volume	
	scr.wav=Mix_LoadWAV("sound.wav");
	scr.mus =Mix_LoadMUS("./res_generale/music.ogg");
	Mix_PlayMusic(scr.mus,-1);

	joueur(scr);


				
	Mix_FreeMusic(scr.mus);
	Mix_FreeChunk(scr.wav);
	Mix_CloseAudio();
	SDL_Quit();
	TTF_Quit();
return 0;
}
