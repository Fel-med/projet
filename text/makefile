game: clean main.o source.o
	gcc main.o source.o -o game -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c
source.o:source.c
	gcc -c source.c
clean:
	rm -f main.o source.o game
