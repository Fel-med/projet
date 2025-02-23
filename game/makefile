game:clean louay.o main.o
	gcc main.o louay.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -L/usr/lib/mysql -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql
louay.o:louay.c
	gcc -c louay.c -g
main.o:main.c
	gcc -c main.c -g
clean:
	rm -f main.o louay.o game
