CC = g++
CFLAGS = -std=c++0x -Wall -g -pedantic
LDFLAGS=-lncurses

default: game
#	chmod +x main.o

game: output/main.o output/object.o output/character.o output/block.o output/gravityObject.o output/weapon.o output/ai.o output/aiCharacter.o output/aStar.o output/level.o
	$(CC) $(CFLAGS) -o game output/main.o output/object.o output/character.o output/block.o output/gravityObject.o output/weapon.o output/ai.o output/aiCharacter.o output/aStar.o output/level.o $(LDFLAGS)

output/main.o: main.cpp
	$(CC) $(CFLAGS) -c -o output/main.o main.cpp 

output/object.o: object.cpp
	$(CC) $(CFLAGS) -c -o output/object.o object.cpp

output/character.o: character.cpp
	$(CC) $(CFLAGS) -c -o output/character.o character.cpp

output/block.o: block.cpp
	$(CC) $(CFLAGS) -c -o output/block.o block.cpp

output/gravityObject.o: gravityObject.cpp
	$(CC) $(CFLAGS) -c -o output/gravityObject.o gravityObject.cpp

output/weapon.o: weapon.cpp
	$(CC) $(CFLAGS) -c -o output/weapon.o weapon.cpp

output/ai.o: ./ai/ai.cpp
	$(CC) $(CFLAGS) -c -o output/ai.o ./ai/ai.cpp

output/aiCharacter.o: aiCharacter.cpp
	$(CC) $(CFLAGS) -c -o output/aiCharacter.o aiCharacter.cpp

output/aStar.o: ./ai/aStar.cpp
	$(CC) $(CFLAGS) -c -o output/aStar.o ./ai/aStar.cpp

output/level.o: level.cpp
	$(CC) $(CFLAGS) -c -o output/level.o level.cpp

clean:
	rm output/*.o
