CC = g++
CFLAGS = -std=c++0x -Wall -g
LDFLAGS=-lncurses

default: game
#	chmod +x main.o

game: main.o object.o character.o block.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o game main.o object.o character.o block.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o main.o main.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o object.o object.cpp

character.o: character.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o character.o character.cpp

block.o: block.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o block.o block.cpp

clean:
	rm *.o
