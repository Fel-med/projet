#include "head.h"
#include <stdio.h>

int main() {

    screen scr;

    if (init_sdl()!=0) return 1;

    if (init_ecran(&scr)) return 1;

	puts("hh");

    menu_option(&scr);  //votre fonction

    quit(&scr);

    return 0;

}
