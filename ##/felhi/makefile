game:clean source.o main.o
	gcc main.o felhi.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -L/usr/lib/mysql -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql
felhi.o:felhi.c
	gcc -c felhi.c -g
main.o:main.c
	gcc -c main.c -g
clean:
	rm -f main.o source.o game
