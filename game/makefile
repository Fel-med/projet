game: clean alaa.o felhi.o omar.o louay.o rania.o puzzle.o charrad.o main.o
	gcc felhi.o alaa.o rania.o omar.o puzzle.o charrad.o louay.o main.o -o game -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -L/usr/lib/mysql -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql

main.o: main.c head.h
	gcc -c main.c -g

omar.o: omar.c head.h
	gcc -c omar.c -g

charrad.o: charrad.c head.h
	gcc -c charrad.c -g

felhi.o: felhi.c head.h
	gcc -c felhi.c -g

louay.o: louay.c head.h
	gcc -c louay.c -g

rania.o: rania.c head.h
	gcc -c rania.c -g

puzzle.o: puzzle.c head.h
	gcc -c puzzle.c -g

alaa.o:alaa.c
	gcc -c alaa.c -g

clean:
	rm -f felhi.o alaa.o rania.o omar.o puzzle.o charrad.o louay.o main.o game
