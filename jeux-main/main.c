
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


// first window
init_val_1(&win1);


// second window
init_val_2(&win2);

start(win1);



puts("\n GOOD BYE o/a\n");

return 0;

}
