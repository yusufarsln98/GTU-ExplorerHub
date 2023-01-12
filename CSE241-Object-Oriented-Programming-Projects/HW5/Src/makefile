CC = g++ -std=c++11
CFLAGS = -Wall -g

main: main.o boardgame2d.o pegsolitaire.o eightpuzzle.o klotski.o
	$(CC) $(CFLAGS) -o main main.o boardgame2d.o pegsolitaire.o eightpuzzle.o klotski.o

main.o: main.cpp boardgame2d.h pegsolitaire.h eightpuzzle.h klotski.h
	$(CC) $(CFLAGS) -c main.cpp

boardgame2d.o: boardgame2d.h

pegsolitaire.o: pegsolitaire.h

eightpuzzle.o: eightpuzzle.h

klotski.o: klotski.h
