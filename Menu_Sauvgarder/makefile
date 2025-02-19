game:clean source.o main.o
	gcc main.o source.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -L/usr/lib/mysql -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql
source.o:source.c
	gcc -c source.c -g
main.o:main.c
	gcc -c main.c -g
clean:
	rm -f main.o source.o game
