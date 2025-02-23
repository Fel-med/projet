game: felhi.o louay.o main.o
	gcc main.o felhi.o louay.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -L/usr/lib/mysql -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql

main.o: main.c head.h
	gcc -c main.c -g

felhi.o: felhi.c head.h
	gcc -c felhi.c -g

louay.o: louay.c head.h
	gcc -c louay.c -g

clean:
	rm -f main.o felhi.o louay.o game
