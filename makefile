CC = g++
CFLAGS = -std=c++0x -Wall -g -pedantic
LDFLAGS=-lncurses

default: game
#	chmod +x main.o

game: main.o object.o character.o block.o gravityObject.o weapon.o ai.o aiCharacter.o path.o
	$(CC) $(CFLAGS) -o game main.o object.o character.o block.o gravityObject.o weapon.o ai.o aiCharacter.o path.o $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c -o main.o main.cpp 

object.o: object.cpp
	$(CC) $(CFLAGS) -c -o object.o object.cpp

character.o: character.cpp
	$(CC) $(CFLAGS) -c -o character.o character.cpp

block.o: block.cpp
	$(CC) $(CFLAGS) -c -o block.o block.cpp

gravityObject.o: gravityObject.cpp
	$(CC) $(CFLAGS) -c -o gravityObject.o gravityObject.cpp

weapon.o: weapon.cpp
	$(CC) $(CFLAGS) -c -o weapon.o weapon.cpp

ai.o: ./ai/ai.cpp
	$(CC) $(CFLAGS) -c -o ai.o ./ai/ai.cpp

aiCharacter.o: aiCharacter.cpp
	$(CC) $(CFLAGS) -c -o aiCharacter.o aiCharacter.cpp

path.o: path.cpp
	$(CC) $(CFLAGS) -c -o path.o path.cpp

clean:
	rm *.o
