#include "head.h"

void initImage1(image2 *pic, char path[], int x, int y){
	pic -> img = IMG_Load(path);
	if (pic -> img== NULL){
		printf("Can't Load Image From Path %s \n", path);
		return;
	}
	pic -> pos1.x = x;
	pic -> pos1.y = y;
	pic -> pos1.w = pic -> img -> w;
	pic -> pos1.h = pic -> img -> h;
	pic -> pos2.x = SCREEN_WIDTH;
	pic -> pos2.y = SCREEN_HEIGHT;
	pic -> pos2.w = pic -> img -> w;
	pic -> pos2.h = pic -> img -> h;
	pic -> hidden = 0;
	pic -> hover = 0;
}

void initImage(image2 *pic, char path1[], char path2[], int x, int y, int hidden){
	pic -> img = IMG_Load(path1);
	if (pic -> img== NULL){
		printf("Can't Load Image From Path %s \n", path1);
		return;
	}
	pic -> img2 = IMG_Load(path2);
	if (pic -> img2== NULL){
		printf("Can't Load Image 2 From Path %s \n", path2);
		return;
	}
	pic -> pos1.x = x;
	pic -> pos1.y = y;
	pic -> pos1.w = pic -> img -> w;
	pic -> pos1.h = pic -> img -> h;
	pic -> pos2.x = SCREEN_WIDTH;
	pic -> pos2.y = SCREEN_HEIGHT;
	pic -> pos2.w = pic -> img -> w;
	pic -> pos2.h = pic -> img -> h;
	pic -> hidden = hidden;
	pic -> hover = 0;
}


void afficher_omar(image2 p, SDL_Surface **screen){
	if (p.img == NULL) return;
	if (p.hidden){
		SDL_BlitSurface(p.img,NULL,*screen,&p.pos2);
	}
	else if (p.hover){
		SDL_BlitSurface(p.img2,NULL,*screen,&p.pos1);
	}
	else{
		SDL_BlitSurface(p.img,NULL,*screen,&p.pos1);
	}
}


void afficher_omar_uni(image2 p, SDL_Surface **screen, int etat, int id, int mode, int clickk, int id2){
	if (p.img == NULL) return;
	if (p.hidden){
		SDL_BlitSurface(p.img,NULL,*screen,&p.pos2);
	}
	else if (p.hover) {
		SDL_BlitSurface(p.img2,NULL,*screen,&p.pos1);
	}
	else if ( ( (id==1 && etat==1) || (id==2 && etat==2) ) && mode == 1) {
		printf("\n1111");
		SDL_BlitSurface(p.img2,NULL,*screen,&p.pos1);
	}
	else if ( clickk == 1 && id2 == 1 && mode == 2) {
		printf("\n2222222");
		SDL_BlitSurface(p.img2,NULL,*screen,&p.pos1);
	}
	else{
		SDL_BlitSurface(p.img,NULL,*screen,&p.pos1);
	}
}

void liberer (image2 picture){
	SDL_FreeSurface(picture.img);
}


int joueur_menu(screen scr, donne *d){

SDL_Event event;
	
//Init Variables
int mouseOnMonoPlayerButton = 0, mouseOnMultiPlayerButton = 0, mouseOnReturnButton = 0, mouseOnAvatar1Button = 0, mouseOnAvatar2Button = 0, mouseOnInput1Button = 0, mouseOnInput2Button = 0, mouseOnValidateButton = 0, playerModeSelectionWindow = 1, avatarSelectionWindow = 0, mainWindow = 0, bestScoreWindow = 0;

//Init Image Variables
image2 background ,monoPlayerButton , multiPlayerButton, returnButton, avatar1Button, avatar2Button, input1Button, input2Button, validateButton;
	
//Link Exit Event To SDL_Quit Function
atexit(SDL_Quit);
fflush(stdout);
	
//Init All Images (Var, Path, X, Y, Hidden)
initImage1(&background, "./res-omar/background.jpg", 0, 0);
initImage(&monoPlayerButton, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 300, 175, 0);
initImage(&multiPlayerButton, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 700, 175, 0);
initImage(&returnButton, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 850, 350, 0);
initImage(&input1Button, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 300, 175, 1);
initImage(&input2Button, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 700, 175, 1);
initImage(&avatar1Button, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 300, 100, 1);
initImage(&avatar2Button, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 700, 100, 1);
initImage(&input1Button, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 300, 175, 1);
initImage(&validateButton, "./res-omar/bouton.jpg", "./res-omar/bouton-2.jpg", 500, 250, 1);


int choix = -1;
int mode = 0, avatar = 0, input = 0, click1 = 0, click2 = 0;
//Game Loop
while(choix == -1)
{		
	//Refresh Images
	afficher_omar(background,&(scr.ecran));
	afficher_omar(monoPlayerButton,&scr.ecran);
	afficher_omar(multiPlayerButton,&scr.ecran);
	afficher_omar(returnButton,&scr.ecran);
	afficher_omar_uni(avatar1Button,&scr.ecran,avatar,1,mode,click1,1);
	afficher_omar_uni(avatar2Button,&scr.ecran,avatar,2,mode,click2,1);
	afficher_omar_uni(input1Button,&scr.ecran,input,1,mode,click1,2);
	afficher_omar_uni(input2Button,&scr.ecran,input,2,mode,click2,2);
	afficher_omar(validateButton,&scr.ecran);

	//Refresh Screen
	SDL_Flip(scr.ecran);
		
	//Poll Event To not stop the Animation While Waiting for an Event
	if(SDL_PollEvent(&event)){		
	switch(event.type){
	case SDL_QUIT:
		choix = 0;
		break;
				
	case SDL_MOUSEMOTION:
 		//Print Mouse Position (To Know Coordinates)

		if (playerModeSelectionWindow){
			//Mouse ON Which Button
			mouseOnMonoPlayerButton = 0;
			mouseOnMultiPlayerButton = 0;
			mouseOnReturnButton = 0;

		if(event.button.x >= 300 && event.button.x <= 450 && event.button.y >=175 && event.button.y <=235){
			//printf("Mouse On Mono Player Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
						
			//Mouse ON Which Button
			mouseOnMonoPlayerButton = 1;
			mouseOnMultiPlayerButton = 0;
			mouseOnReturnButton = 0;

		}
		else if(event.button.x >= 700 && event.button.x <= 850 && event.button.y >=175 && event.button.y <=235){
			//printf("Mouse On Multi Player Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
					
			//Mouse ON Which Button
			mouseOnMonoPlayerButton = 0;
			mouseOnMultiPlayerButton = 1;
			mouseOnReturnButton = 0;
		}
		else if(event.button.x >= 850 && event.button.x <= 1000 && event.button.y >=350 && event.button.y <=410){
			//printf("Mouse On Return Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
					
			//Mouse ON Which Button
			mouseOnMonoPlayerButton = 0;
			mouseOnMultiPlayerButton = 0;
			mouseOnReturnButton = 1;
		}
	}
	else if (avatarSelectionWindow){
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 0;

		if(event.button.x >= 300 && event.button.x <= 450 && event.button.y >=175 && event.button.y <=235){
			//printf("Mouse On Input 1 Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 1;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 0;
			}
		else if(event.button.x >= 700 && event.button.x <= 850 && event.button.y >=175 && event.button.y <=235){
			//printf("Mouse On Input 2 Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 1;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 0;
						}

		else if(event.button.x >= 300 && event.button.x <= 450 && event.button.y >=100 && event.button.y <=160){
			//printf("Mouse On Avatar 1 Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 1;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 0;
		}
		else if(event.button.x >= 700 && event.button.x <= 850 && event.button.y >=100 && event.button.y <=160){
			//printf("Mouse On Avatar 2 Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 1;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 0;
		}
		else if(event.button.x >= 500 && event.button.x <= 650 && event.button.y >=250 && event.button.y <=310){
			//printf("Mouse On Validation Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 1;
			mouseOnReturnButton = 0;
		}
		else if(event.button.x >= 850 && event.button.x <= 1000 && event.button.y >=350 && event.button.y <=410){
			//printf("Mouse On Return Button\n");
			//Mix_PlayChannel(1,scr.wav,0);
							
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			mouseOnReturnButton = 1;
		}
	}

	monoPlayerButton.hover = mouseOnMonoPlayerButton;
	multiPlayerButton.hover = mouseOnMultiPlayerButton;
	returnButton.hover = mouseOnReturnButton;
	avatar1Button.hover = mouseOnAvatar1Button;
	avatar2Button.hover = mouseOnAvatar2Button;
	input1Button.hover = mouseOnInput1Button;
	input2Button.hover = mouseOnInput2Button;
	validateButton.hover = mouseOnValidateButton;

	break;

	case SDL_MOUSEBUTTONUP:
				
	//Select Player Button
	if((mouseOnMonoPlayerButton || mouseOnMultiPlayerButton) && playerModeSelectionWindow){				
			printf("Open Player Menu\n");
			if(mouseOnMonoPlayerButton) mode = 1;
			else if(mouseOnMultiPlayerButton) mode = 2;
			Mix_PlayChannel(1,scr.wav,0);
			//Mouse ON Which Button
			mouseOnMonoPlayerButton = 0;
			mouseOnMultiPlayerButton = 0;
			mouseOnReturnButton = 0;
									
			//Hide and Show Bottons
			monoPlayerButton.hidden = 1;
			multiPlayerButton.hidden = 1;
			input1Button.hidden = 0;
			input2Button.hidden = 0;
			avatar1Button.hidden = 0;
			avatar2Button.hidden = 0;
			input1Button.hidden = 0;
			validateButton.hidden = 0;

			//Select Window
			playerModeSelectionWindow = 0;
			avatarSelectionWindow = 1;
			bestScoreWindow = 0;
			mainWindow = 0 ;

		}
		else if (mouseOnReturnButton && avatarSelectionWindow){
			//Mouse ON Which Button
			mode = 0;
			avatar = 0;
			input = 0;
			Mix_PlayChannel(1,scr.wav,0);
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			avatarSelectionWindow = 0;

			//Select Window
			playerModeSelectionWindow = 1;
			avatarSelectionWindow = 0;
			bestScoreWindow = 0;
			mainWindow = 0 ;


			//Hide and Show Bottons
			monoPlayerButton.hidden = 0;
			multiPlayerButton.hidden = 0;
			input1Button.hidden = 1;
			input2Button.hidden = 1;
			avatar1Button.hidden = 1;
			avatar2Button.hidden = 1;
			input1Button.hidden = 1;
			validateButton.hidden = 1;
		}
/////////////////////////////////////////////
		else if (mouseOnAvatar1Button && avatarSelectionWindow){
			//Mouse ON Which Button
			printf("\navatar 1");
			Mix_PlayChannel(1,scr.wav,0);
			click1 = !click1;
			if (click1 || mode == 1) avatar = 1;
			else avatar = 0;
		}
		else if (mouseOnAvatar2Button && avatarSelectionWindow){
			//Mouse ON Which Button
			printf("\navatar 2");
			Mix_PlayChannel(1,scr.wav,0);
			click2 = !click2;
			if (click2 || mode == 1) avatar = 2;
			else avatar = 0;
		}

		else if (mouseOnInput1Button && avatarSelectionWindow){
			//Mouse ON Which Button
			printf("\ninput 1");
			Mix_PlayChannel(1,scr.wav,0);
			input = 1;
		}
		else if (mouseOnInput2Button && avatarSelectionWindow){
			//Mouse ON Which Button
			printf("\ninput 2");
			Mix_PlayChannel(1,scr.wav,0);
			input = 2;
		}
		else if (mouseOnReturnButton && playerModeSelectionWindow){
			//Mouse ON Which Button
			Mix_PlayChannel(1,scr.wav,0);
			mouseOnMonoPlayerButton = 0;
			mouseOnMultiPlayerButton = 0;
			mouseOnReturnButton = 0;

			//Select Window
			playerModeSelectionWindow = 0;
			avatarSelectionWindow = 0;
			bestScoreWindow = 0;
			mainWindow = 1 ;


			//Hide and Show Bottons
			monoPlayerButton.hidden = 1;
			multiPlayerButton.hidden = 1;
			input1Button.hidden = 1;
			input2Button.hidden = 1;
			avatar1Button.hidden = 1;
			avatar2Button.hidden = 1;
			input1Button.hidden = 1;
			validateButton.hidden = 1;
			returnButton.hidden = 1;


			//Show Main Window (To be integrated)
			choix = 7;
		}
		else if (mouseOnValidateButton && avatarSelectionWindow && avatar != 0 && input != 0){
			//Mouse ON Which Button
			Mix_PlayChannel(1,scr.wav,0);
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			avatarSelectionWindow = 0;

			//Select Window
			playerModeSelectionWindow = 0;
			avatarSelectionWindow = 0;
			bestScoreWindow = 1;
			mainWindow = 0 ;


			//Hide and Show Bottons
			monoPlayerButton.hidden = 1;
			multiPlayerButton.hidden = 1;
			input1Button.hidden = 1;
			input2Button.hidden = 1;
			avatar1Button.hidden = 1;
			avatar2Button.hidden = 1;
			input1Button.hidden = 1;
			validateButton.hidden = 1;
			returnButton.hidden = 1;

			//Show Best Score (To be Integrated)
			choix = 4;
		}

		SDL_PollEvent(&event);
		while (event.type != SDL_MOUSEBUTTONUP){
			SDL_PollEvent(&event);
			SDL_Delay(16);
		}
					
		break;
					
	case SDL_KEYDOWN:
		 //Go To Best Score Window (ENTER KEY)
		 if(event.key.keysym.sym == SDLK_RETURN && avatarSelectionWindow && avatar != 0 && input != 0)
		 			{		
		 					
			printf("ENTER Button, Best Score Menu\n");
						
			//Mouse ON Which Button
			mouseOnInput1Button = 0;
			mouseOnInput2Button = 0;
			mouseOnAvatar1Button = 0;
			mouseOnAvatar2Button = 0;
			mouseOnValidateButton = 0;
			avatarSelectionWindow = 0;

			//Select Window
			playerModeSelectionWindow = 0;
			avatarSelectionWindow = 0;
			bestScoreWindow = 1;
			mainWindow = 0 ;


			//Hide and Show Bottons
			monoPlayerButton.hidden = 1;
			multiPlayerButton.hidden = 1;
			input1Button.hidden = 1;
			input2Button.hidden = 1;
			avatar1Button.hidden = 1;
			avatar2Button.hidden = 1;
			input1Button.hidden = 1;
			validateButton.hidden = 1;
			returnButton.hidden = 1;

			//Show Best Score (To be Integrated)
			choix = 4;		
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE){
			choix = 0;
		}
		break;	
					
	default: 
		break;		
	}
}	

}

printf("\nthe mode : %d, the avatar : %d, the input : %d\n",mode,avatar,input);
d->input = input;
d->avatar = avatar;
						
	//Free other ressources	
	liberer(background);
	liberer(monoPlayerButton);
	liberer(multiPlayerButton);
	liberer(input1Button);
	liberer(input2Button);
	liberer(avatar1Button);
	liberer(avatar2Button);
	liberer(validateButton);
	liberer(returnButton);
	if (mode == 2 && choix != 0) return 1;
	else if(mode == 1 && choix != 0) return 4;
	else return choix;
}
