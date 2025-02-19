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
screen ecr;

char file_name[] = "file.bin";
int choix;

donne e;
printf("give me your data to save it (name, score and level) :\n-->");
fflush(stdout);
scanf("%s %d %d", e.user_name, &(e.score), &(e.level));


// first window
init_val_1(&win1);
choix = start(win1,&ecr);
if (choix == 2) save(e);

// second window
init_val_2(&win2);
choix = start(win2,&ecr);
if (choix == 1){
search(&e, e.user_name);
printf("\n\nyour Data:\nname: %s, the score: %d, the level : %d\n", e.user_name, e.score, e.level);
}

//afficher
down(file_name);
aff(file_name);

puts("\nAdios mi amigo/a\n");


return 0;
}
