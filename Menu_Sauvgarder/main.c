#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "head.h"

int main()
{

menu win1, win2;
char file_name[] = "file.bin";
int choix;

donne e;
printf("give me your data to save it (score and name) :\n-->");
scanf("%d %s",&(e.score), e.user_name);


// first window
init_val_1(&win1);
choix = start(win1);
if (choix == 2) sau(file_name,e);

// second window
init_val_2(&win2);
start(win2);

//afficher
aff(file_name);

puts("\nAdios mi amigo/a\n");

return 0;
}
