game:clean source.o main.o
	gcc main.o source.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
source.o:source.c
	gcc -c source.c -g
main.o:main.c
	gcc -c main.c -g
clean:
	rm -f main.o source.o game
