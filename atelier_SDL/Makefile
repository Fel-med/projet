prog:main.o source.o
	gcc main.o source.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
source.o:source.c
	gcc -c source.c -g
