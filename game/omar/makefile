game: clean main.o image.o
	gcc main.o image.o -o game -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c
	gcc -c main.c
image.o:image.c
	gcc -c image.c
clean:
	rm -f main.o image.o game
